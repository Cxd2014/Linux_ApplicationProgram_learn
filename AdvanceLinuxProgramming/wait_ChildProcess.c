/*
* 使用 fork 和 exec 函数,来创建子进程
* 并等待子进程执行完毕,然后分析退出码
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char* program,char** arg_list)
{
	pid_t child_pid;

	child_pid = fork(); /* 复制这个进程 */
	if(child_pid != 0)
		return child_pid; /* 运行的是父进程 */
	else{
		/* 执行子程序 */
		execvp(program,arg_list);
		/* execvp 函数只会在出现错误时返回 */
		fprintf(stderr, "an error occured in execvp\n");
		abort();
	}
}

int main(int argc, char const *argv[])
{
	int child_status;

	/* 传递给 ls 命令的参数列表 */
	char *arg_list[] = {
		"ls",
		"-l",
		"/",
		NULL /* 参数列表必须以 NULL 结束 */
	};

	spawn("ls",arg_list);

	/* 等待子进程执行完毕,然后判断退出码 */
	wait(&child_status);
	if(WIFEXITED(child_status))
		printf("the child process exited normally,with exit code %d\n",
				WEXITSTATUS(child_status));
	else
		printf("the child process exited abnormally\n");

	printf("done with main program\n");

	return 0;
}