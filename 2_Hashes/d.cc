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

#define X_X 307ULL
#define BORDER 1000000021ULL

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

  uint32_t FindMinLength() {
    CountZFunction();
    uint32_t ans = zFunc_[0];
    for (uint32_t i = 1; i < zFunc_.size(); ++i) {
      if (zFunc_[i] == zFunc_.size() - i && i < ans) {
        ans = i;
      }
    }
    return ans;
  }

  vect_type& GetZFunc() {
    CountZFunction();
    return zFunc_;
  }

  vect_type FindCubs() {
    vect_type ans;
    for (uint32_t i = 1; i <= (hash_.size() - 1) / 2; ++i) {
      if (ComparePolynom(1, hash_.size() - 2 * i, i)) {
        ans.push_back(i);
      }
    }
    ans.push_back(hash_.size() - 1);
    return ans;
  }

 private:
  vect_type hash_;
  vect_type reverseHash_;
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

  void CountReverseHash() {
    uint32_t size = hash_.size();
    reverseHash_.resize(size);
    for (uint32_t i = 1; i < size; ++i) {
      reverseHash_[i] = (reverseHash_[i - 1] * X_X + s_[size - i]) % BORDER;
    }
  }

  bool ComparePolynom(uint32_t start, uint32_t start_rev,
                      uint32_t len) const noexcept {
    return (hash_[start + len - 1] + reverseHash_[start_rev - 1] * args_[len]) %
               BORDER ==
           (reverseHash_[start_rev + len - 1] + hash_[start - 1] * args_[len]) %
               BORDER;
  }
};

int main() {
  uint64_t n, m;
  std::cin >> n >> m;
  vect_type cubs(n + 1), hash(n + 1), reverse_hash(n + 1), args(n + 1);
  for (uint32_t i = 1; i < n + 1; ++i) {
    std::cin >> cubs[i];
  }
  args[0] = 1;
  for (uint32_t i = 1; i < n + 1; ++i) {
    hash[i] = (hash[i - 1] * X_X + cubs[i]) % BORDER;
    reverse_hash[i] = (reverse_hash[i - 1] * X_X + cubs[n - i + 1]) % BORDER;
    args[i] = (args[i - 1] * X_X) % BORDER;
  }

  for (uint32_t i = n / 2; i > 0; --i) {
    if ((hash[i] + reverse_hash[n - 2 * i] * args[i]) %
               BORDER ==
           (reverse_hash[n - i] + hash[0] * args[i]) %
               BORDER) {
    std::cout << n - i << " ";
    }
  }
  std::cout << n << std::endl;
}
