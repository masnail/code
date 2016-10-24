/*************************************************************************
 Author:MASnail
 Created Time: 2016年07月13日 星期三 23时56分57秒
 File Name: func_proc.h
 Description: 
 ************************************************************************/
#ifndef FUNC_PROC_H
#define FUNC_PROC_H

#include "head.h"
#include "func_qunofac.h"
#include "file_socket.h"
#include "func_commd.h"

void *func_handle(void*);

void init_factory(factory*);

void create_proc(factory*);

#endif

