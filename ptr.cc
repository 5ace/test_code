#include <iostream>
#include <memory>

class Test {
 public:
  Test() {
    std::cout << "construction\n";
  }
  ~Test() {
    std::cout << "~construction\n";
  }
};

int main() {
  std::unique_ptr<Test> p = std::make_unique<Test>();
	std::cout<<"before lambda\n";
	{
		auto f = [t= std::move(p)](){
			std::cout<<"in lambda\n";	
		};
		f();
	}
	std::cout<<"after lambda\n";
	return 0;
}