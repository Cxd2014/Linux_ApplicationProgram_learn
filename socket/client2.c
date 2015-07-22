/*
* AF_INET
* This designates the address format that goes with the Internet namespace
* 网络编程 -- 客户端
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	int server_fd;
	char buf[100] = {0};

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	/* inet_addr 将字符串转换为int型数据 */
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(8080);

	//建立socket
	server_fd = socket(AF_INET,SOCK_STREAM,0);
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