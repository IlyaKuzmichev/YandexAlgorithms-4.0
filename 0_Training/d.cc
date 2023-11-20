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

void count_str(std::string& s, std::vector<uint32_t>& vect) {
  for (uint32_t i = 0; i < s.size(); ++i) {
    ++vect[s[i] - 'a'];
  }
}

int main() {
  std::string s1, s2;
  std::vector<uint32_t> count1('z' - 'a' + 1, 0), count2('z' - 'a' + 1, 0);

  std::cin >> s1 >> s2;
  count_str(s1, count1);
  count_str(s2, count2);

  bool ans = true;
  for (uint32_t i = 0; i < count1.size() && ans; ++i) {
    if (count1[i] != count2[i]) {
      ans = false;
    }
  }
  std::cout << (ans ? "YES" : "NO") << std::endl;
}