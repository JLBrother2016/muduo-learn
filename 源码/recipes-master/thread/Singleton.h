// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#ifndef MUDUO_BASE_SINGLETON_H
#define MUDUO_BASE_SINGLETON_H

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <stdlib.h> // atexit

namespace muduo
{

template<typename T>
class Singleton : boost::noncopyable
{
 public:
  static T& instance()
  {
    pthread_once(&ponce_, &Singleton::init); // 调用会回调函数
    return *value_;
  }
// 单例类的实现就是把构造函数和析构函数设置为私有, 然后用一个static函数来声明一个对象
 private:
  Singleton();
  ~Singleton();
// exit函数运行时首先会执行由atexit()函数登记的函数，然后会做一些自身的清理工作，
// 同时刷新所有输出流、关闭所有打开的流并且关闭通过标准I/O函数tmpfile()创建的临时文件，
// 最后调用_exit系统函数
  static void init()
  {
    value_ = new T();
    ::atexit(destroy);  // 注册exit系统调用的函数
  }

  static void destroy()
  {
    delete value_;
  }

 private:
  static pthread_once_t ponce_;
  static T*             value_;
};
// 静态变量的初始化
template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;
// 必须在头文件中定义static变量
template<typename T>
T* Singleton<T>::value_ = NULL;

}
#endif

