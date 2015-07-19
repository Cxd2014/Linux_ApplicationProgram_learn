/*
* 进程通信--共享内存
* 读内存
*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	void *share_memory = NULL;
	//建立共享内存
	int shmid = shmget(12345,2048,IPC_CREAT);
	if(shmid != -1){
		//映射地址
		share_memory = shmat(shmid,NULL,0);
		if(share_memory != (void *)-1){
			//读出共享内存的内容
			printf("read memory = %s\n",(char *)share_memory);
			//关闭
			shmdt(share_memory);
		}else
			perror("shmat failed");
	}else
		perror("shmget failed");
	return 0;
}