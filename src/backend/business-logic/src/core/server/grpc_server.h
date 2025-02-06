#pragma once

#include "secret_management_service.h"

namespace sv::bl {

// Dummy
struct Socket {
  std::string ip;
  std::string port;

  std::string MakeServerAddress() { return {ip + ':' + port}; }
};

class Server {
 public:
  Server() = delete;
  Server(const Socket& socket);
  Server(Socket&& socket);
  Server(const Server& server) = delete;
  Server& operator=(const Server& server) = delete;

  void RunServer();

 private:
  server::SecretManagementService service_;
  Socket socketInfo_;
  grpc::ServerBuilder builder_;
  std::unique_ptr<grpc::Server> grpcServer_;

 private:
  void CreateServer();
};

}  // namespace sv::bl