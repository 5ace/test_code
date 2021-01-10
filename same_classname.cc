#include <iostream>

namespace a {
class same {
 public:
  same() {
    std::cout << "a\n";
  }
};
}  // namespace a

namespace b {
class same {
 public:
  same() {
    std::cout << "a\n";
  }
};
}  // namespace b

int main() {
  a::same t;
  return 0;
}