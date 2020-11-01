// Problem Statement: Assume Sender A is transmitting a packet made  of three 8-bit data (A7)16, (CA)16, (90)16 to  Receiver B. Apply the appropriate error detection  mechanism that involves binary addition to  compute the code word at the sender end.

#include <bits/stdc++.h>
using namespace std;

int add(int a, int b)
{	
	int target = 0,sum = 0,carry = 0;
	for (int i = 0; i < 8; i++)
	{
		int A = a%10;
		a/=10;
		int B = b%10;
		b/=10;
		
		sum = A^B^carry;
		carry = (B|carry)&(A|carry)&(A|B);
		target = target + pow(10,i)*sum;
	}
	if (carry == 1)	return add(carry,target);		
	else return target;
}

int complement(int a)
{
	int temp = 11111111;
	return temp-a;
}
int main()
{	
	cout<<"Implemenation of the checksum.\nEnter the number of data packets: ";
	int n;
	cin>>n;
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		cout<<"Enter the "<<i<<"th 8-bits binary number: ";
		int temp;
		cin>>temp;
		result = add(result,temp);	
	}
	cout<<endl;

	cout<<"The sum of the data is "<<setfill('0')<<setw(8)<<result<<endl;
	cout<<"The checksum value is "<<setfill('0')<<setw(8)<<complement(result)<<endl;
	cout<<endl;
	
	cout<<"The sum of the data recieved by the reciever is "<<setfill('0')<<setw(8)<<result<<endl;
	int reciever = result + complement(result);
	cout<<endl;

	cout<<"The checksum value + sum of data is "<<setfill('0')<<setw(8)<<reciever<<endl;
	cout<<"Conclusion value is "<<setfill('0')<<setw(8)<<complement(reciever)<<endl;
	cout<<endl;

	if (complement(reciever) == 0)	cout << "Accepted Data"<<endl;
	else	cout<<"Rejected Data"<<endl;
	
	return 0;
}
