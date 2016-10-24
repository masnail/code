/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月15日 星期五 13时18分54秒
 File Name: func_log.c
 Description: 
 ************************************************************************/
#include "func_log.h"

void create_time(char *timeb)
{
	time_t timer;
	struct tm *timeinfo;
	time(&timer);
	timeinfo=localtime(&timer);
	strftime(timeb,21,"%m-%d-%Y/%H:%M:%S|",timeinfo);
}

void write_user_log(char *name,char *logstat)
{
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	sprintf(path,"./log/log/%s",name);
	int ret=mkdir("./log/log",0666);

	int fdw=open(path,O_CREAT|O_WRONLY|O_APPEND|O_EXCL,0666);
	char buff[SIZE_BUFF],timeb[21];
	if(-1 == fdw)
	{
	fdw=open(path,O_WRONLY|O_APPEND);
	/*	if(-1 == *fdw)
		{
			perror("write log error");
			return;
		}
		*/
	}
	memset(buff,0,sizeof(buff));
	memset(timeb,0,sizeof(timeb));
	create_time(timeb);
	sprintf(buff,"%s--%s--%s\n",timeb,name,logstat);
	write(fdw,buff,strlen(buff));
	close(fdw);
}

void write_user_com(msgcom com)
{
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	sprintf(path,"./log/com/%s",com.com_name);
	int ret=mkdir("./log/com",0666);

	int fdw=open(path,O_CREAT|O_WRONLY|O_APPEND|O_EXCL,0666);
	char buff[SIZE_BUFF],timeb[21];
	if(-1 == fdw)
	{
	fdw=open(path,O_WRONLY|O_APPEND);
	/*	if(-1 == *fdw)
		{
			perror("write log error");
			return;
		}
		*/
	}
	memset(buff,0,sizeof(buff));
	memset(timeb,0,sizeof(timeb));
	create_time(timeb);
	sprintf(buff,"%s--%s %s %s %s--%s\n",timeb,com.com_name,com.com_com,com.com_param,com.com_varparam,com.path_cur);
	write(fdw,buff,strlen(buff));
	close(fdw);
}

void write_client_log(struct sockaddr_in addr,msgcom com)
{
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	sprintf(path,"/log/log/%s",com.com_param);
	int ret=mkdir("/log/log",0666);

	int fdw=open(path,O_CREAT|O_WRONLY|O_APPEND|O_EXCL,0666);
	char buff[SIZE_BUFF],timeb[21];
	if(-1 == fdw)
	{
	fdw=open(path,O_WRONLY|O_APPEND);
	/*	if(-1 == *fdw)
		{
			perror("write log error");
			return;
		}
		*/
	}
	memset(buff,0,sizeof(buff));
	memset(timeb,0,sizeof(timeb));
	create_time(timeb);
	sprintf(buff,"%s--%s %s--%s\n",timeb,com.com_name,inet_ntoa(addr.sin_addr),com.com_param);
	write(fdw,buff,strlen(buff));
	close(fdw);
}

void write_client_com(msgcom com)
{
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	sprintf(path,"/log/com/%s",com.com_name);
	int ret=mkdir("/log/com",0666);

	int fdw=open(path,O_CREAT|O_WRONLY|O_APPEND|O_EXCL,0666);
	char buff[SIZE_BUFF],timeb[21];
	if(-1 == fdw)
	{
	fdw=open(path,O_WRONLY|O_APPEND);
	/*	if(-1 == *fdw)
		{
			perror("write log error");
			return;
		}
		*/
	}
	memset(buff,0,sizeof(buff));
	memset(timeb,0,sizeof(timeb));
	create_time(timeb);
	sprintf(buff,"%s--%s %s %s %s--%s\n",timeb,com.com_name,com.com_com,com.com_param,com.com_varparam,com.path_cur);
	write(fdw,buff,strlen(buff));
	close(fdw);
}

