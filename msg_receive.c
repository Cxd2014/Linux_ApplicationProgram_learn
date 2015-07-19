/*
* 进程通信--消息队列
* 接受消息
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct msgbuf
{
	long mytype;
	char mtext[255];
};

int main(int argc, char const *argv[])
{
	struct msgbuf mybuf;

	//创建消息队列
	int msgqid = msgget(2345,IPC_CREAT);
	if(msgqid != 1){
		//接受消息
		if(msgrcv(msgqid,&mybuf,sizeof(mybuf.mtext),0,IPC_NOWAIT) != -1){
			printf("receive message = %s\n",mybuf.mtext);
			//删除消息队列
			if(msgctl(msgqid,IPC_RMID,0) != -1)
				printf("delete queue succeed\n");
		}else
			perror("msgrcv failed");
	}else
		perror("msgget failed");

	return 0;
}