/*
* 编译: gcc -o thread thread.c -lpthread
* 创建一个detached threads(脱离线程):
* 运行后自动结束并清理,不需要主线程使用pthread_join函数获取返回值
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_fanction(void *thread_arg)
{
	system("ls -l /");
	return NULL;
}

int main(int argc, char const *argv[])
{
	/* 创建一个 pthread_attr_t 对象 attr */
	pthread_attr_t attr;

	pthread_t thread;

	/* 调用 pthread_attr_init 初始化 attr 为默认值*/
	pthread_attr_init(&attr);

	/* 设置 attr 对象的值,使他成为脱离线程 */
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
	/* 将 attr 对象传入 pthread_create 函数*/
	pthread_create(&thread,&attr,&thread_fanction,NULL);

	printf("hello\n");

	/* 等待线程执行结束 */
	sleep(2);

	return 0;
}