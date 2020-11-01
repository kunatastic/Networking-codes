#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>


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

	
	int n,ws;
	printf("Enter the no of frames to be sent: ");
	scanf("%d",&n);
	
	printf("Enter the last digit of Reg no: ");
	scanf("%d",&ws);
	
	ws = (ws%3)+2;
	printf("\nThe Window Size is: %d\n\n",ws);
	
	for (int i=1; i<=n;i+=ws)
	{
		int val = 0, control = -1;
		char ind[5];
		for (int k = 0;k<ws;k++){
			
			char buffer[100];
			memset(buffer,'\0',strlen(buffer));		
			char temp[5];	
			strcat(buffer,"D");
			sprintf(temp,"%d",i+k);
			strcat(buffer,temp);
			if (i+k<=n){
				printf("Message sent reciever: %s\n",buffer);
				sendto(sockdesc, buffer, strlen(buffer), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
				
				int len=sizeof(servaddr);
				char buffer1[100];
				memset(buffer1,'\0',strlen(buffer1));
				recvfrom(sockdesc, buffer1,sizeof(buffer1), 0, (struct sockaddr *) &servaddr, &len);
				printf("Message from server: %s\n", buffer1);
				if (strstr(buffer1,"NACK")!=0){
					printf("Wait Will resend soon...\n\n");
					control = 1;
					strcpy(ind,buffer);
				}
			}
			
		}
		if (val != 0){
			i-=ws;
			i+=val%ws;
		}
		
		if (control == 1){
			printf("Message sent reciever: %s\n",ind);
			sendto(sockdesc, ind, strlen(ind), 0, (struct  sockaddr *) &servaddr, sizeof(servaddr));
			int len=sizeof(servaddr);
			char buffer1[100];
			memset(buffer1,'\0',strlen(buffer1));
			recvfrom(sockdesc, buffer1,sizeof(buffer1), 0, (struct sockaddr *) &servaddr, &len);
			printf("Message from server: %s\n", buffer1);
		}
		
		printf("\nWINDOW SHIFT\n\n");
	}
	sendto(sockdesc, "stop", strlen("stop"), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Connection disconnected\n");
	close(sockdesc);
	return 0;

}
