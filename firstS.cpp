#include"unp.h"
#include <time.h>
int main(int argc,char **argv)
{
	struct sockaddr_in servaddr;
	int fd,n,cfd;
	char buff[255];
	if((fd=socket(AF_INET,SOCK_STREAM,0))<=0)
	{
		printf("error");
		return -1;
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(2213);
	if(0!=bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr)))
	{
		printf("error bind,%s",strerror(errno));
		return -1;
	}
	if(0!=listen(fd,5))
	{
		printf("error listen,%s",strerror(errno));
		return -1;
	}
	while(true)
	{
		size_t a;
		if((cfd=accept(fd,NULL,&a))<0)
		{
			printf("%d\n",fd);
			printf("error accept,%s\n",strerror(errno));
			return -1;
		}
		time_t ti=time(NULL);
		sleep(3);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ti));
		printf("\n%s\n",buff);
		printf("the fd %d \n",cfd);
		if((n=write(cfd,&buff,sizeof(buff)))<=0)
		{	
			printf("error write");
			return -1;
		}
		printf("%d",n);
		close(cfd);	
	}	
	
}
