/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 15时26分31秒
 File Name: head.h
 Description: 
 ************************************************************************/
#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <crypt.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <pwd.h>
#include <string.h>
#include <sys/epoll.h>
#include <time.h>
#include <shadow.h>
#include <sys/mman.h>


#define SIZE_BUFF 512
/*
 * TCP连接数
 */
#define SIZE_CONNECT 8 
/*
 *线程连接数
 */
#define SIZE_PTHREAD 3 

#define SIZE_MSG 512 
#define OFF_SET 1024*1024*110
#define PATH_CONFIGURE "./config"
#define OFF 4096 


#endif
