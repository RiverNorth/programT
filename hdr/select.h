#include "unp.h"

#ifndef SELECT_H
#define SELECT_H 

#define MAX_CONNECTION 20
#define MAX_CONCURRENT 5

#define ON_CREATED 1
#define CON_CONNECTING 2
#define CON_CONNECTED 3
#define CON_CLOSED 4

fd_set wset,rset;
char buff[65500];
int maxfd,concurrent,leftcon,conNum,pindex;
struct sockaddr_in serv_addr;
struct con_file
{
	int status;
	int fd;
	char* path;
}con_files[MAX_CONNECTION];

int Socket(int domain,int type,int protocol)
{
        int fd;
        if((fd=socket(domain,type,protocol))<0)
	{ 
		ERROR("SOCKET");
	}
        return fd;
}

void Inet_pton(int domain,const char *str,struct in_addr *addr)
{
	if(inet_pton(domain,str,addr)<=0)
	{
		ERROR("INET_PTON");	
	}
}

//be careful with this method ,it could  write incompletely 
int Write(int fd, char* buff,int size)
{
	int n,length=0;
	if((n=write(fd,(buff+length),size-length))<0)
	{	
		ERROR("write");
	}
	else if(n>0)
	{
		if((length+=n)>=size)
			return length;	
	}		
	else
	{
		return length;
	}
}

int Read(int fd,char* buff,int size)
{
	int n,length=0;
	while((n=read(fd,buff+length,size-length)))
	{
		if(n==0)
			return length;
		if(n<0)
		{
			if(errno==EAGAIN)
			{
				return length;
			}
			else
			{
				ERROR("read");
			}
		}
		if(n>0)
		{
			if((length+=n)>=size)
				return length;	
		}
	}
}

//considering give a value to indicate how much data to transfer , compare it with Write return value to judge whether the data had been totally transferd in case signal comes or something happending disturbed the transferring.
void requestLink(struct con_file *file)
{
	
	snprintf(buff,sizeof(buff),"GET %s HTTP/1.0\r\n\r\n",file->path);			
	Write(file->fd,buff,sizeof(buff));
}


void readData(int fd)
{
	Read(fd,buff,sizeof(buff));	
	printf("\n%s\n",buff);
}

void connect_nonb(struct con_file *file,struct sockaddr* addr,socklen_t len)
{
	int n;
	if(file->status!=ON_CREATED)
	{
		ERR_SYS("connect");
		return;
	}
	if((n=connect(file->fd,addr,len))<0)
	{
		if(errno!=EINPROGRESS)
		{
			ERR_SYS("connect");
			return;
		}
		else
		{
			file->status=CON_CONNECTING;
			FD_SET(file->fd,&wset);
		}
	}	
	else
	{
		requestLink(file);
		file->status=CON_CONNECTED;
		FD_SET(file->fd,&rset);
	}
	if(file->fd>maxfd)
		maxfd=file->fd;	
}

#endif
