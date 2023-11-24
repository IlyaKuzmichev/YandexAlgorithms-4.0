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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define X_X 307
#define BORDER 1000000021

using vect_type = std::vector<uint64_t>;

class HashStr {
 public:
  explicit HashStr(std::string s) : s_(' ' + s) {
    hash_.resize(s.size() + 1, 0);
    args_.resize(s.size() + 1, 1);
    CountHash();
  }

  bool IsEqualSubstr(uint32_t start1, uint32_t start2,
                     uint32_t len) const noexcept {
    return (hash_[start1 + len - 1] + hash_[start2 - 1] * args_[len]) %
               BORDER ==
           (hash_[start2 + len - 1] + hash_[start1 - 1] * args_[len]) % BORDER;
  }

  uint32_t findMinLength() {
    CountZFunction();
    uint32_t ans = zFunc_[0];
    for (uint32_t i = 1; i < zFunc_.size(); ++i) {
      if (zFunc_[i] == zFunc_.size() - i && i < ans) {
        ans = i;
      }
    }
    return ans;
  }

  vect_type& getZFunc() {
    CountZFunction();
    return zFunc_;
  }

 private:
  vect_type hash_;
  vect_type args_;
  vect_type zFunc_;
  std::string s_;

  void CountHash() {
    for (uint32_t i = 1; i < hash_.size(); ++i) {
      hash_[i] = (hash_[i - 1] * X_X + s_[i]) % BORDER;
      args_[i] = (args_[i - 1] * X_X) % BORDER;
    }
  }

    void CountZFunction() {
    zFunc_.resize(s_.size() - 1, 0);
    zFunc_[0] = 0;
    for (uint32_t i = 1; i < zFunc_.size(); ++i) {
      uint32_t left = 0, right = zFunc_.size() - i, mid;
      while (left < right) {
        mid = (left + right + 1) / 2;
        if (IsEqualSubstr(1, i + 1, mid)) {
          left = mid;
        } else {
          right = mid - 1;
        }
      }
      zFunc_[i] = left;
    }
  }
};

int main() {
  std::string input_str;
  std::cin >> input_str;
  HashStr elem(input_str);
  vect_type vect = elem.getZFunc();
  for (uint32_t i = 0; i < input_str.size(); ++i) {
    std::cout << vect[i] << " ";
  }
}