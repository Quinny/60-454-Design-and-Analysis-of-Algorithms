#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

// Pretty print vector.
void show(const std::vector<int>& v) {
  for (auto i : v) std::cout << i << " ";
  std::cout << std::endl;
}

// Reverse v[i..j].
void flip(std::vector<int>& v, int i, int j) {
  std::reverse(v.begin() + i, v.begin() + j);
}

// Merge two sorted sequences of {0, 1}.
void merge(std::vector<int>& v, int start1, int end1, int start2, int end2) {
  while (v[start1] == 0 && start1 < end1) ++start1;
  // If start1 contains all zeros, then QED.
  if (start1 == end1) return;

  while (v[start2] == 0 && start2 < end2) ++start2;
  flip(v, start1, start2);
}

void flipsort(std::vector<int>& v, int i, int j) {
  int size = j - i;
  // Consider size 1 or less to be sorted.
  if (size > 1) {
    int mid = size / 2;
    // Flip sort the left half.
    flipsort(v, i, i + mid);
    // Flip sort the right half.
    flipsort(v, i + mid, j);
    // Merge the two.
    merge(v, i, i + mid, i + mid, j);
  }
}

int main() {
  std::vector<int> v;
  for (int i = 0; i < 100000; ++i) {
    v.push_back(rand() % 2);
  }
  flipsort(v, 0, v.size());
  assert(std::is_sorted(v.begin(), v.end()));
  // show(v);
}
