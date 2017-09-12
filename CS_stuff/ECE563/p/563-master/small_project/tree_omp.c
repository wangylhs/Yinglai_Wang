/******************************************************************************
* FILE: tree_opm.c
* DESCRIPTION:
*   OpenMP Tree Search
*   This program will generate a binary tree sorted by name, and then search it
*   to identify all of the people within the tree that have a certain age and
*   return their names.
*
*   The program will also analyze the time differences depending on if a parallel
*   or sequential algorithm is used.
*
* AUTHOR: Nathan Tornquist 2/15
* LAST REVISED: 02/09/15
*
* On OSX:
* g++-4.9 -o tree_omp -fopenmp tree_omp.c
*
* On EceGrid:
* gcc -o tree_omp -fopenmp tree_omp.c
*
* FAQ:
*
* How does this work?
*   It does a breadth first search to generate multiple root nodes, then
*   assigns each root node to a core to distribute the work?
*
* How do I configure it?
*   Change the variables at the top of the main function.
*
* How do I compile it?
*   See above, I have osx options and ecegrid.  OSX uses the current version
*   of gcc installed with brew.
*
* How do I run it?
*   Execute the compiled file.  ./tree_omp after compiling.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

long long current_timestamp();

struct Node {
  char *name;
  int age;
  struct Node *left;
  struct Node *right;
};
typedef struct Node node;

struct List {
  node * value;
  struct List * next;
};
typedef struct List list;

struct TwoLists {
  list * list_1;
  list * list_2;
};
typedef struct TwoLists two_lists;

list * addToList(list * top, node * value) {
  list * newItem = (list*)malloc(sizeof(list));
  newItem->next = top;
  newItem->value = value;
  return newItem;
}

char * getName() {
  char *name;
  name = (char *) malloc(5*sizeof(char));
  int i = 0;
  for (i = 0; i < 5; i++) {
    name[i] = rand()%75 + 48;
  }
  return name;
}

int getAge() {
  return rand()%80;
}

node * newNode() {
  node* root = (node *)malloc(sizeof(node));
  root->age = getAge();
  root->name = getName();
  root->left = NULL;
  root->right = NULL;
  return root;
}


node * addNode(node* tree, node * node) {
  if (tree == NULL) {
    return node;
  } else {
    if (strcmp(node->name, tree->name) < 0)
    {
      tree->left = addNode(tree->left, node);
    }
    else {
      tree->right = addNode(tree->right, node);
    }
  }
  return tree;
}

void print_tree(node * root) {
  if (root) {
    print_tree(root->left);
    printf("%s %d\n", root->name, root->age);
    print_tree(root->right);
  }
}

void freeTree(node * tree) {
  if (tree) {
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree->name);
    free(tree);
  }
}

list * search_tree(node * tree, int age, list * list) {
  if (tree) {
    list = search_tree(tree->left, age, list);
    if (age == tree->age) {
      list = addToList(list, tree);
    }
    list = search_tree(tree->right, age, list);
  }
  return list;
}

void deleteList(list * listroot){
  if (listroot)
  {
    deleteList(listroot->next);
    free(listroot);
  }
}

int lenList(list * listroot) {
  if (listroot) {
    return 1 + lenList(listroot->next);
  }
  return 0;
}

void printList(list * listNodes) {
  while (listNodes != NULL)
  {
    printf("%s %d\n", (listNodes->value)->name, (listNodes->value)->age);
    listNodes = listNodes->next;
  }
}

two_lists generateStartingPoint(node * tree, list * search, int searchAge, int cores) {
  list* startList = NULL;
  startList = addToList(startList,tree);
  while (lenList(startList) != cores) {
    list * lastNode = startList;
    if (lenList(startList) == 1)
    {
      //First Case only
      if ((lastNode->value)->age == searchAge) {
        search = addToList(search, lastNode->value);
      }
      node * right = (lastNode->value)->right;
      node * left = (lastNode->value)->left;
      startList = NULL;
      startList = addToList(startList, right);
      startList = addToList(startList, left);
      free(lastNode);
    }
    else {
      //Common Case
      while ((lastNode -> next) -> next != NULL)
      {
        lastNode = lastNode -> next;
      }
      list * final = (lastNode -> next);
      lastNode -> next = NULL;
      if ((final->value)->age == searchAge) {
        search = addToList(search, final->value);
      }
      node * right = (final->value)->right;
      node * left = (final->value)->left;
      free(final);
      startList = addToList(startList, right);
      startList = addToList(startList, left);
    }
  }
  two_lists lists;
  lists.list_1 = startList;
  lists.list_2 = search;
  return lists;
}

int main (int argc, char *argv[])
{
  int i;
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int cores = 16;
  int nodes = 10000000;
  int searchAge = 25;

  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  omp_set_dynamic(0);     // Disable Dynamic Threads
  omp_set_num_threads(cores); // Set Num Threads (change for benchmarking)

  // Initialize a, b, and c matrices
  int seed = time(NULL);
  srand(seed);

  printf("Generating Tree\n");
  node *tree = NULL;
  i = 0;
  while (i < nodes) {
    tree = addNode(tree, newNode());
    i++;
  }

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time_1, time_2;

  printf("Starting Parallel Operation\n");
  t1 = current_timestamp();

  //////////////////////////////////////////////////////////////////////
  //////////////////////// START PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  node * topNodes[cores];
  list * listNodes_par[cores];
  for (i = 0; i < cores; i++)
  {
    listNodes_par[i] = NULL;
  }
  two_lists lists = generateStartingPoint(tree, listNodes_par[0], searchAge, cores);
  list * startingPoint = lists.list_1;
  listNodes_par[0] = lists.list_2;
  for (i = 0; i < cores; i++)
  {
    topNodes[i] = startingPoint->value;
    list * temp = startingPoint;
    startingPoint = startingPoint -> next;
    free(temp);
  }

  #pragma omp parallel shared(listNodes_par, topNodes)
  {
    int pid = omp_get_thread_num();
    listNodes_par[pid] = search_tree(topNodes[pid], searchAge, listNodes_par[pid]);
  }
  //Combine Lists
  for (i = 0; i < cores; i++){
    printf("Core %d matches: %d\n", i, lenList(listNodes_par[i]));
  }
  list * listNodes_par_comb = NULL;
  for (i = 0; i < cores; i++){
    if (listNodes_par_comb == NULL){
      listNodes_par_comb = listNodes_par[i];
    }else {
      if (listNodes_par[i] != NULL) {
        list * tempTop = listNodes_par_comb;
        while (tempTop->next != NULL)
        {
          tempTop = tempTop->next;
        }
        tempTop->next = listNodes_par[i];
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  t2 = current_timestamp();
  time_1 = t2 - t1;

  printf("Search Completed\n");
  printf("Generating Solution for Verification\n");

  t1 = current_timestamp();
  //Sequential Program
  list * listNodes = NULL;
  listNodes = search_tree(tree, searchAge, listNodes);
  t2 = current_timestamp();
  time_2 = t2 - t1;

  //VERIFY SOLUTION
  printf("Verifying Solution\n\n");
  int miss = lenList(listNodes) - lenList(listNodes_par_comb);

  printf("Results:\n");
  if (miss != 0) {
    printf("Solution: Invalid\n");
    printf("Sequential Matches: %d\n", lenList(listNodes));
    printf("Parallel Matches:   %d\n", lenList(listNodes_par_comb));
  }
  else {
    printf("Solution: Valid\n");
    printf("Sequential Matches: %d\n", lenList(listNodes));
    printf("Parallel Matches:   %d\n", lenList(listNodes_par_comb));
    printf("Parallel:   %f s\n", ((float)time_1)/1000);;
    printf("Sequential: %f s\n", ((float)time_2)/1000);;
    printf("Speedup: %.2f %%\n", (100*((float)time_2)/((float)time_1)));
    printf("Cores: %d\n", cores);
  }
  freeTree(tree);
}

//FROM a StackOverflow article on calculating accurate times
//http://stackoverflow.com/questions/3756323/getting-the-current-time-in-milliseconds
long long current_timestamp() {
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
  //printf("milliseconds: %lld\n", milliseconds);
  return milliseconds;
}
