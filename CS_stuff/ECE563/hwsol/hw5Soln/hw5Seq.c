#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

struct node {
   float val;
   struct node* l;
   struct node* r;
} nodeT;

#define MAXLEVEL 18

struct node* build(int level) {

   if (level < MAXLEVEL) {
      struct node* p = (struct node*) malloc(sizeof(nodeT));
      p->val = (double)rand() / (double)((unsigned)RAND_MAX + 1);
      p->l = build(level+1);
      p->r = build(level+1);
      return p;
   } else {
      return NULL;
  }
}

void traverse(struct node* p, int* c) {
   if (p == NULL) return;
   if (p->l == NULL) return;
   else {
      if (p->val < 0.5) *c = *c+1;
      traverse(p->l, c);
   }
   if (p->r == NULL) return;
   else {
      if (p->val < 0.5) *c = *c+1;
      traverse(p->r, c);
   }
}

int main( ) {

   struct node* h = build(0);
   int c = 0;
   double t = -omp_get_wtime( );
   traverse(h, &c);
   t += omp_get_wtime( );
   printf("count: %d\n", c);
   printf("time: %2f\n", t);


}

