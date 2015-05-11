//
//  ByteUtil.h
//  testProject
//
//  Created by Ying on 15/5/11.
//
//

#ifndef __testProject__ByteUtil__
#define __testProject__ByteUtil__

#include <string>

#ifndef REVERSE_MEMCPY
//反向copy src的数据到 dest
//BACKUP:
#define REVERSE_MEMCPY(dest,src,length) for(int i=0;i<length;i++){*(dest+i)=*(src+length-1-i);}

#endif

//判断cpu是大端还是小端, 使用不同的情况转换数据
#ifndef HOST_NETWORK_CONVERTOR
#if __DARWIN_BYTE_ORDER == __DARWIN_LITTLE_ENDIAN
#define HOST_NETWORK_CONVERTOR(dest,src,length) REVERSE_MEMCPY(dest,src,length)
#else // __DARWIN_BYTE_ORDER == BIG_ENDIAN
#define HOST_NETWORK_CONVERTOR(dest,src,length) memcpy(dest,src,length);
#endif
#endif

class ByteUtil {
    
public:
    static int readInt(const unsigned char* data);
    
    //将数据转换成网络字节序,写入对应地址
    template <class T>
    static void writeValue(T value,unsigned char* data) {
        int valueLength = sizeof(value);
        unsigned char * p_value = (unsigned char *)&value;
        HOST_NETWORK_CONVERTOR(data,p_value,valueLength)
    }
    
    //获得网络字节序的数据, 返回值用完需要释放
    template <class T>
    static unsigned char* valueToByte(T value) {
        unsigned char * data = new unsigned char[sizeof(T)];
        writeValue(value, data);
        return data;
    }
    //将一个数据按指定类型从buffer取出, 适用于所有基本数据类型
    template <class T>
    static T byteToValue(const unsigned char* data)
    {
        T value=0;
        int _length = sizeof(T);\
        unsigned char * p = (unsigned char *)&value;
        HOST_NETWORK_CONVERTOR(p,data,_length);
        return value;
    }
    
};


#endif /* defined(__testProject__ByteUtil__) */
