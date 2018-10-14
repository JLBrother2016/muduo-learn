#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *arg)    // 线程调用函数
{
    printf("pid = %d begin doit ...\n", static_cast<int>(getpid()));
    pthread_mutex_lock(&mutex);
    struct timespec ts = {2, 0};       // 锁住睡2S
    nanosleep(&ts, NULL);
    pthread_mutex_unlock(&mutex);
    printf("pid = %d end doit ...\n", static_cast<int>(getpid()));

    return NULL;
}

void prepare(void)        // 解锁
{
    pthread_mutex_unlock(&mutex);
}

void parent(void)         // 加锁
{
    pthread_mutex_lock(&mutex);
}

int main(void)
{
    // 先调用当调用fork时，内部创建子进程前在父进程中会调用prepare，内部创建子进程成功后，父进程会调用parent ，子进程会调用child(NULL)
    pthread_atfork(prepare, parent, NULL);  // pthread_atfork 会先于fork调用
    printf("pid = %d Entering main ...\n", static_cast<int>(getpid()));
    pthread_t tid;
    pthread_create(&tid, NULL, doit, NULL); // 创建一个子线程调用doit, 会阻塞2S 
    struct timespec ts = {1, 0};
    nanosleep(&ts, NULL);                   // 延时1S
    // 调用fork之前, 父进程会解锁, fork之后父进程会加锁, 两个线程同时抢占同一把锁会阻塞等待
    if (fork() == 0)                        // 子进程
    {
        doit(NULL);                         // 子进程中, 调用doit
    }
    pthread_join(tid, NULL);                // 等子线程死掉
    printf("pid = %d Exiting main ...\n", static_cast<int>(getpid()));

    // 但在执行fork() 创建子进程之前，先执行prepare(), 将子线程加锁的mutex 解锁下，
    // 然后为了与doit() 配对，在创建子进程成功后，父进程调用parent() 再次加锁，这时父进程的doit() 就可以接着解锁执行下去。
    // 而对于子进程来说，由于在fork() 创建子进程之前，mutex已经被解锁，故复制的状态也是解锁的，所以执行doit()就不会死锁了

    return 0;
}
