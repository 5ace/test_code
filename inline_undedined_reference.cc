// 成员函数外部inline导致链接错误
// g++ inline_undedined_reference.cc  inline_undefine_class.cc

#include "inline_undedine_class.h"
int main() {
  Undefine undefine;
  undefine.line();
}
