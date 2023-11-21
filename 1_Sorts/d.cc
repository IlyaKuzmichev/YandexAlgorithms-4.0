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

using pair_it = std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator>;
using vect_it = std::vector<int32_t>::iterator;

std::pair<uint32_t, uint32_t> partition(int32_t predicat, std::vector<int32_t>& vect, uint32_t i, uint32_t j) {
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

int main() {
  uint32_t n;

  std::cin >> n;
  std::vector<int32_t> vect(n);
  for (uint32_t i = 0; i < n; ++i) {
    std::cin >> vect[i];
  }
  mergeSort(vect.begin(), vect.end());
  for (uint32_t i = 0; i < n; ++i) {
    std::cout <<  vect[i] << " ";
  }
}