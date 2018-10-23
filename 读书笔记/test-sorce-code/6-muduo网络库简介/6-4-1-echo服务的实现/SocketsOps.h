// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_SOCKETSOPS_H
#define MUDUO_NET_SOCKETSOPS_H

#include <arpa/inet.h>

namespace muduo      // muduo库的命名空间
{
namespace net        // net的命名空间
{
namespace sockets    // sockets的命名空间
{

///
/// Creates a non-blocking socket file descriptor,
/// abort if any error.
int createNonblockingOrDie(sa_family_t family);  // 创建一个非阻塞的文件描述符

int  connect(int sockfd, const struct sockaddr* addr);   // 建立连接
void bindOrDie(int sockfd, const struct sockaddr* addr); // 绑定网络文件描述符
void listenOrDie(int sockfd);   // 监听网络文件描述符
int  accept(int sockfd, struct sockaddr_in6* addr); // 接收连接
ssize_t read(int sockfd, void *buf, size_t count); // 从套接字的buffer缓存中读取数据
// readv和writev可以同时操作多个缓冲区
ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
ssize_t write(int sockfd, const void *buf, size_t count); // 向套接字中写数据
void close(int sockfd); // 关闭socket套接字
void shutdownWrite(int sockfd);

void toIpPort(char* buf, size_t size,
              const struct sockaddr* addr);
void toIp(char* buf, size_t size,
          const struct sockaddr* addr);

void fromIpPort(const char* ip, uint16_t port,
                struct sockaddr_in* addr);
void fromIpPort(const char* ip, uint16_t port,
                struct sockaddr_in6* addr);

int getSocketError(int sockfd);

const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr);
const struct sockaddr* sockaddr_cast(const struct sockaddr_in6* addr);
struct sockaddr* sockaddr_cast(struct sockaddr_in6* addr);
const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr);
const struct sockaddr_in6* sockaddr_in6_cast(const struct sockaddr* addr);

struct sockaddr_in6 getLocalAddr(int sockfd);
struct sockaddr_in6 getPeerAddr(int sockfd);
bool isSelfConnect(int sockfd);

}
}
}

#endif  // MUDUO_NET_SOCKETSOPS_H
