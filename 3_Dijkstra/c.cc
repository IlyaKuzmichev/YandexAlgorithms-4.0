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

constexpr int64_t kMax = INT64_MAX;

class Dijkstra {
 public:
  void FillGraph(int64_t n) {
    int64_t el;
    vertex.resize(n);
    for (int64_t i = 0; i < n; ++i) {
      vertex[i].reserve(n);
      for (int64_t j = 0; j < n; ++j) {
        std::cin >> el;
        if (el >= 0 && i != j) {
          vertex[i].push_back({j, el});
        }
      }
    }
    std::vector<std::pair<int64_t, int64_t>> d(n, {kMax, -1});
    dist = std::move(d);
  }

  void NiceInput(int64_t n, int64_t k) {
    int64_t a, b, l;
    vertex.resize(n);
    for (int64_t i = 0; i < k; ++i) {
      std::cin >> a >> b >> l;
      vertex[a - 1].push_back({b - 1, l});
      vertex[b - 1].push_back({a - 1, l});
    }
    std::vector<std::pair<int64_t, int64_t>> d(n, {kMax, -1});
    dist = std::move(d);
  }

  int64_t FindDist(int64_t start, int64_t finish) {
    dist[start].first = 0;
    queue.insert({dist[start].first, start});
    while (!queue.empty()) {
      int64_t now = queue.begin()->second;
      queue.erase(queue.begin());
      for (uint64_t i = 0; i < vertex[now].size(); ++i) {
        int64_t next = vertex[now][i].first;
        int64_t len = vertex[now][i].second;
        if (dist[now].first + len < dist[next].first) {
          queue.erase({dist[next].first, next});
          dist[next].first = dist[now].first + len;
          dist[next].second = now;
          queue.insert({dist[next].first, next});
        }
      }
    }
    return dist[finish].first == kMax ? -1 : dist[finish].first;
  }

  std::vector<int64_t> FindWay(int64_t start, int64_t finish) {
    std::vector<int64_t> way;
    if (FindDist(start, finish) == -1) {
      way.push_back(-1);
      return way;
    }
    if (finish == start) {
      way.push_back(finish + 1);
      return way;
    }
    int64_t curr = dist[finish].second;
    way.push_back(finish + 1);
    while (curr != start) {
      way.push_back(curr + 1);
      curr = dist[curr].second;
    }
    way.push_back(start + 1);
    std::reverse(way.begin(), way.end());
    return way;
  }

 private:
  std::vector<std::vector<std::pair<int64_t, int64_t>>> vertex;
  std::vector<std::pair<int64_t, int64_t>> dist;
  std::set<std::pair<int64_t, int64_t>> queue;
};

int main() {
  int64_t n, k, a, b;
  std::cin >> n >> k;
  Dijkstra solution;
  solution.NiceInput(n, k);
  std::cin >> a >> b;
  std::cout << solution.FindDist(a - 1, b - 1);
}