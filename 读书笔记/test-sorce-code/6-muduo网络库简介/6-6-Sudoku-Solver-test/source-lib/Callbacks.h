// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef MUDUO_NET_CALLBACKS_H
#define MUDUO_NET_CALLBACKS_H

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "Timestamp.h"

namespace muduo
{

// Adapted from google-protobuf stubs/common.h
// see License in muduo/base/Types.h
template<typename To, typename From>
inline ::boost::shared_ptr<To> down_pointer_cast(const ::boost::shared_ptr<From>& f)  // 用shared_ptr来管理类型
{
  if (false)
  {
    implicit_cast<From*, To*>(0);   // 进行隐式转换, 最后返回的是From类型
  }

#ifndef NDEBUG
  assert(f == NULL || dynamic_cast<To*>(get_pointer(f)) != NULL);
#endif
  return ::boost::static_pointer_cast<To>(f);   // 类型的强制转换
}

namespace net
{

// All client visible callbacks go here.

class Buffer;        // 声明一个buffer换冲类
class TcpConnection; // 声明一个tcp连接的类TcpConnectionPtr
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;//利用shared_ptr管理连接
typedef boost::function<void()> TimerCallback;  // 定时器回调, 空函数指针
// 连接回调函数, shared_ptr<TcpConnection>的常量引用
typedef boost::function<void (const TcpConnectionPtr&)> ConnectionCallback;
// 断开连接的回调函数
typedef boost::function<void (const TcpConnectionPtr&)> CloseCallback;
// 写完成的回调函数
typedef boost::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
// 高水位标记的回调函数
typedef boost::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;
// 消息回调函数
// the data has been read to (buf, len)
typedef boost::function<void (const TcpConnectionPtr&,
                              Buffer*,
                              Timestamp)> MessageCallback;
// 默认链接的回调函数
void defaultConnectionCallback(const TcpConnectionPtr& conn);
// 默认的消息回调函数
void defaultMessageCallback(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp receiveTime);

}
}

#endif  // MUDUO_NET_CALLBACKS_H
