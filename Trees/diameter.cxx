//Given a tree in the form of parent pointers of every node (for root assume parent pointer to be null), write code to find the diameter of tree (i.e. longest length)

#include <stdio.h>

/*
              10
          4        15
      2       8

Longest path = 15 -> 10 -> 4 -> 2

              10
          4        15
      2       8
    1            9

Longest path = 1 -> 2 -> 4 -> 8 -> 9

*/

struct node {
  int V;
  node * L;
  node * R;
};

void findDiameter(node * n, int &max_depth, int &max_diameter) {
  int l_depth = 0;
  int r_depth = 0;
  int l_diameter = 0;
  int r_diameter = 0;
  if (n->L != NULL) findDiameter(n->L, l_depth, l_diameter);
  if (n->R != NULL) findDiameter(n->R, r_depth, r_diameter);
  int diameter = l_depth + 1 + r_depth;

  max_depth += l_depth > r_depth ? l_depth : r_depth;
  max_depth++;
  max_diameter = max_diameter > diameter ? max_diameter : diameter;
  max_diameter = max_diameter > l_diameter ? max_diameter : l_diameter;
  max_diameter = max_diameter > r_diameter ? max_diameter : r_diameter;
  
  printf("Check %d, diameter = %d, max_depth = %d \n", n->V, diameter, max_depth);

}

void printTree(node * n, int level = 0) {
  if (n->L != NULL) printTree(n->L, level + 1);
  for (int i = 0; i < level; ++i) {
    printf("  ");
  }
  printf("%d\n", n->V);
  if (n->R != NULL) printTree(n->R, level + 1);
}


int main(int argc, char * argv[]) {
  node * root = new node();
  root->V = 10;
  root->L = new node();
  root->L->V = 4;
  root->L->L = new node();
  root->L->L->V = 2;
  root->L->R = new node();
  root->L->R->V = 8;
  root->R = new node();
  root->R->V = 15;

  /* root->L->L->L = new node(); */
  /* root->L->L->L->V = 1; */
  /* root->L->R->R = new node(); */
  /* root->L->R->R->V = 9; */
  
  printTree(root);

  int max_depth = 0;
  int max_diameter = 0;
  findDiameter(root, max_depth, max_diameter);
  printf("Max diameter = %d\n", max_diameter);
}
