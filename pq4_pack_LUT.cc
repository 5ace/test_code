#include <iostream>
#include <string>
#include <vector>

#include <string.h>

void pq4_pack_LUT(int nq, int nsq, const uint8_t *src, uint8_t *dest) {
  // nq 个query
  for (int q = 0; q < nq; q++) {
    // M
    for (int sq = 0; sq < nsq; sq += 2) {
      memcpy(dest + (sq / 2 * nq + q) * 32, src + (q * nsq + sq) * 16, 16);
      memcpy(dest + (sq / 2 * nq + q) * 32 + 16, src + (q * nsq + sq + 1) * 16, 16);
    }
  }
}

void pq4_pack_LUT(int nq, int nsq, const std::vector<std::string> &src, std::vector<std::string> &dest) {
  // nq 个query
  for (int q = 0; q < nq; q++) {
    // M
    for (int sq = 0; sq < nsq; sq += 2) {
      dest[(sq / 2 * nq + q) * 2] = src[q * nsq + sq];
      dest[(sq / 2 * nq + q) * 2 + 1] = src[q * nsq + sq + 1];
    }
  }
}

int main() {
  int nq = 4;
  int M = 8;
  std::vector<std::string> ori;
  std::vector<std::string> pack(nq * M);
  for (int i = 0; i < nq; i++) {
    for (int j = 0; j < M; j++) {
      ori.push_back("q" + std::to_string(i) + "_M" + std::to_string(j));
    }
  }
  pq4_pack_LUT(nq, M, ori, pack);
  for (auto d : pack) {
    std::cout << d << " ";
  }
  std::cout << std::endl;
  return 0;
}
