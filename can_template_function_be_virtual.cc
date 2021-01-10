#include<iostream>
using namespace std;

template<typename T>
class Base{
 public:
  virtual void print(T t) =0;
};
template<typename T>
class Derive :public Base<T>{
 public:
  void print(T t) override {
    cout <<"derive print " << t <<endl;
  }
};

int main(){
  Derive<float> a;
  a.print(1);
  return 0;
}
