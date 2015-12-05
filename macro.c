/*
* C语言宏中的 # 的用法 
*/
#include <stdio.h>

/* 将 x 转换为字符串 */
#define A(x)	#x

/* 将 x 与 day 链接起来变成 dayx */
#define B(x)	day##x

int main()
{
	int day1 = 10;
	int day2 = 20;

	printf(A(cxd\n));


	/*
	* B(1) 代表变量 day1
	* B(2) 代表变量 day2 
	*/
	printf("day = %d\n", B(1));
	printf("day = %d\n", B(2));

}