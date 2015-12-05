/*
* 进程的创建 fork()
*
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	//system("ls"); //执行shell命令
	//execl("/root/desktop/hello","hello",NULL); //调用desktop下的progress程序使它运行，不返回
	//execlp("ps","ps","-a",NULL); //duplicate the actions of the shell in searching for an executable file

	pid_t cpid;
	cpid = fork();//创建进程

	/* 下面的程序执行了2遍，一遍是父进程另一遍是子进程，执行顺序是不可预知的
	 * 父进程创建子进程的时候是将自己拷贝一份，然后两个进程独立运行
	 */
	if(cpid == -1)
		perror("faulure");
	else if(cpid == 0)
		printf("The child progress ID = %d\n",getpid());
	else
		printf("The parent progress ID = %d\n",getpid());

	pid_t pid = getpid();     //得到进程ID
	printf("\npid = %d\n",pid);

	pid_t ppid = getppid();   //得到父进程ID
	printf("\nppid = %d\n",ppid);
	return 0;
}
