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

		int client_fd=0,ret=0,off=0;
		char buff[SIZE_BUFF];
		filelist *head=(filelist*)calloc(1,sizeof(filelist)),*tail=head,*p;
		node nd;
		delete_queue(&fac,&nd);
		client_fd=nd.client_fd;

		memset(buff,0,sizeof(buff));
	//	printf("fd =%d\n",client_fd);
		ret=recv_msg(client_fd,buff);//file name
		find_dir_file("/home/lzf/test",&tail);
		p=head;
		while(NULL != p)
		{
//			printf("%s\n",p->name);
			if(0==strcmp(buff,p->name))
			break;
			p=p->next;
		}
		
	/*	p=head;
		while(NULL!=p)
		{
			printf("%s\n",p->name);
			if(0 == strcmp(buff,p->name));
					break;
			p=p->next;
		}*/
		if(p != NULL)
		{
			memset(buff,0,sizeof(buff));
			sprintf(buff,"/home/lzf/test");
			struct stat fstat;
			memset(&fstat,0,sizeof(fstat));
			stat(buff,&fstat);
			unsigned long len=fstat.st_size;
			printf("find file path=%s\n",buff);
			send(client_fd,&len,sizeof(len),0);//file size
			printf("send file len=%lu\n",len);

			int index=0;
			index=len/OFF;
			if(len%OFF!=0)
				index+=1;

		//	for(int i=0;i<1;i++)
			{
		//		recv(client_fd,&off,sizeof(off),0);//file off
		//		printf("recv off=%d\n",off);
				send_file(client_fd,buff,17927);//file dat
			
			}
		}
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
