#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>

#include <common/types.h>

#include "pg_connection.h"

namespace postgres {

class Pool
{
public:
  Pool() = default;
  void Build(i32 size, const ConnectionRules& rules);
  std::shared_ptr<postgres::Connection> GetConnection();
  void FreeConnection(std::shared_ptr<postgres::Connection> connection);

private:
  std::mutex mutex_;
  std::condition_variable condition_;
  std::queue<std::shared_ptr<postgres::Connection>> pool_;

  u32 size_;

  void CreatePool(const ConnectionRules& rules);
};

}  // namespace postgres
