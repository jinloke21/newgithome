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
	lfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET��׼Ipv4, AF_INET6��׼Ipv6
	//SOCK_STREAM ʹ��tcp���䣬SOCK_DGRAMʹ��udp����   //0��Ĭ��Э��
	//�ɹ������ļ��׽�����������ʧ�ܷ���-1

	serv_addr.sin_family = AF_INEF;         
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin._addr.s_addr = htonl(INADDR_ANY);

	bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); //bind��Ip��ַ�Ͷ˿ںţ��������ṹ���С
	
	listen(lfd, 128);  //ָ��ͬʱ������ٿͻ�������������

	clie_addr_len = sizeof(clie_addr);
	cfd = accept(lfd, (struct sockaddr*)&clie_addr, clie_addr_len);
	//accept:�ڶ�������Ϊ����������������������������ӵĿͻ��˵�Ip�Ͷ˿ںţ�����Ҫ����ʼ��
	//���������������봫�������������ṹ���С
	//����ֵ���ɹ������µ��ļ�������������ʹ��������ͻ��˽���ͨ�ţ�ʧ�ܷ���-1


	//�ͻ������������������ʹ��connect����
	//connect():
			//����������������1.���������ļ�������2.��������IP�Ͷ˿ںš�3.2�Ľṹ���С
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