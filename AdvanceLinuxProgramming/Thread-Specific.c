/*
* 编译: gcc -o thread thread.c -lpthread
* 创建五个线程,学习使用线程私有数据对每个线程产生一个相应的日志文件
*/

#include <pthread.h>
#include <stdio.h>
#include <malloc.h>

/* 定义一个 pthread_key_t 用于访问线程特有数据 */
static pthread_key_t thread_log_key;

/* 向 log 文件中写数据 */
void inline write_to_thread_log(const char *message)
{
	/* 从thread_log_key中得到线程私有数据 */
	FILE *thread_log = (FILE *)pthread_getspecific(thread_log_key);
	fprintf(thread_log, "%s\n", message);
}

/* 清理函数 */
void inline close_thread_log(void *thread_log)
{
	fclose((FILE *)thread_log);
}

void *thread_function(void *args)
{
	/* 保存文件名字 */
	char thread_log_filename[20];

	FILE *thread_log;

	/* 得到进程ID来组成日志文件名字 */
	sprintf(thread_log_filename,"thread%d.log",(int)pthread_self());

	thread_log = fopen(thread_log_filename,"w");

	/* 将文件指针存放在thread_log_key标记的线程私有数据中 */
	pthread_setspecific(thread_log_key,thread_log);

	write_to_thread_log(thread_log_filename);

	/* 这里不能使用 return 只能用 pthread_exit 返回,具体原因不明 */
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t thread[5];
	int i;

	/* 创建一个 pthread_key 并注册清理函数,当线程退出时会自动
	 * 调用清理函数并将这个pthread_key作为传入清理函数
	 */
	pthread_key_create(&thread_log_key,close_thread_log);
	
	for(i = 0;i < 5;i++)
		pthread_create(&(thread[i]),NULL,&thread_function,NULL);

	for(i = 0;i < 5;i++)
		pthread_join(thread[i],NULL);

	return 0;
}