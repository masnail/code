/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月07日 星期四 19时22分01秒
 File Name: func_scoket.h
 Description: 
 ************************************************************************/

#ifndef FUNC_SOCKET_H
#define FUNC_SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>


void socket_server_tcp(int*,int,char*,int);

void socket_accept(int,struct sockaddr*,int*);

void socket_client_tcp(int*,int,char*);

void socket_server_udp(int*,int,char*);

void socket_client_udp(int*,int,char*,struct sockaddr*);


#endif

