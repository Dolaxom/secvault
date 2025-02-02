#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <common/types.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#include <stdexcept>
#include <string>

namespace sv {

struct Crypto {
  static std::string GenerateString() {
    unsigned char randomRawString[SHA256_DIGEST_LENGTH];
    i32 res = RAND_bytes(randomRawString, sizeof(randomRawString));
    if (res != 1) {
      throw std::runtime_error("Can`t generate random string. Result = " + res);
    }

    return std::string{reinterpret_cast<char*>(randomRawString), sizeof(randomRawString)};
  }

  static std::string GenerateSha256(const std::string& seed) {
    u8 token[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Ctx;
    SHA256_Init(&sha256Ctx);
    SHA256_Update(&sha256Ctx, seed.c_str(), seed.size());
    SHA256_Final(token, &sha256Ctx);

    std::stringstream stream;
    for (i32 i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
      stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<i32>(token[i]);
    }

    return stream.str();
  }

  static std::string Encrypt(const std::string& data, const std::string& key)
  {
    // TODO
    return data + "-" + key;
  }

  static std::string Decrypt(const std::string& data, const std::string& key)
  {
    // TODO
    return data;
  }
};

}  // namespace sv
