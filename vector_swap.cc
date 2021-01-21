#include <algorithm>
#include <iostream>
#include <vector>

// https://www.cnblogs.com/guoliushui/p/10302747.html
int main() {
  int n = 500000000;
  // 2G
  {
    std::vector<int> t(n);
    std::fill(t.begin(), t.end(), -1);
  }
  std::cout << "destruct see mem\n";
  getchar();
  // 4G
  {
    std::vector<int> t(n * 2);
    std::fill(t.begin(), t.end(), -1);
    std::vector<int>().swap(t);
  }
  std::cout << "swap see mem\n";
  getchar();
  return 0;
}