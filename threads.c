/*
* 创建三个线程，同步操作
× 编译命令 gcc -pthread -o thread thread.c
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//定义一个锁
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
//线程初始化函数
void *thread_function(void *arg)
{
	pthread_mutex_lock(&mymutex); //锁定
	int i;
	for(i=0;i<5;i++){
		printf("thread init = %d\n",(int)arg);
	}
	pthread_mutex_unlock(&mymutex);//解锁
}

int main(int argc, char const *argv[])
{
	pthread_t mythread[3];
	int i;
	for(i = 0;i<3;i++){
		//创建一个线程
		if(pthread_create(&mythread[i],NULL,thread_function,(void *)i) == 0){
			printf("create succeed\n");
		}
	}
	sleep(1);
	return 0;
}
