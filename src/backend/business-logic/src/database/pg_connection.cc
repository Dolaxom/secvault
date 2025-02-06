#include "pg_connection.h"

#include <common/types.h>
#include <common/logger.h>

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
    sv::Logger::Instance().Write(sv::Severity::Error, fmt::format("DATABASE CONNECTION ERROR; result = {}", (i32)PQstatus(rawConnection_.get())));
    throw std::runtime_error("Wrong on the server side");
  }
}

std::shared_ptr<PGconn> Connection::GetRaw() const {
  return rawConnection_;
}

}  // namespace postgres