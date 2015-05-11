//
//  SocketThread.cpp
//  testProject
//
//  Created by zouly on 15/5/9.
//
//

#include "SocketThread.h"

SocketThread::SocketThread(){
    arry = new char[10];
    printf("SocketThread ctor \n");
}

SocketThread::~SocketThread(){
    delete []arry;
    printf("SocketThread deCtor \n ");
}