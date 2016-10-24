/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月12日 星期二 16时31分21秒
 File Name: client.c
 Description: 
 ************************************************************************/
#include "head.h"
#include "file_socket.h"
#include "func_socket.h"
#include "msg_socket.h"
#include "func_commd.h"
#include "func_log.h"

void getPasswd(char *passwd)
{
	int index=0;
	char ch;
	while((ch=getchar())!=13)
	{
		if(ch==8)
		{
			if(index>0&&index<=20)
			{
				passwd[index--]='\0';
				printf("\b \b");
			}
		}else if(ch != 32){ 
			if(index<19)
			{
				passwd[index++]=ch;
				printf("\b \b");
			}
		}
	}
}

void user_log(int fd,char *name)
{
	int ret;
	 char passwd[SIZE_BUFF],buff[SIZE_BUFF],salt[SIZE_MSG];
	 char *serc=NULL;

	memset(passwd,0,sizeof(passwd));
	memset(buff,0,sizeof(buff));
	memset(salt,0,sizeof(salt));

	printf("login as:");
	scanf("%s",name);
	printf("%s@ password:",name);
	scanf("%s",passwd);
//	getPasswd(passwd);	
	sprintf(buff,"log %s",name);
	send_msg(fd,buff,strlen(buff));//send
	
	ret=recv_msg(fd,buff);//recv serc and salt
//	printf("valu=%s\n",buff);
	if(ret>0)
	{
		int index=0;
		for(int i=0;i<strlen(buff);i++)
			if('$' == buff[i])
			{
				index++;
				if(3 == index)
				{
					index=i;
					break;
				}
			}
		memcpy(salt,buff,index);
//		printf("salt=%s\n",salt);
//		puts(salt);
		while(1)
		{
			serc=crypt(passwd,salt);	
			if(0 ==strcmp(serc,buff))
				break;
			memset(passwd,0,sizeof(passwd));
			printf(" Access denied\n");
			printf("%s@Linux password:",name);
//			getPasswd(passwd);	
			scanf("%s",passwd);
		write_user_log(name,"log-FAIL");
		}		
		
	}else{
		while(1)
		{
			memset(passwd,0,sizeof(passwd));
			printf(" Access denied\n");
			printf("%s@Linux password:",name);
			scanf("%s",passwd);
		write_user_log(name,"log-FAIL");
		}		
	}
//		printf("[%s@Linux/ /]#> ",name);
		printf("Welcome %s you !\n",name);
		write_user_log(name,"log-SUCCESS");
}
int init_client(/*int *client_fd,*/char *ip,int *port)
{	
	char buff[21];
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
	buff[strlen(buff)-1]='\0';
	char *p=strtok(buff,"|");
	*port=atoi(p);
	p=strtok(NULL,"|");
	strcpy(ip,p);
	close(file_fd);
//	socket_client_tcp(client_fd,*port,ip);
}

int main()
{
	int client_fd,len,port;
	char buff[21],ip[16];
	char path[SIZE_BUFF],name[SIZE_BUFF];
	memset(ip,0,sizeof(ip));
	memset(name,0,sizeof(name));
	memset(path,0,sizeof(path));

	init_client(/*&client_fd,*/ip,&port);		
//	user_log(client_fd,name);
//	close(client_fd);

	sprintf(path,"/home/%s",name);

//	socket_client_tcp(&client_fd,port,ip);
	msgcom msg_com;

/*	memset(&msg_path,0,sizeof(msg_path));
	msg_path.len=strlen(path);
	sprintf(msg_path.msg,"cd %s",path);
	send_msg(client_fd,msg_path);
	printf("start =%s\n",msg_path.msg);
	memset(path,0,sizeof(path));
	recv_msg(client_fd,path);//set path
	close(client_fd);*/

	while(1)
	{
		memset(buff,0,sizeof(buff));
//		printf("[%s@Linux/ %s]#> ",name,path);
		read(0,buff,sizeof(buff));
	//	puts(buff);
		if(strlen(buff)>0)
		{
			socket_client_tcp(&client_fd,port,ip);

	//		memset(path,0,sizeof(path));
//			recv_msg(client_fd,path);//set path*/

		//	send_msg(client_fd,buff);//order

			memset(&msg_com,0,sizeof(msg_com));
			sub_msg(buff,&msg_com);
			send_msg(client_fd,buff,strlen(buff));
			strcpy(msg_com.path_cur,path);
	//		send_msg(client_fd,path);
	//		puts(msg_data.msg);
		
			strcpy(msg_com.com_name,name);
	//		send_msg(client_fd,name);
			unsigned long capat;
			recv(client_fd,&capat,sizeof(unsigned long),0);
			printf("recv file len=%lu\n",capat);
			if(capat>0)
			{
				int index=capat/OFF;
				if(capat%OFF != 0)
					index+=1;
				printf("off set=%d\n",index);
				int i=0;
			//	for(int i=;i<1;i++)
				{
				//	printf("exce count =%d\n",i);
				//	send(client_fd,&i,sizeof(int),0);
					recv_file(client_fd,buff,17926);
				}
			}
	/*		memset(&msg_data,0,sizeof(msg_data));
			msg_data.len=strlen(path);
			memcpy(msg_data.msg,path,msg_data.len);
			send_msg(client_fd,msg_data);//path*/

	//		commd_adapte(client_fd,msg_com);

	//		if(0 == strcmp("cd",msg_com.com_com))
	//		{
	//			memset(path,0,sizeof(path));
	//			recv_msg(client_fd,path);//recv path
	//		}
			//	puts(path);
			close(client_fd);
		}
	}
//	close(client_fd);
}
