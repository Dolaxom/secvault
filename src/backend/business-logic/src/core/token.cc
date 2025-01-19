#include "token.h"

namespace sv::token {

Token::Token(const std::u8string& token) {
  data_ = token;
}

Token::Token(std::u8string&& token) noexcept {
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
}

Token& Token::operator=(Token&& token) noexcept {
  data_ = std::move(token.data_);
}

bool Token::operator==(const Token& token) {
  return data_ == token.data_;
}

void Token::Generate() {

}

std::u8string Token::Dump() const {
  return u8"";
}

}  // namespace sv::token
