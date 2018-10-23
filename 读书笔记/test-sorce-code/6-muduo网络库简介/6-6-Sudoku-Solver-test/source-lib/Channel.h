// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_CHANNEL_H
#define MUDUO_NET_CHANNEL_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "Timestamp.h"

namespace muduo
{
namespace net
{

class EventLoop;         // 事件循环类

///
/// A selectable I/O channel.
///
/// This class doesn't own the file descriptor.
/// The file descriptor could be a socket,
/// an eventfd, a timerfd, or a signalfd
class Channel : boost::noncopyable     // 一个可选择的I/O通道, 用于事件回调
{
 public:
  typedef boost::function<void()> EventCallback;  // 函数对象
  typedef boost::function<void(Timestamp)> ReadEventCallback; // 读事件回调函数

  Channel(EventLoop* loop, int fd);
  ~Channel();

  void handleEvent(Timestamp receiveTime);
  void setReadCallback(const ReadEventCallback& cb)    // 注册回调函数
  { readCallback_ = cb; }
  void setWriteCallback(const EventCallback& cb)
  { writeCallback_ = cb; }
  void setCloseCallback(const EventCallback& cb)
  { closeCallback_ = cb; }
  void setErrorCallback(const EventCallback& cb)
  { errorCallback_ = cb; }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  void setReadCallback(ReadEventCallback&& cb)
  { readCallback_ = std::move(cb); }
  void setWriteCallback(EventCallback&& cb)
  { writeCallback_ = std::move(cb); }
  void setCloseCallback(EventCallback&& cb)
  { closeCallback_ = std::move(cb); }
  void setErrorCallback(EventCallback&& cb)
  { errorCallback_ = std::move(cb); }
#endif

  /// Tie this channel to the owner object managed by shared_ptr,
  /// prevent the owner object being destroyed in handleEvent.
  void tie(const boost::shared_ptr<void>&);   // 建立联系

  int fd() const { return fd_; }              // 返回文件描述符
  int events() const { return events_; }      // I/O通道上的总事件个数
  void set_revents(int revt) { revents_ = revt; } // used by pollers
  // int revents() const { return revents_; }
  bool isNoneEvent() const { return events_ == kNoneEvent; }

  void enableReading() { events_ |= kReadEvent; update(); }
  void disableReading() { events_ &= ~kReadEvent; update(); }
  void enableWriting() { events_ |= kWriteEvent; update(); }
  void disableWriting() { events_ &= ~kWriteEvent; update(); }
  void disableAll() { events_ = kNoneEvent; update(); }
  bool isWriting() const { return events_ & kWriteEvent; }
  bool isReading() const { return events_ & kReadEvent; }

  // for Poller
  int index() { return index_; }
  void set_index(int idx) { index_ = idx; }

  // for debug
  string reventsToString() const;
  string eventsToString() const;

  void doNotLogHup() { logHup_ = false; }

  EventLoop* ownerLoop() { return loop_; }
  void remove();

 private:
  static string eventsToString(int fd, int ev);

  void update();
  void handleEventWithGuard(Timestamp receiveTime);   // 处理事件时加锁

  static const int kNoneEvent;    // 类共有的数据
  static const int kReadEvent;
  static const int kWriteEvent;

  EventLoop* loop_;     // 事件循环
  const int  fd_;       // 文件描述符
  int        events_;   // 事件集
  int        revents_;  // it's the received event types of epoll or poll
  int        index_;    // used by Poller.
  bool       logHup_;   // 是否被日志中断??

  boost::weak_ptr<void> tie_;
  bool tied_;
  bool eventHandling_;
  bool addedToLoop_;
  ReadEventCallback readCallback_;   // 读事件的函数对象
  EventCallback writeCallback_;      // 写事件的函数对象
  EventCallback closeCallback_;      // 关闭套接字的回调函数对象
  EventCallback errorCallback_;      // 错误处理的回调函数对象
};

}
}
#endif  // MUDUO_NET_CHANNEL_H
