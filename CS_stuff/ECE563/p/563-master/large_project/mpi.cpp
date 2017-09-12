/******************************************************************************
* FILE: mpi.c
* DESCRIPTION:
*   Performs map reduce to create a word count analysis over a set of inputs.
* AUTHOR: Nathan Tornquist 4/4
* LAST REVISED: 04/09/15
******************************************************************************/
using namespace std;
#include <omp.h>
#include <mpi.h>
#include <queue>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <tuple>
#include <math.h>

long long current_timestamp();

bool charChecker(int i) {
  return !std::isalnum(i);
}

#define READER_ID 0
#define MAPPER_ID 1
#define REDUCER_ID 2

#define MPI_FILE_REQUEST 0
#define MPI_FILE_NAME 1
#define MPI_REDUCE 2

int main (int argc, char *argv[])
{

  /* MPI Parameters */
  int rank, size, len;
  MPI_Init(&argc, &argv);                 /* start MPI           */
  MPI_Comm_size(MPI_COMM_WORLD, &size);   /* get number of ranks */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get rank            */

  int threads = 3;
  if (rank == 0) { threads = threads + 1; } //Additional node for master file issuer

  omp_set_dynamic(0);           // Disable Dynamic Threads
  omp_set_num_threads(threads); // Set Num Threads (change for benchmarking)

  queue<string> words[2]; //Double Buffer Word List (So both reader and mapper can access it)
  int wordBufferIndex = 0;
  omp_lock_t mpi_lock;
  omp_lock_t mapper_lock;
  omp_lock_t cores_lock;
  omp_init_lock (&mapper_lock);
  omp_init_lock (&mpi_lock);
  omp_init_lock (&cores_lock);
  queue<string> files;

  map<string, int> words_count; //Double Buffer Count

  bool more_books = true; //Trigger for reader to continue
  bool mapper_running = true;
  int remaining_cores = 1; //Required to start it above zero for reducer

  //Time Variables
  long long t1, t2, t3;
  long long diff;
  long long time_1, time_2;

  t1 = current_timestamp();

  #pragma omp parallel shared(files, words, more_books, mapper_running, remaining_cores, words_count)
  {
    MPI_Status status; //Each core and each thread has this locally

    int threadNum;
    threadNum = omp_get_thread_num();
    //// MASTER READER
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    if (rank == 0 && threadNum == 0) {
      //printf("Node: %d, Thread: %d  -  Master Reader\n", rank, threadNum);
      for (int i = 1; i < argc; i++) {
        files.push(argv[i]);
      }
      int requesting_location = 0;
      int file_size = 0;
      remaining_cores = size - 1;
      bool keep_running = true;
      if (size == 1) { keep_running = false; }
      while(keep_running) {
        MPI_Recv(&requesting_location, 1, MPI_INT, MPI_ANY_SOURCE, MPI_FILE_REQUEST, MPI_COMM_WORLD, &status);
        //printf("Request from: %d for %s\n", requesting_location, files.front().c_str());

        // Respond
        omp_set_lock(&mpi_lock);

        if (!files.empty()) {
          file_size = files.front().size();
          MPI_Send(&file_size, 1, MPI_INT, requesting_location, MPI_FILE_NAME, MPI_COMM_WORLD);
          MPI_Send((void *) files.front().c_str(), files.front().size(), MPI_CHAR, requesting_location, MPI_FILE_NAME, MPI_COMM_WORLD);
          files.pop();
        } else {
          //printf("Sending Stop to: %d\n", requesting_location);
          file_size = 4;
          MPI_Send(&file_size, 1, MPI_INT, requesting_location, MPI_FILE_NAME, MPI_COMM_WORLD);
          MPI_Send((void *)"STOP", 4, MPI_CHAR, requesting_location, MPI_FILE_NAME, MPI_COMM_WORLD);
          omp_set_lock(&cores_lock);
          remaining_cores = remaining_cores - 1;
          if (remaining_cores == 0) {
            keep_running = false;
          }
          omp_unset_lock(&cores_lock);
        }

        omp_unset_lock(&mpi_lock);
      }

    } else
    {
      //// READER THREAD
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      if ((rank != 0 && threadNum == READER_ID) || (rank == 0 && threadNum == (READER_ID + 1))) {
        //printf("Node: %d, Thread: %d  -  Worker Thread\n", rank, threadNum);

        string stop = "STOP";
        while(more_books) {
          string filename;
          if (rank != 0) {
            //Not on master core
            MPI_Send(&rank, 1, MPI_INT, 0, MPI_FILE_REQUEST, MPI_COMM_WORLD);
            int length;
            MPI_Recv(&length, 1, MPI_INT, 0, MPI_FILE_NAME, MPI_COMM_WORLD, &status);
            char *buf = new char[length];
            MPI_Recv(buf, length, MPI_CHAR, 0, MPI_FILE_NAME, MPI_COMM_WORLD, &status);
            string fname(buf, length);
            filename = fname;
          } else {
            //On same core as master, cannot use MPI to communicate
            omp_set_lock(&mpi_lock);
            if (!files.empty()) {
              filename = files.front();
              files.pop();
            } else {
              filename = "STOP";
            }

            omp_unset_lock(&mpi_lock);
          }
          //printf("Node: %d, Thread: %d  - %s\n", rank, threadNum, filename.c_str());
          //printf("Received: %s in %d\n", filename.c_str(), rank);
          if (filename.compare(stop) == 0) {
            more_books = false;
            //printf("Node: %d, Thread: %d  - Exit\n", rank, threadNum);
          } else {
            //READER
            ifstream file;
            file.open(filename.c_str());
            string word;
            int word_count = 0;
            while(file >> word)
            {
              //Lowercase
              if (wordBufferIndex == 0 && words[1].empty()) {
                wordBufferIndex = 1;
              } else if (wordBufferIndex == 1 && words[0].empty()) {
                wordBufferIndex = 0;
              }
              transform(word.begin(), word.end(), word.begin(), ::tolower);
              word.erase(std::remove_if(word.begin(), word.end(), charChecker), word.end());
              if (word.size() > 0) {
                word_count++;
                words[wordBufferIndex].push(word);
              }
            }
            //printf("%40s Word Count: %d\n", filename.c_str(), word_count);
            file.close();
          }
        }
      }
      //// MAPPER THREAD
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      else if ((rank != 0 && threadNum == MAPPER_ID) || (rank == 0 && threadNum == (MAPPER_ID + 1))) {
        //printf("MAPPER: %d - Started\n", rank);
        //int c = 0;
        while (more_books || !words[0].empty() || !words[1].empty()) {
          string word = "";

          int buffer = (wordBufferIndex == 1) ? 0 : 1;

          /*
          if (c > 1000) {
            printf("Rank: %d  More_books: %d Words[0]: %d - %d Words[1]: %d - %d Buffer: %d\n", rank, more_books, !words[0].empty(), words[0].size(), !words[1].empty(), words[1].size(), buffer);
            c = 0;
          }
          c = c + 1;
          */

          if (!words[buffer].empty()) {
            word = words[buffer].front();
            words[buffer].pop();
          }
          if (word.compare("") != 0) {
            words_count[word] = words_count[word] + 1;
          }

          if (!more_books) {
            if (words[buffer].empty()) {
              wordBufferIndex = (wordBufferIndex == 1) ? 0 : 1;
            }
          }
        }
        omp_set_lock(&mapper_lock);
        mapper_running = false;
        omp_unset_lock(&mapper_lock);

        //printf("MAPPER: %d - Finished\n", rank);

      }
      //// REDUCER THREAD
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      else if ((rank != 0 && threadNum == REDUCER_ID) || (rank == 0 && threadNum == (REDUCER_ID + 1))) {
        //printf("Node: %d, Thread: %d  -  Sender Thread\n", rank, threadNum);
        //printf("Node: %d, Thread: %d  - Exit\n", rank, threadNum);
	      bool temp = true;
        while (temp) {
            omp_set_lock(&mapper_lock);
            temp = mapper_running;
            omp_unset_lock(&mapper_lock);
        }
        temp = true;
        if (rank == 0) {
          while (temp) {
            omp_set_lock(&cores_lock);
            if (remaining_cores == 0) {
              temp = false;
            }
            omp_unset_lock(&cores_lock);
          }
        }

        int round = 0;
        int action = 0; // 1 = Send, 0 = Receive
        int step = 0;
        while (action == 0 && step < size/2) {
          int count = 0;
          step = pow(2, round);
          int value = rank;

          while (value >= 0) {
            value -= step;
            count++;
          }

          if (count % 2 == 0) {
            //printf("Rank: %d  Round: %d  Action: Send to %d \n\n", rank, round, rank - step); // Send
            action = 1;

            for (map<string, int>::iterator it=words_count.begin(); it!=words_count.end(); ++it)
            {
              string key = it->first;
              int value = it->second;

              omp_set_lock(&mpi_lock);

              int t = key.size();
              MPI_Send(&t, 1, MPI_INT, rank-step, MPI_REDUCE, MPI_COMM_WORLD);
              MPI_Send((void *) key.c_str(), key.size(), MPI_CHAR, rank-step, MPI_REDUCE, MPI_COMM_WORLD);
              MPI_Send(&value, 1, MPI_INT, rank-step, MPI_REDUCE, MPI_COMM_WORLD);
              omp_unset_lock(&mpi_lock);
            }
            int temp = -1;
            omp_set_lock(&mpi_lock);
            MPI_Send(&temp, 1, MPI_INT, rank-step, MPI_REDUCE, MPI_COMM_WORLD);
            omp_unset_lock(&mpi_lock);
          } else {
            //printf("Rank: %d  Round: %d  Action: Receive from %d\n\n", rank, round, rank + step); // Receive
            action = 0;

            int length = 0;
            int value = 0;
            string word;
            while (length >= 0) {
              omp_set_lock(&mpi_lock);
              MPI_Recv(&length, 1, MPI_INT, rank + step, MPI_REDUCE, MPI_COMM_WORLD, &status);
              if (length >= 0) {
                char *buf = new char[length];
                MPI_Recv(buf, length, MPI_CHAR, rank + step, MPI_REDUCE, MPI_COMM_WORLD, &status);
                string temp_word(buf, length);
                MPI_Recv(&value, 1, MPI_INT, rank + step, MPI_REDUCE, MPI_COMM_WORLD, &status);
                word = temp_word;
              }
              omp_unset_lock(&mpi_lock);
              if (length >= 0) {
                //Perform mapping
                words_count[word] = words_count[word] + value;
              }
            }
          }
          round = round + 1;
        }
        //printf("After receive completed\n");
        if (rank == 0) {
          t2 = current_timestamp();
          //printf("Core 0 printing\n");
          fstream outputFile;
          outputFile.open("output.txt", fstream::out);
          outputFile << "Word Count Results" << endl;
          int totalCount = 0;
          for (map<string, int>::iterator it=words_count.begin(); it!=words_count.end(); ++it)
          {
            string key = it->first;
            int value = it->second;

            outputFile << key << " : " << value << endl;
            totalCount = totalCount + value;
          }
          outputFile << "Total Words Identified: " << totalCount << endl;
          outputFile.close();

          printf("\n%28s Total Words Identified: %d\n", "", totalCount);
        }
      }
      //// Invalid State
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////
      else {
        printf("Node: %d, Thread: %d  - Error State\n", rank, threadNum);
      }
    }
  }

  if (rank == 0) {
    t3 = current_timestamp();
    time_1 = t2 - t1;
    time_2 = t3 - t1;
    printf("%45s Cores: %d\n", "", size);
    printf("%30s Time (exclude print): %f s\n", "",((float)time_1)/1000);
    printf("%38s Time (total): %f s\n", "",((float)time_2)/1000);
  }

  omp_destroy_lock(&mpi_lock);
  omp_destroy_lock(&mapper_lock);
  omp_destroy_lock(&cores_lock);
  #pragma omp barrier
  MPI_Finalize();                         /* terminate MPI       */

  return 0;
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
