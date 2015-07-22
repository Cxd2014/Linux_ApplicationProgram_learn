/*
* AF_INET
* This designates the address format that goes with the Internet namespace
* 将read write 函数换成 send recv 函数
* 使用 hostname 通信，而不是IP地址
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
#include <netdb.h>

int main(int argc, char const *argv[])
{
	if(argc < 2){
		perror("please input the host name");
		exit(EXIT_FAILURE);
	}

	struct hostent *hostname;
	hostname = gethostbyname(argv[1]); //得到　hostname 
	if(hostname == NULL){
		perror("get hostname error");
		exit(EXIT_FAILURE);
	}

	int server_fd;
	char buf[100] = {0};

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	/* inet_addr 将字符串转换为int型数据 */
	serveraddr.sin_addr = *((struct in_addr *)hostname->h_addr);
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
	recv(server_fd,buf,100,0);
	printf("get message = %s\n",buf);

	close(server_fd);
	return 0;
}