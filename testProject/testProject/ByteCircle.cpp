//
//  ByteCircle.cpp
//
//  Created by zouly on 15/5/10.
//
//

#include "ByteCircle.h"

ByteCircle::ByteCircle(size_t _size)
:dataHead(0)
,dataLength(0)
,lock(NULL)
{
    circle = new char[_size];
    size = _size;
    lock = new ThreadMutex();
}

ByteCircle::~ByteCircle(){
    delete [] circle;
}

int ByteCircle::pushData(const unsigned char* data, size_t start, size_t length){
    //do lock
    ThreadLock fieldLock(lock);
    
    if (NULL == data) {
        return -1;
    }
    if (length > size) {
        printf("erro :ByteCircle::pushData length > circle size \n");
        return -1;
    }
    
    size_t dataNewStart = dataHead + dataLength;
    if (dataNewStart >= size) {
        dataNewStart -= size;
    }
    
    //dataHead+dataLength本身就是指向下一个可填充的位置 这里需要end length -1·
    size_t dataNewEnd = dataHead + dataLength + length - 1;
    if (dataNewEnd >= size) {
        dataNewEnd -= size;
    }
    
    //表示未超出环
    if (dataNewEnd >= dataNewStart) {
        memcpy(this->circle + dataNewStart, data + start, length);
        dataLength += length;
        return 0;
    }
    
    //超出环 需要分两部分
    size_t part1 = size - dataNewStart;
    size_t part2 = length - part1;
    memcpy(this->circle + dataNewStart, data + start, part1);
    memcpy(this->circle, data + start + part1 , part2);
    dataLength += length;
    return 0;
}

//获得指定长度的数据
//返回的char*需要被主动释放
unsigned char* ByteCircle::getData(size_t length){
    if (length > dataLength) {
        return NULL;
    }
    
    unsigned char* data = new unsigned char[length];
    this->getData(data, 0, length);
    return data;
}

//获得指定长度的数据, 并写入指定数组中
int ByteCircle::getData(unsigned char* data, size_t length){
    return this->getData(data, 0, length);
}

//获得指定长度的数据, 并写入指定数组中的开始位置
int ByteCircle::getData(unsigned char* data, size_t start, size_t length){
    
    ThreadLock fieldLock(lock);
    
    if (data == nullptr) {
        printf("ByteCircle::getData agument expect not null \n");
        return -1;
    }
    
    if (dataLength < length) {
        printf("ByteCircle::getData dataLength < length, data is not Enough \n");
        return -1;
    }
    if (dataHead + length <= size) {
        memcpy(data + start, this->circle + dataHead, length);
    }
    
    if (dataHead + length > size) {
        size_t part1 = size - dataHead;
        size_t part2 = length - part1;
        memcpy(data + start, this->circle + dataHead , part1);
        memcpy(data + start + part1, this->circle, part2);
    }
    
    return 0;
    
}

void ByteCircle::skip(size_t length){
    ThreadLock fieldLock(lock);
    if (length > dataLength) {
        printf("erro: ByteCircle::skip agument length > dataLength \n");
        return;
    }
    dataLength -= length;
    dataHead += length;
    if (dataHead > size) {
        dataHead -= size;
    }
}
