#pragma once

#include <common/sys.h>
#include <common/types.h>
#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/hmac.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#include <iomanip>
#include <iostream>
#include <sstream>
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

  /**
   * @brief Encrypts with AES-256
   */
  static std::string Encrypt(const std::string& data, const std::string& key) {
    using CryptoPP::byte;
    std::string ciphertext;

    CryptoPP::AutoSeededRandomPool rng;
    byte iv[CryptoPP::AES::BLOCKSIZE];
    rng.GenerateBlock(iv, CryptoPP::AES::BLOCKSIZE);

    std::string aesKey = key;
    aesKey.resize(CryptoPP::AES::MAX_KEYLENGTH, '0');

    try {
      CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
      encryptor.SetKeyWithIV(reinterpret_cast<const byte*>(aesKey.data()), CryptoPP::AES::MAX_KEYLENGTH, iv);

      std::string encryptedData;
      CryptoPP::StringSource(data, true, new CryptoPP::StreamTransformationFilter(encryptor, new CryptoPP::StringSink(encryptedData)));

      ciphertext.assign(reinterpret_cast<const char*>(iv), CryptoPP::AES::BLOCKSIZE);
      ciphertext += encryptedData;
    } catch (const CryptoPP::Exception& e) {
      throw std::runtime_error("Encryption error: " + std::string(e.what())); // TODO replace on logger
    }

    return ciphertext;
  }

  /**
   * @brief Decrypts with AES-256
   */
  static std::string Decrypt(const std::string& encryptedData, const std::string& key) {
    using CryptoPP::byte;
    if (encryptedData.size() < CryptoPP::AES::BLOCKSIZE) {
      throw std::runtime_error("Invalid encrypted data size.");
    }

    std::string decryptedtext;

    byte iv[CryptoPP::AES::BLOCKSIZE];
    std::memcpy(iv, encryptedData.data(), CryptoPP::AES::BLOCKSIZE);

    std::string aesKey = key;
    aesKey.resize(CryptoPP::AES::MAX_KEYLENGTH, '0');

    try {
      CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
      decryptor.SetKeyWithIV(reinterpret_cast<const byte*>(aesKey.data()), CryptoPP::AES::MAX_KEYLENGTH, iv);

      CryptoPP::StringSource(encryptedData.substr(CryptoPP::AES::BLOCKSIZE), true, new CryptoPP::StreamTransformationFilter(decryptor, new CryptoPP::StringSink(decryptedtext)));
    } catch (const CryptoPP::Exception& e) {
      throw std::runtime_error("Decryption error: " + std::string(e.what())); // TODO replace on logger
    }

    return decryptedtext;
  }
};

}  // namespace sv
