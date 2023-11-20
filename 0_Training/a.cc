#include <algorithm>
#include <cctype>
#include <cstdint>
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

int main() {
  uint32_t n, m, l, r;

  std::cin >> n >> m;
  std::vector<uint32_t> seq(n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> seq[i];
  }

  for (uint32_t i = 0; i < m; ++i) {
    std::cin >> l >> r;
    ++l;
    bool ans = false;
    while (l <= r && !ans) {
      if (seq[l] != seq[l - 1]) {
        std::cout << std::max(seq[l], seq[l - 1]) << std::endl;;
        ans = true;
      } else {
        ++l;
      }
    }
    if (!ans) {
      std::cout << "NOT FOUND" << std::endl;
    }
  }
}