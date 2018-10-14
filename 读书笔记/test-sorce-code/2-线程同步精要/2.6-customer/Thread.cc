// excerpts from http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (giantchen at gmail dot com)

#include "Thread.h"

#include <boost/weak_ptr.hpp>

#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace muduo
{
namespace CurrentThread
{
  __thread const char* t_threadName = "unknown";  // 每个线程都会持有一个t_threadName变量, 表示当前线程的名字    
}
}

namespace
{
__thread pid_t t_cachedTid = 0;     // t_cachedTid 缓存线程ID

pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid)); // 将一次内核调用转换为pid
}

void afterFork()
{
  t_cachedTid = gettid();                           // 获得当前线程的ID
  muduo::CurrentThread::t_threadName = "main";      // 将当前线程的名字改为主线程
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer   // 线程名字服务初始化的类
{
 public:
  ThreadNameInitializer()     // 在构造函数中初始化线程名字, 并调用pthread_atfork
  {
    muduo::CurrentThread::t_threadName = "main";
    pthread_atfork(NULL, NULL, &afterFork);// fork创建进程后,子进程调用afterFork函数
  }
};

ThreadNameInitializer init;  // 在作用域中声明一个全局类对象

struct ThreadData            // 声明一个线程数据类
{
  typedef muduo::Thread::ThreadFunc ThreadFunc;  // 线程安全的函数对象
  ThreadFunc func_;          // 函数对象
  std::string name_;         // 名字服务
  boost::weak_ptr<pid_t> wkTid_; // 弱引用, weak_ptr智能指针, 不会改变引用计数的值
  // weak_ptr避免了循环引用（或环形引用）的问题
  // weak_ptr是为了配合shared_ptr而引入的一种智能指针，
  // 它指向一个由shared_ptr管理的对象而不影响所指对象的生命周期，
  // 也就是将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。
  // 不论是否有weak_ptr指向，一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放。
  // 从这个角度看，weak_ptr更像是shared_ptr的一个助手而不是智能指针
  // weak_ptr并不改变其所共享的shared_ptr实例的引用计数，
  // 那就可能存在weak_ptr指向的对象被释放掉这种情况

  ThreadData(const ThreadFunc& func,
             const std::string& name,
             const boost::shared_ptr<pid_t>& tid)
    : func_(func),    // 构造函数
      name_(name),
      wkTid_(tid)     // 使用弱引用指针指向线程ID
  { }

  void runInThread()
  {
    pid_t tid = muduo::CurrentThread::tid();       // 获取当前线程的ID
    boost::shared_ptr<pid_t> ptid = wkTid_.lock(); // 如果对象存在，lock()函数返回一个指向共享对象的shared_ptr，否则返回一个空shared_ptr

    if (ptid)
    {
      *ptid = tid;      // ptid 是一个shared_ptr智能指针          
      ptid.reset();     // 引用计数减1, 当引用计数为0时, 对象自动析构
    }

    muduo::CurrentThread::t_threadName = name_.empty() ? "muduoThread" : name_.c_str();          // 线程名字是否为空, 如果是赋值为muduoThread, 否则赋值为name_
    // 调用为进程设计的系统调用prctl函数
    ::prctl(PR_SET_NAME, muduo::CurrentThread::t_threadName);  // 将进程重命名
    // 调用构造函数传入的线程函数
    func_(); // FIXME: surround with try-catch, see muduo
    muduo::CurrentThread::t_threadName = "finished";  // 更改线程的名字为finished
  }
};

void* startThread(void* obj)    // 传入泛型指针
{                               // 强行转换为ThreadData类指针
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->runInThread();          // 运行对象的线程函数, 在启动线程中回调运行线程
  delete data;                  // 删除对象资源
  return NULL;
}

}

using namespace muduo;

pid_t CurrentThread::tid()
{
  if (t_cachedTid == 0)        // 获取线程ID
  {
    t_cachedTid = gettid();
  }
  return t_cachedTid;
}

const char* CurrentThread::name()
{
  return t_threadName;
}

bool CurrentThread::isMainThread()
{
  return tid() == ::getpid(); // 如果线程ID等于进程ID则证明是主线程
}

AtomicInt32 Thread::numCreated_;  // 原子操作的引用计数

Thread::Thread(const ThreadFunc& func, const std::string& n)
  : started_(false),
    joined_(false),
    pthreadId_(0),
    tid_(new pid_t(0)),
    func_(func),
    name_(n)
{
  numCreated_.increment();    // 引用计数加1
}

Thread::~Thread()
{
  if (started_ && !joined_)
  {
    pthread_detach(pthreadId_); // pthread_detach子线程会脱离主线程, 生死自理
  }
}

void Thread::start()
{
  assert(!started_);
  started_ = true;

  ThreadData* data = new ThreadData(func_, name_, tid_);   // 创建一个线程对象
  if (pthread_create(&pthreadId_, NULL, &startThread, data)) // 创建线程
  {
    started_ = false; 
    delete data;   // 异常情况
    abort();
  }
}

void Thread::join()
{
  assert(started_);
  assert(!joined_);
  joined_ = true;
  // pthread_join用来等待一个线程的结束,线程间同步的操作
  pthread_join(pthreadId_, NULL);  
}
