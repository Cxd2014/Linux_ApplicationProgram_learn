/* epoll 实现的回射服务器 */

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100
#define BACK_LOG 10
#define BUF_SIZE 1024

void setnonblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);
	if(opts < 0) {
		perror("fcntl(sock, GETFL) error");
		exit(1);
	}

	opts = opts | O_NONBLOCK;
	if(fcntl(sock, F_SETFL, opts) < 0) {
		perror("fcntl(sock, SETFL, opts) error");
		exit(1);
	}
}

/* 初始化一个服务器端的监听套接字 */
int init_server_socket(char **argv)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("server socket create error\n");
        exit(EXIT_FAILURE);
    }

    setnonblocking(listenfd);
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_aton(argv[1], &(server_addr.sin_addr));
	server_addr.sin_port = htons(atoi(argv[2]));
    bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listenfd, BACK_LOG);

    return listenfd;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: ./epoll 192.168.152.129 88\n");
        exit(EXIT_FAILURE);
    }

    int listenfd = init_server_socket(argv);

     /* 创建一个 epoll 句柄，参见 man epoll_create 手册 */
    struct epoll_event ev, events[MAX_EVENTS];
    int epollfd = epoll_create(MAX_EVENTS);
    if (epollfd < 0) {
        perror("epoll create error\n");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN | EPOLLET; /* 监听数据可读事件,边沿触发 */
    ev.data.fd = listenfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
        perror("epoll_ctl: listenfd");
        exit(EXIT_FAILURE);
    }

    int nfds = 0, conn_fd = 0, sock_fd = 0, n = 0, size = 0;
    char buf[BUF_SIZE] = {0};
    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);

    while(1) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (n = 0; n < nfds; n++) {
            if (events[n].data.fd == listenfd) { /* 一个新连接 */
                conn_fd = accept(listenfd, (struct sockaddr *) &client_addr, &addr_len);
                if (conn_fd == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                
                char *addr = inet_ntoa(client_addr.sin_addr);
                printf("connect from %s\n", addr);
                
                setnonblocking(conn_fd);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_fd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_fd, &ev) == -1) {
                    perror("epoll_ctl: conn_fd");
                    exit(EXIT_FAILURE);
                }
            } else if(events[n].events & EPOLLIN) { /* 一个可读事件 */
                if((sock_fd = events[n].data.fd) < 0) 
                    continue;

                memset(buf, 0, sizeof(buf));
				if((size = read(sock_fd, buf, BUF_SIZE)) < 0) {
					if(errno == ECONNRESET) {
						close(sock_fd);
                        events[n].data.fd = -1;
					} else {
						printf("read buf error\n");
					}
				} else if(size == 0) {
                    printf("size = 0 close socket\n");
					close(sock_fd);
                    events[n].data.fd = -1;  
				} else {
                    printf("received data: %s size : %d\n", buf, size);
                    write(sock_fd, buf, strlen(buf));

                    ev.data.fd = sock_fd;
                    ev.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, sock_fd, &ev);
                }
            }
        }
    }
    return 0;
}
