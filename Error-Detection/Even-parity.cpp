// Problem Statement: Implement a C program to generate the  code word for the data block ‘10101’

#include <iostream>
using namespace std;

int main(){
	cout<<"Implementing one bit even parity"<<endl;
	cout<<"Enter a binary number: ";
	string input;
	cin>>input;
	int countOf1 = 0, n = input.length();
	for (int i = 0; i < n; i++)
	{
		if (input[i]=='1')	countOf1++;	
	}
	if (countOf1%2==0)	input+='0';
	else 	input+='1';
	cout<<"The output binary number: "<<input<<endl;
	return 0;
}
