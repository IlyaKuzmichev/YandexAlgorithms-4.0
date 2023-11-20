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
  std::stack<char> brackets;
  std::string str;
  bool ans = true;
  std::cin >> str;

  for (auto c : str) {
    if (c == '(' || c == '{' || c == '[') {
      brackets.push(c);
    } else {
      if (brackets.empty() || (c == ')' && brackets.top() != '(') ||
          (c == '}' && brackets.top() != '{') ||
          (c == ']' && brackets.top() != '[')) {
        ans = false;
        break;
      } else {
        brackets.pop();
      }
    }
  }
  if (!brackets.empty()) {
    ans = false;
  }
  std::cout << (ans ? "yes" : "no") << std::endl;
}