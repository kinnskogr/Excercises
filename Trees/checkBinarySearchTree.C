//Given a binary tree input, check that the daughters are all valid

#include <stdio.h>
#include <limits.h>

class node {
public:
  int V;
  node * L;
  node * R;
  node(int v, node * l = NULL, node * r = NULL);
  ~node();
};

node::node(int v, node * l, node * r) {
  V = v;
  if (l != NULL) L = l;
  if (r != NULL) R = r;
}

node::~node() {
  if (L != NULL) delete L;
  if (R != NULL) delete R;
  L = NULL;
  R = NULL;
}

bool isValid(node * n, int low, int high) {
  if (n->V < low || n->V > high) return false;
  bool output = true;
  if (n->L != NULL) output &= isValid(n->L, low, n->V);
  if (n->R != NULL) output &= isValid(n->R, n->V, high);
  return output;
}

void printTree(node * n, int level = 0) {
  if (n->L != NULL) printTree(n->L, level + 1);
  for (int i = 0; i < level; ++i) {
    printf("  ");
  }
  printf("%d\n", n->V);
  if (n->R != NULL) printTree(n->R, level + 1);
}

/* Tree looks like:
                    10
                 4         15
              2   50
*/

int main(int argc, char * argv[]) {
  node * root = new node(10);
  root->L = new node(4);
  root->L->L = new node(2);
  root->L->R = new node(50);
  root->R = new node(15);

  printTree(root);

  bool result = isValid(root, -INT_MAX, INT_MAX);
  printf("Result is %i\n", result);

  delete root;
  
  root = new node(10);
  root->L = new node(4);
  root->L->L = new node(2);
  root->L->R = new node(9);
  root->R = new node(15);

  printTree(root);

  result = isValid(root, -INT_MAX, INT_MAX);
  printf("Result is %i\n", result);

  delete root;

}
