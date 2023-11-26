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
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using vectGr = std::vector<std::vector<std::pair<int32_t, int32_t>>>;

int main() {
  int32_t n, el;
  std::cin >> n;
  vectGr graph(n + 1);
  const int32_t sizeBuff = std::pow(2, n - 1);
  int32_t *ptrArray = new int32_t[sizeBuff];
  ptrArray[0] = 0;

  for (int32_t i = 1; i <= n; ++i) {
    for (int32_t j = 1; j <= n; ++j) {
      std::cin >> el;
      if (el != 0) {
        graph[i].push_back({j, el});
      }
    }
  }

  int32_t ansFinal = 0, ansInd = 0, find = 0, border = 2;
  for (int32_t i = 1; i <= sizeBuff - 1; ++i) {
    int32_t prev, tmpAns;
    if (i == border) {
      border *= 2;
      ++find;
    }
    prev = i ^ (1 << find);
    tmpAns = ptrArray[prev];

    for (auto neig : graph[find + 1]) {
      if (prev & (1 << (neig.first - 1))) {
        tmpAns -= neig.second;
      } else {
        tmpAns += neig.second;
      }
    }
    ptrArray[i] = tmpAns;

    if (tmpAns > ansFinal) {
      ansFinal = tmpAns;
      ansInd = i;
    }
  }

  std::cout << ansFinal << std::endl;
  for (int32_t i = 0; i < n; ++i) {
    std::cout << 2 - ((ansInd >> i) & 1) << " ";
  }
}