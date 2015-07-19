/*
* 进程通信--消息队列
* 发送消息
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
	mybuf.mytype = 1;
	strcpy(mybuf.mtext,"hello world");

	//创建消息队列
	int msgqid = msgget(2345,IPC_CREAT);
	if(msgqid != 1){
		//发送消息
		if(msgsnd(msgqid,&mybuf,sizeof(mybuf.mtext),0) != -1){
			printf("send message succeed\n");
		}else
			perror("msgsnd failed");
	}else
		perror("msgget failed");

	return 0;
}