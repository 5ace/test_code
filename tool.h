#pragma once
#include <chrono>

namespace ace {
class Timer {
 public:
  Timer() {
    start_ = std::chrono::system_clock::now();
    last_ = start_;
  }

  ~Timer() = default;

  uint64_t IntervalUs() {
    auto last = last_;
    last_ = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(last_ - last).count();
  }

  uint64_t IntervalMs() {
    auto last = last_;
    last_ = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(last_ - last).count();
  }

  uint64_t StopUs() {
    last_ = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(last_ - start_).count();
  }

  uint64_t StopMs() {
    last_ = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(last_ - start_).count();
  }

 private:
  std::chrono::system_clock::time_point start_;
  std::chrono::system_clock::time_point last_;
};
}  // namespace ace