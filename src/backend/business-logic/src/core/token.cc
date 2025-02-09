#include "token.h"

#include <common/crypto.h>
#include <common/types.h>

namespace sv::core {

Token::Token(const std::string& token) {
  data_ = token;
}

Token::Token(std::string&& token) noexcept {
  data_ = std::move(token);
}

Token::Token(const Token& token) {
  *this = token;
}

Token::Token(Token&& token) noexcept {
  *this = std::move(token);
}

Token& Token::operator=(const Token& token) {
  data_ = token.data_;
  return *this;
}

Token& Token::operator=(Token&& token) noexcept {
  data_ = std::move(token.data_);
  return *this;
}

bool Token::operator==(const Token& token) const noexcept {
  return data_ == token.data_;
}

void Token::Generate() {
  auto seed = Crypto::GenerateString();
  auto sha256str = Crypto::GenerateSha256(seed);

  data_ = sha256str;
}

Token Token::CreateRandom() {
  Token token;
  token.Generate();

  return token;
}

std::string Token::Dump() const {
  return data_;
}

}  // namespace sv::core
