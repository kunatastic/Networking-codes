#include <stdio.h>
#include <stdlib.h>

int main(){
	int data[10];
	printf("Enter the the hexadecimal value: ");
	for (int i=0;i<10;i++){
		scanf("%X",&data[i]);
	}
	int sum = 0;
	for(int i=0;i<10;i++){
		sum += data[i];
	}
	int add = sum/65536;
	sum = sum%65536;
	sum+=add;
	
	int comp = 65535 - sum;
	printf("The sum of the digits are: %04X\n",sum);
	comp = abs(comp);
	printf("The checksum value is: %04X\n",comp);
	if (comp == 0){
		printf("No Error Found!\n");
	}
	else{
		printf("Error Found!\n");
	}
	return 0;
}
