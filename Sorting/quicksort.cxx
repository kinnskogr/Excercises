#include <vector>
#include <iostream>

template<typename K> std::vector<K> quicksort(std::vector<K> &v) {
  if (v.size() <= 1)
    return v;

  typename std::vector<K>::iterator pivot = v.begin();
  std::advance(pivot, v.size() / 2);

  std::vector<K> left, right;
  for (typename std::vector<K>::iterator it = v.begin(), it_end = v.end(); it != it_end; ++it) {
    if (it == pivot) {
      continue;
    }
    if (*it <= *pivot) {
      left.push_back(*it);
    } else {
      right.push_back(*it);
    }
  }
  
  left = quicksort(left);
  right = quicksort(right);

  std::vector<K> output;
  output.reserve(v.size());

  output.insert(output.end(), left.begin(), left.end());
  output.push_back(*pivot);
  output.insert(output.end(), right.begin(), right.end());
  
  return output;

}

template<typename K> typename std::vector<K>::iterator partition(std::vector<K> &v, typename std::vector<K>::iterator left, typename std::vector<K>::iterator right, typename std::vector<K>::iterator pivot) {
  K pValue = *pivot;

  if (right - left <= 1) 
    return left;

  std::iter_swap(pivot, right-1);
  typename std::vector<K>::iterator store = left;
  for (typename std::vector<K>::iterator it = left; it != right-1; ++it) {
    if (*it < pValue) {
      std::iter_swap(it, store);
      store++;
    }
  }
  std::iter_swap(store, right-1);
  return store;
}

template<typename K> void inplace_quicksort(std::vector<K> &v, typename std::vector<K>::iterator left, typename std::vector<K>::iterator right) {
  if (right - left <= 1)
    return;

  typename std::vector<K>::iterator pivot = left;
  std::advance(pivot, (right - left) / 2);

  typename std::vector<K>::iterator pivotNew = partition(v, left, right, pivot);
  inplace_quicksort(v, left, pivotNew);
  inplace_quicksort(v, pivotNew + 1, right);
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
  std::vector<int> v2 = quicksort<int>(v1);

  std::cout << "Sorted vector" << std::endl;
  for (std::vector<int>::iterator it = v2.begin(), itend = v2.end(); it != itend; ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;

  std::cout << "Perform inplace sort" << std::endl;
  inplace_quicksort<int>(v1, v1.begin(), v1.end());

  std::cout << "Sorted vector" << std::endl;
  for (std::vector<int>::iterator it = v1.begin(), itend = v1.end(); it != itend; ++it) {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;


}


