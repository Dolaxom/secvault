#pragma once

#include <string>

namespace sv::core
{

class Token {
public:
  Token() = default;
  Token(const std::string& token);
  Token(std::string&& token) noexcept;

  Token(const Token& token);
  Token(Token&& token) noexcept;

  Token& operator=(const Token& token);
  Token& operator=(Token&& token) noexcept;
  bool operator==(const Token& token) const noexcept;

  void Generate();
  static Token CreateRandom();
  std::string Dump() const;

private:
  std::string data_;
};

} // namespace sv::core
