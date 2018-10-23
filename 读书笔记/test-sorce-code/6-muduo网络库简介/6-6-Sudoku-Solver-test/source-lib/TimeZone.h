// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_TIMEZONE_H
#define MUDUO_BASE_TIMEZONE_H

#include "copyable.h"              // copyable是一个空类
#include <boost/shared_ptr.hpp>
#include <time.h>

namespace muduo                    // muduo命名空间
{

// TimeZone for 1970~2030
class TimeZone : public muduo::copyable // 时区类
{
 public:
  explicit TimeZone(const char* zonefile);  // 显示构造函数
  TimeZone(int eastOfUtc, const char* tzname);  // a fixed timezone
  TimeZone() {}  // an invalid timezone 空的构造函数

  // default copy ctor/assignment/dtor are Okay.

  bool valid() const     // 数据是否合法
  {
    // 'explicit operator bool() const' in C++11
    return static_cast<bool>(data_);
  }

  struct tm toLocalTime(time_t secondsSinceEpoch) const;  // 获取当地的时间
  time_t fromLocalTime(const struct tm&) const;

  // gmtime(3)
  static struct tm toUtcTime(time_t secondsSinceEpoch, bool yday = false);
  // timegm(3)
  static time_t fromUtcTime(const struct tm&);
  // year in [1900..2500], month in [1..12], day in [1..31]
  static time_t fromUtcTime(int year, int month, int day,
                            int hour, int minute, int seconds);

  struct Data;    

 private:

  boost::shared_ptr<Data> data_;  // 又是用智能指针管理数据
};

}
#endif  // MUDUO_BASE_TIMEZONE_H
