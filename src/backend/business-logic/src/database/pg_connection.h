#pragma once

#include <libpq-fe.h>

#include <memory>
#include <mutex>
#include <string>

namespace postgres {

struct ConnectionRules {
  std::string host;
  std::string port;
  std::string dbname;
  std::string dbuser;
  std::string dbpass;
};

class Connection {
 public:
  Connection(const ConnectionRules& rules);
  std::shared_ptr<PGconn> GetRaw() const;

 private:
  ConnectionRules rules_;
  std::shared_ptr<PGconn> rawConnection_;
};

}  // namespace postgres
