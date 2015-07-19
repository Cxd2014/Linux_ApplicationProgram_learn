/*
* 进程通信 -- 信号
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int sig_no)
{
	if(sig_no == SIGINT){
		printf("get SIGINT\n"); //ctrl + c 发送SIGINT

	}else if(sig_no == SIGQUIT){//ctrl + \ 发送SIGQUIT
		printf("get SIGQUIT\n");
	}
}

int main(int argc, char const *argv[])
{
	//注册信号处理函数
	/*    信号类型  处理函数       */
	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	pause(); //等待
	return 0;
}