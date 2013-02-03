#include "unp.h"
#define ERROR(x) perror(x);exit(errno);

Socket(int domain,int type,int protocol)
{
	int fd;
	if((fd=socket(domain,type,protocol))<0)
		ERROR("SOCKET");
	return fd;
}

#define MAX_CONNECTION 20;
#define MAX_CONCURRENT 5;
fd_set rset,wset;
struct sockaddr_in serv_addr;
int maxfd,concurrent=0,leftcon=MAX_CONNECTION;
int main()
{
        fd_set trset,twset;
	int n,error;
	int error_s=sizeof(error);
	struct timeval tval={0,100};
	for(int i=0;i<MAX_CONNECTION;i++)
	{
		int fd,flag;
		fd=Socket(AF_INET,SOCK_STREAM,0);
		struct con_file confile={ON_CREATED,fd};
		if((flag=fcntl(fd,F_GETFL,0))<0)
                        ERROR("fcntl,F_GETFL");
                if(fcntl(fd,F_SETFL,flag|O_NONBLOCK)<0)
                        ERROR("fcntl,F_SETFL");
		con_files[i].fd=fd;
		con_files[i].status=CON_CREATED;
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(5505);
	Inet_pton(AF_INET,SOCK_STREAM,&serv_addr.in_addr);	
	socklent_t len = sizeof(serv_addr);
        FD_ZERO(&rset);
        wset=rset;
        while(leftcon!=0)
        {
		if(concurrent<MAX_CONCURRENT)
		{
			connect_nonb(&con_files[i],(struct sockaddr*)&serv_addr,len);
		}
		trset=rset;
		twset=wset;
		if((n=select(maxfd+1,&rset,&wset,NULL,&tval))>0)
		{
			for(int i=0;i<MAX_CONNECTION,n>0;i++)
			{
				trset=rset;
				twset=wset;
				error=0;
				if(FD_ISSET(files[i].fd,&wset)||FD_ISSET(files[i].fd,&rset))
				{
					if(getsockopt(files[i].fd,SOL_SOCKET,SO_ERROR,&error,&error_s)<0||error!=0)
					{	
						ERR_SYS("read write or connect error");
						close(files[i]);
						files[i]=CON_CREATED;
					}
					else if(files[i].status==CON_CONNECTING)
					{
						//be careful with the write function,cause it'll block or may not write the whoel data,be carefully 
						//with the error handle.
						requestLink(files[i]);
						files[i].status=CON_CONNECTED;
						FD_CLR(files[i].fd,&wset);
						FD_SET(files[i].fd,&rset);
					}
					else if(files[i].status==CON_CONNECTED)
					{
						//be carefule with the close and read function, it will cause block and may not read the whole date.
						//and also be careful with read error handdle;
						readData(files[i]);
						files[i].status=CON_CLOSED;
						FD_CLR(files[i].fd,&rset);
						close(files[i]);
						concurrent--;
						leftconn--;
					}
					else
					{
						err_sys("unknown error");
					}
				}
			}
		}
		else if(n<0)
		{
			ERR_SYS("select");
		}
	}

}
