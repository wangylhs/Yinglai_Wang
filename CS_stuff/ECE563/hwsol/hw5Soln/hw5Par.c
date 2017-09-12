#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

struct node {
   float val;
   struct node* l;
   struct node* r;
} nodeT;

#define MAXLEVEL 18

int lg2(int k) {
   int c = 0;
   while (k > 1) {
      k = k/2;
      c++;
   }
   return c;
}

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

// a sequential traversal of a subtree done by a task.
void traverse(struct node* p, int c[ ], int tid) {
   if (p == NULL) return;
   if (p->val < 0.5) c[tid] = c[tid]+1;
   if (p->l == NULL) return;
   else {
      traverse(p->l, c, tid);
   }
   if (p->r == NULL) return;
   else {
      traverse(p->r, c, tid);
   }
}

// a sequential traversal of the tree until lvl is 0
// and then we spawn a task to traverse the left and 
// right subtree.
void spawn(struct node* p, int lvl, int c[ ], int* tid) {
   if (p == NULL) return;
   if (p->val < 0.5) c[0] += c[0];
   if (lvl == 0) {
      int ltid, rtid;
      if (p->l != NULL) { 
         int ltid = *tid;
         *tid = ++ltid;
         #pragma omp task
         traverse(p->l, c, ltid);
      }
      if (p->r != NULL) {
         int rtid = *tid;
         *tid = ++rtid;
         #pragma omp task
         traverse(p->r, c, rtid);
      }
   } else {
      spawn(p->l, lvl-1, c, tid);
      spawn(p->r, lvl-1, c, tid);
   }
}

int main( ) {

   struct node* h = build(0);
   double t = -omp_get_wtime( );
   int SIZE = 16;
   int count[SIZE];
   int tid = 0;
   int i;

   for (i = 0; i < SIZE; i++) count[i] = 0;

   omp_set_num_threads(SIZE);
   t = -omp_get_wtime( );
   #pragma omp parallel
   {
      #pragma omp single
      {
         int l2 = lg2(omp_get_num_threads( )); 
         fflush(stdout);
         spawn(h, l2-1, count, &tid); 
      }
   }

   for (i = 1; i < SIZE; i++) {
      count[0] += count[i];
   }
   t += omp_get_wtime( );
      
   printf("count: %d\n", count[0]);
   printf("time: %2f\n", t);
}
