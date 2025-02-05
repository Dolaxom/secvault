#pragma once

#include <common/types.h>
#include <database/pg_pool.h>
#include <grpcpp/grpcpp.h>
#include <secret_management.grpc.pb.h>

namespace sv::server {

class SecretManagementService final : public secretmanagement::SecretService::Service {
 public:
  SecretManagementService();

  grpc::Status WriteSecret(grpc::ServerContext* context,
                           const secretmanagement::WriteSecretRequest* request,
                           secretmanagement::WriteSecretResponse* response);

  grpc::Status ReadSecret(grpc::ServerContext* context,
                          const secretmanagement::ReadSecretRequest* request,
                          secretmanagement::ReadSecretResponse* response);

 private:
  std::shared_ptr<postgres::Pool> pgPool_;

 private:
  sv::Result InsertSecretDb(std::shared_ptr<postgres::Connection>& connection,
                            const std::string& token,
                            const std::string& secret);

  sv::Result ReadSecretFromDb(std::shared_ptr<postgres::Connection>& connection,
                              const std::string& token,
                              std::string& secret);
};

}  // namespace sv::server
