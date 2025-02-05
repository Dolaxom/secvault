#include "secret_management_service.h"

#include <common/crypto.h>
#include <core/token.h>

namespace sv::server {

using namespace grpc;

namespace rules {

struct Database {
  i32 poolSize;
  postgres::ConnectionRules connRules;
};

}  // namespace rules

SecretManagementService::SecretManagementService() {
  // only for testing
  // TODO remove it
  postgres::ConnectionRules tempConnRules{
      .host = "localhost",
      .port = "5432",
      .dbname = "sv_test",
      .dbuser = "postgres",
      .dbpass = "test_pass"};

  rules::Database dbSetupRules;
  dbSetupRules.poolSize = 8;
  dbSetupRules.connRules = tempConnRules;

  pgPool_ = std::make_shared<postgres::Pool>();
  pgPool_->Build(dbSetupRules.poolSize, dbSetupRules.connRules);
}

Status SecretManagementService::WriteSecret(ServerContext* context, const secretmanagement::WriteSecretRequest* request, secretmanagement::WriteSecretResponse* response) {
  auto token = core::Token::CreateRandom().Dump();
  auto secretBinary = sv::Crypto::Encrypt(request->secret(), request->password());
  std::string secretEncrypted = sv::Crypto::EncodeBase64(secretBinary);

  auto dbConnection = pgPool_->GetConnection();
  if (InsertSecretDb(dbConnection, token, secretEncrypted) != Result::kOk) {
    pgPool_->FreeConnection(dbConnection);
    return Status{StatusCode::UNAVAILABLE, "Server error"};
  }
  pgPool_->FreeConnection(dbConnection);

  response->set_first_token(token);
  response->set_second_token(request->password());

  return Status{};
}

Status SecretManagementService::ReadSecret(ServerContext* context, const secretmanagement::ReadSecretRequest* request, secretmanagement::ReadSecretResponse* response) {
  std::string encryptedTextFromDB;
  auto dbConnection = pgPool_->GetConnection();
  if (ReadSecretFromDb(dbConnection, request->first_token(), encryptedTextFromDB) != Result::kOk) {
    pgPool_->FreeConnection(dbConnection);
    return Status{StatusCode::UNAVAILABLE, "Server error"};
  }
  pgPool_->FreeConnection(dbConnection);

  try {
    std::string encryptedBinary = sv::Crypto::DecodeBase64(encryptedTextFromDB);
    auto secret = sv::Crypto::Decrypt(encryptedBinary, request->second_token());

    response->set_secret(secret);
  } catch (const std::exception& e) {
    return Status{StatusCode::UNAVAILABLE, e.what()};
  }

  return {};
}

sv::Result SecretManagementService::InsertSecretDb(std::shared_ptr<postgres::Connection>& connection, const std::string& token, const std::string& secret) {
  const char* query = "INSERT INTO secrets (id, message) VALUES ($1, $2);";
  const char* values[] = {token.c_str(), secret.c_str()};
  PGresult* pgresult = PQexecParams(connection->GetRaw().get(), query, 2, nullptr, values, nullptr, nullptr, 0);
  if (auto res = PQresultStatus(pgresult); res != PGRES_COMMAND_OK) {
    std::cerr << "[INFO] InsertSecretDb() db error, res = " << res << std::endl;
    return Result::kDbError;
  }

  PQclear(pgresult);

  return Result::kOk;
}

sv::Result SecretManagementService::ReadSecretFromDb(std::shared_ptr<postgres::Connection>& connection, const std::string& token, std::string& result) {
  const char* query = "SELECT message FROM secrets WHERE id = $1;";
  const char* values[] = {token.c_str()};
  PGresult* pgresult = PQexecParams(connection->GetRaw().get(), query, 1, nullptr, values, nullptr, nullptr, 0);

  if (PQresultStatus(pgresult) != PGRES_TUPLES_OK) {
    PQclear(pgresult);
    return Result::kDbError;
  }

  int rowCount = PQntuples(pgresult);
  if (rowCount > 0) {
    result = PQgetvalue(pgresult, 0, 0);
  } else {
    PQclear(pgresult);
    return Result::kFalse;
  }

  PQclear(pgresult);
  return Result::kOk;
}

}  // namespace sv::server
