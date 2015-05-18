//
//  DataOutputStream.cpp
//  testProject
//
//  Created by Ying on 15/5/12.
//
//

#include "DataOutputStream.h"
#include "ByteUtil.h"
#include "unistd.h"

DataOutputStream::DataOutputStream()
:mBuffer(nullptr)
,mSize(0)
,mIndex(0)
{
    mSize = 0;
    mBuffer = new unsigned char[10 * 1024];
    
}

DataOutputStream::~DataOutputStream(){
    delete [] mBuffer;
}

void DataOutputStream::writeByte(unsigned char value){
    int length = sizeof(value);
    unsigned char* data = new unsigned char[length];
    ByteUtil::byteToValue<unsigned char>(data);
    this->writeBytes(data, length);
}
void DataOutputStream::writeBoolean(bool value){
    int length = sizeof(value);
    unsigned char* data = new unsigned char[length];
    ByteUtil::byteToValue<bool>(data);
    this->writeBytes(data, length);
}
void DataOutputStream::writeShort(int16_t value){
    int length = sizeof(value);
    unsigned char* data = new unsigned char[length];
    ByteUtil::byteToValue<int16_t>(data);
    this->writeBytes(data, length);
}
void DataOutputStream::writeInt(int32_t value){
    int length = sizeof(value);
    unsigned char* data = new unsigned char[length];
    ByteUtil::byteToValue<int32_t>(data);
    this->writeBytes(data, length);
}
void DataOutputStream::writeFloat(float value){
    ByteUtil::writeValue(value, mBuffer);
}
void DataOutputStream::writeLong(int64_t value){
    int length = sizeof(value);
    unsigned char* data = new unsigned char[length];
    ByteUtil::byteToValue<int64_t>(data);
    this->writeBytes(data, length);
}
void DataOutputStream::writeDouble(double value){

}

void DataOutputStream::writeBytes(const unsigned char * data,size_t aLength){
    if (data == nullptr) {
        return;
    }
    size_t newSize = mSize + aLength;
    //不够 扩容
    if(newSize > strlen((char*)mBuffer)){
        this->extendBuffer(5 * 1024);
    }
    
    memcpy(mBuffer + mSize, data, aLength);
    mSize = newSize;
    printf("mSize == %zd \n", mSize);
}

void DataOutputStream::extendBuffer(size_t aLength){
    unsigned char* newBuffer = new unsigned char[strlen((char*)mBuffer) + aLength];
    memcpy(newBuffer, mBuffer, mSize);
    delete [] mBuffer;
    mBuffer = newBuffer;
}

const unsigned char* const DataOutputStream::getBuffer(){
    return this->mBuffer;
}

unsigned long DataOutputStream::getSize(){
    return this->mSize;
}
