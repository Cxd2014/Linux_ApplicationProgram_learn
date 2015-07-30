/*
* 指针在函数中传递
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *getmemory()
{
	/* malloc 正确的使用方式 */
	char *p;
	p = (char *)malloc(20);
	strcpy(p,"hello world1");
	return p;
}

void fanc(char *p)
{
	/* 改变了指针p的值，所以导致传递 fanc 函数的指针 c 所指的内容没有变*/
	printf("p = %x\n",(unsigned int)p);
	p = (char *)malloc(20); 
	strcpy(p,"hello world2");
	printf("p = %x\n",(unsigned int)p);
}

void fanc1(char *p)
{
	/* 没有改变指针p的值，所以传递 fanc1 函数的指针 d 所指的内容改变了 */
	printf("p = %x\n",(unsigned int)p);
	p[0] = 'h';
	*(p+1) = 'e';
	p[2] = 'l';
	printf("p = %x\n",(unsigned int)p);
}

void fanc2(char *p)
{
	/* 改变了指针p的值，所以导致传递 fanc2 函数的指针 d 所指的内容没有变*/
	printf("p = %x\n",(unsigned int)p);
	p = "hello world3";
	printf("p = %x\n",(unsigned int)p);
}

int main()
{
	char *str = NULL;
	str = getmemory();
	printf("%s\n",str);
	free(str);


	char *c;
	c = "cxd2";
	fanc(c);
	printf("%s\n",c); 

	char x[] = "cxd3";
	fanc1(x);
	printf("%s\n",x);

	char d[] = "cxd4";
	fanc2(d);
	printf("%s\n",d);

	return 0;
}
