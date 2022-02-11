#include "tool.h"

#include <cstring>
#include <iostream>

int main() {
  const int n = 10000000;
  ace::Timer timer;
  std::cout << "new:" << timer.IntervalUs() << std::endl;
  uint16_t *data = new uint16_t[n];
  std::memset(data, 0, n * sizeof(uint16_t));
  std::cout << "fisrt memset cost us:" << timer.IntervalUs() << std::endl;
  std::memset(data, 0, n * sizeof(uint16_t));
  std::cout << "second memset cost us:" << timer.IntervalUs() << std::endl;
  std::memset(data, 0, n * sizeof(uint16_t));
  std::cout << "third memset " << data[0] << " " << data[1] << ",cost:" << timer.IntervalUs() << std::endl;
  return 0;
}