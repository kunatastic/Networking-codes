#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

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
    
    int cnnt = connect(sockdesc, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (cnnt<0) {
    	printf("Connection failed\n");
    	return -1;
    }
    char buffer[100];
    printf("Enter the query: ");
    scanf("%s",&buffer);
    write(sockdesc, buffer, 100);
    
    char buffer1[100];
    read(sockdesc, buffer1, 100);
    printf("Message recieved from server: %s\n",buffer1); 
      
    close(sockdesc);
    return 0;
}
