#include "echo.h"

#include "Logging.h"

#include <boost/bind.hpp>

// using namespace muduo;
// using namespace muduo::net;

EchoServer::EchoServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr)
  : server_(loop, listenAddr, "EchoServer")
{
  server_.setConnectionCallback(
      boost::bind(&EchoServer::onConnection, this, _1)); // 注册回调函数, 有一个参数
  server_.setMessageCallback(
      boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
}

void EchoServer::start()
{
  server_.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{                                                       // 对端IP地址
  LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is " // 本地IP地址
           << (conn->connected() ? "UP" : "DOWN"); // connected返回的是bool类型
}
// echo服务器的业务逻辑就是把收到的数据原封不动地发回客户端
void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf, // buf是缓冲数据块
                           muduo::Timestamp time)   // time 是收到数据的确切时间
{                                                   // epoll_wait返回的时间
  muduo::string msg(buf->retrieveAllAsString());      // 读数据
  LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
           << "data received at " << time.toString(); // 打印数据  
  conn->send(msg);                                    // 把读取的数据写回去
} 

