/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月08日 星期五 13时55分42秒
 File Name: socket.h
 Description: 暂时支持IPV4，没有添加支持IPV6机制
 ************************************************************************/

#include "socket.h"

/*
 * port 服务器的端口号
 * concnt 服务器的最大可连接的数量
 *
 * 返回服务器端得到的套接字描述符fd_sock
 *
 */

int socket_server_tcp()
{

    char ipchar[17];
    char port[9];
    char concnt[9];
    memset(ipchar, sizeof(ipchar), 0);
    memset(port, sizeof(port), 0);
    memset(concnt, sizeof(concnt), 0);

    //read configure file
    FILE *fp = fopen("config", "r");

    if(fp == NULL)
    {
	perror("read configure file error!");
	exit(-1);
    }
    fgets(ipchar, sizeof(ipchar), fp);
    fgets(port, sizeof(port), fp);
    fgets(concnt, sizeof(concnt), fp);

    fclose(fp);//close file

	int fd_sock = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd_sock)
	{
		perror("socket");
		exit(0);
	}

	int cancel_port=0;//cancel port res
	setsockopt(fd_sock,SOL_SOCKET,SO_REUSEADDR,(const void*)&cancel_port,sizeof(int));

	struct sockaddr_in ip_addr;
	memset(&ip_addr,0,sizeof(ip_addr));
	ip_addr.sin_family=AF_INET;
	ip_addr.sin_port=htons(atoi(port));
	ip_addr.sin_addr.s_addr=inet_addr(ipchar);//htonl(INADDR_ANY);

	int ret;
	ret = bind(fd_sock,(struct sockaddr*)&ip_addr,sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("bind");
		close(fd_sock);
		exit(0);
	}
	
	ret = listen(fd_sock,atoi(concnt));
	if(-1 == ret)
	{
		perror("listen");
		close(fd_sock);
		exit(0);
	}

	return fd_sock;

}


/*
 * port 客户端的端口号
 * ipchar 客户端要连接到服务器端的ip
 * 
 * 返回客户端得到的套接字描述符fd_sock
 *
 */

int  socket_client_tcp()
{
    char ipchar[17];
    char port[9];
    memset(ipchar, sizeof(ipchar), 0);
    memset(port, sizeof(port), 0);

    //read configure file
    FILE *fp = fopen("config", "r");

    if(fp == NULL)
    {
	perror("read configure file error!");
	exit(-1);
    }
    fgets(ipchar, sizeof(ipchar), fp);
    fgets(port, sizeof(port), fp);
    fclose(fp);//close file

	int fd_sock = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd_sock)
	{
		perror("socket");
		exit(0);
	}

	int cancel_port=0;//cancel port res
	setsockopt(fd_sock,SOL_SOCKET,SO_REUSEADDR,(const void*)&cancel_port,sizeof(int));

	struct sockaddr_in ip_addr;
	memset(&ip_addr,0,sizeof(ip_addr));
	ip_addr.sin_family=AF_INET;
	ip_addr.sin_port=htons(atoi(port));
	ip_addr.sin_addr.s_addr=inet_addr(ipchar);
	
	int ret;
	ret = connect(fd_sock,(struct sockaddr*)&ip_addr,sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("connect");
		close(fd_sock);
		exit(0);
	}

	return fd_sock;
}


/*
 * port 服务器的端口号
 * 
 * 返回服务器端得到的套接字描述符fd_sock
 *
 */

int socket_server_udp(struct sockaddr_in *ip_addr)
{
    char ipchar[17];
    char port[9];
    memset(ipchar, sizeof(ipchar), 0);
    memset(port, sizeof(port), 0);

    //read configure file
    FILE *fp = fopen("config", "r");

    if(fp == NULL)
    {
	perror("read configure file error!");
	exit(-1);
    }
    fgets(ipchar, sizeof(ipchar), fp);
    fgets(port, sizeof(port), fp);
    fclose(fp);//close file

	int fd_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == fd_sock)
	{
		perror("socket");
		exit(0);
	}

	//struct sockaddr_in ip_addr;
	memset(ip_addr,0,sizeof(ip_addr));
	ip_addr->sin_family=AF_INET;
	ip_addr->sin_port=htons(atoi(port));
	ip_addr->sin_addr.s_addr=inet_addr(ipchar);//htonl(INADDR_ANY);

	int ret;
	ret = bind(fd_sock,(struct sockaddr*)&ip_addr,sizeof(struct sockaddr));
	if(-1 == ret)
	{
		perror("bind");
		close(fd_sock);
		exit(0);
	}	

	return fd_sock;
}


/*
 * port 客户端的端口号
 * ipchar 客户端要连接到服务器端的IP
 * ip_addr 返回要发送到服务器端的ip地址结构
 *
 * 返回客户端端得到的套接字描述符fd_sock
 *
 */

int socket_client_udp(struct sockaddr_in *ip_addr)
{
    char ipchar[17];
    char port[9];
    memset(ipchar, sizeof(ipchar), 0);
    memset(port, sizeof(port), 0);

    //read configure file
    FILE *fp = fopen("config", "r");

    if(fp == NULL)
    {
	perror("read configure file error!");
	exit(-1);
    }
    fgets(ipchar, sizeof(ipchar), fp);
    fgets(port, sizeof(port), fp);
    fclose(fp);//close file

	int fd_sock = socket(AF_INET,SOCK_DGRAM,0);
	if(-1 == fd_sock)
	{
		perror("socket");
		exit(0);
	}

	memset(ip_addr,0,sizeof(struct sockaddr_in));
	(*ip_addr).sin_family=AF_INET;
	(*ip_addr).sin_port=htons(atoi(port));
	(*ip_addr).sin_addr.s_addr=inet_addr(ipchar);//INADDR_ANY;

	return fd_sock;
}
