#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

int main(){

	int ipaddress[4];
	printf("Enter the IP address with suffix length: ");
	for (int i=0;i<4;i++){
		char temp;
		scanf("%d%c",&ipaddress[i],&temp);
	}
	int prelen;
	scanf("%d",&prelen);
	
	
	int n;
	printf("Enter the number of subnets: ");
	scanf("%d",&n);
	int arr[n];
	printf("Enter the number of host in each subnets: \n");
	for (int i=0;i<n;i++){
		printf("Network %c: ",'A'+i);
		scanf("%d",&arr[i]);
	}
	qsort(arr, n, sizeof(int), cmpfunc);
	//to sort if the network is not sorted. So that maximum lengthed
	//network is accomadated first.
	
	// main function
	int safe = prelen/8;
	for (int i=safe;i<4;i++){
		ipaddress[i] = 0;
	}
	printf("\n\nThe IP address with suffix length of each subnet: \n");
	int count = 7;
	for (int i=n-1;i>=0;i--)
	{
		printf("Network %c: ",'A'+(n-i-1));
		for (int j=0;j<safe;j++){
			printf("%d.",ipaddress[j]);
		}
		printf("%d",ipaddress[safe]);
		prelen++;
		ipaddress[safe] += pow(2,count);
		count--;
		for (int j = safe+1;j<4;j++){
			printf(".%d",ipaddress[j]);
		}
		printf("/%d\n",prelen);
	}
	printf("\n");
	return 0;
}
