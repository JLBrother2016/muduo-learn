// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "CountDownLatch.h"

using namespace muduo;

CountDownLatch::CountDownLatch(int count)
  : mutex_(),
    condition_(mutex_),     // 构造函数的初始化顺序要与成员声明保持一致
    count_(count)           // 初始化有几个线程要等待, 有点像屏障的味道
{
}

void CountDownLatch::wait()
{
  MutexLockGuard lock(mutex_);
  while (count_ > 0)        // 如果计数值大于0, 条件变量就进行等待
  {
    condition_.wait();
  }
}

void CountDownLatch::countDown()
{
  MutexLockGuard lock(mutex_); // 先加锁, 计数值自减1
  --count_;
  if (count_ == 0)          // 当计数值为0的时候, 条件变量就通知所有的线程
  {
    condition_.notifyAll();
  }                         // 该函数执行完后, 会自动析构
}

int CountDownLatch::getCount() const
{
  MutexLockGuard lock(mutex_); // 加锁
  return count_;
}

