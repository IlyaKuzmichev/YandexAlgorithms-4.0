#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::pair<uint32_t, uint32_t> partition(int32_t predicat, std::vector<int32_t>& vect, uint32_t i, uint32_t j) {
  uint32_t eq = i, gt = i, now = i;
  int32_t buf;
  while (now < j) {
    if (vect[now] < predicat) {
      buf = vect[now];
      vect[now] = vect[gt];
      vect[gt] = vect[eq];
      vect[eq] = buf;
      ++gt;
      ++eq;
    } else if (vect[now] == predicat) {
      std::swap(vect[now], vect[gt]);
      ++gt;
    }
    ++now;
  }
  return {eq, gt};
}

void quicksort(std::vector<int32_t>& vect, uint32_t i, uint32_t j) {
  if (i >= j) {
    return;
  }
  int32_t predicat = vect[i + (rand() % (j - i))];
  std::pair<uint32_t, uint32_t> p = partition(predicat, vect, i, j);
  quicksort(vect, i, p.first);
  quicksort(vect, p.second, j);
}

int main() {
  uint32_t n;

  std::cin >> n;
  std::vector<int32_t> vect(n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> vect[i];
  }
  quicksort(vect, 0, n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cout << vect[i] << " ";
  }
}