#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main() {

    int sockdesc = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket Number: %d\n",sockdesc);
    if (sockdesc < 0){
    	printf("Socket failed\n");
    	return -1;
    }
    printf("Server Socket is created.\n");
    
    
    struct sockaddr_in servaddr;
    struct sockaddr_in newAddr;
    memset(&servaddr, '\0', sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(4000); // range from 1024 to 49151
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
    printf("Listening...\n");
    
    socklen_t addr_size;
    char buffer[1024];

    while(1)
    {
		int newSocket = accept(sockdesc, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		
		pid_t childpid;		
		if((childpid = fork()) == 0){
			close(sockdesc);

			while(1){
				recv(newSocket, buffer, 1024, 0);
				if(strcmp(buffer, "quit") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else{
					printf("Client: %s\n", buffer);
					send(newSocket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
			}
		}
    }
    close(sockdesc);
    
    return 0;
}

