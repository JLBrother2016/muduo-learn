// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#ifndef MUDUO_BASE_MUTEX_H
#define MUDUO_BASE_MUTEX_H

#include "Thread.h"

#include <boost/noncopyable.hpp>
#include <assert.h>
#include <pthread.h>

namespace muduo
{

class MutexLock : boost::noncopyable       // 互斥锁不可以被拷贝
{
 public:
  MutexLock()
    : holder_(0)                           // holder_为持有线程的id, tid
  {
    pthread_mutex_init(&mutex_, NULL);     // 在构造函数中初始化互斥量
  }

  ~MutexLock()
  {
    assert(holder_ == 0);                  // 在析构函数中, 先检查是否将持有者线程全部清楚, 即调至为0
    pthread_mutex_destroy(&mutex_);        // 在析构函数中, 销毁互斥量
  }

  bool isLockedByThisThread()
  {
    return holder_ == CurrentThread::tid(); // 如果是该线程持有互斥量, holder_就等于线程id;
  }

  void assertLocked()
  {
    assert(isLockedByThisThread());       // 断言线程是否被锁, 如果持有者是该线程, 表示该线程被锁
  }

  // internal usage
  // 用友元函数实现访问权限的限制
  void lock()                            // 仅供MutexLockGuard调用, 严禁用户代码调用
  {
    pthread_mutex_lock(&mutex_);         // 先将线程锁住，这两行顺序不能反
    holder_ = CurrentThread::tid();      // 再将线程id赋值给持有者holder_
  }

  void unlock()
  {
    holder_ = 0;                         // 解锁时, 先将持有者置0
    pthread_mutex_unlock(&mutex_);       // 再将互斥量解锁
  }

  pthread_mutex_t* getPthreadMutex() /* non-const */ 
  {                                      // 仅供Condition 调用, 严禁用户代码调用
    return &mutex_;                      // 直接返回互斥量的地址
  }

 private:

  pthread_mutex_t mutex_;                // 两个私有成员变量
  pid_t holder_;                         // 一个是互斥量, 另一个是持有者
};

class MutexLockGuard : boost::noncopyable // 重新声明一个类在构造函数中加锁, 在析构函数中解锁
{
 public:     // 利用了作用域的概念
  explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex)
  {
    mutex_.lock();
  }

  ~MutexLockGuard()
  {
    mutex_.unlock();
  }

 private:

  MutexLock& mutex_;              // 一个私有成员变量是自己声明的MutexLock类对象, 这是一种组合方法
};

}

// Prevent misuse like:
// MutexLockGuard(mutex_);        // 防止遗漏变量名
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"

#endif  // MUDUO_BASE_MUTEX_H
