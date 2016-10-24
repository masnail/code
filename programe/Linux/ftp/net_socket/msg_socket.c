/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 16时31分21秒
 File Name:file_socket.c
 Description: 
 ************************************************************************/
#include "msg_socket.h"

void sub_msg(char *msg,msgcom *com)
{
	char *p;
	char del[3]=" \n";
	int index=0;
	p=strtok(msg,del);
	while(NULL != p)
	{
		index+=1;
		if(1 == index)
			strcpy(com->com_com,p);
		else if(2 == index)
			strcpy(com->com_param,p);
		else if(3 == index)
			strcpy(com->com_varparam,p);
		else  if(5 == index)
			strcpy(com->path_cur,p);
		else  if(4 == index)
			strcpy(com->com_name,p);
		p=strtok(NULL,del);
	}
		com->cnt=index;
}

int recv_msg(int client_fd,char *buff)
{
	int ret=0;
	int len=0,cnt=0;
	
	/* int count */
	ret = recv(client_fd,&len,sizeof(int),0);
	if(0 == len)
	{
		return 0;
	}else if(-1 == ret)
	{
		return -1;
	}
	/* recv msg data */
	while(cnt <len)
	{
		ret=recv(client_fd,buff+cnt,len-cnt,0); 
		if(0 == ret)
		{	
			return 0;
		}else if(-1 == ret){
			return -1;
		}
		cnt+=ret;
	}
//		buff[len]='\0';	
		return cnt;
}

int send_msg(int sock_fd,char *info)
{
	msgnode msg;
	memset(&msg, 0, sizeof(msg));
	msg.len = strlen(info);
	memcpy(msg.msg, info, msg.len);
	int ret=0,total=0;	
	while(total<msg.len+4)
	{
		ret = send(sock_fd,&msg+total,4+msg.len-total,0);
		if(-1 == ret)
		{
			return -1;
		}else if(0 == ret){						
			return 0;
		}
		total+=ret;
	}
	return total;
}

int recv_errno(int client_fd,int *err)
{
	int total=0,ret=0;
	while(total<4)
	{
		ret = recv(client_fd,err+total,4-total,0);
		if(-1 == ret)
		{
			return -1;
		}else if(0 == ret){
			return 0;
		}else{
			total+=ret;
		}
	}
	return 0;
}

int send_errno(int sock_fd,int err)
{
	int val=err,ret=0,total=0;
	while(total<4)
	{
		ret = send(sock_fd,&val+total,4-total,0);
		if(-1 == ret)
		{
			return -1;
		}else if(0 == ret){
			return 0;
		}else{
			total+=ret;
		}
	}
	return 0;
}

