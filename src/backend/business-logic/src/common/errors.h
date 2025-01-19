#pragma once

#include <common/types.h>
#include <common/logger.h>

#include <stdexcept>
#include <string>

namespace sv {

inline void expect(Result result) {
  if (result != Result::kOk) {
    // + logging
    throw std::runtime_error(std::to_string(static_cast<u32>(result)));
  }
}

inline void check(Result result) {
  if (result != Result::kOk) {
    // + logging
  }
}

inline bool is_success(Result result) {
  return result == Result::kOk ? true : false;
}

}  // namespace sv