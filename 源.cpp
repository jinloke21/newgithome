#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<ctype.h>
#include<arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666
int main() {
	int lfd,cfd;
	char buf(BUFSIZ);
	socklen_t clie_addr_len;
	struct sockaddr_in serv_addr, clie_addr;
	lfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET标准Ipv4, AF_INET6标准Ipv6
	//SOCK_STREAM 使用tcp传输，SOCK_DGRAM使用udp传输   //0传默认协议
	//成功返回文件套接字描述符，失败返回-1

	serv_addr.sin_family = AF_INEF;         
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin._addr.s_addr = htonl(INADDR_ANY);

	bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); //bind绑定Ip地址和端口号，最后参数结构体大小
	
	listen(lfd, 128);  //指定同时允许多少客户端允许建立连接

	clie_addr_len = sizeof(clie_addr);
	cfd = accept(lfd, (struct sockaddr*)&clie_addr, clie_addr_len);
	//accept:第二个参数为传出参数，返回与服务器建立连接的客户端的Ip和端口号，不需要做初始化
	//第三个参数，传入传出参数，描述结构体大小
	//返回值，成功返回新的文件描述符，可以使服务器与客户端进行通信，失败返回-1


	//客户端与服务器健康连接使用connect函数
	//connect():
			//函数有三个参数，1.服务器的文件描述符2.服务器的IP和端口号。3.2的结构体大小
	while (1) {
		int n = read(cfd, buf, sizeof(buf));
		for (int i = 0; i < n; i++)
			buf[i] = toupper(buf[i]);
		write(cfd, buf, n);
	}
	close(lfd);
	close(cfd);
	return 0;
}