#include "secret_management_service.h"

#include <core/token.h>

namespace sv::server {

using namespace grpc;

Status SecretManagementService::WriteSecret(ServerContext* context, const secretmanagement::WriteSecretRequest* request, secretmanagement::WriteSecretResponse* response) {
  auto password = request->password();

  core::Token token;
  token.Generate();

  // Запись в бд

  response->set_first_token(token.Dump());
  response->set_second_token(password);

  return {};
}

Status SecretManagementService::ReadSecret(ServerContext* context, const secretmanagement::ReadSecretRequest* request, secretmanagement::ReadSecretResponse* response) {
  response->set_secret("Not implemented.");

  return {};
}

}  // namespace sv::server
