#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int Palindrome(char str[]) 
{ 

    int l = 0; 
    int h = strlen(str) - 1; 
  
    while (h > l) 
    { 
        if (str[l++] != str[h--]) 
        { 
            return 0; 
        } 
    } 
    return 1; 
} 

int EvenParity(char str[])
{
	int c = 0,count = 0;
	
	while(str[c]!= '\0')
	{
		if (str[c]=='1')	count++;
		if (str[c] != '1' && str[c] != '0') return 2;
		c++;
	}
	if (count%2==0)	return 0;
	else	return 1;
}

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
    // user timeout in milliseconds [ms]
	struct timeval timeout;      
    timeout.tv_sec = 10*60*1000;
    timeout.tv_usec = 0;

    while(setsockopt (sockdesc, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) >= 0)
    {
		//17.08.2020
		struct sockaddr_in cliaddr;
		int len = sizeof(cliaddr);
		int connfd = accept(sockdesc, (struct sockaddr *) &cliaddr, &len);
		if (connfd < 0){
			printf("Accept failed\n");
			return -1;
		}
			
		char buffer[100];	
		//strcpy(buffer,"");	
		read(connfd, buffer, 100);
		printf("Messge recieved from client: %s\n",buffer);
		
		
		
		//process
		int size = strlen(buffer);
		printf("The size is the query is: %d\n",size);
		
		char option[100];
		int j;
		for(j=0;j<4;j++){
			option[j] = buffer[j]; 
		}
		option[j] = '\0';
		printf("The option of the query is: %s\n\n",option);
		
		char value[100];
		int c = 0;
		while(c<size){
			value[c] = buffer[4+c];
			c++;
		}
		value[c] = '\0';
		
		//Palindrome
		if (strcmp(option,"PALI") == 0) {
			if (Palindrome(value)==1){
				write(connfd, "Palindrome", sizeof("Palindrome"));
			}
			else{
				write(connfd, "Not palindrome", sizeof("Not palindrome"));
			}
		}
		
		//even or odd
		else if (strcmp(option,"EVOD")==0) 
		{
			int num = atoi(value);
			if ((num%2)==0){
				write(connfd, "Even Number", sizeof("Even Number"));
			}
			else{
				write(connfd, "Odd Number", sizeof("Odd Number"));
			}
			
		}
		
		//even parity bit
		else if (strcmp(option,"EPRT")==0) {
			
			if (EvenParity(value)==1){
				write(connfd, "1", sizeof("1"));
			}
			else if (EvenParity(value)==0){
				write(connfd, "0", sizeof("0"));
			}
			else if (EvenParity(value)==2){
				write(connfd, "Input should be binary number", sizeof("Input should be binary number"));
			}
		}
		
		//others
		else{
			write(connfd, "Invalid Option", sizeof("Invalid Option"));
		}
		write(connfd, buffer, 100);
    }
    close(sockdesc);
    
    return 0;
}
