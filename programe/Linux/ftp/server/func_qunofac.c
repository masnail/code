/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 21时15分20秒
 File Name: func_qunofac.c

 Description: 
 ************************************************************************/
#include "func_qunofac.h"

void insert_queue(factory *fac,node vnode)
{
//	printf("len =%d\n",len);
	node *nd=(node*)calloc(1,sizeof(node));
	memcpy(nd,&vnode,sizeof(node));
	pthread_mutex_lock(&fac->mutex);
	queue *qu=fac->pqu;
	if(qu->phead==qu->ptail)
	{
		qu->ptail=nd;
		qu->phead=nd;
	}else{
		qu->ptail->next=nd;
		qu->ptail=nd;
	}
	if((fac->pqu)->size_cur<(fac->pqu)->size_max)
		 (fac->pqu)->size_cur+=1;
	pthread_mutex_unlock(&fac->mutex);
}

void delete_queue(factory **fac,node *vnode)
{
	pthread_mutex_lock(&(*fac)->mutex);
	queue *qu=(*fac)->pqu;
	node *nd=qu->phead;	
	memcpy(vnode,nd,sizeof(node));
	qu->phead=nd->next;
	if(NULL == qu->phead)
	{
		qu->ptail=NULL;
	}
	if(((*fac)->pqu)->size_cur>0)
		 ((*fac)->pqu)->size_cur-=1;
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

