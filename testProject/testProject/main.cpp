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
#include "SocketUtil.h"
#include "unistd.h"
#include "DataOutputStream.h"
#include "Rijndael.h"

const unsigned char* AES128EncryptWithKey(const string& inputData, const string& keyhexstr)
{
    //One block testing
    CRijndael oRijndael;
    oRijndael.MakeKey(keyhexstr.c_str(), CRijndael::sm_chain0, 16, 16);
    
    
    int BLOCK_SIZE = 16;
    size_t blockNum = (inputData.size() / BLOCK_SIZE + 1);
    size_t pDataSize = blockNum * BLOCK_SIZE;
    char* szDataIn = new char[pDataSize];
    int padding = BLOCK_SIZE - (inputData.size() % BLOCK_SIZE);
    
    // szDataIn全置0
    memset(szDataIn, 0, pDataSize);
    // inputData复制到szDataIn
    strcpy(szDataIn, inputData.c_str());
    // szDataIn最后一部分PCK7填充补齐
    memset(szDataIn + pDataSize - padding, padding, padding);
    
    // 分配szDataOut的内存
    unsigned char *szDataOut = (unsigned char *)malloc(pDataSize);
    // szDataOut全置0
    memset(szDataOut, 0, pDataSize);
    
    oRijndael.ResetChain();
    oRijndael.Encrypt(szDataIn, (char*)szDataOut, pDataSize, CRijndael::CBC);
//    cocos2d::Data* finalData = new Data;
//    finalData->fastSet(szDataOut, pDataSize);
    
    return szDataOut;
    //    delete[] ptrData;
    
    //return finalData;
    //    return NULL;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //本地  测试
 //   ByteCircle* circle = new ByteCircle(1024*1024);
//    int value = htonl(23);
//    
//    const unsigned char* data = (unsigned char*) &value;
//    printf(" value data length == %zd \n", strlen((const char*)data));
//    printf(" data == %d \n", ByteUtil::readInt(data));
//    size_t length = strlen((const char*)data);
//    circle->pushData(data, 0, sizeof(value));
//    printf(" data == %d \n", ByteUtil::readInt(circle->getData(sizeof(value))));
//    circle->skip(length);
//    
//    const unsigned char* data2 = (unsigned char*)"zoulingying";
//    length = strlen((const char*)data2);
//    circle->pushData(data2, 0, strlen((const char*)data2));
//    printf(" data == %s \n", circle->getData(length));
//    //circle->skip(length);
//    
//    const unsigned char* data3 = (unsigned char*)"zou@lingy@ing";
//    length = strlen((const char*)data3);
//    circle->pushData(data3, 0, strlen((const char*)data3));
//    printf(" data == %s", circle->getData(length));
    
    
    
    SocketUtil* sockUtil = new SocketUtil();
    int socketFd = sockUtil->connect("192.168.1.157", 21001);
    
    return 0;
    
    int bufferSize = 2 * 100 * 1024;
    unsigned char* inBuffer = new unsigned char[bufferSize];
    
    const unsigned char* sendData = AES128EncryptWithKey("{\"type\":6005, \"tag\":0, \"channel\":0,\"account\":\"zouly\",\"password\":\"qqqqqq\"}", "adgjmpbp**@!bpm@");
    auto_ptr<DataOutputStream> dataOutput(new DataOutputStream());
    
    dataOutput->writeInt((int32_t)strlen((char*)sendData));
    dataOutput->writeBytes(sendData, strlen((char*)sendData));
    
    if (socketFd > 0) {
        sockUtil->sendData(socketFd, dataOutput->getBuffer(), dataOutput->getSize());
        
        while (true) {
            size_t result = sockUtil->receiveData(socketFd, inBuffer, bufferSize);
            printf("result == %zd \n",result);
            if (result > 0) {
                printf("result ==== %zd \n", result);
                return 0;
            }
            sleep(1);
        }

    }
    
    if(socketFd >= 0){
        close(socketFd);
        shutdown(socketFd,SHUT_RDWR);
        socketFd=-1;
    }
    
    return 0;
}
