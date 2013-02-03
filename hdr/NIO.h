#ifndef NIO_H
#define NIO_H
#include "unp.h"
#include "inlist.h"

#define CLI_CONNECTED 0
#define CLI_READED 1
#define CLI_WRITED 2
#define CLI_CLOSED 3
struct FileList
{
    InList inlist;
    int fd;
    int status;
};

inline int Socket(int domain,int type,int protocol)
{
        int fd;
        if((fd=socket(domain,type,protocol))<0)
	{
		ERROR("SOCKET");
	}
        return fd;
}


inline void Inet_pton(int domain,const char *str,struct in_addr *addr)
{
	if(inet_pton(domain,str,addr)<=0)
	{
		ERROR("INET_PTON");
	}
}

inline void Bind(int fd,struct sockaddr* addr,int len)
{
	if(bind(fd,addr,len)<0)
	{
		ERROR(bind);
	}
}

inline void Listen(int fd,int backlog)
{
	if(listen(fd,backlog)<0)
	{
		ERROR(bind);
	}
}

inline void Fcntl(int fd,int flag)
{
	int flag1;
	if((flag1=fcntl(fd,F_GETFL,0))<0)
	{
		ERROR("fcntl getflag");
	}
	flag=flag|flag1;
	if(fcntl(fd,F_SETFL,&flag)==-1)
	{
		ERROR("fcntl setflag");
	}

}

inline void Read

#endif
