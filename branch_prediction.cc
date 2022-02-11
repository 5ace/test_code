#include <iostream>
#include <random>
#include "tool.h"
// g++ -std=gnu++11 -O3 git_test_code/branch_prediction.cc
void inner_out_loop(int n, int sw) {
  int sum1 = 0;
  int sum2 = 0;
  ace::Timer timer;
  for (int i = 0; i < n; i++) {
    if (sw == 1) {
      sum1 += sw;
    } else {
      sum1 += 1;
    }
  }
  int t1 = timer.IntervalUs();
  if (sw == 1) {
    for (int i = 0; i < n; i++) {
      sum2 += sw;
    }
  } else {
    for (int i = 0; i < n; i++) {
      sum2 += 1;
    }
  }
  std::cout << "loop:" << n << ",inner cost:" << t1 << ",outer cost:" << timer.IntervalUs() << ",sum:" << sum1
            << " " << sum2 << std::endl;
}

int main() {
  std::default_random_engine e;
  e.seed(1000);
  inner_out_loop(100000000, e());
  return 0;
}