/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 15时33分09秒
 File Name: server.c
 Description: 
 ************************************************************************/
#include "head.h"
#include "func_socket.h"
#include "file_socket.h"
#include "func_qunofac.h"
#include "msg_socket.h"
#include "func_proc.h"
#include "func_commd.h"

int init(factory *fac,int *sock_fd)
{
	int ret;
	int port;
	char ip[16],buff[21];
	memset(ip,0,sizeof(ip));
	memset(buff,0,sizeof(buff));
	int file_fd=open(PATH_CONFIGURE,O_RDONLY);
	if(-1 == file_fd)
	{
		perror("config error");
		return -1;
	}
	ret = read(file_fd,buff,sizeof(buff));
	if(-1 == ret)
	{
		perror("configi file error");
		close(file_fd);
		return -1;
	}
	char *p=strtok(buff,"|");
	port=atoi(p);
	p=strtok(NULL,"|");
	strcpy(ip,p);
	close(file_fd);

	//init factory
	init_factory(fac);
	create_proc(fac);

	socket_server_tcp(sock_fd,port,ip,SIZE_CONNECT);
}

int main()	
{
	factory fac;
	int sock_fd,client_fd,ret,addrlen;
	node nd;	
	struct sockaddr_in addr;
	char buff[SIZE_BUFF];
//	login(1);
	addrlen=sizeof(struct sockaddr);
	init(&fac,&sock_fd);	
	while(1)
	{
		memset(&addr,0,sizeof(struct sockaddr));
		client_fd  = accept(sock_fd,(struct sockaddr*)&addr,&addrlen);
		if(-1 != client_fd)
		{
//			printf("clinet_fd=%d\n",client_fd);
			memset(&nd,0,sizeof(nd));
		//	memset(buff,0,sizeof(buff));
		//	recv_msg(client_fd,buff);
		//	sub_msg(buff,&nd.com);
		//	memset(buff,0,sizeof(buff));
		//	recv_msg(client_fd,buff);
		//	memcpy(nd.pathnow,buff,strlen(buff));
			nd.addr=addr;
			nd.client_fd=client_fd;
			insert_queue(&fac,nd);
			pthread_cond_signal(&fac.cond);
		}
	}
	return 0;
}
