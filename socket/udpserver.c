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
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	int server_fd;
	char buf[100] = {0};

	struct sockaddr_in serveraddr;
	int addr_len = sizeof(serveraddr);
	/* AF_INET
	* This designates the address format that goes with the Internet namespace
	*/
	serveraddr.sin_family = AF_INET;
	/* htonl 和 htons 是将数据转换为网络字节序 避免机器的大小端影响 */
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //设置所有地址都可以链接
	serveraddr.sin_port = htons(8080); //设置端口
	
	//建立socket
	server_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(server_fd == -1){
		perror("socket error");
		exit(-1);
	}
	//绑定
	if(bind(server_fd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == -1){
		perror("bind error");
		exit(-1);
	}
	
	//接受客户端发送的数据
	recvfrom(server_fd,buf,100,0,(struct sockaddr *)&serveraddr,&addr_len);
	//send(client_fd,"hello world\n",11,0); //网口客户端发送一个字符串
	printf("get form client = %s\n",buf);

	close(server_fd);
	//system("rm socketfile"); //调用shell命令删除socketfile文件
	return 0;
}