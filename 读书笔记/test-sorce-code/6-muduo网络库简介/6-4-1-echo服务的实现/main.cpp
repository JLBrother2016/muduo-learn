#include "echo.h"

#include "Logging.h"
#include "EventLoop.h"

#include <unistd.h>

// using namespace muduo;
// using namespace muduo::net;

int main()
{
  LOG_INFO << "pid = " << getpid();   // 打印主进程的pid
  muduo::net::EventLoop loop;         // 事件循环
  muduo::net::InetAddress listenAddr(2007);
  EchoServer server(&loop, listenAddr);
  server.start();
  loop.loop();
}

