/*
* 内存映射的使用
* 执行命令时后面带一个文件名： ./mmap-write filename
* 通过内存映射的方式向文件中写入一个随机字符 
*/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#define FILE_LENGTH 0x10

/* 返回一个范围在[low,high]内的一个随机数 */
int random_range(unsigned const low,unsigned const high)
{
	unsigned const range = high - low + 1;
	return low + (int)( ((double)range)*rand() / (RAND_MAX+1.0));
}

int main(int argc, char const *argv[])
{
	int fd;
	void *file_memory;

	/* 为随机树生成器提供种子 */
	srand(time(NULL));

	fd = open(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	/* lseek 函数的作用是重新定位文件的偏移值，这里的作用是扩大文件的大小为 FILE_LENGTH+1 */
	lseek(fd,FILE_LENGTH+1,SEEK_SET);

	write(fd,"",1);
	lseek(fd,0,SEEK_SET);

	/* 将生成的文件映射到内存，返回映射内存的起始地址 */
	file_memory = mmap(NULL,FILE_LENGTH,PROT_WRITE,MAP_SHARED,fd,0);	
	close(fd);

	/* 向映射内存出写一个随机数 */
	sprintf((char *)file_memory,"%d\n",random_range(-100,100));

	/* 取消映射 */
	munmap(file_memory,FILE_LENGTH);

	return 0;
}