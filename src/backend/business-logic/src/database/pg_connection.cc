#include "pg_connection.h"

namespace postgres {

Connection::Connection(const ConnectionRules& rules) {
  rules_ = rules;

  rawConnection_.reset(PQsetdbLogin(rules.host.c_str(),
                                    rules.port.c_str(),
                                    nullptr,
                                    nullptr,
                                    rules.dbname.c_str(),
                                    rules.dbuser.c_str(),
                                    rules.dbpass.c_str()),
                                    &PQfinish);

  if (PQstatus(rawConnection_.get()) != CONNECTION_OK && PQsetnonblocking(rawConnection_.get(), 1) != 0) {
    throw std::runtime_error(PQerrorMessage(rawConnection_.get()));
  }
}

std::shared_ptr<PGconn> Connection::GetRaw() const {
  return rawConnection_;
}

}  // namespace postgres