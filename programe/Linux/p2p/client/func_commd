/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月14日 星期四 14时16分58秒
 File Name: func_commd.c--client
 Description: 
 ************************************************************************/
#include "func_commd.h"


void commd_adapte(int client_fd,msgcom msg)
{
	if(0 == strcmp("log",msg.com_com))
		commd_log(client_fd,msg);

	else if(0 == strcmp("cd",msg.com_com))
		commd_cd(client_fd,msg);

	else if(0 == strcmp("ls",msg.com_com))
		commd_ls(client_fd,msg);

	else if(0 == strcmp("gets",msg.com_com))
		commd_gets(client_fd,msg);

	else if(0 == strcmp("puts",msg.com_com))
		commd_puts(client_fd,msg);

	else if(0 == strcmp("rm",msg.com_com))
		commd_rm(client_fd,msg);

	else if(0 == strcmp("pwd",msg.com_com))
		commd_pwd(client_fd,msg);

	else 
		commd_error(msg.com_com);
	write_user_com(msg);
}

int commd_log(int client_fd,msgcom com)
{

}

int commd_cd(int client_fd,msgcom com)
{
	commd_errno_show(client_fd,com.com_com);
	return 0;
}

int commd_ls(int client_fd,msgcom com)
{
	int ret;
	char buff[SIZE_BUFF];
	memset(buff,0,sizeof(buff));
	commd_errno_show(client_fd,com.com_com);
	recv_errno(client_fd,&ret);
	
	while(ret >0)
	{
		memset(buff,0,sizeof(buff));
		recv_msg(client_fd,buff);
		puts(buff);
		ret--;
	}
	if(ret >0)
	{
		errno=atoi(buff);
		perror(NULL);
	}
		return ret;
}

int commd_gets(int client_fd,msgcom com)
{
	int ret=0;
	char path[SIZE_BUFF];
	memset(com.path_cur,0,sizeof(com.path_cur));
	getcwd(path,SIZE_BUFF-1);
	sprintf(com.path_cur,"%s/%s",path,com.com_param);
	printf("recv %s...\n",com.com_param);

	ret=recv_file(client_fd,com.path_cur);

	if(-1 == ret)
		printf("recv inter\n");
	else
		printf("recv done\n");
	return ret;
}

int commd_puts(int client_fd,msgcom com)
{
	int ret=0;
	char buff[SIZE_BUFF];
	printf("send %s...\n",com.com_param);
	ret=send_file(client_fd,com.com_param);
	if(-1 == ret)
		printf("send inter\n");
	else
		printf("send done\n");

	return ret;
}

int commd_rm(int client_fd,msgcom com)
{
	commd_errno_show(client_fd,com.com_com);
	return 0;
}

int commd_pwd(int client_fd,msgcom com)
{	
	int ret=0,index=0;
	char buff[SIZE_BUFF];
	memset(buff,0,sizeof(buff));
	
	ret=recv_msg(client_fd,buff);
	if(ret > 0)
	{
		for(int i=0;i<strlen(buff);i++)
		{
			if(buff[i]=='/')
				index++;
			if(index==2)
			{
				ret=i;
			}
		}
	}
	if(index<=2)
		printf("/\n");
	else
		puts(buff+ret+1);
	return 0;
}

int commd_error(char *com)
{	
	printf("%s:command not found\n",com);
	return 0;
}

int commd_errno_show(int client_fd,char *s)
{
	int err;
	recv_errno(client_fd,&err);
//	printf("err=%d\n",err);
	errno=err;
	if(errno!=0)
		perror(s);
}
