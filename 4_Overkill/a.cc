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

class Permutation {
 public:
  Permutation(uint32_t n, std::string out) : n_(n), fout(out) {}

  ~Permutation() {
    if (fout) {
      fout.close();
    }
  }

  void RecursivePermutation(uint32_t pos, std::string& currPermutation,
                            int32_t& bitMask) {
    if (pos == n_) {
      fout << currPermutation << '\n';
      return;
    }

    ++pos;
    for (uint32_t i = 0; i < n_; ++i) {
      if (bitMask & (1 << i)) {
        continue;
      }
      bitMask = bitMask | (1 << i);
      currPermutation.push_back('1' + i);
      RecursivePermutation(pos, currPermutation, bitMask);
      currPermutation.pop_back();
      bitMask = bitMask & (~(1 << i));
    }
  }

  void FindPermutations() {
    std::string str;
    int32_t bitMask = 0;
    str.reserve(n_);
    RecursivePermutation(0, str, bitMask);
  }

  // void PrintAns() {
  //   std::ofstream fout ("output.txt");
  //   for (uint32_t i = 0; i < vect_.size(); ++i) {
  //     fout << vect_[i] << '\n';
  //   }
  //   fout.close();
  // }

 private:
  uint32_t n_;
  std::ofstream fout;
};

int main() {
  uint32_t n;
  std::cin >> n;
  Permutation perm(n, "output.txt");
  perm.FindPermutations();
}