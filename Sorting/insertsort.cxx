#include <stdio.h>

void insertsort(int * arr, int len) {
  for (int i = 1; i < len; ++i) {
    if (arr[i] >= arr[i-1]) continue;
    int j = i;
    int curr = arr[i];
    while(j > 0 && arr[j-1] > curr) {
      arr[j] = arr[j-1];
      --j;
    }
    arr[j] = curr;
  }
}

void printArr(int * arr, int len) {
  for (int i = 0; i < len; ++i) {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}

int main(int argc, char * argv[]) {
  const int len = 5;
  int arr[len] = {6, 5, 7, 9, 8};

  printArr(arr, len);
  insertsort(arr, len);
  printArr(arr, len);
}
