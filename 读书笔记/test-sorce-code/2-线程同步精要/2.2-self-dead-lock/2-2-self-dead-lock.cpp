#include "Mutex.h"

class Request     // 请求类
{
 public:
  void process() // __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);   // 作用域加锁
    print();                              // 会递归加锁, 一般会发生死锁
  }

  void print() const // __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);   // 作用域加锁
  }

 private:
  mutable muduo::MutexLock mutex_;        // 可变的条件变量
};

int main()
{
  Request req;
  req.process();
}
