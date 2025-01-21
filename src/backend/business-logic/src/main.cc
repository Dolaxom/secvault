#include <core/server/bl_server.h>

int main() {
  sv::bl::Server rpcServer{ sv::bl::Socket {"127.0.0.1", "9005"} };

  rpcServer.RunServer();
}
