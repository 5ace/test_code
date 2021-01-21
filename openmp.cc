#include <omp.h>

#include <iostream>
#include <mutex>
#include <thread>
// ./build_tools/gcc-8.3.0/bin/g++  -static-libstdc++ -fopenmp
// 结论用的是线程池
std::mutex mutex;
void f(int n) {
  std::lock_guard<std::mutex> lock(mutex);
  std::cout << "ID: " << std::this_thread::get_id() << ",omp no:" << omp_get_thread_num()
            << ", Max threads: " << omp_get_max_threads() << ", Num threads:" << omp_get_num_threads()
            << ",i:" << n << std::endl;
}

int main() {
  for (int j = 0; j < 2; j++) {
    std::cout << "======= loop:" << j << "\n\n";

    int n = 10;
    std::cout << "++ step1\n";
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; i++) {
      f(i);
    }
    std::cout << "++ step2\n";
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++) {
      f(i);
    }
    std::cout << "++ step3\n";
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; i++) {
      f(i);
    }
  }
  return 0;
}