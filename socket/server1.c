/*
* AF_UNIX
* This designates the local namespace, in which socket addresses are local names,
* and its associated family of protocols 
* 网络编程 -- 服务器端
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int server_fd;
	int client_fd;

	struct sockaddr_un serveraddr;
	serveraddr.sun_family = AF_UNIX;
	strcpy(serveraddr.sun_path,"socketfile");

	struct sockaddr_un clientaddr;
	int clientaddr_len = sizeof(clientaddr);

	//建立socket
	server_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(server_fd == -1){
		perror("socket error");
		exit(-1);
	}
	//绑定
	if(bind(server_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == -1){
		perror("bind error");
		exit(-1);
	}
	//监听
	if(listen(server_fd,20) == -1){
		perror("listen error");
		exit(-1);
	}
	printf("Listening...\n");
	//接受客户端链接
	client_fd = accept(server_fd,(struct sockaddr *)&clientaddr,&clientaddr_len);
	if(client_fd == -1){
		perror("accept error");
		exit(-1);
	}
	//操作
	write(client_fd,"hello world\n",11); //网口客户端发送一个字符串
	printf("write to client\n");
	//关闭
	close(client_fd);
	close(server_fd);
	system("rm socketfile"); //调用shell命令删除socketfile文件
	return 0;
}