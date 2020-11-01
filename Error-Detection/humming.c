#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//considering Even Bit Parity;
int main(){
	int n;
	printf("Enter the total number of bits: ");
	scanf("%d",&n);
	
	int r = ceil(log2(n+1));
	printf("The redundent bits are: %d\n\nEnter the humming code here: ",r);
	
	int data[n];
	for (int i=n;i>0;i--){
		scanf("%d",&data[i]);
	}
	
	int redunt[r], count = r;
	
	int lmt = 0;
  	for (int i=1;i<=n;i=pow(2, lmt))
    {
    		lmt++;
      	int parity = 0;
      	int j = i, k = i;
      	int min = 1, max = i;
      	for (j;j<=n;)
	 	{
	   		for (k = j; max >= min && k <= n; min++, k++)
		 	{
		   		if (data[k] == 1)
	  				parity++;
		 	}
	   		j = k + i;
	   		min = 1;
	   	}
	   	if (parity % 2 == 0) // Even Parity
		{
			redunt[count] = 0;
			count--;
		}
		else
	 	{
	   		redunt[count] = 1;
	   		count--;
	 	}
    }
    printf("The redundant bits are: ");
    int sum = 0;
    for (int i=1;i<=r;i++){
    	printf("%d ",redunt[i]);
    	sum+=redunt[i];
    }
    printf("\n");
    
    if (sum == 0){
    	printf("No Error Found!\n");
    }
    else{
    	printf("Error Found!\n");
    }
	
	return 0;
}
