/*
* 信号处理应用
* 后台运行此程序 ./signal &
* 向程序发送信号,输入命令 kill -10 pid
*/

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

sig_atomic_t signal_count = 0;

void handler(int signal_number)
{
	signal_count ++;
	printf("\n The num is %d\n", signal_count);
}

int main(int argc, char const *argv[])
{
	struct sigaction sa;
	memset(&sa,0,sizeof(sa)); /* 清零 */

	sa.sa_handler = &handler; /* 得到信号处理函数的地址 */
	sigaction(SIGUSR1,&sa,NULL); /* 注册信号处理函数 */

	printf("the pid is %d\n", (int)getpid());
	printf("the SIGUSR1 num is %d\n",SIGUSR1);

	sleep(30);

	return 0;
}