/* 
* 进程间通信--无名管道
* 只适用于父子进程之间的通信
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char w_cont[] = "hello world!";//写入管道的字符
	char r_cont[255];

	int pfd[2];
	//创建管道
	if(pipe(pfd)<0){
		perror("create pipe filed");
		exit(-1);
	}

	//创建子进程，退出父进程
	pid_t pid = fork();
	if(pid<0){
		perror("create process filed");
		exit(-1);
	}
	else if (pid>0){
		//父进程
		close(pfd[0]);//不能同时进行读写操作
		write(pfd[1],w_cont,strlen(w_cont)); //向管道内写入字符
		close(pfd[1]);
		wait();//等待子进程读完成
	}else{
		//子进程
		sleep(1);//等待父进程写完成
		close(pfd[1]);
		read(pfd[0],r_cont,255);
		printf("child process read:%s\n",r_cont);
	}

	return 0;
}
