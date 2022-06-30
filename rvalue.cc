// g++ rvalue.cc -std=c++11
// 测试rvalue 和 emplace_back

#include <iostream>
#include <string>
#include <vector>

struct President {
  std::string name;
  std::string country;
  int year;

  President(std::string p_name, std::string p_country, int p_year)
      : name(std::move(p_name)), country(std::move(p_country)), year(p_year) {
    std::cout << "I am being constructed." << name << "\n";
  }
  President(const President &other)
      : name(std::move(other.name)), country(std::move(other.country)), year(other.year) {
    std::cout << "I am being copy constructed." << name << "\n";
  }
  President(President &&other) noexcept
      : name(std::move(other.name)), country(std::move(other.country)), year(other.year) {
    std::cout << "I am being moved." << name << "\n";
  }
  President &operator=(const President &other);
};

void f(int && x) {
  std::cout <<",in && "<< x << std::endl;
}

template<typename T>
void tf(T&& x) {
  std::cout <<",tf && "<< x << std::endl;
}

int main() {
  std::vector<President> elections;
  std::cout << "emplace_back:\n";
  elections.emplace_back("Nelson Mandela", "South Africa", 1994);  //没有类的创建

  std::vector<President> reElections;
  reElections.reserve(6);
  std::cout << "\npush_back:\n";
  reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
  std::cout << "-----\n";
  reElections.emplace_back(std::move(President("mao", "the CHN", 1936)));
  std::cout << "zzzzzzz\n";
  auto p = President("xi", "the CHN", 1936);
  auto d = President("deng", "the CHN", 1936);
  std::cout << "zzzzzzz push\n";
  reElections.push_back(p);
  std::cout << "zzzzzzz emplace_back\n";
  reElections.emplace_back(p);
  std::cout << "zzzzzzz push_back rvalue\n";
  reElections.push_back(std::move(p));
  std::cout << "zzzzzzz emplace_back rvalue\n";
  reElections.emplace_back(std::move(d));

  std::cout << "\nContents:\n";
  for (President const &president : elections) {
    std::cout << president.name << " was elected president of " << president.country << " in "
              << president.year << ".\n";
  }
  for (President const &president : reElections) {
    std::cout << president.name << " was re-elected president of " << president.country << " in "
              << president.year << ".\n";
  }


  int cc= 3;
  // f(cc); //cannot bind ‘int’ lvalue to ‘int&&’
  int &dd =cc;
  // f(dd); // cannot bind ‘int’ lvalue to ‘int&&’
  // int && dd = std::move(cc); 
  // f(dd); // cannot bind ‘int’ lvalue to ‘int&&’
  f(4);
  // =================================================================
  tf(4);
  tf(cc);
  tf(dd);
}
