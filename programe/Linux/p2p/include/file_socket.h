/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 19时51分14秒
 File Name: file_socket.h
 Description: 
 ************************************************************************/
#ifndef FILE_SOCKET_H
#define FILE_SOCKET_H

#include "head.h"
#include "msg_socket.h"

typedef struct filename
{
	char name[SIZE_BUFF];
	char path[SIZE_BUFF];
	struct filename *next;
}filelist;

int recv_file(int,char*,int);

int recv_file_data(int,int);

int send_file(int,char*,int);

int send_file_data(int,int);

//int send_file_mmap(int,int,unsigned long,unsigned long);

int find_dir_file(char*, filelist**);


#endif
