/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月14日 星期四 00时14分42秒
 File Name: func_log.h
 Description: 
************************************************************************/
#ifndef FUNC_LOG_H
#define FUNC_LOG_H

#include "head.h"
#include "msg_socket.h"

void create_time(char*);

void write_user_log(char*,char*);

void write_user_com(msgcom);

void write_client_log(struct sockaddr_in,msgcom);

void write_client_com(msgcom);

#endif
