//
//  ByteUtil.cpp
//  testProject
//
//  Created by Ying on 15/5/11.
//
//

#include "ByteUtil.h"

int ByteUtil::readInt(const unsigned char* data){
    return  byteToValue<int>(data);
}



