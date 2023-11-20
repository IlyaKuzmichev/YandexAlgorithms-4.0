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
  std::stack<uint32_t> people;
  uint64_t k, n, el, lift, ans = 0;

  std::cin >> k >> n;
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> el;
    people.push(el);
  }

  while (true) {
    while (n > 0 && people.top() == 0) {
      people.pop();
      --n;
    }
    if (n == 0) {
      break;
    }
    if (people.top() % k != 0) {
      ans += (2 * n) * (people.top() / k + 1);
      lift = 0;
    } else {
      ans += (2 * n) * (people.top() / k);
      lift = k;
    }
    people.top() %= k;
    while (n > 0 && lift < k) {
      if (people.top() > k - lift) {
        people.top() -= k - lift;
        lift = k;
      } else {
        lift += people.top();
        people.pop();
        --n;
      }
    }
  }
  std::cout << ans << std::endl;
}