// Taken from PCRE pcre_stringpiece.h
//
// Copyright (c) 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Sanjay Ghemawat
//
// A string like object that points into another piece of memory.
// Useful for providing an interface that allows clients to easily
// pass in either a "const char*" or a "string".
//
// Arghh!  I wish C++ literals were automatically of type "string".

#ifndef MUDUO_BASE_STRINGPIECE_H
#define MUDUO_BASE_STRINGPIECE_H

#include <string.h>
#include <iosfwd>    // for ostream forward-declaration, 前向输出流

#include "Types.h"
#ifndef MUDUO_STD_STRING
#include <string>
#endif

namespace muduo {    // muduo的命名空间

// For passing C-style string argument to a function.
class StringArg // copyable, 可利用构造赋值函数
{
 public:
  StringArg(const char* str)  // 以字符指针的方式构造字符串
    : str_(str)
  { }

  StringArg(const string& str)// 以字符引用的方式构造字符串
    : str_(str.c_str())
  { }

#ifndef MUDUO_STD_STRING      // 如果没有使用这个宏, 那么就需要手动添加std的命名空间
  StringArg(const std::string& str)
    : str_(str.c_str())
  { }
#endif

  const char* c_str() const { return str_; }

 private:
  const char* str_;   // 常量指针
};

class StringPiece {   // 字符块
 private:
  const char*   ptr_; // 一个私有的字符常量指针
  int           length_; // 一个私有成员表示字符串的长度

 public:
  // We provide non-explicit singleton constructors so users can pass
  // in a "const char*" or a "string" wherever a "StringPiece" is
  // expected.
  StringPiece()     // 空的构造函数
    : ptr_(NULL), length_(0) { }
  StringPiece(const char* str) // 一个常量指针进行构造
    : ptr_(str), length_(static_cast<int>(strlen(ptr_))) { }
  StringPiece(const unsigned char* str)
    : ptr_(reinterpret_cast<const char*>(str)),  // 处理无关类型之间的转换
      length_(static_cast<int>(strlen(ptr_))) { }
  StringPiece(const string& str)
    : ptr_(str.data()), length_(static_cast<int>(str.size())) { }
#ifndef MUDUO_STD_STRING
  StringPiece(const std::string& str)
    : ptr_(str.data()), length_(static_cast<int>(str.size())) { }
#endif
  StringPiece(const char* offset, int len)
    : ptr_(offset), length_(len) { }

  // data() may return a pointer to a buffer with embedded NULs, and the
  // returned buffer may or may not be null terminated.  Therefore it is
  // typically a mistake to pass data() to a routine that expects a NUL
  // terminated string.  Use "as_string().c_str()" if you really need to do
  // this.  Or better yet, change your routine so it does not rely on NUL
  // termination.
  const char* data() const { return ptr_; }
  int size() const { return length_; }
  bool empty() const { return length_ == 0; }
  const char* begin() const { return ptr_; }   // 开始的字符
  const char* end() const { return ptr_ + length_; } // 结束的字符

  void clear() { ptr_ = NULL; length_ = 0; } // 直接清除掉字符串
  void set(const char* buffer, int len) { ptr_ = buffer; length_ = len; }
  void set(const char* str) {
    ptr_ = str;     // 设置这个私有的字符串指针
    length_ = static_cast<int>(strlen(str)); 
  }
  void set(const void* buffer, int len) {
    ptr_ = reinterpret_cast<const char*>(buffer);
    length_ = len;
  }
  // 重载[]中括号操作符, 应该有一个容错处理把
  char operator[](int i) const { return ptr_[i]; }

  void remove_prefix(int n) {  // 字符串整体向后移动n个字符
    ptr_ += n;
    length_ -= n;
  }

  void remove_suffix(int n) {  // 字符串尾部删除n 个字符
    length_ -= n;
  }

  bool operator==(const StringPiece& x) const { // 重载等于==操作符
    return ((length_ == x.length_) &&
            (memcmp(ptr_, x.ptr_, length_) == 0));
  }
  bool operator!=(const StringPiece& x) const { // 重载不等于!=操作符
    return !(*this == x);
  }
// 用宏替换两个操作符
#define STRINGPIECE_BINARY_PREDICATE(cmp,auxcmp)                             \
  bool operator cmp (const StringPiece& x) const {                           \
    int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_); \
    return ((r auxcmp 0) || ((r == 0) && (length_ cmp x.length_)));          \
  }
  STRINGPIECE_BINARY_PREDICATE(<,  <);
  STRINGPIECE_BINARY_PREDICATE(<=, <);
  STRINGPIECE_BINARY_PREDICATE(>=, >);
  STRINGPIECE_BINARY_PREDICATE(>,  >);
#undef STRINGPIECE_BINARY_PREDICATE
  // 比较函数, 比较x和ptr的大小关系
  int compare(const StringPiece& x) const {
    int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_);
    if (r == 0) {
      if (length_ < x.length_) r = -1;
      else if (length_ > x.length_) r = +1;
    }
    return r;
  }

  string as_string() const {
    return string(data(), size());  // 将ptr构造成一个string类对象
  }

  void CopyToString(string* target) const {
    target->assign(ptr_, length_);  // 复制构造函数
  }

#ifndef MUDUO_STD_STRING    // 如果没有使用std命名空间
  void CopyToStdString(std::string* target) const {
    target->assign(ptr_, length_);
  }
#endif

  // Does "this" start with "x"   // ptr是否以x开头的字符串
  bool starts_with(const StringPiece& x) const {
    return ((length_ >= x.length_) && (memcmp(ptr_, x.ptr_, x.length_) == 0));
  }
};

}   // namespace muduo

// ------------------------------------------------------------------
// Functions used to create STL containers that use StringPiece
//  Remember that a StringPiece's lifetime had better be less than
//  that of the underlying string or char*.  If it is not, then you
//  cannot safely store a StringPiece into an STL container
// ------------------------------------------------------------------

#ifdef HAVE_TYPE_TRAITS   // 这个的作用是什么呢?
// This makes vector<StringPiece> really fast for some STL implementations
template<> struct __type_traits<muduo::StringPiece> {
  typedef __true_type    has_trivial_default_constructor;
  typedef __true_type    has_trivial_copy_constructor;
  typedef __true_type    has_trivial_assignment_operator;
  typedef __true_type    has_trivial_destructor;
  typedef __true_type    is_POD_type;
};
#endif

// allow StringPiece to be logged
std::ostream& operator<<(std::ostream& o, const muduo::StringPiece& piece);

#endif  // MUDUO_BASE_STRINGPIECE_H
