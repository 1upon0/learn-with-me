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
int count(int a)
{
	int n=1;
	for(int i=2;i<a;i++)
		if(gcd(a,i)==1)n++;
	return n;
}
int sqrt(int n){
	int r=n-1;
	while(r<<2+n-r*r<4)
		r=(r+n/r)>>1;
	return r;
}
int isprime(long n){//checks if a number is prime
	if(n==1)//taking 1 as a prime
		return 1;
	long n_2=sqrt(n);
	for(int i=2;i<=n_2;i++)
	{
		if(n%i==0)
			return 0;
	}
	return 1;
}
void print_array(int *A,int m){
	if(!m){
		cout<<"Array empty\n";
		return;
	}
	cout<<A[0];
	int i=1;
	while(i<m)
		cout<<","<<A[i++];
	cout<<endl;
}
int primefac(int n,int *intArray){
	int j=0;
	for(int i=2;i<=n;i++)
	{
		if(j==10)
			break;
		if(n%i==0&&isprime(i)){
			intArray[j++]=i;
			n=n/i;
		}
	}
	return j;
}
int compare(int n,int f_n,int *intArray,int m){
	int a=1,b=1;
	int g_n;
	for(int i=0;i<m;i++)
		a*=intArray[i],b*=intArray[i]-1;
	g_n=(n/a)*b;
	cout<<"g("<<n<<")="<<g_n<<endl;
	if(g_n==f_n)
		return 1;
	return 0;
	
}
int main()
{
	char again='y';
	int n,f_n,intArray[10],m=0;
	while(again=='y'){
		cout<<"Enter the value of n:";
		cin>>n;
		f_n=count(n);
		cout<<"f("<<n<<")="<<f_n<<endl;
		m=primefac(n,intArray);
		cout<<"Prime factors of "<<n<<endl;
		print_array(intArray,m);
		cout<<"f(x)==g(x)?"<<compare(n,f_n,intArray,m);
		cout<<"\nRun again?[y]:";
		cin>>again;
	}
	return 0;
}

