#pragma once

#include <cstdint>

using i8 = int8_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

namespace sv {

enum class Result : u8 {
  kOk = 0,
  kFalse = 1,
};

}  // namespace sv