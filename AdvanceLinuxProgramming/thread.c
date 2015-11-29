/*
* 编译: gcc -o thread thread.c -lpthread
* 创建两个线程,观察线程调度情况
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_x(void *unused)
{
	while(1){
		fputc('x',stderr);
		sleep(1);
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t thread_id;
	/* 创建新线程 */
	pthread_create(&thread_id,NULL,&print_x,NULL);

	while(1){
		fputc('o',stderr);
		sleep(1);
	}
	return 0;
}