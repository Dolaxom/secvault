#pragma once

#include <string>
#include <cstdlib>

namespace sys {

struct Environment
{
  static std::string Salt()
  {
    const char* salt = std::getenv("SECV_SALT");
    return salt ? salt : "INSECURE_SALT";
  }
};

}  // namespace sys