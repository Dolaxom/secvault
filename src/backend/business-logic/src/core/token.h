#pragma once

#include <string>

namespace sv::token
{

class Token {
public:
  Token() = default;
  Token(const std::u8string& token);
  Token(std::u8string&& token) noexcept;

  Token(const Token& token);
  Token(Token&& token) noexcept;

  Token& operator=(const Token& token);
  Token& operator=(Token&& token) noexcept;
  constexpr bool operator==(const Token& token) noexcept;

  void Generate();
  std::u8string Dump() const;

private:
  std::u8string data_;
};

} // namespace sv::token
