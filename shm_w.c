/*
* 进程通信--共享内存
* 写内存 命令 ipcs 查看所有的共享内存
*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	char content[] = "Hello world";
	void *share_memory = NULL;
	//建立共享内存
	int shmid = shmget(12345,2048,IPC_CREAT);
	if(shmid != -1){
		//映射地址
		share_memory = shmat(shmid,NULL,0);
		if(share_memory != (void *)-1){
			//拷贝数据到共享内存
			memcpy(share_memory,content,12);
			printf("write succeed\n");
			//关闭
			shmdt(share_memory);
		}else
			perror("shmat failed");
	}else
		perror("shmget failed");
	return 0;
}