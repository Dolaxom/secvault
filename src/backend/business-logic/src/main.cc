#include <common/logger.h>

int main() {
  sv::Logger logger{"traces.log"};

  logger.Log(sv::LogCategory::ERROR, "test error msg");
  logger.Log(sv::LogCategory::WARN, "test warn msg");
  logger.Log(sv::LogCategory::INFO, "test info msg");
}
