/******************************************************************************
* FILE: omp.c
* DESCRIPTION:
*   Performs map reduce to create a word count analysis over a set of inputs.
* AUTHOR: Nathan Tornquist 3/1
* LAST REVISED: 03/01/15
*
* Compile OSX:
* g++-4.9 omp.cpp -o omp -fopenmp -std=c++11
*
* On ECEGrid:
*
*
* Run:
* ./omp [file1] [file2] .. [fileN]
*
******************************************************************************/
using namespace std;
#include <omp.h>
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

long long current_timestamp();

bool charChecker(int i) {
  return !std::isalnum(i);
}


int charConvert(int value) {
  if (value >= 97 && value <= 122) {
    return (value - 97);
    printf("Character\n");
  } else if (value >= 48 && value <= 57) {
    return (value - 48 + 26);
  } else
  {
    return 0;
  }
}

int findCore(int value, int cores) {
  int pid = 0;
  int range_start = pid*36/cores;
  int range_end = (pid+1)*36/cores - 1;
  while (value < range_start || value > range_end)
  {
    pid = pid + 1;
    range_start = pid*36/cores;
    range_end = (pid+1)*36/cores - 1;
  }
  return pid;
}

int main (int argc, char *argv[])
{
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  // INITIALIZATION LOGIC

  int cores = 1;

  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  // Queues

  queue<string> files;
  queue<string> words;
  //omp_lock_t reducer_queue_lock[cores];
  queue<tuple<string, int>> reducer_queue[cores][cores];
  map<string, int> reduced_count[cores];

  //Init locks
  //for (int i = 0; i < cores; i++) {
  //  omp_init_lock(&(reducer_queue_lock[i]));
  //}
  //

  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////

  omp_set_dynamic(0);     // Disable Dynamic Threads
  omp_set_num_threads(cores); // Set Num Threads (change for benchmarking)

  //Time Variables
  long long t1, t2;
  long long diff;
  long long time_1;

  printf("Starting Operation for %d cores\n", cores);
  t1 = current_timestamp();

  //////////////////////////////////////////////////////////////////////
  //////////////////////// START PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////

  int readers = 0;
  int mappers = 0;
  int reducers = 0;
  bool reader = false;
  bool mapper = false;
  bool written = false;
  int writers = 0;
  int totalCount = 0;
  //#pragma omp parallel shared(readers, mappers, reducers, files, words, written, writers, totalCount) private(reader, mapper)
  #pragma omp parallel shared(readers, mappers, reducers, files, written, writers, totalCount) private(reader, mapper, words)
  {
    int pid = omp_get_thread_num();
    if (pid == 0) {
      for (int i = 1; i < argc; i++) {
        files.push(argv[i]);
      }
    }
    #pragma omp barrier

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  START READER LOGIC  ////////////////////////
    //////////////////////////////////////////////////////////////////////
    while (!files.empty()) {
      string filePath = "";
      #pragma omp critical (fileAccess)
      {
        if (!files.empty()) {
          filePath = files.front();
          files.pop();
          if (!reader) {
            readers = readers + 1;
            reader = true;
          }
        }
      }
      if (filePath.compare("") != 0) {
        ifstream file;
        file.open(filePath.c_str());
        string word;
        int word_count = 0;
        while(file >> word)
        {
          //Lowercase
          transform(word.begin(), word.end(), word.begin(), ::tolower);
          word.erase(std::remove_if(word.begin(), word.end(), charChecker), word.end());
          if (word.size() > 0) {
            word_count++;
            //cout << word << endl;
            /*int words_index = charConvert(word.at(0));
            omp_set_lock(&(words_lock[words_index]));
            words[words_index].push(word);
            omp_unset_lock(&(words_lock[words_index]));*/
            //#pragma omp critical
            {
              words.push(word);
            }
          }
        }
        printf("%40s Word Count: %d\n", filePath.c_str(), word_count);
        file.close();
      }
    }
    if (reader) {
      #pragma omp atomic
      readers--;
      if (readers == 0) {
        printf("Readers Finished\n", readers);
      }
    }

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  START MAPPER LOGIC  ////////////////////////
    //////////////////////////////////////////////////////////////////////
    //Some Parts of the program can progress to here while others are still reading
    map<string, int> words_count;
    //int range_start = pid*36/cores;
    //int range_end = (pid+1)*36/cores - 1;
    //printf("Range %d -> %d\n", range_start, range_end);
    while (!words.empty() || readers > 0) {
      string word = "";
      //#pragma omp critical (getWordForReader)
      {
        if (!words.empty()) {
          word = words.front();
          words.pop();
          if (!mapper) {
            mappers = mappers + 1;
            mapper = true;
          }
        }
        //Mapper logic
        if (word.compare("") != 0) {
          words_count[word] = words_count[word] + 1;
          //printf("%s, %d\n", word.c_str(), words_count[word]);
          //printf("%d\n", word.at(0));
        }
      }
    }
    //for (auto key_value : words_count)
    for (map<string, int>::iterator it=words_count.begin(); it!=words_count.end(); ++it)
    {
      //string key = key_value.first;
      //int value = key_value.second;
      string key = it->first;
      int value = it->second;
      int converted = charConvert(key.at(0));
      int dest = findCore(converted, cores);

      tuple<string, int> item (key, value);

      //omp_set_lock(&(reducer_queue_lock[dest]));
      reducer_queue[dest][pid].push(item);
      //omp_unset_lock(&(reducer_queue_lock[dest]));

      //printf("Key %s, Value %d, Dest %d\n", key.c_str(), value, dest);
    }
    if (mapper) {
      #pragma omp atomic
      mappers--;
    }
    #pragma omp barrier
    if (pid == 0) { printf("Mapping Finished\n"); }

    //Reducer Logic
    //queue<tuple<string, int>> reducer_queue[cores];
    //unordered_map<string, int> reduced_count[cores];

    //////////////////////////////////////////////////////////////////////
    //////////////////////// START REDUCER LOGIC  ////////////////////////
    //////////////////////////////////////////////////////////////////////
    #pragma omp atomic
    reducers++;

    for (int i = 0; i < cores; i++) {
      while (!reducer_queue[pid][i].empty()) {
        tuple<string, int> item = reducer_queue[pid][i].front();
        reducer_queue[pid][i].pop();
        reduced_count[pid][get<0>(item)] = reduced_count[pid][get<0>(item)] + get<1>(item);
      }
    }

    #pragma omp critical
    {
      reducers = reducers - 1;
      if (reducers == 0) {
        printf("Reduction Finished\n");
      }
    }
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  START WRITER LOGIC  ////////////////////////
    //////////////////////////////////////////////////////////////////////
    //Writer Logic
    #pragma omp critical
    {
      writers = writers + 1;
      fstream outputFile;
      if (!written) {
        written = true;
        outputFile.open("output.txt", fstream::out);
        outputFile << "Word Count Results" << endl;
      } else
      {
        outputFile.open("output.txt", fstream::out | fstream::app);
      }

      //for (auto key_value : reduced_count[pid])
      for (map<string, int>::iterator it=reduced_count[pid].begin(); it!=reduced_count[pid].end(); ++it)
      {
        //string key = key_value.first;
        //int value = key_value.second;
        string key = it->first;
        int value = it->second;
        outputFile << key << " : " << value << endl;
        totalCount = totalCount + value;
      }
      if (writers == cores) {
        outputFile << "Total Words Identified: " << totalCount << endl;
      }
      outputFile.close();
    }
    if (writers == cores)
    {
      printf("Writing Finished\n");
    }
  }

  //////////////////////////////////////////////////////////////////////
  ////////////////////////// END PARALLEL LOGIC ////////////////////////
  //////////////////////////////////////////////////////////////////////
  t2 = current_timestamp();
  time_1 = t2 - t1;

  printf("Completed\n");
  printf("Time:   %f s\n", ((float)time_1)/1000);

  //Free locks
  //for (int i = 0; i < cores; i++) {
  //  omp_destroy_lock(&(reducer_queue_lock[i]));
  //}
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
