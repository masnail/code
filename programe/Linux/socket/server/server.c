/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 15时33分09秒
 File Name: server.c
 Description: 
 ************************************************************************/
#include "../include/head.h"
#include "../include/func_socket.h"
#include "../include/file_socket.h"
#include "../include/func_qunofac.h"

void* func_handle(void *p)
{
	factory *fac=(factory*)p;
	while(1)
	{
		pthread_mutex_lock(&fac->mutex);
		if(0 == (fac->pqu)->size_cur)
		{
			pthread_cond_wait(&fac->cond,&fac->mutex);
		}
		pthread_mutex_unlock(&fac->mutex);
		int client_fd,len;
		char *pathname;
		delete_queue(&fac,&client_fd,&pathname,&len);
		printf("thread fd =%d\n",client_fd);
		send_file(client_fd,PATH);
	}
}

int main()
{
	int ret;
	int sock_fd;
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


	printf("ip=%s:port=%d\n",ip,port);	
	//init factory
	factory fac;
	fac.pqu=(queue*)calloc(1,sizeof(queue));
	(fac.pqu)->size_max=SIZE_CONNECT;
	(fac.pqu)->size_cur=0;
	fac.pth=(pthread_t*)calloc(SIZE_PTHREAD,sizeof(pthread_t));
	pthread_mutex_init(&fac.mutex,NULL);
	pthread_cond_init(&fac.cond,NULL);
	fac.pth_func=func_handle;
	fac.start_flags=0;
	/* create pthread */
	for(int i=0;i<SIZE_PTHREAD;i++)
	{
		pthread_create(&fac.pth[i],NULL,func_handle,(void*)&fac);
		printf("init \n");
	}

	socket_server_tcp(&sock_fd,port,ip,SIZE_CONNECT);
	fac.start_flags=0;
	printf("sock_fd =%d\n",sock_fd);
	while(1)
	{
		ret  = accept(sock_fd,NULL,NULL);
		if(-1 != ret)
		{
			insert_queue(&fac,ret,NULL,0);
			pthread_cond_signal(&fac.cond);
			printf("new_fd=%d\n",ret);
		}

	}
	close(sock_fd);
	return 0;
}
