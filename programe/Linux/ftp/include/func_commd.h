/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月14日 星期四 14时17分29秒
 File Name: func_commd.h
 Description: 
 ************************************************************************/
#ifndef FUNC_COMMD_H
#define FUNC_COMMD_H

#include "head.h"
#include "msg_socket.h"
#include "func_socket.h"
#include "file_socket.h"
#include "func_log.h"

void commd_adapte(int,msgcom);

int commd_log(int,msgcom);

void commd_log_in(int,char*);

int commd_cd(int,msgcom);

int commd_ls(int,msgcom);

int commd_gets(int,msgcom);

int commd_puts(int,msgcom);

int commd_rm(int,msgcom);

int commd_pwd(int,msgcom);

int commd_error(char*);

int commd_errno_show(int,char*);

#endif
