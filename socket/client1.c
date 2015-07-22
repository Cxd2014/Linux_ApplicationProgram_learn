/*
* AF_UNIX
* This designates the local namespace, in which socket addresses are local names,
* and its associated family of protocols 
* 网络编程 -- 客户端
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>

int main(int argc, char const *argv[])
{
	int server_fd;
	char buf[100] = {0};

	struct sockaddr_un serveraddr;

	serveraddr.sun_family = AF_UNIX; 
	strcpy(serveraddr.sun_path,"socketfile");

	//建立socket
	server_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(server_fd == -1){
		perror("socket error");
		exit(-1);
	}
	//连接
	if(connect(server_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == -1){
		perror("connect error");
		exit(-1);
	}
	//读取服务器端发送的信息
	read(server_fd,buf,100);
	printf("get message = %s\n",buf);

	close(server_fd);
	return 0;
}