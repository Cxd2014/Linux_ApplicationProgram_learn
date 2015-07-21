/*
* 创建线程
× 编译命令 gcc -pthread -o thread thread.c
*/
#include <stdio.h>
#include <pthread.h>

//线程初始化函数
void *thread_function(void *arg)
{
	printf("thread init = %s\n",(char *)arg);
	//返回一个 “good bye” 字符串
	pthread_exit("good bye");
}

int main(int argc, char const *argv[])
{
	void *retval; //定义一个无类型的指针
	pthread_t mythread;
	char message[] = "hello world";
	//创建一个线程
	if(pthread_create(&mythread,NULL,thread_function,(void *)message) == 0){
		printf("create succeed\n");
	}
	//等待线程执行完成并接受线程的返回值
	pthread_join(mythread,&retval);
	printf("get result = %s\n",(char *)retval);
	return 0;
}
