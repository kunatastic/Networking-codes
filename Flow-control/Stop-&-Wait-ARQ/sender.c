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

	
	int n;
	printf("Enter the number of frames to be sent: ");
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		char buffer[100];
		memset(buffer,'\0',strlen(buffer));		
		char temp[5];
		strcmp(temp,"");
		strcat(buffer,"D");
		sprintf(temp,"%d",i);
		strcat(buffer,temp);
		
		printf("Message sent reciever: %s\n",buffer);
		sendto(sockdesc, buffer, strlen(buffer), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
		
						
		int len=sizeof(servaddr);
		char buffer1[100];
		memset(buffer1,'\0',strlen(buffer1));
		recvfrom(sockdesc, buffer1,sizeof(buffer1), 0, (struct sockaddr *) &servaddr, &len);
		printf("Message from server: %s\n", buffer1);
		if (strstr(buffer1,"NACK")!=0){
			i--;
			printf("Resending the packet...\n");
		}
		printf("\n");
	}
	sendto(sockdesc, "stop", strlen("stop"), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Connection disconnected\n");
	close(sockdesc);
	return 0;

}
