/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 16时31分21秒
 File Name: client.c
 Description: 
 ************************************************************************/
#include "../include/head.h"
#include "../include/file_socket.h"
#include "../include/func_socket.h"

int main()
{

	int client_fd;
	int port=2016;
	char ip[16]="192.168.1.116";
	socket_client_tcp(&client_fd,port,ip);
	recv_file(client_fd);
	
	return 0;
}
