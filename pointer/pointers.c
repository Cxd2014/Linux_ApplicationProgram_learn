/*
* 多维数组的学习
*/
#include <stdio.h>


int main()
{
	int apricot[2][3][5];
	int (*r)[5] = apricot[0]; //指向数组的指针
	int *t = apricot[0][0];

	char *p = "Hello"; /* "Hello" 为 const char 类型*/
	printf("*p = %s\n",p);
	printf("p = %x\n",p);
	printf("&p = %x\n",&p);

	/*
		*p = "c"; //不能编译通过
		*p = 'c'; //能编译通过，但是运行的时候出现 内存访问冲突，因为不能改变const char 的内容
		printf("*p = %s\n",p);
	*/

	p = "world"; 
	printf("*p = %s\n",p);
	printf("p = %x\n",p); // p 所指向的地址发生改变了
	printf("&p = %x\n",&p);

	printf("apricot[0][0][0] = %x\n",&(apricot[0][0][0]));
	printf("*r = %x\n",r);
	printf("*t = %x\n",t);

	*r++;
	*t++;
	printf("apricot[0][0][1] = %x\n",&(apricot[0][0][1]));
	printf("*r = %x\n",r);
	printf("*t = %x\n",t);

	return 0;
}
