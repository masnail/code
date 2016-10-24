/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 21时15分20秒
 File Name: func_qunofac.c
 Description: 
 ************************************************************************/
#include "../include/func_qunofac.h"

void insert_queue(factory *fac,int fd,char *pathname,int len)
{
//	printf("len =%d\n",len);
	node *nd=(node*)calloc(1,sizeof(node));
	nd->client_fd=fd;
	pthread_mutex_lock(&fac->mutex);
	memcpy(nd->pathname,pathname,len);
	queue *qu=fac->pqu;
	if(qu->phead==qu->ptail)
	{
		qu->ptail=nd;
		qu->phead=nd;
	}else{
		qu->ptail->next=nd;
		qu->ptail=nd;
	}
	(fac->pqu)->size_cur+=1;

/*	node *head=qu->phead;
	printf("insert the queue size:%d\n",(fac->pqu)->size_cur);
	while(head!=NULL)
	{
		printf("%d ",head->client_fd);
		head=head->next;
	}
	printf("\n");
*/
	pthread_mutex_unlock(&fac->mutex);
}

void delete_queue(factory **fac,int *fd,char **pathname,int *len)
{
	pthread_mutex_lock(&(*fac)->mutex);
	queue *qu=(*fac)->pqu;
	node *nd=qu->phead;
	*fd=nd->client_fd;
	*pathname=nd->pathname;
	*len=strlen(nd->pathname);
	qu->phead=nd->next;
	if(NULL == qu->phead)
	{
		qu->ptail=NULL;
	}
	((*fac)->pqu)->size_cur-=1;

/*	node *head=qu->phead;
	printf("delete the queue size:%d\n",((*fac)->pqu)->size_cur);
	while(head!=NULL)
	{
		printf("%d ",head->client_fd);
		head=head->next;
	}
	printf("\n");
*/
	pthread_mutex_unlock(&(*fac)->mutex);
	free(nd);
}

void destory(factory *fac)
{
	node *head=fac->pqu->phead;
	node *p=head;
	
	while(head!=NULL)
	{
		head=head->next;
		free(p);
		p=head;
	}
	free(fac->pqu);
}

