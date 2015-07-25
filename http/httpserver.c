/*
* http 服务器程序
* 测试　在浏览器中输入本机 IP 地址，就会出现　hello world
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
	char content[] = "<html><h1>hello world</h1></html>";
	int server_fd,client_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;\
	int client_len = sizeof(client_addr);

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(80);

	//建立socket链接
	server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_fd == -1){
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	//绑定
	if(bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1){
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	//监听
	if(listen(server_fd,20) == -1){
		perror("listen error");
		exit(EXIT_FAILURE);
	}
	printf("listening...\n");

	while(1){
		client_fd = accept(server_fd,(struct sockaddr *)&server_addr,&client_len);
		if(client_fd == -1){
			perror("accept error");
			exit(EXIT_FAILURE);
		}
		printf("accept\n");
		send(client_fd,content,sizeof(content),0);
		close(client_fd);
	}
	close(server_fd);
	return 0;
}