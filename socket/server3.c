/*
* AF_INET
* This designates the address format that goes with the Internet namespace
* 将read write 函数换成 send recv 函数
* 网络编程 -- 服务器端
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int server_fd;
	int client_fd;

	struct sockaddr_in serveraddr;
	/* AF_INET
	* This designates the address format that goes with the Internet namespace
	*/
	serveraddr.sin_family = AF_INET;
	/* htonl 和 htons 是将数据转换为网络字节序 避免机器的大小端影响 */
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //设置所有地址都可以链接
	serveraddr.sin_port = htons(8080); //设置端口

	struct sockaddr_in clientaddr;
	int clientaddr_len = sizeof(clientaddr);

	//建立socket
	server_fd = socket(AF_INET,SOCK_STREAM,0);
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
	//接受客户端链接
	while(1){
		printf("Listening...\n");
		client_fd = accept(server_fd,(struct sockaddr *)&clientaddr,&clientaddr_len);
		if(client_fd == -1){
			perror("accept error");
			exit(-1);
		}
		//操作
		send(client_fd,"hello world\n",11,0); //网口客户端发送一个字符串
		printf("write to client\n");
		//关闭客户端
		close(client_fd);
	}
	close(server_fd);
	//system("rm socketfile"); //调用shell命令删除socketfile文件
	return 0;
}