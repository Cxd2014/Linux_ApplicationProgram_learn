/*
* 利用 /dev/random 设备文件，读取系统产生的随机数
*/
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/* 返回一个范围在[low,high]内的一个随机数 */
int random_number(int min,int max)
{
	/* 用一个静态变量存放 /dev/random 文件的描述符
	 * 以免每次调用次函数都要打开次文件
	 */
	static int dev_random_fd = -1;
	char *next_random_byte;
	int bytes_to_read;
	unsigned random_value;

	/* 确保 max 大于 min */
	assert(max > min);

	/* 打开 /dev/random 文件 */
	if(dev_random_fd == -1){
		dev_random_fd = open("/dev/random",O_RDONLY);
		assert(dev_random_fd != -1);
	}

	next_random_byte = (char *)&random_value;
	bytes_to_read = sizeof(random_value);
	
	/* 循环直到读4个字节的数据，因为 /dev/random 是根据用户行为产生随机数的
	 * 所以可能只读取到一个字节就返回了。
	 */
	do{
		int bytes_read;
		/* read 函数返回读取的字节数 */
		bytes_read = read(dev_random_fd,next_random_byte,bytes_to_read);
		bytes_to_read -= bytes_read;
		next_random_byte += bytes_read;
	}while(bytes_to_read > 0);

	return min + (random_value % (max - min + 1));
}

int main(int argc, char const *argv[])
{
	int random = 0;

	random = random_number(50,100);

	printf("the random num is : %d\n", random);

	return 0;
}