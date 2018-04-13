/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 15时33分09秒
 File Name: func_proc.c
 Description: 
 ************************************************************************/
#include "func_proc.h"

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

		int client_fd=0,ret=0;
		char buff[SIZE_BUFF];
		node nd;
		msgcom com,path_cur;
		delete_queue(&fac,&nd);
		client_fd=nd.client_fd;

	//	while(1)
		
			memset(buff,0,sizeof(buff));
			memset(&com,0,sizeof(com));
	//		printf("fd =%d\n",client_fd);
			ret=recv_msg(client_fd,buff);//order
			sub_msg(buff,&com);
//			printf("cur_path=%s\n",com.com_param);
			if(0 == strcmp("log",com.com_com))
			{write_client_log(nd.addr,com);
				commd_adapte(client_fd,com);
				
			}else{
			//	memset(&com,0,sizeof(com));
			//	sub_msg(buff,&com);

				memset(buff,0,sizeof(buff));//path
				ret=recv_msg(client_fd,buff);//path
				strcpy(com.path_cur,buff);

				memset(buff,0,sizeof(buff));//name
				ret=recv_msg(client_fd,buff);//name
				strcpy(com.com_name,buff);
			//	chdir(path);
//				commd_adapte(client_fd,com);
//				recv_msg(client_fd,com.path_cur);//recv path
//				memcpy(com.path_cur,path,strlen(path));
				commd_adapte(client_fd,com);
			}
//			msg.len=strlen(com.path_cur);
//			memcpy(msg.msg,com.path_cur,msg.len);
//			send_msg(client_fd,msg);
		
//			printf("here\n");
		close(client_fd);
	//	printf("out\n");
	}
}

void init_factory(factory *fac)
{
	fac->pqu=(queue*)calloc(1,sizeof(queue));
	(fac->pqu)->size_max=SIZE_CONNECT;
	(fac->pqu)->size_cur=0;
	fac->pth=(pthread_t*)calloc(SIZE_PTHREAD,sizeof(pthread_t));
	pthread_mutex_init(&fac->mutex,NULL);
	pthread_cond_init(&fac->cond,NULL);
	fac->pth_func=func_handle;
	fac->start_flags=0;
}
void create_proc(factory *fac)
{
	/* create pthread */
	for(int i=0;i<SIZE_PTHREAD;i++)
	{
		pthread_create(&fac->pth[i],NULL,func_handle,(void*)fac);
	}

	fac->start_flags=1;
}
