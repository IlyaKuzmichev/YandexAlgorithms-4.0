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

using bool_v = std::vector<bool>;

class Dinosaurs {
 public:
  Dinosaurs(uint32_t n) : field_(n) {}

  void Recurisive(uint32_t ind, bool_v& str, bool_v& mainD, bool_v& sideD) {
    ++ind;

    for (uint32_t i = 0; i < field_; ++i) {
      if (str[i] || mainD[field_ + i - ind] || sideD[i + ind]) {
        continue;
      } else if (ind == field_) {
        ans_ += 1;
        return;
      }
      str[i] = true;
      mainD[field_ + i - ind] = true;
      sideD[i + ind] = true;
      Recurisive(ind, str, mainD, sideD);
      str[i] = false;
      mainD[field_ + i - ind] = false;
      sideD[i + ind] = false;
    }
  }

  uint32_t GetAns() {
    bool_v str(field_ + 1, false), mainD(2 * field_ + 1, false),
        sideD(2 * field_ + 1, false);

    Recurisive(0, str, mainD, sideD);
    return ans_;
  }

 private:
  uint32_t field_;
  uint32_t ans_ = 0;
};

int main() {
  uint32_t n;
  std::cin >> n;
  Dinosaurs d(n);

  std::cout << d.GetAns() << std::endl;
}