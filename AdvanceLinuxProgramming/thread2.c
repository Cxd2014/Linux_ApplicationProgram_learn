/* 
* 编译: gcc -o thread thread.c -lpthread
* 创建两个线程,传递一个结构体,执行同一个函数
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct char_parms
{
	char character;
	int count;
};

void *char_print(void *parameters)
{
	struct char_parms *p = (struct char_parms *)parameters;
	int i;
	
	for(i = 0;i < p->count; i++)
		printf("%c ",p->character);

	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t thread_id1;
	pthread_t thread_id2;

	struct char_parms thread1_args;
	struct char_parms thread2_args;

	printf("hello\n");

	thread1_args.character = 'x';
	thread1_args.count = 5;
	pthread_create(&thread_id1,NULL,&char_print,&thread1_args);

	thread2_args.character = 'o';
	thread2_args.count = 10;
	pthread_create(&thread_id2,NULL,&char_print,&thread2_args);

	/* 等待两个线程执行完毕,才能退出 */
	pthread_join(thread_id1,NULL);
	pthread_join(thread_id2,NULL);

	return 0;
}