/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 16时31分21秒
 File Name:file_socket.c
 Description: 
 ************************************************************************/
#include "../include/file_socket.h"


int recv_file(int client_fd)
{
	int ret;
	int len=0;
	char buff[SIZE_BUFF];
	memset(buff,0,sizeof(buff));
	
	ret = recv(client_fd,&len,sizeof(int),0);
	if(0 >= len)
	{
		printf("recv file name fail!\n");
		close(client_fd);
		return -1;
	}
	ret = recv(client_fd,buff,sizeof(buff),0);
	if(-1 == ret)
	{
		perror("recv fail!\n");
		close(client_fd);
		return -1;
	}

	/* 不支持断点续传 */
	int file_fd=open(buff,O_RDWR);
	if(-1 != file_fd)
	{
		unlink(buff);
		close(file_fd);
		return -1;
	}
	file_fd=open(buff,O_CREAT|O_RDWR,0666);
	/* recv file data */
	recv_file_data(client_fd,file_fd);
}

/* 断点续传函数位置 */

int recv_file_data(int client_fd,int file_fd)
{
	int len=0,ret=0,cnt=0;//一次接受的数据长度
	char buff[SIZE_BUFF];
	while(memset(buff,0,sizeof(buff)),(ret=recv(client_fd,&len,4,0))> 0 )
	{
		if(0 == len)
		{
			printf("recv file name done!\n");
			close(client_fd);
			close(file_fd);
			return 0;
		}
		cnt=0;
		while(cnt<len)
		{
			memset(buff,0,sizeof(buff));
			ret = recv(client_fd,buff,len-cnt,0);
			if(-1 == ret)
			{
				perror("recv fail!\n");
				close(client_fd);
				close(file_fd);
				return -1;
			}
			cnt+=ret;
			write(file_fd,buff,len);
		}
	}
	
	close(client_fd);
	close(file_fd);
	return 0;

}

int send_file(int sock_fd,char *pathname)
{
	int ret;
	datalist data;
	memset(&data,0,sizeof(data));

	int file_fd=open(pathname,O_RDONLY);
	if(-1 == file_fd)
	{
		perror("file_fd");
		close(sock_fd);
		return -1;
	}
	data.len=strlen(pathname);
	memcpy(data.buff,pathname,data.len);
	ret = send(sock_fd,&data,4+data.len,0);
	if(-1 == ret)
	{
		perror("send");
		close(sock_fd);
		close(file_fd);
		return -1;
	}
	/* 发送文件的数据 */
	send_file_data(sock_fd,file_fd);
	
	return 0;
}

int send_file_data(int sock_fd,int file_fd)
{

	int ret=0,cnt=0;//单次发送的数据量
	datalist data;
	while(memset(&data,0,sizeof(data)),(ret = read(file_fd,data.buff,sizeof(data.buff)))>0)
	{
		if(ret == 0)
		{
			printf("send file data done!\n");
			close(sock_fd);
			close(file_fd);
			return 0;
		}
		else if(-1 == ret)
		{
			perror("send file fail");
			close(sock_fd);
			close(file_fd);
			return -1;
		}else{
			cnt=0;
			data.len=ret;
			while(cnt<data.len)
			{
				ret = send(sock_fd,&data+cnt,4+data.len-cnt,0);
				cnt+=ret;
			}
		}
	}

	
	return 0;
}
