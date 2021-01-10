#include <cstring>
#include <iostream>
int main() {
  const int n = 2;
  uint64_t d[n];
  std::memset(d, 1, n * sizeof(uint64_t));
  std::cout << d[0] << " " << d[1] << std::endl;
  std::memset(d, -1, n * sizeof(uint64_t));
  std::cout << d[0] << " " << d[1] << std::endl;
  return 0;
}