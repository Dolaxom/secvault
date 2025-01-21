#include "secret_management_service.h"

namespace sv {

using namespace grpc;

Status SecretManagementService::WriteSecret(ServerContext* context, const secretmanagement::WriteSecretRequest* request, secretmanagement::WriteSecretResponse* response) {
  auto password = request->password();

  response->set_first_token("Not implemented.");
  response->set_second_token(password);

  return {};
}

Status SecretManagementService::ReadSecret(ServerContext* context, const secretmanagement::ReadSecretRequest* request, secretmanagement::ReadSecretResponse* response) {
  response->set_secret("Not implemented.");

  return {};
}

}  // namespace sv
