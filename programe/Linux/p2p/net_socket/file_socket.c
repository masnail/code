/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 16时31分21秒
 File Name:file_socket.c
 Description: 
 ************************************************************************/
#include "file_socket.h"


int recv_file(int client_fd,char *path,int off)
{
	//	printf("start recv file\n");
	/* int count */
	//	printf("recv file name =%s\n",path)
	/* 支持断点续传 */
//	unlink(path);
	int file_fd=open(path,O_CREAT|O_WRONLY,0666);
//	int file_fd=open(path,O_RDWR);

/*	if(-1 == file_fd)
	{
		file_fd=open(path,O_CREAT|O_WRONLY,0666);
	}*/
//	int off;
//	char buff[50]={0};
//	recv_msg(client_fd,buff);
//	puts(buff);
//	off=atoi(buff);
//	printf("recv off=%d\n",off);
	unsigned long lenfd=lseek(file_fd,off*OFF,SEEK_SET);
	
	/* recv file data */
	recv_file_data(client_fd,file_fd);
	close(file_fd);
	return 0;
}

/* 断点续传函数位置 */

int recv_file_data(int client_fd,int file_fd)
{
	int len=0,ret=0;//一次接受的数据长度
	char buff[SIZE_BUFF];

	while(1)
	{
		memset(&buff,0,sizeof(buff));
		ret=recv_msg(client_fd,buff);
//		printf("recv ret=%d\n",ret);
		if(0 == ret)
		{		return 0;
		}else if(-1 == ret)
		{		
			return -1;
		}
		printf("recv file data=%d\n",ret);
		write(file_fd,buff,ret);
	}
}

int send_file(int sock_fd,char *pathname,int off)
{
	int ret;
	//	printf("start send file\n");
//	printf("path name =%s:off=%d\n",pathname,off);
	int file_fd=open(pathname,O_RDONLY);
	if(-1 == file_fd)
	{
//		perror("file_fd");
		return -1;
	}
	/* 发送文件的数据 */
	//	path[strlen(path)]='.';
	//	puts(buff);
	ret=lseek(file_fd,off*OFF,SEEK_SET);
	if(-1 == ret)
	{
		return -1;
	}
//	char buff[50]={0};
//	sprintf(buff,"%d",off);
//	puts(buff);
//	send_msg(sock_fd,buff);
	send_file_data(sock_fd,file_fd);

	close(file_fd);
//	printf("send file data end done\n");
	return 0;
}

/* 断点续传函数位置 */

int send_file_data(int sock_fd,int file_fd)
{
	int ret=0;//单次发送的数据量
	int index=0;
	char buff[SIZE_BUFF];
	memset(buff,0,sizeof(buff));
	while(index<OFF)		
	{
//		memset(buff,0,sizeof(buff));
//		ret=read(file_fd,buff,sizeof(buff)-1);
//		memset(buff,0,sizeof(buff));
		ret=read(file_fd,buff,sizeof(buff));
		if(ret>0)
		{
//		if(-1 == ret)
//		{
//			perror("send file fail");
//			return -1;
//		}else if(0 == ret){
//			return 0;
//		}
		if(OFF-index>SIZE_BUFF)	
			ret=send_msg(sock_fd,buff,SIZE_BUFF);
		else
			ret=send_msg(sock_fd,buff,OFF-index);
			if(-1 == ret)
				return -1;
			index+=ret;
		
		printf("send file data=%d\n",ret);
		memset(buff,0,sizeof(buff));
		}else
			return 0;
	}
	return 0;
}

/*int send_file_mmap(int sock_fd,int file_fd,unsigned long len,unsigned long off)
{
	int ret;
	char buff[SIZE_BUFF];
	char *p=(char*)mmap(NULL,len,PROT_READ,MAP_SHARED,file_fd,0);
	if((char*)-1 == p)
	{
		return -1;
	}
	while(off<len)
	{
		memset(buff,0,sizeof(buff));
		if(len-off>SIZE_MSG)
		{
			memcpy(buff,p+off,SIZE_MSG);
		}else{
			memcpy(buff,p+off,len-off);
		}
		ret=send_msg(sock_fd,buff);
		if(-1 == ret)
		{
			close(file_fd);
			return -1;
		}
		off+=SIZE_MSG;
	}
	ret=munmap(p,len);
	close(file_fd);
	return ret;
}
*/
int find_dir_file(char *src, filelist **tail)//len=str(len)
{
	int ret, mode;
	struct stat fstat;
	char buff[SIZE_BUFF];
	memset(&fstat, 0, sizeof(fstat));
	//	printf("before src =%s\n",src);
	ret = stat(src, &fstat);
	if (-1 == ret)
	{
		//perror("stat");
		return -1;
	}
	mode = (fstat.st_mode >> 12) & 0x000f;

	//	printf("\nfunc %d\n",mode);
	if (4 == mode)
	{
		struct dirent *pdir;
		//		printf("src=%s\n",src);
		DIR *dir = opendir(src);
		while (NULL != (pdir = readdir(dir)))
		{
			memset(buff, 0, sizeof(buff));
			sprintf(buff, "%s/%s", src, pdir->d_name);
			//			printf("dir =%s\n",buff);
			if (0 != strcmp(".", pdir->d_name) && 0 != strcmp("..", pdir->d_name))
				find_dir_file(buff,tail);
		}
	}
	else if (8 == mode){
	//	printf("%s\n",src);
		for(int i=strlen(src);i>=0;i--)
		{
			if(src[i]=='/')
			{
				filelist *p=(filelist*)calloc(1,sizeof(filelist));
				strcpy(p->name,src+i+1);
				memcpy(p->path,src,i);
				(*tail)->next=p;
				*tail=p;
				break;
			}
		}

		//		printf("file path=%s\n",src);
	}
	return 0;

}

