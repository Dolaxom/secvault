#include <core/server/bl_server.h>

int main() {
  // TODO поменять на command line
  sv::bl::Server rpcServer{ sv::bl::Socket {"127.0.0.1", "9005"} };

  rpcServer.RunServer();
}
