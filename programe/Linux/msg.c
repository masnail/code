/*************************************************************************
 Author:0054
 Created Time: 2016年07月12日 星期二 09时48分10秒
 File Name: msg.c
 Description: 
 ************************************************************************/

void send_msg(int fdw,int fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));

	/* 必须初始化 */
	struct iovec *iov=(struct iovec*)calloc(1,sizeof(struct iovec));
	char buff[5]={0};
	iov->iov_base=buff;
	iov->iov_len=5;

	struct cmsghdr cmsg;
	int len = CMSG_LEN(4);
	cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg.cmsg_len=len;
	cmsg.cmsg_level=SOL_SOCKET;
	cmsg.cmsg_type=SCM_RIGHTS;
	*(int*)CMSG_DATA(cmsg)=fd;//赋值

	msg.msg_iov=iov;
	msg.msg_iovlen=1;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	int ret =sendmsg(fdw,fd,0);
	if(-1 == ret)
	{
		perror("sendmsg");
		exit(-1);
	}
}

void recv_msg(int fdr,int *fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));

	/* 必须初始化 */
	struct iovec *iov=(struct iovec*)calloc(1,sizeof(struct iovec));
	char buff[5]={0};
	iov->iov_base=buff;
	iov->iov_len=5;

	struct cmsghdr cmsg;
	int len = CMSG_LEN(4);
	cmsg=(struct cmsghdr*)calloc(1,len);
	cmsg.cmsg_len=len;
	cmsg.cmsg_level=SOL_SOCKET;
	cmsg.cmsg_type=SCM_RIGHTS;

	msg.msg_iov=iov;
	msg.msg_iovlen=1;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	int ret =recvmsg(fdr,fd,0);
	if(-1 == ret)
	{
		perror("sendmsg");
		exit(-1);
	}
	*fd=*(int*)CMSG_DATA(cmsg);//取值
}

