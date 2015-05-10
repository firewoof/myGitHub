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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //本地  测试
    ByteCircle* circle = new ByteCircle(15);
    const unsigned char* data = (unsigned char*)"01234567";
    size_t length = strlen((const char*)data);
    circle->pushData(data, 0, length);
    printf(" data == %s \n", circle->getData(length));
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
