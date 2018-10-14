#include "Mutex.h"
#include "Thread.h"
#include <vector>
#include <stdio.h>
#include <iostream>

using namespace muduo;

class Foo
{
 public:
  void doit() const;
};

MutexLock mutex;
// std::vector<Foo> foos;

// 利用shared_ptr解决死锁
typedef std::vector<Foo> FooList;
typedef boost::shared_ptr<FooList> FooListPtr;
FooListPtr g_foos;   // 全局变量

void post(const Foo& f)
{
  printf("post\n");
  MutexLockGuard lock(mutex);   // 锁住互斥量
  // foos.push_back(f);            // 用完, 函数结束就解锁互斥量
  if(!g_foos.unique()) {
    g_foos.reset(new FooList(*g_foos));
    printf("copy the whole list\n");
  }
  printf("assert\n");
  // assert(!g_foos.unique());
  g_foos->push_back(f);
}

void traverse()
{
  // MutexLockGuard lock(mutex);   // 先加锁

  // int i = 0;
  // for (std::vector<Foo>::const_iterator it = foos.begin();
  //     it != foos.end(); ++it)
  // {
  //   std::cout << i << std::endl;
  //   it->doit();         // 程序会在这里堵塞, 这里迭代器可能会失效
  //   // it->doit(); doit函数中也会加锁, 锁进行了递归调用, 针对不可重入的锁可能会出现死锁
  //   ++i;
  // }

  /** 用一个FooListPtr栈上局部变量当做观察者 **/
  FooListPtr foos;
  {
    MutexLockGuard lock(mutex);
    foos = g_foos;
    assert(!g_foos.unique());
  }
  // assert(!g_foos.unique());  这个断言不成立
  for(std::vector<Foo>::const_iterator it = foos->begin();
      it != foos->end(); ++it) {
    it->doit();
  }
}

void Foo::doit() const
{
  Foo f;               // 生成新的对象
  post(f);             // 加锁和解锁操作, 注释掉这一行应该可以正常运行
}

int main()
{
  Foo f;
  std::cout << "begin~" << std::endl;
  post(f);
  traverse();
  std::cout << "end~" << std::endl;
}
