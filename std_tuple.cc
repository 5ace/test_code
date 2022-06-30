

// ./build_tools/gcc-8.3.0/bin/g++ -static-libstdc++ git_test_code/std_move.cc

#include <iostream>
#include <tuple>
#include <vector>

class A {
 public:
  A() {
    std::cout << "A()\n";
  }

  A(const A &a) {
    std::cout << "const A &\n";
  }

  A(A &&a) {
    std::cout << "A &&\n";
  }
};

int main() {
  std::vector<std::tuple<A, int>> v;
	v.reserve(10);
  std::cout << " ==== 1 \n";
  A a;
  v.emplace_back(a, 0);

  std::cout << " ==== 2 \n";
  v.emplace_back(std::move(std::move(a)), 0);

  std::cout << " ==== 3 \n";
  v.emplace_back(A(), 0);

  return 0;
}