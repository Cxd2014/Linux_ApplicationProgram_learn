/*
* 利用 UDP 协议通信
* SOCK_DGRAM
* The SOCK_DGRAM style is used for sending individually-addressed packets unreliably.
* It is the diametrical opposite of SOCK_STREAM
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

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	/* inet_addr 将字符串转换为int型数据 */
	serveraddr.sin_addr = *((struct in_addr *)hostname->h_addr);
	serveraddr.sin_port = htons(8080);

	//建立socket
	server_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(server_fd == -1){
		perror("socket error");
		exit(-1);
	}
	
	//发送信息到服务器端
	sendto(server_fd,"hello world\n",11,0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	printf("send message\n");

	close(server_fd);
	return 0;
}