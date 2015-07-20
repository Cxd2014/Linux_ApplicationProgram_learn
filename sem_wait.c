/*
* 进程通信--信号量
× 读取信号量，若为0则堵塞，直到信号量为1，在继续运行
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int semid;
struct sembuf sem_down = {0,-1,SEM_UNDO};
struct sembuf sem_up = {0,1,SEM_UNDO};


void down()
{
	if(semop(semid,&sem_down,1) == -1)
		perror("semop down error");
}

void up()
{
	if(semop(semid,&sem_up,1) == -1)
		perror("semop up error");
}

int main(int argc, char const *argv[])
{
	//创建信号量
	semid = semget(2345,1,IPC_CREAT);

	if(semid != -1){
		down(); //锁定
		printf("hello world!\n");
		sleep(10);
		up();//解锁
	}else
		perror("semget failed");
	return 0;
}