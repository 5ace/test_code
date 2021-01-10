#include <iostream>
#include <string>

// g++
// ./build_tools/gcc-8.3.0/bin/g++ git_test_code/attribute_target.cc -static-libstdc++
// 在支持avx512机器 输出avx512f
// 在支持不支持avx512机器 输出avx2
// ./build_tools/gcc-8.3.0/bin/g++ git_test_code/attribute_target.cc -static-libstdc++ -mavx512f
// 在所有机器输出avx512

__attribute__((target("default"))) std::string version() {
  return "default";
}
__attribute__((target("sse2"))) std::string version() {
  return "sse2";
}
__attribute__((target("ssse3"))) std::string version() {
  return "ssse3";
}
// __attribute__((target("sse4"))) std::string version() {
//   return "sse4";
// }
__attribute__((target("avx2"))) std::string version() {
  return "avx2";
}

// __attribute__((target("avx512bw"))) std::string version() {
//   return "avx512bw";
// }

__attribute__((target("avx512f"))) std::string version() {
  return "avx512f";
}

// __attribute__((target("avx512dq"))) std::string version() {
//   return "avx512dq";
// }

int main() {
  std::cout << version() << std::endl;
  return 0;
}
