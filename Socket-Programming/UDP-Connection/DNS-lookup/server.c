#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

const char *openfile(char str[],char out[]){
	FILE *fp;
	fp = fopen("lookup.txt", "r");
	if (fp == NULL)
	{
		printf("Error while opening the file.\n");
	}
	else{
		char ch[50];
		
		while(fgets ( ch, 50, fp ) != NULL )
		{
			
			int len = strlen(str);
			
			char temp[len];
			int i=0;
			for(i;i<len;i++){
				temp[i] = ch[i];
			}
			temp[i] = '\0';
			if (strcmp(temp,str)==0){
				len = strlen(ch);
				int count = 0;
				i++;
				for (i;i<len;i++){
					out[count] = ch[i];
					count++;
				}
				out[count] = '\0';
				break;
			}
			
		}
	}
	fclose(fp);
	return out;
}
int main()
{
	int sockdesc;
	struct sockaddr_in servaddr,cliaddr;

	sockdesc=socket(AF_INET,SOCK_DGRAM,0);
	if(sockdesc==-1)
	{
		printf("Socket not created\n \n");
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
	char output[100];
	while(1)
	{
		int len=sizeof(cliaddr);
		memset(buffer,'\0',strlen(buffer));
		printf("Waiting for a request...\n");
		recvfrom(sockdesc,buffer,sizeof(buffer),0,(struct sockaddr *)&cliaddr,&len);
		printf("Message received from client: %s\n", buffer);
		if (strcmp(buffer,"quit")==0)
		{
			printf("Server Down");
			break;
		}
		memset(output,'\0',strlen(output));
		openfile(buffer,output);
		printf("Server: %s\n",(output));
		sendto(sockdesc,output,sizeof(output),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		
		
	}

	close(sockdesc);
	return 0;
}
