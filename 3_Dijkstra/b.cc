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

constexpr int32_t kMax = INT32_MAX;

class Dijkstra {
  public:
    void FillGraph(int32_t n) {
      int32_t el;
      vertex.resize(n + 1);
      for (int32_t i = 0; i < n; ++i) {
        vertex[i].reserve(n);
        for (int32_t j = 0; j < n; ++j) {
          std::cin >> el;
          if (el >= 0 && i != j) {
            vertex[i].push_back({j, el});
          }
        }
      }
      std::vector<std::pair<int32_t, int32_t>> d(n, {kMax, -1});
      dist = std::move(d);  
    }
    
    int32_t FindDist(int32_t start, int32_t finish) {
      dist[start].first = 0;
      queue.insert({dist[start].first, start});
      while (!queue.empty()) {
        int32_t now = queue.begin()->second;
        queue.erase(queue.begin());
        for (uint32_t i = 0; i < vertex[now].size(); ++i) {
          int32_t next = vertex[now][i].first;
          int32_t len = vertex[now][i].second;
          if (dist[now].first + len < dist[next].first) {
            queue.erase({dist[next].first, next});
            dist[next].first = dist[now].first + len;
            dist[next].second = now;
            queue.insert({dist[next].first, next});
          }
        }
      }
      return dist[finish].first == INT32_MAX ? -1 : dist[finish].first;
    }

    std::vector<int32_t> FindWay(int32_t start, int32_t finish) {
      std::vector<int32_t> way;
      if (FindDist(start, finish) == -1) {
        way.push_back(-1);
        return way;
      }
      if (finish == start) {
        way.push_back(finish + 1);
        return way;
      }
      int32_t curr = dist[finish].second;
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
    std::vector<std::vector<std::pair<int32_t, int32_t>>> vertex;
    std::vector<std::pair<int32_t, int32_t>> dist;
    std::set<std::pair<int32_t, int32_t>> queue;
};

int main() {
  int32_t n, s, f;
  std::cin >> n >> s >> f;
  Dijkstra solution;
  solution.FillGraph(n);
  std::vector<int32_t> ans = solution.FindWay(s - 1, f - 1); 
  for (auto el : ans) {
    std::cout << el << " ";
  }
}