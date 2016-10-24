/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月14日 星期四 14时16分58秒
 File Name: func_commd.c--server
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
	write_client_com(msg);
}

int commd_log(int client_fd,msgcom msgc)
{
	struct spwd *sp;
	char *serc=NULL;
	sp = getspnam(msgc.com_param);
	if(NULL == sp)
	{
		send_msg(client_fd,NULL);
		return -1;
	}
	send_msg(client_fd, sp->sp_pwdp);
	return 0;
}

int commd_cd(int client_fd,msgcom com)
{
	int ret,errv=0;
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	sprintf(path,"%s/%s",com.path_cur,com.com_param);
	ret = chdir(path);
	if(-1 == ret)
	{
		errv=errno;
		goto err;
	}
	memset(path,0,sizeof(path));
	getcwd(path,SIZE_BUFF);
	
	int index=0;
	for(int i=0;i<strlen(path);i++)
	{
		if(path[i]=='/')
			index++;
	}
	if(index >= 2)
		goto nom;
	else
		goto err; 

nom:	send_errno(client_fd,errv);
		send_msg(client_fd,path);
		return 0;

err:	send_errno(client_fd,errv);
		send_msg(client_fd, com.path_cur);
		return -1;
}

int commd_ls(int client_fd,msgcom com)
{
	int ret,errv=0;
	char buff[SIZE_BUFF],send_buff[SIZE_BUFF],path[SIZE_BUFF];
	msgnode msg;	
	memset(path,0,sizeof(path));
	pmsgnode *head=(pmsgnode*)calloc(1,sizeof(pmsgnode)),*p=head;
	
//	if(com.cnt==1)
//		com.com_param[0]='.';
	sprintf(path,"%s/%s",com.path_cur,com.com_param);
	if(strlen(com.com_param)>=2)	
	if(com.com_param[0]=='.'&&com.com_param[1]=='.')
	{
		int index=0;
		for(int i=0;i<strlen(com.path_cur);i++)
		{
			if(com.path_cur[i]=='/')
			index++;
		}
		if(index<=2)
			goto err;
	}
	DIR *dir=opendir(path);
	if(NULL == dir)
	{
		errv=errno;
		goto err;
	}
	struct dirent *pdir;
	struct stat fstat;

	while(NULL !=(pdir=readdir(dir)))
	{
		if(0 !=strcmp(pdir->d_name,".") && 0 != strcmp(pdir->d_name,".."))
		{
		memset(buff,0,sizeof(buff));
		memset(&fstat,0,sizeof(fstat));
		sprintf(buff,"%s/%s",path,pdir->d_name);
		ret=stat(buff,&fstat);
		if(-1 == ret)
		{
			errv=errno;
			goto err;
		}
		memset(send_buff,0,sizeof(send_buff));
		memset(&msg,0,sizeof(msg));
		sprintf(send_buff,"%10ld \t%s",fstat.st_size,pdir->d_name);
		msg.len=strlen(send_buff);
		memcpy(msg.msg,send_buff,msg.len);
		pmsgnode *pmsg=(pmsgnode*)calloc(1,sizeof(pmsgnode));
		memcpy(&pmsg->msgn,&msg,sizeof(msgnode));
		p->next=pmsg;
		p=pmsg;
		(head->msgn).len+=1;
		}
	}	
err:	send_errno(client_fd,errv);
		send_errno(client_fd,(head->msgn).len);
		p=head;
		while(NULL != p)
		{
			send_msg(client_fd,head->msgn.msg);
			head=head->next;
			free(p);
			p=head;
		}
		closedir(dir);
	return 0;
}

int commd_gets(int client_fd,msgcom com)
{
	int ret; 
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	sprintf(path,"%s/%s",com.path_cur,com.com_param);
	ret=send_file(client_fd,path);
	return 0;
}

int commd_puts(int client_fd,msgcom com)
{
	int ret,index=0;
	char path[SIZE_BUFF];
	memset(path,0,sizeof(path));
	for(int i=strlen(com.com_param);i>=0;i--)
	{
		if(com.com_param[i]=='/')
		{
			index=i;
			break;
		}
	}
	sprintf(path,"%s/%s",com.path_cur,com.com_param+index);
	ret=recv_file(client_fd,path);
	return 0;
}

int commd_rm(int client_fd,msgcom com)
{
	int ret,errv=0;
	char path[SIZE_BUFF];
	struct stat fstat;
	struct passwd *sp;
	memset(path,0,sizeof(path));
	memset(&fstat,0,sizeof(struct stat));
	
	sprintf(path,"%s/%s",com.path_cur,com.com_param);
	ret=stat(path,&fstat);
	sp=getpwnam(com.com_name);
	if(fstat.st_uid==sp->pw_uid)
	{
		ret=unlink(path);
		errv=errno;
	}else
	{
	   errv=13;
	}
	send_errno(client_fd,errv);
	return ret;
}

int commd_pwd(int client_fd,msgcom com)
{
	
	int ret,errv=0;
	ret = send_msg(client_fd, com.path_cur);
	return ret;
}

