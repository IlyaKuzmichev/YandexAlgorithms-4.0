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
    hashSize_ = s.size() + 1;
    hash_.resize(hashSize_, 0);
    reverseHash_.resize(hashSize_, 0);
    args_.resize(hashSize_, 1);
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

  uint64_t CountPalindroms() {
    uint64_t ans = 0;
    for (uint32_t i = 1; i < hashSize_; ++i) {
      ans += CountPalindromsInPoint(i);
    }
    return ans;
  }

 private:
  vect_type hash_;
  vect_type reverseHash_;
  vect_type args_;
  vect_type zFunc_;
  std::string s_;
  uint32_t hashSize_;

  void CountHash() {
    for (uint32_t i = 1; i < hash_.size(); ++i) {
      hash_[i] = (hash_[i - 1] * X_X + s_[i]) % BORDER;
      args_[i] = (args_[i - 1] * X_X) % BORDER;
      reverseHash_[i] =
          (reverseHash_[i - 1] * X_X + s_[hash_.size() - i]) % BORDER;
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

  bool ComparePolynom(uint32_t start, uint32_t start_rev,
                      uint32_t len) const noexcept {
    return (hash_[start + len - 1] + reverseHash_[start_rev - 1] * args_[len]) %
               BORDER ==
           (reverseHash_[start_rev + len - 1] + hash_[start - 1] * args_[len]) %
               BORDER;
  }

  uint64_t CountPalindromsInPoint(uint32_t i) {
    uint32_t left = 0, right = std::min(i - 1, hashSize_ - i - 1), mid;
    uint64_t ans = 1;

    while (left < right) {
      mid = (left + right + 1) / 2;
      if (ComparePolynom(i - mid, hashSize_ - i - mid, mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    ans += left;

    left = 0;
    right = std::min(i, hashSize_ - i - 1);
    while (left < right) {
      mid = (left + right + 1) / 2;
      if (ComparePolynom(i - mid + 1, hashSize_ - i - mid, mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    ans += left;
    return ans;
  }
};

int main() {
  std::string str;
  std::cin >> str;
  HashStr Hash(str);
  std::cout << Hash.CountPalindroms() << std::endl;
}
