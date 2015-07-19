/*
	参考libc.pdf文档
	文件的基本读写操作
	Low-Level Input/Output
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd;
	char buf[1024];
	if(argc<2){

		printf("please input filename\n");
		exit(1);
	} else {
		
		umask(0000);//改变文件的默认权限
		//打开文件，如果没有就创建一个文件，权限是666
		fd = open(argv[1], O_RDWR|O_CREAT,0666); 
		if(fd < 0){
			printf("Open file filed!\n");
			exit(1);
		}

		write(fd,"Hello world!\n",13);//写字符到文件中
	}
	close(fd);//关闭文件

	memset(buf,0,1024); //分配内存，并清0

	fd = open(argv[1], O_RDWR); 
	read(fd,buf,1024);
	printf("buf = %s\n",buf);

	int i = lseek(fd,0,SEEK_END);//计算文件长度
	printf("The file length = %d\n",i);

	pwrite(fd,"ABC\n",4,i);//在文件中追加内容

	close(fd);//关闭文件
	
	return 0;
}
