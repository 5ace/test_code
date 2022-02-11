#include <iostream>

class T1{
  public:
  int a=0;
  void p(){std::cout<<"in p\n";}
};
template<class T>
class T2{
  public:
  void f(){
    std::cout<<t.a<<" in f \n";
    t.p();
  }

  T t;
};
int main(){
  T2<T1> t;
  t.f();
  return 0;
}