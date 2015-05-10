//
//  ByteCircle.h
//  testProject
//
//  Created by zouly on 15/5/10.
//
//

#ifndef __testProject__ByteCircle__
#define __testProject__ByteCircle__

#include <iostream>
#include "pthread.h"
#include "ThreadMutex.h"

class ByteCircle{
public:
    ByteCircle(size_t _size);
    ~ByteCircle();
    

    int getSize();
    
    int pushData(const unsigned char* data, size_t start, size_t length);
    
    //获得指定长度的数据
    //返回的char*需要被主动释放
    unsigned char* getData(size_t length);
    
    //获得指定长度的数据, 并写入指定数组中
    int getData(unsigned char* data, size_t length);
    
    //获得指定长度的数据, 并写入指定数组中的开始位置
    int getData(unsigned char* data, size_t start, size_t length);
    
    //忽略指定长度
    void skip(size_t length);
    
    /**
     * 将数据从数据环弹出
     *
     * @param length
     * @return 数据指针, 需要被释放
     */
    unsigned char* popData(size_t length);
    
    //从数据环弹出一个package长度的数据
    //void popData(const cocos2d::Data* package);
    
    /**
     * 获取一个数据包
     * 这个数据包开头4byte是数据包长度
     * @return 数据指针, 需要被释放
     */
    //cocos2d::Data* getPackage();
    
    void reset();
    
private:
    int dataHead;       //类似游标 标明数据起始点
    int dataLength;
    
    ThreadMutex* lock;
    
    char* circle;
    
    size_t size;
};


#endif /* defined(__testProject__ByteCircle__) */
