#include "unp.h"aaa bbbb
#include "NIO.h"sdfsd

int main(int argc,char** argv)
{
	if(argc !=2)
	{
		fprintf(stderr,"usage:a.out port");
	}
	int fds[255+1];
	int maxfd,num;
	fd_set rset,wset,trset,twset;
	FD_ZERO(&rset);
	FD_ZERO(&wset);
	struct timeval tv={0,0};
	int port=atoi(argv[1]);
	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	int servfd=Socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(port);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	Bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	Listen(servfd,255);
	Fcntl(servfd,O_NONBLOCK);
	FD_SET(&rset,servfd);
	maxfd=servfd;
	int tempfd;
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	//init a list to contain the fd;
	INITLIST(head);
	do{
		trset=rset;
		twset=wset;
		if((num=select(maxfd+1,&trset,&twset,NULL,NULL))<0)
		{
			if(errno==EINTR)
			{
				continue;
			}
			else
			{
				ERROR("select");
			}
		}
		else if(n>0)
		{

            if(FD_ISSET[servfd,&trset])
            {
                if((tempfd=accept(servfd,&cliaddr,len))<0)
                {
                    if(errno==EWOULDBLOCKl)
                        ERR_SYS("client absorted");
                    else if(errno==EINTR)
                        ERR_SYS("signal interrupt");
                    else
                    {
                        ERROR("accept");
                    }
                }
                else
                {
                    struct FileList* templist=(struct FileList*)malloc(sizeof(struct FileList));
                    templist->fd=tempfd;
                    templist->status=CLI_CONNECTED;
                    add_node_tail(&(templist->inlist),head);
                    n--;
                }
            }

				if(n>0&&FD_ISSET[servfd,&trset]
			}
		}
	}
}
