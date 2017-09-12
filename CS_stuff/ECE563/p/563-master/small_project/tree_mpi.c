/******************************************************************************
* FILE: tree_mpi.c
* DESCRIPTION:
*   MPI Tree Search
*   This program will generate a binary tree sorted by name, and then search it
*   to identify all of the people within the tree that have a certain age and
*   return their names.
*
*   The program will also analyze the time differences depending on if a parallel
*   or sequential algorithm is used.
*
* AUTHOR: Nathan Tornquist 3/24
* LAST REVISED: 03/04/15
*
* Compile the program:
* mpicc tree_mpi.c -o tree_mpi
*
* Execute the program:
* qsub -l nodes=1:ppn=16,walltime=00:01:00 ./tree_mpi.sub
******************************************************************************/
#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

long long current_timestamp();

struct Node {
  int value;
  struct Node *left;
  struct Node *right;
};
typedef struct Node node;

int getValue() {
  return rand()%100;
}

node * newNode() {
  node* root = (node *)malloc(sizeof(node));
  root->value = getValue();
  root->left = NULL;
  root->right = NULL;
  return root;
}

node * generateTree(node * parent, int depth) {
  if (depth <= 0) { return NULL; }
  if (parent == NULL) {
    parent = newNode();
  }
  node * temp1 = newNode();
  node * temp2 = newNode();
  parent->left = temp1;
  parent->right = temp2;
  generateTree(temp1, depth - 1);
  generateTree(temp2, depth - 1);
  return parent;
}

void freeTree(node * tree) {
  if (tree) {
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
  }
}

void printTree(node * tree) {
  if (tree == NULL) { return; }
  printf("%d ", tree->value);
  if (tree->left == NULL) {
    printf("() ");
  } else {
    printf("(");
    printTree(tree->left);
    printf(") ");
  }

  if (tree->right == NULL) {
    printf("()");
  } else {
    printf("(");
    printTree(tree->right);
    printf(")");
  }
}

void fprintTree(node * tree, FILE * file) {
  if (tree == NULL) { return; }
  fprintf(file, "%d ", tree->value);
  if (tree->left == NULL) {
    fprintf(file, "() ");
  } else {
    fprintf(file, "(");
    fprintTree(tree->left, file);
    fprintf(file, ") ");
  }

  if (tree->right == NULL) {
    fprintf(file, "()");
  } else {
    fprintf(file, "(");
    fprintTree(tree->right, file);
    fprintf(file, ")");
  }
}

int scanSubFile(FILE * file, int min, int max, int start, int end, int rank, int size) {
  //Adjust Start (Make sure whole numbers in each range)
  if (rank != 0) {
    while (1) {
      fseek(file, start, SEEK_SET);
      char temp = fgetc(file);
      if (temp == '(' || temp == ')' || temp == ' ') { break; }
      start = start - 1;
    }
  }
  //Adjust End (Major sure whole numbers in each range)
  if (rank != size - 1) {
    while (1) {
      fseek(file, end, SEEK_SET);
      char temp = fgetc(file);
      if (temp == '(' || temp == ')' || temp == ' ') { break; }
      end = end - 1;
    }
  }

  fseek(file, start, SEEK_SET);
  char c;
  int count = 0;
  char tempArray[5] = {' ', ' ', ' ', ' ', '\0'};
  int arrayIndex = 0;
  while (ftell(file) <= end) {
    c = fgetc(file);
    if (c == '(' || c == ')' || c == ' ')
    {
      if (arrayIndex > 0){
        tempArray[arrayIndex] = '\0';
        int test = atoi(tempArray);
        if (test >= min && test <= max)
        {
          count = count + 1;
        }
        arrayIndex = 0;
      }
    } else
    {
      tempArray[arrayIndex] = c;
      arrayIndex = arrayIndex + 1;
    }
  }
  return count;
}

int main (int argc, char *argv[])
{
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int depth = 21;
  int min = 0;
  int max = 10;

  /* MPI Parameters */
  int rank, size, len;
  MPI_Init(&argc, &argv);                 /* start MPI           */
  MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */

  int i, j = 0;
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // Initialize a, b, and c matrices
  int seed = time(NULL);
  srand(seed);

  int totalMatches = 0;

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time_1, time_2;
  if (rank == 0){
    printf("/////////////////////////////////////////////////////////////////\n");
    printf("/////////////////////////////////////////////////////////////////\n");
    printf("/////////////////////////////////////////////////////////////////\n");
    node * tree;
    printf("Generating Tree\n");
    tree = generateTree(NULL, depth);
    FILE * file;
    file = fopen("binary_tree.txt", "w");
    printf("Printing Tree to File\n");
    fprintTree(tree, file);
    fclose(file);

    printf("Starting Parallel Operation\n");
    t1 = current_timestamp();
    //////////////////////////////////////////////////////////////////////
    //////////////////////// START PARALLEL LOGIC ////////////////////////
    //////////////////////////////////////////////////////////////////////
    file = fopen("binary_tree.txt", "rb");
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fclose(file);
    printf("Characters: %d\n", fileSize);
    printf("P # | Start - End | Matches\n");
    MPI_Bcast(&fileSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int interval = fileSize/size;
    int start_position = rank*interval;
    int end_position = (rank+1)*interval - 1;

    file = fopen("binary_tree.txt","r");
    int matches = scanSubFile(file, min, max, start_position, end_position, rank, size);
    fclose(file);

    printf("P %d | %d - %d | %d\n",rank,start_position,end_position, matches);

    MPI_Reduce(&matches, &totalMatches, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("Total Matches: %d\n", totalMatches);
    //////////////////////////////////////////////////////////////////////
    ////////////////////////// END PARALLEL LOGIC ////////////////////////
    //////////////////////////////////////////////////////////////////////
    t2 = current_timestamp();
    time_1 = t2 - t1;

    printf("Search Completed\n");
    printf("Generating Solution for Verification\n");

    t1 = current_timestamp();
    //Single Core logic
    file = fopen("binary_tree.txt","r");
    matches = scanSubFile(file, min, max, 0, fileSize, 0, 0);
    fclose(file);
    t2 = current_timestamp();
    time_2 = t2 - t1;

    //VERIFY SOLUTION
    printf("Verifying Solution\n\n");
    int miss = 0;

    printf("Results:\n");
    if (matches != totalMatches) {
      printf("Solution: Invalid\n");
      printf("Sequential Matches: %d\n", matches);
      printf("Parallel Matches:   %d\n", totalMatches);
    }
    else {
      printf("Solution: Valid\n");
      printf("Sequential Matches: %d\n", matches);
      printf("Parallel Matches:   %d\n", totalMatches);
      printf("Parallel:   %f s\n", ((float)time_1)/1000);;
      printf("Sequential: %f s\n", ((float)time_2)/1000);;
      printf("Speedup: %.2f %%\n", (100*((float)time_2)/((float)time_1)));
      printf("Threads: %d\n", size);
    }
    freeTree(tree);
  }
  else {
    //Non rank 0 processes
    int fileSize = 0;
    MPI_Bcast(&fileSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int interval = fileSize/size;
    int start_position = rank*interval;
    int end_position = (rank+1)*interval - 1;
    if (rank == size - 1) {
      end_position = fileSize - 1;
    }

    FILE * file;
    file = fopen("binary_tree.txt","r");
    int matches = scanSubFile(file, min, max, start_position, end_position, rank, size);
    fclose(file);
    printf("P %d | %d - %d | %d\n",rank,start_position,end_position, matches);
    MPI_Reduce(&matches, &totalMatches, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  }
  MPI_Finalize();                         /* terminate MPI       */
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
