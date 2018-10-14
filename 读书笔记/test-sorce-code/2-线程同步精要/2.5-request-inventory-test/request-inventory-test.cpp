#include "Mutex.h"
#include "Thread.h"
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <stdio.h>

class Request;
typedef boost::shared_ptr<Request> RequestPtr;  // 全局的shared_ptr指针

class Inventory
{
 public:
  Inventory()
    : requests_(new RequestList)
  {
  }

  void add(const RequestPtr& req)
  {
    muduo::MutexLockGuard lock(mutex_);
    if (!requests_.unique())
    {
      requests_.reset(new RequestList(*requests_));
      printf("Inventory::add() copy the whole list\n");
    }
    assert(requests_.unique());
    requests_->insert(req);
  }

  void remove(const RequestPtr& req) // __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);
    if (!requests_.unique())
    {
      requests_.reset(new RequestList(*requests_));
      printf("Inventory::remove() copy the whole list\n");
    }
    assert(requests_.unique());
    requests_->erase(req);
  }

  void printAll() const;

 private:
  typedef std::set<RequestPtr> RequestList;
  typedef boost::shared_ptr<RequestList> RequestListPtr;

  RequestListPtr getData() const
  {
    muduo::MutexLockGuard lock(mutex_);
    return requests_;
  }

  mutable muduo::MutexLock mutex_;
  RequestListPtr requests_;
};

Inventory g_inventory;

class Request : public boost::enable_shared_from_this<Request>
{
 public:
  Request()
    : x_(0)
  {
  }

  ~Request()
  {
    x_ = -1;    // 析构没有sleep
  }
                // 但多添加了一个cancel成员函数
  void cancel() __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);
    x_ = 1;
    sleep(1);
    printf("cancel()\n");
    g_inventory.remove(shared_from_this());  // shared_from_this是boost库的
  }

  void process() // __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);
    g_inventory.add(shared_from_this());// 把之前的this指针改为shared_from_this函数
    // ...
  }

  void print() const __attribute__ ((noinline))
  {
    muduo::MutexLockGuard lock(mutex_);
    // ...
    printf("print Request %p x=%d\n", this, x_);
  }

 private:
  mutable muduo::MutexLock mutex_;
  int x_;
};

void Inventory::printAll() const
{
  RequestListPtr requests = getData();
  printf("printAll()\n");
  sleep(1);
  for (std::set<RequestPtr>::const_iterator it = requests->begin();
      it != requests->end();
      ++it)
  {
    (*it)->print();
  }
}

void threadFunc()
{
  RequestPtr req(new Request);
  req->process();
  req->cancel();
}

int main()
{
  muduo::Thread thread(threadFunc);
  thread.start();
  usleep(500*1000);
  g_inventory.printAll();
  thread.join();
}
