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
	int port;
	char ip[16],buff[21];
	memset(ip,0,sizeof(ip));
	memset(buff,0,sizeof(buff));
	
	int file_fd=open(PATH_CONFIGURE,O_RDONLY);
	if(-1 == file_fd)
	{
		perror("config error");
		return -1;
	}
	int ret = read(file_fd,buff,sizeof(buff));
	if(-1 == ret)
	{
		perror("config file error");
		close(file_fd);
		return -1;
	}
	char *p=strtok(buff,"|");
	port=atoi(p);
	p=strtok(NULL,"|");
	strcpy(ip,p);
	close(file_fd);

	socket_client_tcp(&client_fd,port,ip);
	recv_file(client_fd);
	
	return 0;
}
