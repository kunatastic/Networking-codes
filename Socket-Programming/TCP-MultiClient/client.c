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
    printf("Client Socket is created.\n");
    
    struct sockaddr_in servaddr;
    memset(&servaddr, '\0', sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(4000); // range from 1024 to 49151
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);//any available ip
    
    
    
    int ret = connect(sockdesc, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(ret < 0){
		printf("Error in connection.\n");
		exit(1);
    }
	printf("Connected to Server.\n");
    

    char buffer[1024];
    while (1)
    {
    	printf("Client: \t");
		scanf("%s", &buffer);
		send(sockdesc, buffer, strlen(buffer), 0);
    	
    	if(strcmp(buffer, "quit") == 0){
			close(sockdesc);
			printf("Disconnected from server.\n");
			exit(1);
		}

		if(recv(sockdesc, buffer, 1024, 0) < 0){
			printf("Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", buffer);
		}
    	
    }
    return 0;
}
