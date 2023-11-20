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
  int64_t n, rate;

  std::cin >> n;
  std::vector<int64_t> rates(n), pref_sum(n + 1, 0);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> rates[i];
    pref_sum[i + 1] = pref_sum[i] + rates[i];
  }
  for (int64_t i = 0; i < n; ++i) {
    rate = rates[i] * i - pref_sum[i] + pref_sum[n] - pref_sum[i + 1] -
           rates[i] * (n - i - 1);
    std::cout << rate << " ";
  }
}