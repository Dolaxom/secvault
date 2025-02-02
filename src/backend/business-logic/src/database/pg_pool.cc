#include "pg_pool.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

namespace postgres {

void Pool::Build(i32 size, const ConnectionRules& rules) {
  size_ = size;
  CreatePool(rules);
}

std::shared_ptr<postgres::Connection> Pool::GetConnection() {
  std::unique_lock<std::mutex> lock{mutex_};

  while (pool_.empty()) {
    condition_.wait(lock);
  }

  auto connector = pool_.front();
  pool_.pop();

  return connector;
}

void Pool::FreeConnection(std::shared_ptr<postgres::Connection> connection) {
  std::unique_lock<std::mutex> lock{mutex_};
  pool_.push(connection);
  lock.unlock();
  condition_.notify_one();
}

void Pool::CreatePool(const ConnectionRules& rules) {
  std::lock_guard<std::mutex> lock{mutex_};

  for (u32 i = 0; i < size_; ++i) {
    pool_.emplace(std::make_shared<postgres::Connection>(rules));
  }
}

}  // namespace postgres