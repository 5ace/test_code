// 主要测试 构造函数中抛异常如何 避免内存泄漏 和 避免多次析构的问题
// g++ git_test_code/exception_in_constrction_function.cc -std=gnu++11
#include <iostream>
#include <stdexcept>
#include <string>

class Data {
  int d_ = -1;

 public:
  Data(int d) : d_(d) {
    std::cout << "in construction Data:" << d_ << " " << reinterpret_cast<void *>(this) << std::endl;
  }
  ~Data() {
    std::cout << "in deconstruction Data:" << d_ << " " << reinterpret_cast<void *>(this) << std::endl;
  }
};

class Base {
 public:
  Base() {
    std::cout << "in construction Base:" << reinterpret_cast<void *>(this) << std::endl;
  }
  ~Base() {
    std::cout << "in deconstruction Base:" << reinterpret_cast<void *>(this) << std::endl;
  }
};
class Derived {
 public:
  Data *p = nullptr;
  Data z{2};
  std::string s;
  Derived() {
    try {
      s = "hello";
      std::cout << "in construction Derived:" << reinterpret_cast<void *>(this) << std::endl;
      p = new Data(1);
      throw std::runtime_error("EX");

    } catch (const std::exception &e) {
      std::cout << "in Derived catch " << e.what() << std::endl;
      // std::cout << "before zhudong shifang~\n";
      // this->~Derived();  // NOTE(这里会core dump
      // 因为构造函数抛异常catch结束返回的时候操作系统会调用一些栈上的析构，这个主动析构也会析构栈上结构
      // 会double free) std::cout << "after zhudong shifang~\n";
      FreeHeapData();
      std::cout << "in Derived end " << std::endl;
      throw;
    }
  }
  void FreeHeapData() {
    delete p;
    p = nullptr;
  }
  ~Derived() {
    std::cout << "in deconstruction Derived:" << reinterpret_cast<void *>(this) << " "
              << reinterpret_cast<void *>(p) << std::endl;
    FreeHeapData();
  }
};

int main() {
  Derived *d = nullptr;
  try {
    d = new Derived();
  } catch (const std::exception &e) {
    std::cout << "in catch " << e.what() << " " << reinterpret_cast<void *>(d) << std::endl;
  }
  // d->~Derived();
  delete d;  // 这里是空指针
  return 0;
}