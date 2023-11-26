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
  Solution(uint32_t n) : n_(n) {
    graph_.resize(n + 1);
    minEdges.resize(n + 1, INT32_MAX);
    int32_t el;

    for (uint32_t i = 1; i <= n; ++i) {
      for (uint32_t j = 1; j <= n; ++j) {
        std::cin >> el;
        if (el != 0) {
          graph_[i].push_back({j, el});
          if (minEdges[i] > el) {
            minEdges[i] = el;
          }
        }
      }
    }
    for (uint32_t i = 1; i <= n; ++i) {
      sumMinEdges += minEdges[i];
      if (minEdges[i] < minEdge) {
        minEdge = minEdges[i];
      }
    }
  }

  void RecursiveSalesman(int32_t now, std::unordered_set<int32_t>& visited) {
    if (ansCurr + sumMinEdges > ans) {
      return;
    }

    if (visited.size() == n_) {
      for (auto neig : graph_[now]) {
        if (neig.first == 1) {
          if (ansCurr + neig.second < ans) {
            ans = ansCurr + neig.second;
          }
          return;
        }
      }
    }

    for (auto neig : graph_[now]) {
      if (visited.find(neig.first) == visited.end()) {
        if (ansCurr +
                minEdge * (static_cast<int32_t>(n_ - visited.size()) + 1) >
            ans) {
          continue;
        }

        visited.insert(neig.first);
        sumMinEdges -= minEdges[now];
        ansCurr += neig.second;
        RecursiveSalesman(neig.first, visited);
        visited.erase(neig.first);
        sumMinEdges += minEdges[now];
        ansCurr -= neig.second;
      }
    }
  }

  int32_t TravelingSalesman() {
    if (n_ == 1) {
      return 0;
    }
    std::unordered_set<int32_t> visited;
    visited.insert(1);
    RecursiveSalesman(1, visited);
    if (ans == INT32_MAX) {
      ans = -1;
    }
    return ans;
  }

 private:
  uint32_t n_;
  vectGr graph_;
  std::vector<int32_t> minEdges;
  int32_t sumMinEdges = 0;
  int32_t minEdge = INT32_MAX;
  int32_t ans = INT32_MAX;
  int32_t ansCurr = 0;
};

int main() {
  uint32_t n;
  std::cin >> n;
  Solution sl(n);
  std::cout << sl.TravelingSalesman() << std::endl;
}