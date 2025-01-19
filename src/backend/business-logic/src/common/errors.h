#pragma once

#include <common/types.h>

#include <stdexcept>
#include <string>

namespace sv::errors {

inline void expect(sv::Result result) {
  if (result != Result::kOk) {
    // + logging
    throw std::runtime_error(std::to_string(static_cast<u32>(result)));
  }
}

inline void check(sv::Result result) {
  if (result != Result::kOk) {
    // + logging
  }
}

inline bool is_success(sv::Result result) {
  return result == Result::kOk ? true : false;
}

}  // namespace sv::errors