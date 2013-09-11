#include <vector>
#include <algorithm>
#include <iostream>

template<typename K> std::vector<K> merge(std::vector<K> left, std::vector<K> right) {
  std::vector<K> output;
  typename std::vector<K>::iterator lit = left.begin(), lend = left.end();
  typename std::vector<K>::iterator rit = right.begin(), rend = right.end();

  while (lit != lend && rit != rend) {
    if (*lit < *rit) {
      output.push_back(*(lit++));
    } else {
      output.push_back(*(rit++));
    }
  }
  while (lit != lend) {
    output.push_back(*(lit++));
  }
  while (rit != rend) {
    output.push_back(*(rit++));
  }
  
  return output;
}


template<typename K> std::vector<K> merge_sort(std::vector<K> v) {
  if (v.size() <= 1) return v;
  
  std::vector<K> left(v.size()/2), right(v.size()/2 + v.size()%2);
  int middle = v.size() / 2;

  typename std::vector<K>::iterator b = v.begin(), m = v.begin(), e = v.end();
  std::advance(m, v.size() / 2);

  std::copy(b, m, left.begin());
  std::copy(m, e, right.begin());

  left = merge_sort(left);
  right = merge_sort(right);
  
  return merge(left, right);

}


int main(int argc, char * argv[]) {
  std::cout << "In main" << std::endl;
  std::vector<int> v1;
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(5);
  v1.push_back(3);
  v1.push_back(7);
  v1.push_back(4);
  v1.push_back(9);

  std::cout << "Original vector" << std::endl;
  for (std::vector<int>::iterator it = v1.begin(), itend = v1.end(); it != itend; ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  std::cout << "Perform sort" << std::endl;
  std::vector<int> v2 = merge_sort<int>(v1);

  std::cout << "Sorted vector" << std::endl;
  for (std::vector<int>::iterator it = v2.begin(), itend = v2.end(); it != itend; ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
}
