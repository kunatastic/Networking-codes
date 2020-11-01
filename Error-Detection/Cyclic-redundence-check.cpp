//Implement the appropriate error detection  mechanism to compute the codeword at the sender  side for the given data word, 101001111 using the  polynomial generator, x4+x2+x+1.

#include<iostream>
using namespace std;

void division(int temp[],int gen[],int n,int r){ 
	for(int i=0;i<n;i++){
		if (gen[0]==temp[i]){
        	for(int j=0,k=i;j<r+1;j++,k++)
             	if(!(temp[k]^gen[j]))
                 	temp[k]=0;
             	else
                 	temp[k]=1;
     	}
	}
}

int main(){
	int n,r,temp[50];
 	cout<<"Enter the message : ";
	string m,g;
 	cin>>m;
 	cout<<"Enter the generator : ";
 	cin>>g;
	n = m.length();
	r = g.length();

	int message[50],gen[50];
	for(int i=0;i<n;i++){
		message[i] = m[i] - 48;
	}
	for(int i=0;i<r;i++){
		gen[i] = g[i] - 48;	
	}

 	r--;
 	for(int i=0;i<r;i++)
    	message[n+i] = 0;
 	for(int i=0;i<n+r;i++)
	    temp[i] = message[i];

 	division(temp,gen,n,r);

	cout<<endl;
 	cout<<"remainder : ";
 	for(int i=0;i<r;i++){
		cout<<temp[n+i];
    	message[n+i] = temp[n+i];
 	}
 	
 	cout<<endl<<"Message after adding remainder: ";
 	for(int i=0;i<n+r;i++)
 		cout<<message[i];
	cout<<endl;
 	return 0;
}
