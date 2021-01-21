#include <iostream>
#include <vector>

#include "boost/align/aligned_allocator.hpp"

// ./build_tools/gcc-8.3.0/bin/g++  -static-libstdc++ git_test_code/mem_alignment.cc
// -Ipub/src/third_party/boost/
int main() {
  std::vector<int, boost::alignment::aligned_allocator<int, 64>> codes = {
      1, 2, 3, 4};  // 只是第一个元素是64bit地址对齐
  std::cout << &codes.at(0) << " " << &codes.at(1) << std::endl;
}