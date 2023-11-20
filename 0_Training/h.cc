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
  int32_t a, b, n, min;
  std::cin >> a >> b >> n;

  min = b / n + (b % n > 0);

  if (a > min) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}