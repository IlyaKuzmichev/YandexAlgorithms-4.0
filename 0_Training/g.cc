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

int main() {
  int32_t n, m, max_side = 0;
  std::cin >> n >> m;

  std::vector<std::vector<int32_t>> grid(n, std::vector<int32_t>(m, 0));
  std::vector<std::vector<int32_t>> dp(n, std::vector<int32_t>(m, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> grid[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 1) {
        if (i == 0 || j == 0) {
          dp[i][j] = 1;
        } else {
          dp[i][j] =
              1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
        }
        max_side = std::max(max_side, dp[i][j]);
      }
    }
  }

  std::cout << max_side << std::endl;
  return 0;
}