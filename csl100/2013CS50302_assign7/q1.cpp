#include <iostream>
#define mod(a) ((a)>0?(a):-(a))
using namespace std;
int gcd(int a,int b)
{
	a=mod(a);
	b=mod(b);
	if(a==0)
		return b;
	if(b==0)
		return a;
	if(a>b)	
		return gcd(a%b,b);
	else if(a<b)
		return gcd(a,b%a);
	return a;
}
int main()
{
	char again='y';
	int a,b;
	while(again=='y'){
		cout<<"Enter the value of a:";
		cin>>a;
		cout<<"Enter the value of b:";
		cin>>b;
		cout<<"Gcd of a,b is :"<<gcd(a,b);
		cout<<"\nRun again?[y]:";
		cin>>again;
	}
	return 0;
}

