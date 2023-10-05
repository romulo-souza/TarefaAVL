#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int id = 0;

link novoNo(int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->id = id++;
  t->altura = 1; // Inicialmente, a altura igual a 1 para o novo no
  return t;
}

Tree createTree() {
  Tree t = malloc(sizeof(struct tree));
  t->z = malloc(sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  t->z->altura = 0;
  return t;
}

int altura(link h) {
  if (h == NULL){
  	return 0;
  } 
  return h->altura;
}

int atualizaAltura(link h) {
  int hl = altura(h->l);
  int hr = altura(h->r);
  return (hl > hr ? hl : hr) + 1;
}

link rotR(Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  h->altura = atualizaAltura(h);
  x->altura = atualizaAltura(x);
  return x;
}

link rotL(Tree t, link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  h->altura = atualizaAltura(h);
  x->altura = atualizaAltura(x);
  return x;
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if(h->item == query)
    return h;
  if(h->item >= query)
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
}

link search(Tree t, int query) {
  return searchR(t, t->head, query);
}

link insertR(Tree t, link h, link n) {
	if(h == t->z){
		return n;
	}
	if(h->item >= n->item){
		h->l = insertR(t, h->l, n);	  
	}
	else{
		h->r = insertR(t, h->r, n);	
	}
	
  h->N++;
  h->altura = atualizaAltura(h);//atualizar altura

  // Verificar o fator de balanceamento para fazer as rotações
  int balance = altura(h->l) - altura(h->r);
  
  // Rotação simples a direita
  if(balance > 1 && n->item < h->l->item){
  	return rotR(t, h);	
  }
  // Rotação simples a esquerda
  if(balance < -1 && n->item > h->r->item){
  	return rotL(t, h);
  }
  // Rotação dupla a esquerda (primeiro uma rotação a direita e depois uma rotação a esquerda)
  if(balance > 1 && n->item > h->l->item){
    h->l = rotL(t, h->l);
    return rotR(t, h);
  }
  // Rotação dupla a direita (primeiro uma rotação a esquerda e depois uma rotação a direita)
  if(balance < -1 && n->item < h->r->item) {
    h->r = rotR(t, h->r);
    return rotL(t, h);
  }

  return h;
}
  
  
link insert(Tree t, int item) {
	if (t->head == t->z){
		return (t->head = novoNo(item, t->z, t->z));
	}
	t->head = insertR(t, t->head, novoNo(item, t->z, t->z));
    return t->head; 
}


void imprimeEmOrdem(Tree t, link h) {
  if (h == t->z) return;
  imprimeEmOrdem(t, h->l);
  printf("<chave: %d N: %d Height: %d>", h->item, h->N, h->altura);
  imprimeEmOrdem(t, h->r);
}

void imprimePosOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimePosOrdem (t, h->l);
  imprimePosOrdem (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}
void imprimePreOrdem (Tree t, link h, int k) {
  if(h == t->z) return;
  for(int i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  imprimePreOrdem (t, h->l, k + 1); 
  imprimePreOrdem (t, h->r, k + 1);
}


void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}
int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}

