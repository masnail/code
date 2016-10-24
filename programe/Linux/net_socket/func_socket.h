/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月07日 星期四 19时22分01秒
 File Name: func_head.h
 Description: 
 ************************************************************************/

#ifndef FUNC_HEAD_H
#define FUNC_HEAD_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void socket_server_tcp(int*,int,char*,int);

void socket_accept(int,int*,struct sockaddr*);

void socket_client_tcp(int*,int,char*);

void socket_server_udp(int*,int,char*);

void socket_client_udp(int*,int,char*);

#endif
