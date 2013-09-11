//Multiply two integers, given in array format

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void printNumber(int A[], int lA) {
  for (int i = 0; i < lA; ++i) {
    printf("%d", A[i]);
  }
  printf("\n");
}

int * mult(const int A[], const int B[], int lA, int lB, int & lC) {
  lC = lA+lB -1;
  int * C = (int *) malloc(lC * sizeof(int));
  for (int i = 0; i < lC; ++i) {
    C[i] = 0;
  }
  for (int i = lA - 1; i >= 0; --i) {
    for (int j = lB -1 ; j >= 0; --j) {
      int o = (A[i]) * (B[j]);
      int k = i + j;
      while (o != 0) {
	C[k] += o % 10;
	if (C[k] >= 10) {
	  C[k] -= 10;
	  C[k-1] += 1;
	}
	k--;
	o /= 10;
      }
    }
  }
  return C;
}

int * intToArray(int a, int & lO) {
  int t = a;
  lO = 0;
  while (t) {
    lO++;
    t /= 10;
  }
  int * o = new int[lO];
  t = lO-1;
  while (a) {
    o[t--] = a % 10;
    a /= 10;
  }
  
  return o;
}

int main(int argv, char *argc[]) {

  int A[2] = {99, 1123};
  int B[2] = {9, 25};

  for (int i = 0; i < 2; ++i) {
    int lD = 0;
    int * D = intToArray(A[i], lD);
    int lE = 0;
    int * E = intToArray(B[i], lE);
    printNumber(D, lD);
    printf("*\n");
    printNumber(E, lE);
    for (int i = 0; i < fmax(lD, lE) + 1; ++i) {
      printf("-");
    }
    printf("\n");
    int lF = 0;
    int * F = mult(D, E, 4, 2,lF);
    printNumber(F, lF);
    printf("\n");
  }


  return 1;
}
