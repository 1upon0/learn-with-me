/*
 * @author Yash Gupta (cs5130302)
 * @desc lab5-Q2 converting number among different base systems
 */

#include <iostream>
using namespace std;
int tobin(int n,int *a,int N=10){
	for(int i=0;i<N;i++)//compiler handles the -ve inegers, as the bit value is directly taken from memory.
		a[i]=(n&(1<<i))>>i;
	return 1;
}
int todec(int *a,int N=10){
	int d=0;
	for(int i=0;i<N;i++)
		d+=a[i]<<i;
	if(a[N-1]==1)//if the MSB is 1, the number is -ve. Subtract 2^N to get the correct -ve value
	    d-=1<<N;
	return d;
}
void topositive(int *a,int n=10){//this function calculates the inverse 2's complement
	int t=0;
	for(int i=0;i<n;i++){
		t=a[i]+1+t;
		a[i]=!(t%2);
		t=t>>1;
	}
}
int printoct(int *a,int N=10){
	int n=N-N%3;//find the largest sub-array with length 3 bits.
	if(a[N-1]==1){
	    topositive(a,N);
	    cout<<'-';
	}
	if(N%3==1)
		cout<<a[n];
	if(N%3==2)
		cout<<a[n]+a[n+1]*2;
	for(int i=n-1;i>=0;i-=3)
		cout<<a[i]*4+a[i-1]*2+a[i-2];
	cout<<endl;
}
void addbin(int *a,int *b,int *c,int n=10){
	int t=0;
	for(int i=0;i<n;i++){
		t=a[i]+b[i]+t;
		c[i]=t%2;
		t=t>>1;
	}
}
void printnum(int *a,int n=10){
	for(int i=n-1;i>=0;i--)
		cout<<a[i];
	cout<<endl;
}
int main()
{
	int a,b,A[10],B[10],C[10],C1[10];
	char again='y';
	while(again=='y'){
		cout<<"Enter a:";
		cin>>a;
		if(a>=512)
		    cout<<"a&b should be < 512. Clamping to 511\n",a=511;
  		if(a<=-512)
		    cout<<"a&b should be > -512. Clamping to -511\n",a=-511;

		cout<<"Enter b:";
		cin>>b;
		if(b>=512)
		    cout<<"a&b should be < 512. Clamping to 511\n",b=511;
		if(b<=-512)
		    cout<<"a&b should be > -512. Clamping to -511\n",b=-511;
		    
		tobin(a,A,10);
		tobin(b,B,10);
		tobin(a+b,C1,10);
		addbin(A,B,C,10);
		cout<<"A           = ";printnum(A);
		cout<<"B           = ";printnum(B);
		cout<<"A+B (bin)   = ";printnum(C);
		cout<<"A+B (dec)   = "<<todec(C)<<endl;
		cout<<"a+b (auto)  = "<<a+b<<endl;
		cout<<"a   (octal) = ";printoct(A,10);
		cout<<"b   (octal) = ";printoct(B,10);
		cout<<"a+b (octal) = ";printoct(C,10);
		cout<<"\nRun again?[y]:";
		cin>>again;
	}
	return 0;
}
