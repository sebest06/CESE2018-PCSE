#ifndef _mythread_h_
#define _mythread_h_

#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>

#include <cstdlib>

using namespace std;

class MyThread {

  private:
    static pthread_mutex_t mutex;

  public:
    pthread_t tid;
    MyThread();
    int Create(void *Callback, void *args);
    int Join();

    static int InitMutex();
    static int LockMutex(const char *identifier);
    static int UnlockMutex(const char *identifier);
};

#endif
