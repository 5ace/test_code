// 测试O3编译器自动向量化
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
// g++ -std=gnu++11 -O3 git_test_code/auto_vectorize.cc
// objdump -d 没有vmu指令，下面就有
// ./kbuild/gcc-8.3.0/bin/g++ -std=gnu++11 -O3 git_test_code/auto_vectorize.cc -mavx512f

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 100);
  std::vector<float> a(256);
  std::vector<float> b(256);
  std::cout << a.size() << std::endl;
  std::for_each(a.begin(), a.end(), [&](float &v) { v = dis(gen) / 100.0f; });
  std::for_each(b.begin(), b.end(), [&](float &v) { v = dis(gen) / 100.0f; });
  float ip = 0.0f;
  for (int i = 0; i < 256; i++) {
    ip += a.at(i) * b.at(i);
  }
  std::cout << "ip:" << ip << std::endl;

  return 0;
}