/*
* 进程通信--信号量
* 设置信号量为 1 在锁定信号量
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int semid;
struct sembuf sem_down = {0,-1,SEM_UNDO};
struct sembuf sem_up = {0,1,SEM_UNDO};

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };

void down()
{
	//将信号量减1，使其他进程不能访问
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
	//printf("semid = %d\n",semid);

	union semun arg;
	arg.val = 1;

	//设置 信号量为 1 
	if(semctl(semid,0,SETVAL,arg) == -1)
		perror("semctl error");

	if(semid != -1){
		down(); //锁定
		printf("hello world!\n");
		sleep(10);
		up();//解锁
	}else
		perror("semget failed");
	return 0;
}