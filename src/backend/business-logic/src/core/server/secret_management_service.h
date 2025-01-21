#pragma once

#include <grpcpp/grpcpp.h>
#include <secret_management.grpc.pb.h>

namespace sv {

class SecretManagementService final : public secretmanagement::SecretService::Service {
 public:
  grpc::Status WriteSecret(grpc::ServerContext* context,
                           const secretmanagement::WriteSecretRequest* request,
                           secretmanagement::WriteSecretResponse* response);

  grpc::Status ReadSecret(grpc::ServerContext* context,
                          const secretmanagement::ReadSecretRequest* request,
                          secretmanagement::ReadSecretResponse* response);
};

}  // namespace sv
