#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

    int sockdesc = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket Number: %d\n",sockdesc);
    if (sockdesc < 0){
    	printf("Socket failed\n");
    	return -1;
    }
    
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(1025); // range from 1024 to 49151
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);//any available ip
    
    
    int bindValue = bind(sockdesc, (struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Bind value: %d\n",bindValue);
    if (bindValue < 0){
    	printf("Bind failed\n");
    	return -1;
    }
    
    
    int listenValue = listen(sockdesc,5);
    printf("Listen value: %d\n",listenValue);
    if (listenValue < 0){
    	printf("Listen failed\n");
    	return -1;
    }
    
    char buffer[100];
    while(strcmp(buffer,"exit") != 0)
    {
		//17.08.2020
		struct sockaddr_in cliaddr;
		int len = sizeof(cliaddr);
		int connfd = accept(sockdesc, (struct sockaddr *) &cliaddr, &len);
		if (connfd < 0){
			printf("Accept failed\n");
			return -1;
		}
		printf("\nWaiting for a request...\n");
		
		//strcpy(buffer,"");	
		read(connfd, buffer, 100);
		printf("Messge recieved from client: %s\n",buffer);
		//process
		system(buffer);
		write(connfd, buffer, 100);
    }
    close(sockdesc);
    
    return 0;
}
