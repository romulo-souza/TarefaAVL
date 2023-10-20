#include <stdio.h>
#include "bst.h"

int main() {
  Tree t = createTree();
  link x;
  insert(t, 99);
  insert(t, 88);
  insert(t, 77);
  insert(t, 75);
  insert(t, 74);
  insert(t, 73);
  insert(t, 100);
  insert(t, 101);
  insert(t, 102);
  
  imprime(t, "oi");

  return 0;
} 
