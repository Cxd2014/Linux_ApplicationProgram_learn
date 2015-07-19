/*
* C语言宏中的 # 的用法 
*/
#include <stdio.h>

#define A(x)	#x 
#define B(x)	day##x

int main()
{
	int day1 = 10;
	int day2 = 20;
	printf(A(cxd\n));
	printf("day = %d\n", B(1));
	printf("day = %d\n", B(2));

}