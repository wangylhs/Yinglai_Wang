#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <dlfcn.h>
#include <stdio.h>
#include <map>
#include <signal.h>
#include <sstream>

//#define DEBUG 1


int (*original_pthread_create)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*) = NULL;
int (*original_pthread_join)(pthread_t, void**) = NULL;
int (*original_pthread_mutex_lock)(pthread_mutex_t*) = NULL;
int (*original_pthread_mutex_unlock)(pthread_mutex_t*) = NULL;

static void initialize_original_functions();

using namespace std;

pthread_mutex_t GL;

int currthrID = 0;
int mainID = 0;
bool firstRun = true;
bool doExit = false;
int syncPoint = 0;
static void check_synchronization();

struct threadStruct {
    int id;
    bool lock_st;
    int run_st; // 1(running) 0(finished) 2(waiting)
};

map<int, threadStruct*> threads;
map<pthread_mutex_t*, threadStruct*> m_locks;
map<pthread_t*, int> threadids;
map<int, threadStruct*>::iterator iter;


struct Thread_Arg {
    void* (*start_routine)(void*);
    void* arg;
};

static
void* thread_main(void *arg)
{
    struct Thread_Arg thread_arg = *(struct Thread_Arg*)arg;
    free(arg);
    
    original_pthread_mutex_lock(&GL);
    void* ret = thread_arg.start_routine(thread_arg.arg);
    currthrID = mainID;
    doExit = true;
    original_pthread_mutex_unlock(&GL);
    
#ifdef DEBUG
    fprintf (stderr, "=====synchronization points: %d\n", syncPoint);
#endif
    
    return ret;
}

extern "C"
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void*), void *arg)
{
#ifdef DEBUG
    puts("=====pthread_create()\n");
#endif
    
    initialize_original_functions();
    
    struct Thread_Arg *thread_arg = (struct Thread_Arg*)malloc(sizeof(struct Thread_Arg));
    thread_arg->start_routine = start_routine;
    thread_arg->arg = arg;
    
    int ret = original_pthread_create(thread, attr, thread_main, thread_arg);
    
    while(firstRun == true)
    {
        original_pthread_mutex_lock(&GL);
        currthrID = (int)pthread_self();
        mainID = currthrID;
        firstRun = false;
    }
    // TODO
    threadStruct *t;
    t = new threadStruct();
    t->id = (int)pthread_self();
    t->lock_st = false;
    t->run_st = 1;
    
    threads[(int)pthread_self()] = t;
    
    t = new threadStruct();
    t->id = (int)*thread;
    t->lock_st = false;
    t->run_st = 1;
    
    threads[(int)*thread] = t;
    
    threadids[thread] = (int)*thread;
    
    check_synchronization();
    
    return ret;
}

extern "C"
int pthread_join(pthread_t joinee, void **retval)
{
#ifdef DEBUG
    puts("=====pthread_join()\n");
#endif
    
    initialize_original_functions();
    
    // TODO
    int ret = 0;
    
    while(true){
        if((ret=pthread_kill(joinee, 0))==0 && doExit!=true) sched_yield();
        else
            break;
    }
    
    return ret;
}

extern "C"
int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    
#ifdef DEBUG
    puts("=====pthread_mutex_lock()\n");
#endif
    initialize_original_functions();
    
    check_synchronization();
    
    // TODO
    int ret = 0;
    while(true){
        if((ret=pthread_mutex_trylock(mutex))!=0){
            threadStruct *t = threads[(int)pthread_self()];
            t->run_st = 2;
            sched_yield();
        }else
            break;
    }
    
    threadStruct *t = threads[(int)pthread_self()];
    m_locks[mutex] = t;
    t->lock_st = true;
    t->run_st = 1;
    
    return ret;
}

extern "C"
int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
#ifdef DEBUG
    puts("=====pthread_mutex_unlock()\n");
#endif
    
    initialize_original_functions();
    
    // TODO
    
    threadStruct *t = m_locks[mutex];
    t->lock_st = false;
    t->run_st = 1;
    
    check_synchronization();
    return original_pthread_mutex_unlock(mutex);
}

extern "C"
int sched_yield(void)
{
#ifdef DEBUG
    puts("=====sched_yield()\n");
#endif
    
    initialize_original_functions();
    
    // TODO
    original_pthread_mutex_unlock(&GL);
    
    iter = threads.begin();
    while(iter != threads.end()){
        threadStruct* curr = iter->second;
        if (curr->id != currthrID && (curr->run_st==1 || curr->run_st==2)){
            curr->run_st = 1;
            currthrID = curr->id;
#ifdef DEBUG
            fprintf(stderr, "=====context swtich to %d\n", curr->id);
#endif
            break;
        }
        iter++;
    }
    
    while (currthrID != (int)pthread_self());
    
    original_pthread_mutex_lock(&GL);
    
    return 0;
}

static void check_synchronization(){
    syncPoint++;
    int curr = -1;
    FILE *data = fopen("curr.txt", "r");
    if (data != NULL)
    {
        char line[1024];
        fgets(line, 1024, data);
        fclose(data);
        curr = atoi(line);
    }
    if(curr > 0){
#ifdef DEBUG
        fprintf(stderr, "=====reach synchronization point: %d of %d.\n", syncPoint, curr);
#endif
    }
    if(curr == syncPoint) sched_yield();
}

static
void initialize_original_functions()
{
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        
        original_pthread_create =
        (int (*)(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*))dlsym(RTLD_NEXT, "pthread_create");
        original_pthread_join =
        (int (*)(pthread_t, void**))dlsym(RTLD_NEXT, "pthread_join");
        original_pthread_mutex_lock =
        (int (*)(pthread_mutex_t*))dlsym(RTLD_NEXT, "pthread_mutex_lock");
        original_pthread_mutex_unlock =
        (int (*)(pthread_mutex_t*))dlsym(RTLD_NEXT, "pthread_mutex_unlock");
    }
}