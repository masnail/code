/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 19时51分14秒
 File Name: file_socket.h
 Description: 
 ************************************************************************/
#ifndef FILE_SOCKET_H
#define FILE_SOCKET_H

#include "head.h"

typedef struct
{
	int len;
	char buff[SIZE_BUFF];
}datalist;

int recv_file(int);

int recv_file_data(int,int);

int send_file(int,char*);

int send_file_data(int,int);

#endif
