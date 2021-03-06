/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 21时06分00秒
 File Name: func_qunofac.h
 Description: 
 ************************************************************************/
#ifndef FUNC_QUNOFAC_H
#define FUNC_QUNOFAC_H

#include "head.h"

typedef struct node_fd
{
	int client_fd;
	char pathname[50];
	struct node_fd *next;
}node;

typedef struct 
{
	node *phead;
	node *ptail;
	int size_cur;
	int size_max;
}queue;

typedef void* (*pth_handle)(void*);
typedef struct 
{
	queue *pqu;
	pthread_t *pth;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pth_handle pth_func;
	int start_flags;
}factory;

void insert_queue(factory*,int,char*,int);

void delete_queue(factory**,int*,char**,int*);

void destory(factory*);


#endif
