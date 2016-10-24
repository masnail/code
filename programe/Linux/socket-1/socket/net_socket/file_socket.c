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
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	
	/* int count */
	ret = recv(client_fd,&len,sizeof(int),0);
	if(0 >= len)
	{
		printf("recv file name fail!\n");
		close(client_fd);
		return -1;
	}
	
	int total=0;
	while(total<len)
	{
		memset(buff,0,sizeof(buff));
		ret = recv(client_fd,buff,len-total,0);
		if(-1 == ret)
		{
			perror("recv fail!\n");
			close(client_fd);
			return -1;
		}
		memcpy(path+total,buff,ret);
		total+=ret;
	}
	printf("recv file name =%s:%d\n",buff,total);

	/* 不支持断点续传 */
	int file_fd=open(path,O_RDWR);
	if(-1 != file_fd)
	{
		close(file_fd);
		unlink(buff);	
	}	
	file_fd=open(path,O_CREAT|O_RDWR,0666);
	/* recv file data */
	recv_file_data(client_fd,file_fd);
}

/* 断点续传函数位置 */

int recv_file_data(int client_fd,int file_fd)
{
	int len=0,ret=0,cnt=0;//一次接受的数据长度
	char buff[SIZE_BUFF];
	while(1)
	{
		ret=recv(client_fd,&len,sizeof(int),0); 
		if(0 == ret)
		{
			printf("recv file  done! \n");
			close(client_fd);
			close(file_fd);
			return 0;
		}else if(-1 == ret)
		{
			close(client_fd);
			close(file_fd);
			return -1;
		}
		cnt=0;
//		index+=len;
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
			write(file_fd,buff,ret);
		}
	}
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
	printf("file name =%s\n",pathname);
	
	int total=0;
	data.len=strlen(pathname);
	memcpy(data.buff,pathname,data.len);
	while(total<data.len+4)
	{
		ret = send(sock_fd,&data+total,4+data.len-total,0);
	/* 不支持断点续传 */

		if(-1 == ret)
		{
			perror("send");
			close(sock_fd);
			close(file_fd);
			return -1;
		}
		total+=ret;
	}

		/* 发送文件的数据 */
	send_file_data(sock_fd,file_fd);
	
	return 0;
}

/* 断点续传函数位置 */

int send_file_data(int sock_fd,int file_fd)
{

	int ret=0,cnt=0;//单次发送的数据量
	datalist data;
	while(1){
			memset(&data,0,sizeof(data));
			ret = read(file_fd,data.buff,sizeof(data.buff));
	
		if(-1 == ret)
		{
			perror("send file fail");
			close(sock_fd);
			close(file_fd);
			return -1;
		}else if(0 == ret){
			close(sock_fd);
			close(file_fd);
			printf("send end done\n");
			return 0;
		}else{
			cnt=0;
			data.len=ret;
			while(cnt<data.len+4)
			{
				ret = send(sock_fd,&data+cnt,4+data.len-cnt,0);
				cnt+=ret;
			}
		}
	}
}
