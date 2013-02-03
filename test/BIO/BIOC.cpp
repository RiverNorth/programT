#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "unp.h"
int main(int argc,char **argv)
{
	struct sockaddr_in servaddr;
	int fd,n;
	char recvline[255];
	if(argc !=2)
	{
		printf("a.out ipaddress");
		return -1;
	}
	if((fd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("error,socket,%s\n",strerror(errno));
		return -1;
	}
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(2213);
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
	{
		printf("error,inet_pton,%s\n",strerror(errno));
		return -1;
	}
	if(connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{	
		printf("error,connect,%s\n",strerror(errno));
		return -1;
	}
	close(fd);
/*	
	while((n=read(fd,recvline,254))>0)
	{
		printf("it arrived");
		recvline[n]=0;
		if(fputs(recvline,stdout)==EOF)
		{
			printf("error,read,%s\n",strerror(errno));
		}
	}

	printf("%d\n",n);
	if(n<0)
	{
		printf("error,iet_pton");
		return -1;
	}
*/
	return 0;
}
