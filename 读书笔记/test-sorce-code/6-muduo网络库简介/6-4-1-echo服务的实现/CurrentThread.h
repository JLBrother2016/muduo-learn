// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_CURRENTTHREAD_H
#define MUDUO_BASE_CURRENTTHREAD_H

#include <stdint.h>

namespace muduo          // muduo命名空间
{
namespace CurrentThread  // CurrentThread命名空间  
{
  // internal
  extern __thread int t_cachedTid;          // 每个线程的缓存线程id
  extern __thread char t_tidString[32];     // 每个线程id的字符串
  extern __thread int t_tidStringLength;    // id的长度
  extern __thread const char* t_threadName; // 每个线程的名字
  void cacheTid();                          // 这个在哪里定义的?

  inline int tid()
  {
    if (__builtin_expect(t_cachedTid == 0, 0))
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline int tidStringLength() // for logging
  {
    return t_tidStringLength;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();

  void sleepUsec(int64_t usec);
}
}

#endif
