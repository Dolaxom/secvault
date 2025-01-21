#include "bl_server.h"

#include <fmt/core.h>

namespace sv::bl {
Server::Server(const Socket& socket)
    : socketInfo_{socket.ip, socket.port} {
  CreateServer();
}

Server::Server(Socket&& socket)
    : socketInfo_{std::move(socket.ip), std::move(socket.port)} {
  CreateServer();
}

void Server::RunServer()
{
  if (grpcServer_) {
    grpcServer_->Wait();
  }
}

// TODO change to SslServerCredentials
void Server::CreateServer() {
  builder_.AddListeningPort(socketInfo_.MakeServerAddress(), grpc::InsecureServerCredentials());
  builder_.RegisterService(&service_);

  grpcServer_ = builder_.BuildAndStart();

  // TODO refactor this trash
  fmt::print("{}[INFO]\t\t{}Server is running at {}{}:{}{}{}\n",
             "\033[32m", "\033[0m", "\033[36m", socketInfo_.ip, socketInfo_.port, "\033[32m", "\033[0m");
}

}  // namespace sv::bl