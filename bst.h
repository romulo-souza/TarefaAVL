#ifndef BST_H
#define BST_H

typedef struct node *link;
struct node {
  link l;
  link r;
  int item;
  int N;      // quantidade de nos na subarvore
  int id;     // id do no
  int altura; // altura da subarvore que esta enraizada nesse no
};

typedef struct tree {
  link head; // raiz
  link z;    // no externo
} * Tree;

Tree createTree();
link rotR(Tree t, link h);
link rotL(Tree t, link h);
link search(Tree h, int query);
link insert(Tree h, int item);
void imprimeEmOrdem(Tree t, link h);
void imprimePosOrdem(Tree t, link h);
void imprimePreOrdem(Tree t, link h, int k);
void imprime(Tree a, char *s);

#endif
