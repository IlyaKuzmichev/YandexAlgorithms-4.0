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

using pair_it =
    std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator>;
using vect_it = std::vector<int32_t>::iterator;

std::pair<uint32_t, uint32_t> partition(int32_t predicat,
                                        std::vector<int32_t>& vect, uint32_t i,
                                        uint32_t j) {
  uint32_t eq = i, gt = i, now = i;
  int32_t buf;
  while (now < j) {
    if (vect[now] < predicat) {
      buf = vect[now];
      vect[now] = vect[gt];
      vect[gt] = vect[eq];
      vect[eq] = buf;
      ++gt;
      ++eq;
    } else if (vect[now] == predicat) {
      std::swap(vect[now], vect[gt]);
      ++gt;
    }
    ++now;
  }
  return {eq, gt};
}

void quicksort(std::vector<int32_t>& vect, uint32_t i, uint32_t j) {
  if (i >= j) {
    return;
  }
  int32_t predicat = vect[i + (rand() % (j - i))];
  std::pair<uint32_t, uint32_t> p = partition(predicat, vect, i, j);
  quicksort(vect, i, p.first);
  quicksort(vect, p.second, j);
}

void merge(pair_it left, pair_it right, vect_it place) {
  while (left.first < left.second || right.first < right.second) {
    if (left.first == left.second) {
      *place = *right.first;
      ++right.first;
    } else if (right.first == right.second) {
      *place = *left.first;
      ++left.first;
    } else {
      if (*right.first < *left.first) {
        *place = *right.first;
        ++right.first;
      } else {
        *place = *left.first;
        ++left.first;
      }
    }
    ++place;
  }
}

void mergeCore(std::vector<int32_t>& tmp, vect_it begin, vect_it end) {
  uint32_t size = std::distance(begin, end);
  if (size <= 1) {
    return;
  }

  vect_it middle = begin + size / 2;
  mergeCore(tmp, begin, middle);
  mergeCore(tmp, middle, end);
  merge({begin, middle}, {middle, end}, tmp.begin());

  std::copy(tmp.begin(), tmp.begin() + size, begin);
}

void mergeSort(vect_it begin, vect_it end) {
  std::vector<int32_t> temp(end - begin);

  mergeCore(temp, begin, end);
}

void fill_buckets(uint16_t digit, std::vector<std::string>& arr,
                  std::vector<std::queue<std::string>>& buckets) {
  uint16_t ind = arr[0].size() - digit - 1;
  for (uint16_t i = 0; i < arr.size(); ++i) {
    buckets[arr[i][ind] - '0'].push(arr[i]);
  }
}

void free_buckets(std::vector<std::string>& arr,
                  std::vector<std::queue<std::string>>& buckets) {
  uint16_t ind = 0;
  for (uint16_t i = 0; i < buckets.size(); ++i) {
    while (!buckets[i].empty()) {
      arr[ind] = buckets[i].front();
      buckets[i].pop();
      ++ind;
    }
  }
}

void bitwiseSort(std::vector<std::string> arr) {
  std::vector<std::queue<std::string>> buckets(10);

  std::cout << "Initial array:" << std::endl;
  for (uint32_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i];
    if (i != arr.size() - 1) {
      std::cout << ", ";
    } else {
      std::cout << std::endl;
    }
  }
  std::cout << "**********" << std::endl;
  for (uint16_t i = 0; i < arr[0].size(); ++i) {
    fill_buckets(i, arr, buckets);
    uint16_t ind = 0;

    std::cout << "Phase " << i + 1 << std::endl;
    for (uint16_t i = 0; i < buckets.size(); ++i) {
      std::cout << "Bucket " << i << ": ";
      if (buckets[i].empty()) {
        std::cout << "empty" << std::endl;
      } else {
        while (!buckets[i].empty()) {
          arr[ind] = buckets[i].front();
          buckets[i].pop();
          std::cout << arr[ind];
          ++ind;
          if (buckets[i].empty()) {
            std::cout << std::endl;
          } else {
            std::cout << ", ";
          }
        }
      }
    }
    std::cout << "**********" << std::endl;
  }
  std::cout << "Sorted array:" << std::endl;
  for (uint32_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i];
    if (i != arr.size() - 1) {
      std::cout << ", ";
    } else {
      std::cout << std::endl;
    }
  }
}

int main() {
  uint16_t n;

  std::cin >> n;
  std::vector<std::string> vect(n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> vect[i];
  }
  bitwiseSort(vect);
}