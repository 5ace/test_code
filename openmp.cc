#include <omp.h>
#include "unistd.h"

#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// ./build_tools/gcc-8.3.0/bin/g++  -static-libstdc++ -fopenmp
// 结论用的是线程池
std::mutex mutex;
void f(int n, int thread_no) {
  std::lock_guard<std::mutex> lock(mutex);
  std::cout << "thread_no:" << thread_no << " ID|" << std::this_thread::get_id()
            << "|,omp no:" << omp_get_thread_num() << ", Max threads: " << omp_get_max_threads()
            << ", Num threads:" << omp_get_num_threads() << ",i:" << n << std::endl;
}
// 测试 一个线程内 多个 part 的 omp 是不是公用线程池
void multi_part_omp(int thread_no) {
  for (int j = 0; j < 2; j++) {
    std::cout << "thread_no:" << thread_no << " ======= loop:" << j
              << ",main thread id:" << std::this_thread::get_id() << "\n\n";

    int n = 10;
    {
      std::lock_guard<std::mutex> lock(mutex);
      std::cout << "thread_no:" << thread_no << "++ step4\n";
    }
#pragma omp parallel for if (0)
    for (int i = 0; i < n; i++) {
      f(i, thread_no);
    }
    {
      std::lock_guard<std::mutex> lock(mutex);

      std::cout << "thread_no:" << thread_no << "++ step1\n";
    }
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; i++) {
      f(i, thread_no);
    }
    {
      std::lock_guard<std::mutex> lock(mutex);
      std::cout << "thread_no:" << thread_no << "++ step2\n";
    }
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++) {
      f(i, thread_no);
    }
    {
      std::lock_guard<std::mutex> lock(mutex);
      std::cout << "thread_no:" << thread_no << "++ step3\n";
    }
#pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; i++) {
      f(i, thread_no);
    }
  }
}

// 测试嵌套 omp 线程池情况
void nest_omp(int thread_no) {
  int do_parallel = 1;
  int args = -1;  //测试是不是 thread local 的
  // omp_set_nested(1);  //不设置的话不能嵌套
  // omp_set_num_threads(10);
#pragma omp parallel if (do_parallel) num_threads(10)
  {
    f(0, -1);
    int n = 100;
    int t = omp_get_thread_num();
#pragma omp parallel for num_threads(20)  //会开20-24个线程
                                          // #pragma omp parallel for  //与omp_set_num_threads一致
    for (int i = 0; i < n; i++) {
      f(i, t);
    }
  }
}

void other(int thread_no) {
  for (int i = 0; i < 100; i++) {
#pragma omp parallel for  // 产生 3个线程
    for (int j = 0; j < 3; j++) {
      f(i, j);
    }
  }
}

void loop(int thread_no) {
  f(-1, -1);
  if (thread_no == 1) {
    omp_set_num_threads(1);  // 只影响当前线程
  }
  for (int k = 0; k < 2; k++) {
#pragma omp parallel for
    for (int i = 0; i < 10; i = i + 2) {
      f(i, -1 + thread_no * 10000);
#pragma omp parallel for
      for (int j = 0; j < 2; j++) {
        f(i, j + thread_no * 10000);
        // sleep(50);
      }
    }
  }
}

void collector(int thread_no) {
  std::vector<int> v = {2, 3, 4, 5, 6, 7};
  for (int k = 0; k < 3; k++) {
    // #pragma omp parallel for
    for (auto a : v) {  // 这样不行
      f(a, thread_no);
    }
  }
}

int main(int argc, char **argv) {
  std::vector<std::thread> threads;
  omp_set_num_threads(1);
  int thread_num = 2;
  for (int i = 0; i < thread_num; i++) {
    threads.emplace_back(std::move(std::thread(loop, i)));
  }
  std::for_each(threads.begin(), threads.end(), [](std::thread &t) { t.join(); });

  return 0;
}