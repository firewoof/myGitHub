//
//  SocketUtil.h
//  testProject
//
//  Created by zouly on 15/5/4.
//
//

#ifndef __SocketUtil_H__
#define __SocketUtil_H__

#include <iostream>

class SocketUtil {
    SocketUtil();
    ~SocketUtil();
    
public:
    
    static int connect(const char* ip, unsigned short port);
    
    static ssize_t receiveData(int handle, unsigned char* buffer, const int64_t& length);
    
    static ssize_t sendData(int handle, const unsigned char* data, const int64_t& length);
    
    static ssize_t setBlockMode(int handle);
    
    static ssize_t setNonBlockMode(int handle);
    
    static std::string getLocalIP(int handle);
    
};

#endif /* defined(__testProject__SocketUtil__) */
