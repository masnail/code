/************************************************************************
 Author:MASnail
 Created Time: 2016年07月17日 星期日 15时56分30秒
 File Name: copydir.c
 Description: 
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#define SRC "/lzf"
#define DES "/123"
#define SIZE_BUFF 512

void copy_file(char *src,char *des,int len)
{
//	puts(path);
	char buff[SIZE_BUFF],capat[SIZE_BUFF];
	memset(buff,0,sizeof(buff));
	int fdr=open(src,O_RDONLY);
	sprintf(buff,"%s/%s",des,src+len);
//	puts(buff);
	int fdw=open(buff,O_CREAT|O_WRONLY,0666);
	
//		perror("copy file");
	//	return;
	
	while(memset(capat,0,sizeof(capat)),read(fdr,capat,sizeof(capat)-1)>0)
	{
//		printf("file data size =%d:len=%d\n",sizeof(capat)-1,strlen(capat));
		write(fdw,capat,strlen(capat));
	//	memset(capat,0,sizeof(capat));
	}
	close(fdw);
	close(fdr);
}

int copy_dir(char *src,char *des,int len)
{
	int ret,mode;
	struct stat fstat;
	char buff[SIZE_BUFF];
	memset(&fstat,0,sizeof(fstat));
//	printf("before src =%s\n",src);
	ret = stat(src,&fstat);
	if(-1 == ret)
	{
		perror("stat");
		return -1;
	}
	mode=(fstat.st_mode>>12)&0x000f;

//	printf("\nfunc %d\n",mode);
	if(4 == mode)
	{
		struct dirent *pdir;
//		printf("src=%s\n",src);
		memset(buff,0,sizeof(buff));
		sprintf(buff,"%s/%s",des,src+len);
//		printf("dir 4 =%s\n",buff);
		mkdir(buff,0666);
		DIR *dir=opendir(src);
		while(NULL != (pdir=readdir(dir)))
		{
			memset(buff,0,sizeof(buff));
			sprintf(buff,"%s/%s",src,pdir->d_name);
//			printf("dir =%s\n",buff);
			if(0 != strcmp(".",pdir->d_name) && 0 != strcmp("..",pdir->d_name))
				copy_dir(buff,des,len);
		}
	}else if(8 == mode){
		copy_file(src,des,len);
//		printf("file path=%s\n",src);
	}
	return 0;
	
}

int main(int argc,char *argv[])
{	
	printf("COPY DIR FILE !\n");
	copy_dir(argv[1],argv[2],strlen(argv[1]));

	return 0;
}
