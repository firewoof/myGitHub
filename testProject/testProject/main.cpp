//
//  main.cpp
//  testProject
//
//  Created by zouly on 15/5/4.
//
//

#include <iostream>
#include <netdb.h>
#include "ByteCircle.h"
#include "ByteUtil.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //本地  测试
    ByteCircle* circle = new ByteCircle(15);
    int value = htonl(23);
    
    const unsigned char* data = (unsigned char*) &value;
    printf(" value data length == %zd \n", strlen((const char*)data));
    printf(" data == %d \n", ByteUtil::readInt(data));
    size_t length = strlen((const char*)data);
    circle->pushData(data, 0, sizeof(value));
    printf(" data == %d \n", ByteUtil::readInt(circle->getData(sizeof(value))));
    circle->skip(length);
    
    const unsigned char* data2 = (unsigned char*)"zoulingying";
    length = strlen((const char*)data2);
    circle->pushData(data2, 0, strlen((const char*)data2));
    printf(" data == %s \n", circle->getData(length));
    //circle->skip(length);
    
    const unsigned char* data3 = (unsigned char*)"zou@lingy@ing";
    length = strlen((const char*)data3);
    circle->pushData(data3, 0, strlen((const char*)data3));
    printf(" data == %s", circle->getData(length));
    
    return 0;
}
