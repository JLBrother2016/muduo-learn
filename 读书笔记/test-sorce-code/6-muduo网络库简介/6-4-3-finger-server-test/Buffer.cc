// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//

#include "Buffer.h"       // 缓冲区大小的类

#include "SocketsOps.h"   // 网络操作的库函数封装函数, 主要是加入了日志类

#include <errno.h>
#include <sys/uio.h>

using namespace muduo;
using namespace muduo::net;

const char Buffer::kCRLF[] = "\r\n";   // 文件结束符\r\n, 应该是windows下的吧

const size_t Buffer::kCheapPrepend;
const size_t Buffer::kInitialSize;

ssize_t Buffer::readFd(int fd, int* savedErrno)
{
  // saved an ioctl()/FIONREAD call to tell how much to read
  char extrabuf[65536];
  struct iovec vec[2];
  // struct iovec {
  //              void  *iov_base;    /* Starting address */
  //              size_t iov_len;     /* Number of bytes to transfer */
  //          };
  const size_t writable = writableBytes();
  vec[0].iov_base = begin()+writerIndex_;
  vec[0].iov_len = writable;
  vec[1].iov_base = extrabuf;
  vec[1].iov_len = sizeof extrabuf;
  // when there is enough space in this buffer, don't read into extrabuf.
  // when extrabuf is used, we read 128k-1 bytes at most.
  const int iovcnt = (writable < sizeof extrabuf) ? 2 : 1;
  const ssize_t n = sockets::readv(fd, vec, iovcnt);   // 读到第几个缓冲区
  if (n < 0)  // 读发生错误
  {
    *savedErrno = errno;
  }
  else if (implicit_cast<size_t>(n) <= writable)  // 直接写入缓冲区
  {
    writerIndex_ += n;
  }
  else    // 读出的数据太大, 放到额外的缓冲区
  {
    writerIndex_ = buffer_.size();
    append(extrabuf, n - writable);
  }
  // if (n == writable + sizeof extrabuf)
  // {
  //   goto line_30;
  // }
  return n;
}

