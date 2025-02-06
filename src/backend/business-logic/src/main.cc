#include <common/logger.h>
#include <core/server/bl_server.h>

int main() {
  ::sv::Logger::Instance("blserver.log").Write(::sv::Severity::Info, "Logger is configured");

  // TODO поменять на command line
  ::sv::bl::Server rpcServer{ ::sv::bl::Socket {"127.0.0.1", "9005"} };

  rpcServer.RunServer();
}
