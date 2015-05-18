//
//  SocketUtil.cpp
//  testProject
//
//  Created by zouly on 15/5/4.
//
//

#include "SocketUtil.h"
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>  //文件系统相关的常量设置
#include <netdb.h>

SocketUtil::SocketUtil(){
    
}

SocketUtil::~SocketUtil(){
    
}


int SocketUtil::connect(const char* ip, unsigned short port){
    struct sockaddr_in sa;
    struct hostent *gamehost;
    
    gamehost = gethostbyname(ip);
    if (gamehost <= 0) {
        printf("ip is vailid");
    }
    
    bzero(&sa, sizeof(sa));
    sa.sin_family = gamehost->h_addrtype;
    sa.sin_addr = *((struct in_addr*)(gamehost->h_addr));
    sa.sin_port = htons(port);
    
    //打印地址端口
    const char* connectIp = inet_ntoa(sa.sin_addr);
    printf("to be connectIp and port is %s:%d \n", connectIp, port);
    
    //创建socket
    int socketFd = socket(sa.sin_family, SOCK_DGRAM, 0);
    
    struct timeval timeout = {0, 10};
    
    //设置
    setsockopt(socketFd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    int flags = fcntl(socketFd, F_GETFL, 0);          //获取建立的sockfd的当前状态
    fcntl(socketFd, F_SETFL, flags | O_NONBLOCK);   //设置非阻塞
    
    //连接
    int ret = ::connect(socketFd, (struct sockaddr *)&sa, sizeof(sa));
    
    if (ret>=0) {
        printf("socketFd: %d \n",socketFd);
        printf("Client connect OK ！ address: %s:%d \n",ip,port);
        return socketFd;
    }
    
    fd_set myset;
    while (true) {
        FD_ZERO(&myset);            //每次循环都要清空集合，否则不能检测描述符变化
        FD_SET(socketFd,&myset);    //添加描述符
        
        //第一个参数 所有文件描述符的最大值加1
        //如果这个集合中有一个文件可写，select就会返回一个大于0的值
        //若超出timeout的时间，select返回0，若发生错误返回负值
        //可以传入NULL值，表示不关心任何文件的写变化
        //若将timeout超时时间设置以NULL形参传入，即不传入时间结构，就是将select置于阻塞状态
        //若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，立即返回
        //timeout的值大于0，这就是等待的超时时间，即select在timeout时间内阻塞，超时时间之内有事件到来就返回了
        ret = select(socketFd + 1, NULL, &myset, NULL, &timeout);
        if (ret < 0) {
            printf("Error connecting %d - %s", errno, strerror(errno));
            return -1;
        }
        if (FD_ISSET(socketFd, &myset)) {   //测试sock是否可写，即已完成握手可发送后续请求了
            return socketFd;
        }
    }
    
    return 0;
}

ssize_t SocketUtil::receiveData(int socketFd, unsigned char* buffer, const int64_t& length){
    if (buffer == NULL) {
        printf("receiveData aguments buffer is NULL");
        return -1;
    }
    ssize_t result = recv(socketFd, buffer, length, 0);
    
    if (result < 0) {
        switch (errno) {
            case EAGAIN:
                //由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
                break;
            case EINTR:
                //系统中断 继续接收
                return 0;
            default:
                //其他错误 可能需要重新连接
                printf("SocketUtil::receiveData errno:%d \n", errno);
                return -1;
                break;
        }
    }
    
    if (result > 0) {
        return result;
    }
    
    if (result == 0) {
        // 这里表示对端的socket已正常关闭.
        return -1;
    }
    return 0;
}

ssize_t SocketUtil::sendData(int handle, const unsigned char* data, const int64_t& length){
    if (data == nullptr) {
        return -1;
    }
    size_t retLength = send(handle, data, length, 0);
    printf("retLength == %zd \n", retLength);
    return retLength;
}
//
//ssize_t SocketUtil::setNonBlockMode(int socketHandle){
//    //设置为非阻塞模式
//    int flags = fcntl(socketHandle,F_GETFL,0);//获取建立的sockfd的当前状态（非阻塞）
//    return fcntl(socketHandle,F_SETFL,flags|O_NONBLOCK);//将当前sockfd设置为非阻塞
//    
//}
//
//ssize_t SocketUtil::setBlockMode(int socketHandle){
//    //设置为阻塞模式
//    int flags = fcntl(socketHandle,F_GETFL,0);//获取建立的sockfd的当前状态（非阻塞）
//    return fcntl(socketHandle,F_SETFL,flags & (~ O_NONBLOCK));//将当前sockfd设置为阻塞
//    
//}

