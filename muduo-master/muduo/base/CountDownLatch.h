// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_COUNTDOWNLATCH_H
#define MUDUO_BASE_COUNTDOWNLATCH_H

#include <muduo/base/Condition.h>
#include <muduo/base/Mutex.h>

#include <boost/noncopyable.hpp>

namespace muduo
{

class CountDownLatch : boost::noncopyable
{
 public:
  // latch是门闩的意思
  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:                   // 顺序很重要, 先mutex后condition
  mutable MutexLock mutex_; // mutex_应先于condition_构造, 并作为后者的构造参数
  Condition condition_;
  int count_;               // 计数值, 用于保存锁持有者的个数
};

}
#endif  // MUDUO_BASE_COUNTDOWNLATCH_H
