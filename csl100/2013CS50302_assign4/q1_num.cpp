/*
 * @author Yash Gupta (cs5130302)
 * @desc lab4-Q2 determining type of number
 */

#include <iostream>
using namespace std;
int isprime(long n){//checks if a number is prime
	if(n==1)
		return 0;
	for(int i=2;i<=n/2;i++)
	{
		if(n%i==0)
			return 0;
	}
	return 1;
}
int main()
{
	long n;
	cout<<"Enter the number:";
	cin>>n;
	cout<<n<<" is ";
	if(n%2==0){//if n is divisible by 2
		cout<<"even";
		if(n==2)//2 is the only prime and even!
			cout<<" and prime";
	}else{
		cout<<"odd";
		if(isprime(n)){
			cout<<" and prime";
		}
	}
	cout<<endl;
	return 0;
}
