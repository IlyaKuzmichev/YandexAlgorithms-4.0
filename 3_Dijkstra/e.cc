#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
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
using myPair = std::pair<double, int32_t>;

void dfs(std::vector<std::vector<double>>& graph,
         std::vector<std::vector<std::pair<int32_t, double>>>& roads,
         std::vector<bool>& visited, int32_t start, int32_t v) {
  visited[v] = true;
  for (auto el : roads[v]) {
    if (visited[el.first] == false) {
      graph[start][el.first] = graph[start][v] + el.second;
      graph[el.first][start] = graph[start][el.first];
      dfs(graph, roads, visited, start, el.first);
    }
  }
}

int main() {
  int32_t n;
  std::cin >> n;

  std::vector<std::pair<double, double>> speed(n + 1, {0, 0});
  int32_t t, v;
  for (int32_t i = 1; i < n + 1; ++i) {
    std::cin >> t >> v;
    speed[i] = {t, v};
  }

  std::vector<std::vector<std::pair<int32_t, double>>> roads(n + 1);
  int32_t a, b;
  double s;
  for (int32_t i = 1; i < n; ++i) {
    std::cin >> a >> b >> s;
    roads[a].push_back({b, s});
    roads[b].push_back({a, s});
  }

  std::vector<std::vector<double>> dist(n + 1, std::vector<double>(n + 1, 0));
  for (int32_t i = 1; i < n + 1; ++i) {
    std::vector<bool> visited(n + 1, false);
    dfs(dist, roads, visited, i, i);
  }

  std::vector<double> time(n + 1, 0.);
  for (int32_t i = 2; i < n + 1; ++i) {
    time[i] = dist[i][1] / speed[i].second + speed[i].first;
  }

  std::vector<std::pair<bool, int32_t>> visited(n + 1, {false, 1});

  while (true) {
    int32_t now = n + 1;
    double nowTime = INFINITY;
    for (int32_t i = 1; i < n + 1; ++i) {
      if (!visited[i].first && time[i] < nowTime) {
        now = i;
        nowTime = time[i];
      }
    }
    if (now == n + 1) {
      break;
    }
    visited[now].first = true;
    for (int32_t i = 2; i < n + 1; ++i) {
      if (i == now) {
        continue;
      }
      double nextTime =
          nowTime + speed[i].first + dist[now][i] / speed[i].second;
      if (nextTime < time[i]) {
        time[i] = nextTime;
        visited[i].second = now;
      }
    }
  }
  double maxTime = 0;
  int32_t maxInd = 0;
  for (int32_t i = 2; i < n + 1; ++i) {
    if (time[i] > maxTime) {
      maxTime = time[i];
      maxInd = i;
    }
  }

  std::cout << std::setprecision(10) << maxTime << std::endl;
  int32_t curr = maxInd;
  while (curr != 1) {
    std::cout << curr << " ";
    curr = visited[curr].second;
  }
  std::cout << 1 << std::endl;
}
