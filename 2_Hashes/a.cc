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

using vect_type = std::vector<int64_t>;

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

 private:
  vect_type hash_;
  vect_type args_;
  std::string s_;

  void CountHash() {
    for (uint32_t i = 1; i < hash_.size(); ++i) {
      hash_[i] = (hash_[i - 1] * X_X + s_[i]) % BORDER;
      args_[i] = (args_[i - 1] * X_X) % BORDER;
    }
  }
};

int main() {
  std::string input_str;
  uint32_t q, l, a, b;
  std::cin >> input_str >> q;
  HashStr elem(input_str);
  for (uint32_t i = 0; i < q; ++i) {
    std::cin >> l >> a >> b;
    std::cout << (elem.IsEqualSubstr(a + 1, b + 1, l) ? "yes" : "no") << std::endl;
  }
}