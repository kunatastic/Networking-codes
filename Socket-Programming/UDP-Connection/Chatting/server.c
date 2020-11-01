#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int sockdesc;
	struct sockaddr_in servaddr,cliaddr;

	sockdesc=socket(AF_INET,SOCK_DGRAM,0);
	if(sockdesc==-1)
	{
		printf("Socket not created\n");
		return -1;
	}

	servaddr.sin_family=AF_INET;
    	servaddr.sin_port=htons(1025);			// PORT number ranges from 1024 to 49151
    	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    	if(bind(sockdesc,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
	{
		printf("Bind Failed\n");
		return -1;
	}
	char buffer[100];
	while (strcmp(buffer,"stop")!=0)
	{
		int len=sizeof(cliaddr);
		memset(buffer,'\0',strlen(buffer));
		recvfrom(sockdesc,buffer,sizeof(buffer),0,(struct sockaddr *)&cliaddr,&len);
		printf("Message received from client: %s\n", buffer);
		if (strcmp(buffer,"stop")==0){
			break;
		}
		printf("Enter the reply message: ");
		scanf("%s", buffer);
		sendto(sockdesc,buffer,strlen(buffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		
		printf("\n");
		
	}
	printf("Connection Disconnected\n");
	close(sockdesc);

	
	
	return 0;
}
