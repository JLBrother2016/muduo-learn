#ifndef MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H
#define MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H

#include "TcpServer.h"

// RFC 862
class EchoServer
{
 public:         // 在构造函数中注册回调函数
  EchoServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr);   // 构造函数

  void start();  // calls server_.start();

 private:        // 连接成功回调该函数
  void onConnection(const muduo::net::TcpConnectionPtr& conn);
                 // 收到消息回调该函数
  void onMessage(const muduo::net::TcpConnectionPtr& conn,
                 muduo::net::Buffer* buf,
                 muduo::Timestamp time);

  muduo::net::TcpServer server_;
};

#endif  // MUDUO_EXAMPLES_SIMPLE_ECHO_ECHO_H
