// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

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
  {                                               //Threads使用互斥锁和条件变量保证由pthread_once()指定的函数执行且仅执行一次, 在多线性中也只被执行一次
    pthread_once(&ponce_, &Singleton::init);      //执行一次马上销毁
    return *value_;
  }

 private:
  Singleton();                //私有的构造函数，可以用static成员函数来创建对象
  ~Singleton();

  static void init()
  {
    value_ = new T();         //创建一个对象
    ::atexit(destroy);        //回调销毁函数
  }

  static void destroy()
  {
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];   //防止不完全指针, 编译器报错
    T_must_be_complete_type dummy; (void) dummy;
    delete value_;
  }

 private:
  static pthread_once_t ponce_;
  static T*             value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

}
#endif

