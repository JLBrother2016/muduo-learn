#include "Mutex.h"
#include "Thread.h"
#include <set>
#include <stdio.h>

class Request;          // 声明一个类

class Inventory         // inventory 清单, 详细目录
{
 public:
  void add(Request* req)
  {
    muduo::MutexLockGuard lock(mutex_);
    requests_.insert(req);
  }

  void remove(Request* req) __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);
    requests_.erase(req);
  }

  void printAll() const;

 private:
  mutable muduo::MutexLock mutex_;
  std::set<Request*> requests_;          // 将请求的对象指针放入一个集合中
};

Inventory g_inventory;     // 全局类对象

class Request    // request类
{
 public:
  void process() // __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);  // 加锁
    g_inventory.add(this);               // 加入目录
    // ...
  }

  ~Request() __attribute__ ((noinline))  // 析构函数不进行内联操作
  {
    muduo::MutexLockGuard lock(mutex_);
    sleep(1);
    g_inventory.remove(this);            // 在析构函数中将请求移除目录
  }

  void print() const __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);
    // ...
  }

 private:
  mutable muduo::MutexLock mutex_;       // 私有的mutable成员成员变量
};

void Inventory::printAll() const         // 打印出目录中的所有内容
{
  muduo::MutexLockGuard lock(mutex_);    // 加锁, print函数中也会加锁
  sleep(1);
  for (std::set<Request*>::const_iterator it = requests_.begin();
      it != requests_.end();
      ++it)
  {
    (*it)->print();
  }
  printf("Inventory::printAll() unlocked\n");
}

/*
void Inventory::printAll() const
{
  std::set<Request*> requests
  {
    muduo::MutexLockGuard lock(mutex_);
    requests = requests_;
  }
  for (std::set<Request*>::const_iterator it = requests.begin();
      it != requests.end();
      ++it)
  {
    (*it)->print();
  }
}
*/

void threadFunc()
{
  Request* req = new Request;
  req->process();    //process函数中会加锁
  delete req;
}

int main()
{
  muduo::Thread thread(threadFunc);     // 构造函数创建一个线程对象
  thread.start();                       // 执行线程
  usleep(500 * 1000);                   // 睡5s
  g_inventory.printAll();               // 可能会死锁
  thread.join();                        // 等待线程死亡
}
