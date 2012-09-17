#ifndef THREAD_H_INCLUDE
#define THREAD_H_INCLUDE

#include <pthread.h>
#include <stdint.h>

#include <string>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>


// Taken from muduo
// muduo/base/Condition.h
// muduo/base/Mutex.h
// muduo/base/Thread.h

// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)


// RAII
class Mutex : boost::noncopyable
{
 public:
  Mutex() { pthread_mutex_init(&mutex_, NULL); }
  ~Mutex() { pthread_mutex_destroy(&mutex_); }

  void lock() { pthread_mutex_lock(&mutex_); }
  void unlock() { pthread_mutex_unlock(&mutex_); }

  pthread_mutex_t* getMutex() { return &mutex_; }

 private:
  pthread_mutex_t mutex_;
};

// RAII
class MutexGuard : boost::noncopyable
{
 public:
  explicit MutexGuard(Mutex& mutex) : mutex_(mutex) { mutex_.lock(); }
  ~MutexGuard() { mutex_.unlock(); }

 private:
  Mutex& mutex_;
};

class Condition : boost::noncopyable
{
 public:
  explicit Condition(Mutex& mutex) : mutex_(mutex) 
  { pthread_cond_init(&cond_, NULL); }
  ~Condition(){ pthread_cond_destroy(&cond_); }

  void wait(){ pthread_cond_wait(&cond_, mutex_.getMutex()); }
  void notify() { pthread_cond_signal(&cond_); }
  void notifyAll() {pthread_cond_broadcast(&cond_);}

 private:
  Mutex& mutex_;
  pthread_cond_t cond_;
};


class Thread : boost::noncopyable
{
 public:
  typedef boost::function<void ()> ThreadFunc;
  explicit Thread(const ThreadFunc&, const std::string& namearg = std::string());
  ~Thread();

  void start();
  int join(); // return pthread_join()

  bool started() const { return started_; }
  pid_t tid() const { return tid_; }
  const std::string& name() const { return name_; }

 private:
  static void* startThread(void* thread);
  void runInThread();

  bool        started_;
  pthread_t   pthreadId_;
  pid_t       tid_;
  ThreadFunc  func_;
  std::string name_;
};

namespace CurrentThread
{
  // internal
  extern __thread int t_cachedTid;
  extern __thread char t_tidString[32];
  extern __thread const char* t_threadName;
  void cacheTid();

  inline int tid()
  {
    if (t_cachedTid == 0)
    {
      cacheTid();
    }
    return t_cachedTid;
  }

  inline const char* tidString() // for logging
  {
    return t_tidString;
  }

  inline const char* name()
  {
    return t_threadName;
  }

  bool isMainThread();
}


#endif // THREAD_H_INCLUDE
