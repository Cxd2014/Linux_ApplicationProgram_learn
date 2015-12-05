/*
* 内存映射的使用：
* 执行命令时后面带一个文件名： ./mmap-read filename
* 通过内存映射的方式从已有文件中读出一个字符，然后乘以2倍写入
*/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#define FILE_LENGTH 0x10

int main(int argc, char const *argv[])
{
	int fd;
	void *file_memory;
	int integer;

	fd = open(argv[1],O_RDWR,S_IRUSR|S_IWUSR);

	file_memory = mmap(0,FILE_LENGTH,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	close(fd);

	/* 从 file_memory 处读取字符 */
	sscanf(file_memory,"%d",&integer);
	printf("value: %d\n", integer);
	
	sprintf((char *)file_memory,"%d\n",2*integer);
	munmap(file_memory,FILE_LENGTH);

	return 0;
}