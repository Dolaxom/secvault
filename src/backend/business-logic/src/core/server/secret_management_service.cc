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
  auto secretEncrypted = sv::Crypto::Encrypt(request->secret(), request->password());

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
  response->set_secret("Not implemented.");

  return {};
}

sv::Result SecretManagementService::InsertSecretDb(std::shared_ptr<postgres::Connection>& connection, const std::string& token, const std::string& secret) {
  const char* query = "INSERT INTO secrets (id, message) VALUES ($1, $2);";
  const char* values[] = {token.c_str(), secret.c_str()};
  PGresult* result = PQexecParams(connection->GetRaw().get(), query, 2, nullptr, values, nullptr, nullptr, 0);
  if (PQresultStatus(result) != PGRES_COMMAND_OK) {
    return Result::kDbError;
  }

  PQclear(result);

  return Result::kOk;
}

}  // namespace sv::server
