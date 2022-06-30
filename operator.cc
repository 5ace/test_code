#include<iostream>
#include<memory>



class A{
	public:
	A(){};
	A(int* a):a_(a){}

	operator bool() const{
		std::cout<<"in bool\n";
		return a_==nullptr;
	}

	// 模拟指针，只判断 是否 == nullptr
	bool operator==(std::nullptr_t){
	 return !(*this);
	}
	// 会一直递归找下去，直到返回一个指针为止
	// 模拟指针行为
	A* operator->(){
		return this;
	}
	void f(){
		std::cout <<"in f\n";
	}
	int* a_=nullptr;
};

int main(){
	auto p = std::make_shared<A>();
	if(*p){
		std::cout<<"p is true\n";
	} else {
		std::cout<<"p is not true\n";	
	}
	auto b = A();
	b->f();

	auto c=&b;
	c->f();
	std::cout << (b==nullptr)<<std::endl;
	return 0;
}