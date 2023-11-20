#include <algorithm>
#include <cctype>
#include <cmath>
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

bool bin_search(int64_t n, int64_t a, int64_t b) {
  int64_t mid, left = 0, right = n;

  while (left <= right) {
    mid = (left + right) / 2;
    if (mid * b >= n && mid * a <= n) {
      return true;
    } else if (mid * b < n) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return false;
}

int main() {
  int64_t t, n, a, b;
  std::cin >> t;

  for (int64_t i = 0; i < t; ++i) {
    std::cin >> n >> a >> b;
    if (bin_search(n, a, b)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}