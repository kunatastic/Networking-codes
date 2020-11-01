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
	struct sockaddr_in servaddr;
	sockdesc=socket(AF_INET,SOCK_DGRAM,0);
	if(sockdesc==-1)
	{
		printf("Socket not created");
		return -1;
	}

	servaddr.sin_family=AF_INET;
    	servaddr.sin_port=htons(1025);			
    	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	char buffer[100];
	while (strcmp(buffer,"stop")!=0)
	{
		printf("Enter the message to be sent: ");
		scanf("%s",buffer);
		sendto(sockdesc,buffer,strlen(buffer),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
		if (strcmp(buffer,"stop")==0){
			break;
		}
		int len=sizeof(servaddr);
		memset(buffer,'\0',strlen(buffer));
		recvfrom(sockdesc,buffer,sizeof(buffer),0,(struct sockaddr *)&servaddr,&len);
		printf("Message from server: %s\n", buffer);
		printf("\n");
	}
	printf("Connection disconnected\n");
	close(sockdesc);
	return 0;

}
