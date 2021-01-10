#include<iostream>
using namespace std;

template<typename T>
class Base{
 public:
  virtual void print(const T& t) =0;
};
template<typename T>
class Derive :public Base<T>{
 public:
  void print(const T& t) override {
    cout <<"derive print " << t <<endl;
  }
};

int main(){
  Derive<float> a;
  a.print(1.0f);
  return 0;
}
