// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include "Atomic.h"

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pthread.h>

namespace muduo
{

class Thread : boost::noncopyable              // 线程封装的类
{
 public:
  typedef boost::function<void ()> ThreadFunc; // 重定义一个函数对象
  // 显示声明一个构造函数, 线程调用的函数接口, 缺省的名字服务
  explicit Thread(const ThreadFunc&, const std::string& name = std::string());
  ~Thread();     // 线程的析构函数

  void start();  // 开始线程 
  void join();   // 线程的同步

  bool started() const { return started_; } // 返回线程的状态, 看看线程是否已经被启动了
  // pthread_t pthreadId() const { return pthreadId_; }
  pid_t tid() const { return *tid_; }   // 返回线程的ID
  const std::string& name() const { return name_; } // 返回线程的名字

  static int numCreated() { return numCreated_.get(); } // static的类成员函数是所有类对象所共有的函数

 private:
  bool        started_;             // 是否启动
  bool        joined_;              // 是否同步
  pthread_t   pthreadId_;           // 线程ID
  boost::shared_ptr<pid_t> tid_;    // shared_ptr共享指针(智能指针)管理资源
  ThreadFunc  func_;                // 函数对象
  std::string name_;                // 线程名字

  static AtomicInt32 numCreated_;   // 原子型的32位整型的static int变量, 类对象所共有
};

namespace CurrentThread             // 当前线程的作用域
{
  pid_t tid();                      // 返回当前线程的ID
  const char* name();               // 返回当前线程的名字
  bool isMainThread();              // 判断当前线程是否是主线程
}

}

#endif
