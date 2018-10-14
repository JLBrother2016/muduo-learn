#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void prepare(void)
{
	printf("pid = %d prepare ...\n", static_cast<int>(getpid()));
}

void parent(void)
{
	printf("pid = %d parent ...\n", static_cast<int>(getpid()));
}

void child(void)
{
	printf("pid = %d child ...\n", static_cast<int>(getpid()));
}


int main(void)
{
	printf("pid = %d Entering main ...\n", static_cast<int>(getpid()));
// 如果一个多线程程序的某个线程调用了fork函数，那么新创建的子进程是否将自动创建和父进程相同数量的线程呢？ 
// 答案是不会，子进程只拥有一个执行线程，它是调用fork的那个线程的完整复制。 
// 并且子进程将自动继承父进程中互斥锁的状态
    // 传递的是三个函数指针
	pthread_atfork(prepare, parent, child);        //pthread_atfork()，以确保fork调用后父进程和子进程都拥有一个清楚地锁状态

	fork();

	printf("pid = %d Exiting main ...\n",static_cast<int>(getpid()));

	return 0;
}
