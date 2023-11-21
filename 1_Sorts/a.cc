#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
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

uint32_t partition(int32_t predicat, std::vector<int32_t>& vect, uint32_t i, uint32_t j) {
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
  return eq;
}

int main() {
  uint32_t n, ans;
  int32_t x;

  std::cin >> n;
  std::vector<int32_t> vect(n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> vect[i];
  }
  std::cin >> x;

  ans = partition(x, vect, 0, n);
  std::cout << ans << std::endl << n - ans << std::endl;
}