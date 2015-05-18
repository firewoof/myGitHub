/*
 *  DataOutputStream.h
 *
 *  Created by Sunwing on 09/09/2013.
 *
 */

#ifndef DATA_OUTPUT_STREAM_H
#define DATA_OUTPUT_STREAM_H

#include <stdlib.h>
#include <memory>

using namespace std;

class DataOutputStream
{

public:
    DataOutputStream();
	virtual ~DataOutputStream();
protected:
	unsigned char *mBuffer;
	size_t  mSize;
	size_t  mIndex;
public:
	const unsigned char * const getBuffer();
	unsigned long getSize();
	size_t getIndex();

public:
    void writeByte(unsigned char bValue);
    void writeBoolean(bool boolValue);
    void writeShort(int16_t sValue);
    void writeInt(int32_t iValue);
    void writeFloat(float iValue);
    void writeLong(int64_t iValue);
    void writeDouble(double iValue);
    void writeUTF(string * uString);
    void writeUTF(const char *aStr);
    void writeBytes(const unsigned char * abuf,size_t aLength);
    void extendBuffer(size_t aLength);
    //cocos2d::Data* toByteArray();

};
#endif