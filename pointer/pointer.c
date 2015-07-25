/*
* 指针和数组的学习
*/
#include <stdio.h>

char ga[] = "this is a dog";

void fanc(int &p)
{
/*
* 这种声明方式只适用与 C++ 语言  在 GCC 编译器中编译不能通过
* 而 g++ 编译器可以通过
*/
	p = 100;
	printf("p = %d\n",p);
}

void fanc1(int *p)
{
	*p = 200;
	printf("p = %d\n",*p);
}


void fanc2(char a[])
{
/*
* C 语言中 当数组作为参数传递时都转换为指针的传递
*/
	printf("\nIn the fanc2\n");
	/* &a 与 &(a[0]) 的值不一样*/
	printf("&a = %x\n",(unsigned int)&a);
	printf("&(a[0]) = %x\n",(unsigned int)&(a[0]));
	printf("&(a[1]) = %x\n",(unsigned int)&(a[1]));

	printf("sizeof = %d\n",sizeof(a)); // 4
}

void fanc3(char *a)
{

	printf("\nIn the fanc3\n");
	
	printf("&a = %x\n",(unsigned int)&a);
	printf("&(a[0]) = %x\n",(unsigned int)&(a[0]));
	printf("&(a[1]) = %x\n",(unsigned int)&(a[1]));

	printf("sizeof = %d\n",sizeof(a)); // 4
}

int main()
{
	int i =67;
	char *p;
	char a[] = "hello world";
	a[2] = 'c';
	fanc(i);
	printf("i = %d\n",i);
	fanc1(&i);
	printf("i = %d\n",i);

	/* &a 与 &(a[0]) 的值是一样的*/
	printf("&a = %x\n",(unsigned int)&a); //强制转换为 unsigned int 不然编译器会出现警告，“%x是 unsigned int 与 char* 不匹配”
	printf("&(a[0]) = %x\n",(unsigned int)&(a[0]));
	printf("&(a[1]) = %x\n",(unsigned int)&(a[1]));
	printf("a = %s\n",a);
	printf("sizeof = %d\n",sizeof(a)); // 12
	
	p = a;
	printf("\n");
	printf("p[0] = %c\n",p[0]);
	printf("p[1] = %c\n",p[1]);
	printf("*p = %c\n",*p);
	printf("*(++p) = %c\n",*(++p));
	printf("*(p+4) = %c\n",*(p+3));
	
	printf("\nprint the ga adress\n");
	printf("&ga = %x\n",(unsigned int)&ga);
	printf("&(ga[0]) = %x\n",(unsigned int)&(ga[0]));
	printf("&(ga[1]) = %x\n",(unsigned int)&(ga[1]));
	printf("ga = %s\n",ga);
	printf("sizeof = %d\n",sizeof(ga)); // 12
	
	fanc2(a);
	fanc3(a);

	return 0;
}
