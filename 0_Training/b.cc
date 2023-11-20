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

int32_t gcd(int32_t up, int32_t down) {
  if (down == 0) {
    return up;
  } else {
    return gcd(down, up % down);
  }
}

int main() {
  int32_t a, b, c, d, up, down;

  std::cin >> a >> b >> c >> d;
  up = a * d + b * c;
  down = b * d;
  int32_t div = gcd(up, down);

  std::cout << up / div << " " << down / div << std::endl;
}