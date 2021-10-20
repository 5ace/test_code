#include <iostream>
#include <utility>

// ./build_tools/gcc-8.3.0/bin/g++ -static-libstdc++ git_test_code/std_move.cc
class MyClass {
 public:
  int d = 0;
  MyClass() = default;
  MyClass(int v) : d(v){};
  MyClass(MyClass &&r) {
    this->d = r.data();
    r.d = 0;
    std::cout << " in rvalue construction\n";
  }
  int data() {
    return d;
  }
};
int main() {
  MyClass a(10);
  MyClass &&b = std::move(a);  // b 是个左值，https://zhuanlan.zhihu.com/p/335994370 能够声明出来的都是左值
  std::cout << "a.data:" << a.data() << std::endl;
  MyClass c(std::move(a));
  std::cout << "a.data:" << a.data() << ",c.data:" << c.data() << std::endl;

  return 0;
}