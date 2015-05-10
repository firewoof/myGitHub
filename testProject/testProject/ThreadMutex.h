//
//  ThreadMutex.h
//  testProject
//
//  Created by zouly on 15/5/10.
//
//

#ifndef __testProject__ThreadMutex__
#define __testProject__ThreadMutex__

#include "pthread.h"

class ThreadMutex{

public:
    ThreadMutex()
    :pLock(nullptr)
    {
        pLock = new pthread_mutex_t;
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(pLock, &attr);
        pthread_mutexattr_destroy(&attr);
    }
    
    ~ThreadMutex(){
        pthread_mutex_destroy(pLock);
        delete pLock;
    }
    
    void lock(){
        pthread_mutex_lock(pLock);
    }
    
    void unLock(){
        pthread_mutex_unlock(pLock);
    }
private:
    pthread_mutex_t* pLock;
};

/**
 * 构造即上锁
 */
class ThreadLock{
public:
    ThreadLock(ThreadMutex* _mutexLock)
    :mutexLock(_mutexLock)
    {
        mutexLock->lock();
    }
    
    ~ThreadLock(){
        mutexLock->unLock();
    }
    
private:
    ThreadMutex* mutexLock;
};

#endif /* defined(__testProject__ThreadMutex__) */
