#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using vectGr = std::vector<std::vector<std::pair<int32_t, int32_t>>>;

class Solution {
 public:
  Solution(uint32_t n) : n_(n) {}

  void RecoursiveBrackets(std::string& str, std::deque<char> brNow) {
    if (str.size() + brNow.size() == n_) {
      std::string out = str;
      uint32_t i = brNow.size();
      while (i > 0) {
        --i;
        if (brNow[i] == '(') {
          out.push_back(')');
        } else {
          out.push_back(']');
        }
      }
      std::cout << out << '\n';
      return;
    }

    for (auto el : br_) {
      if (brNow.empty() && (el == ')' || el == ']')) {
        continue;
      }
      if (el == '(' || el == '[') {
        str.push_back(el);
        brNow.push_back(el);
        RecoursiveBrackets(str, brNow);
        str.pop_back();
        brNow.pop_back();
      } else {
        if (!brNow.empty() && ((el == ')' && brNow.back() == '(') ||
                               (el == ']' && brNow.back() == '['))) {
          str.push_back(el);
          brNow.pop_back();
          RecoursiveBrackets(str, brNow);
          str.pop_back();
          brNow.push_back(el);
        }
      }
    }
  }

 private:
  uint32_t n_;
  const std::string br_ = "([)]";
};

int main() {
  
  uint32_t n;
  std::cin >> n;
  if (n % 2 == 0) {
    Solution sl(n);
    std::string str;
    std::deque<char> brNow;
    std::ios_base::sync_with_stdio(false);
    sl.RecoursiveBrackets(str, brNow);
  }
}