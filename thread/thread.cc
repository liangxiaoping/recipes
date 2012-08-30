// Taken from muduo
// muduo/base/Thread.cc

// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)


#include "thread.h"

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace CurrentThread
{
  __thread int t_cachedTid = 0;
  __thread char t_tidString[32];
  __thread const char* t_threadName = "unknown";
  const bool sameType = boost::is_same<int, pid_t>::value;
  BOOST_STATIC_ASSERT(sameType);
}

namespace detail
{

// 不用pthread_self()获取线程ID
// pthread_t thid = pthread_self(), thid is opaque(uintptr_t)
// pid_t tid = gettid(), tid is task id, usually a small integer
pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void afterFork()
{
  CurrentThread::t_cachedTid = 0;
  CurrentThread::t_threadName = "main";
  CurrentThread::tid();
  // no need to call pthread_atfork(NULL, NULL, &afterFork);
}

class ThreadNameInitializer
{
 public:
  ThreadNameInitializer()
  {
    CurrentThread::t_threadName = "main";
    CurrentThread::tid();
    pthread_atfork(NULL, NULL, &afterFork);  // 清理fork后继承的资源
  }
};

ThreadNameInitializer init;
}


// 仿照getpid()对gettid()进行缓存
// getpid()通常第一次调用是一个系统调用，后面的调用都不是了，系统缓存了。
// 因为一个进程的ID是不会变的，除非这个进程终止。
void CurrentThread::cacheTid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = detail::gettid();
    int n = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    assert(n == 6); (void) n;
  }
}

bool CurrentThread::isMainThread()
{
  return tid() == ::getpid();
}

Thread::Thread(const ThreadFunc& func, const std::string& namearg)
  : started_(false),
    pthreadId_(0),
    tid_(0),
    func_(func),
    name_(namearg)
{
}

Thread::~Thread()
{
  // no join
}

void Thread::start()
{
  assert(!started_);
  started_ = true;
  pthread_create(&pthreadId_, NULL, &startThread, this);
}

int Thread::join()
{
  assert(started_);
  return pthread_join(pthreadId_, NULL);
}

void* Thread::startThread(void* obj)
{
  Thread* thread = static_cast<Thread*>(obj);
  thread->runInThread();
  return NULL;
}

void Thread::runInThread()
{
  tid_ = CurrentThread::tid();
  CurrentThread::t_threadName = name_.c_str();
  func_();
  CurrentThread::t_threadName = "finished";
}
