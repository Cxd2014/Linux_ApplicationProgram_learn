/*
* environ 全局变量是由 GNU C 库定义的。它是一个char **类型的变量，包含了一个
* 以NULL 指针结束的字符串数组。每个字符串都包含了一个环境变量。这个环境变量被表
* 示为“变量=值”的形式
*
*/


#include <stdio.h>

/* 引用全局变量 */
extern char ** environ;

int main(int argc, char const *argv[])
{
	char **var;
	/* 打印所有环境变量 */
	for(var = environ;*var != NULL;var++)
		printf("%s\n", *var);

	return 0;
}