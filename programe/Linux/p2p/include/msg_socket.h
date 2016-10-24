/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 19时51分14秒
 File Name: msg_socket.h
 Description: 
 ************************************************************************/
#ifndef MSG_SOCKET_H
#define MSG_SOCKET_H

#include "head.h"

typedef struct
{
	unsigned long int len;
	char msg[SIZE_MSG];
}msgnode;

typedef struct node_t
{
	msgnode msgn;
	struct node_t *next;
}pmsgnode;
typedef struct
{
	int cnt;
	char com_com[8];
	char com_param[SIZE_MSG];
	char com_varparam[SIZE_MSG];
	char path_cur[SIZE_MSG];
	char com_name[20];
}msgcom;

void sub_msg(char*,msgcom*);

int recv_msg(int,char*);

int send_msg(int,char*,int);

int recv_errno(int,int*);

int send_errno(int,int);

#endif
