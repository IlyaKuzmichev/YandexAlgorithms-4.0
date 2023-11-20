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
  long double xa, ya, xb, yb;
  std::cin >> xa >> ya >> xb >> yb;
   
  long double angle = fabs(std::atan2(ya, xa) - std::atan2(yb, xb));
  if (angle > M_PI) {
    angle = 2.0 * M_PI - angle;
  }
  long double r1 = sqrt(xa * xa + ya * ya);
  long double r2 = sqrt(xb * xb + yb * yb);
  std::cout.precision(12);
  std::cout << std::min(r1 + r2, fabs(r1 - r2) + std::min(r1, r2) * angle) << std::endl;
}