/*
* 写管道
* 进程通信--有名管道
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{	
	int fd;
	char cont_w[] = "hello world\n";

	//建立管道文件
	
	if(mkfifo("fifofile",0666)<0 && errno != EEXIST){
		perror("create fifo failed");
		exit(-1);
	}else{
		printf("create fifo succeed\n");
	}

	fd = open("fifofile",O_WRONLY,0666);
	if (fd>0){
		while(1){
			write(fd,cont_w,sizeof(cont_w));
			printf("write succeed");
			sleep(2);
		}
		close(fd);
	} else{
		perror("open failed");
	}

	return 0;
}