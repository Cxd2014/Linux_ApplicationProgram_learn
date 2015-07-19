/*
	错误输出函数
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd = open("hello.txt",O_RDWR,0666);
	if(fd<0)
	{
		perror("Open filed");//输出错误原因
	}
	return 0;
}

