// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CONDITION_H
#define MUDUO_BASE_CONDITION_H

#include "Mutex.h"

#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace muduo
{

class Condition : boost::noncopyable      // 没有拷贝构造函数和赋值函数
{
 public:
  explicit Condition(MutexLock& mutex)    // 显示构造函数
    : mutex_(mutex)
  {
    MCHECK(pthread_cond_init(&pcond_, NULL)); // 构造函数中初始化条件变量
  }

  ~Condition()
  {
    MCHECK(pthread_cond_destroy(&pcond_)); // 析构函数中销毁条件变量
  }

  void wait()
  {
    MutexLock::UnassignGuard ug(mutex_);   // 先加锁再等待
    MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
  }

  // returns true if time out, false otherwise.
  bool waitForSeconds(double seconds);

  void notify()      // 通知某一个线程
  {
    MCHECK(pthread_cond_signal(&pcond_));
  }

  void notifyAll()   // 通知所有相关的线程
  {
    MCHECK(pthread_cond_broadcast(&pcond_));
  }

 private:
  MutexLock& mutex_;       // 私有成员, 一个互斥变量的封装类
  pthread_cond_t pcond_;   // 一个条件变量
};

}
#endif  // MUDUO_BASE_CONDITION_H
