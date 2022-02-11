#include <algorithm>
#include <iostream>
#include <vector>

class base {
 public:
  virtual void print() {
    std::cout << "base::print\n";
  }
  void p2() {
    std::cout << "base::p2\n";
  }
};
class derived : public base {
 public:
  virtual void print() {
    std::cout << "derived::print\n";
  }
};

typedef void (base::*ftype)();
typedef void (*ctype)();

template <ftype T>
void call(derived *b) {
  (b->*T)();
}
void call1(derived *b, ftype f) {
  (b->*f)();
}
bool compare(const int &lh, const int &rh) {
  return lh < rh;
}

void p3() {
  std::cout << "p3\n";
}
void call3(ctype c) {
  (*c)();
}

int main() {
  ftype f = &base::print;
  // std::cout << reinterpret_cast<void *>(f) << std::endl;
  // std::cout << reinterpret_cast<void *>(&base::p2) << std::endl;
  derived *b = new derived();
  (b->*f)();
  call1(b, f);
  // call<f>(b); https://stackoverflow.com/questions/1174169/function-passed-as-template-argument/22111957
  // error 因为 f 不能再编译器确定，无法作为模板参数 https://www.zhihu.com/question/56487531
  // doOperation(add3()); 传一个functor[函数对象]更好，有机会inline，但是传函数指针不行

  std::vector<int> a{2, 3, 1};
  std::sort(a.begin(), a.end(), compare);
  call3(p3);
  call3(&p3);
  return 0;
}