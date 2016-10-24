/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 16时31分21秒
 File Name:file_socket.c
 Description: 
 ************************************************************************/
#include "file_socket.h"


int recv_file(int client_fd,char *path)
{
	int ret;
	int len=0;
//	printf("start recv file\n");
	/* int count */
	//	printf("recv file name =%s\n",path)
	/* 支持断点续传 */
	int file_fd=open(path,O_RDWR);

	if(-1 == file_fd)
	{
		file_fd=open(path,O_CREAT|O_WRONLY,0666);
	}
		unsigned long lenfd=lseek(file_fd,0,SEEK_END);
		send(client_fd,&lenfd,4,0);
	
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
		memset(buff,0,sizeof(buff));
		ret=recv_msg(client_fd,buff);
		if(0 == ret)
		{
			close(file_fd);
			return 0;
		}else if(-1 == ret)
		{
			close(file_fd);
			return -1;
		}
		write(file_fd,buff,ret);
	}
}

int send_file(int sock_fd,char *pathname)
{
	int ret;
	msgnode msg;
//	printf("start send file\n");
	int file_fd=open(pathname,O_RDONLY);
	if(-1 == file_fd)
	{
//		perror("file_fd");
		return -1;
	}
	/* 发送文件的数据 */
	//	path[strlen(path)]='.';
	unsigned long len,off;
	
	recv(sock_fd,&off,4,0);
//	puts(buff);
	struct stat stat_buff;
	memset(&stat_buff,0,sizeof(struct stat));
	ret = stat(pathname,&stat_buff);
	len=stat_buff.st_size;
	if(len <= OFF_SET)//more
	{
		ret=lseek(file_fd,off,SEEK_SET);
		if(-1 == ret)
		{
			return -1;
		}
		send_file_data(sock_fd,file_fd);
	}else{
		send_file_mmap(sock_fd,file_fd,len,off);
	}
	close(file_fd);
	return 0;
}

/* 断点续传函数位置 */

int send_file_data(int sock_fd,int file_fd)
{
	int ret=0,cnt=0;//单次发送的数据量
	char buff[SIZE_BUFF];
	while(1)
	{
		memset(buff,0,sizeof(buff));
		ret = read(file_fd,buff,sizeof(buff));
		if(-1 == ret)
		{
//			perror("send file fail");
			close(file_fd);
			return -1;
		}else{
			send_msg(sock_fd,buff);
			if(0 == ret)
			{
				close(file_fd);
//				printf("recv file done\n");
				return 0;
			}else if(-1 == ret){
				close(file_fd);
				return -1;
			}
		}
	}
}

int send_file_mmap(int sock_fd,int file_fd,unsigned long len,unsigned long off)
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

int send_dir_file(int client_fd,char *src, int len)//len=str(len)
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
				send_dir_file(client_fd,buff, len);
		}
	}
	else if (8 == mode){
		int fdr = open(src, O_RDONLY);
		if (-1 != fdr)
		{
			//send_msg(client_fd, );
			send_file(fdr, src);
		}
		//		printf("file path=%s\n",src);
	}
	return 0;

}

