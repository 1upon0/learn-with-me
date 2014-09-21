/*
 * @author Yash Gupta (cs5130302)
 * @desc lab5-Q1 categorizing numbers and listing factors
 */
#include <iostream>
#include <math.h>
using namespace std;
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
int print_array(int *A){
	int i=0;
	if(!A[0]){
		cout<<"Array empty\n";
		return 0;
	}
	cout<<A[0];
	i++;
	while(A[i])
		cout<<","<<A[i++];
	cout<<endl;
	return i;
}
int primefac(int n){
	//int sq=sqrt(n);
	int first=1;
	for(int i=2;i<=n;i++)
	{
		if(n%i==0&&isprime(i)){
			cout<<i<<" ";
			n=n/i;
		}
	}cout<<endl;
	return 0;
}
int main(){
	int A[11],B[11],C[11],t,i=0,j=0,k=0;
	while(i<11)
		A[i++]=(B[i]=C[i]=0);//initialize everything to 0
	i=0;t=1;
	while(t&&i<=10&&cin>>t)
		A[i++]=t;
	i=0;
	while(A[i]){
		if(isprime(A[i]))
			B[j++]=A[i];
		else
			C[k++]=A[i];
		i++;
	}
	cout<<"Input data:"<<endl;
	print_array(A);
	
	cout<<"B (Prime numbers):"<<endl;
	j=print_array(B);
	
	cout<<"C (Composite numbers):"<<endl;
	print_array(C);
	
	cout<<"number of primes:"<<j;
	
	cout<<endl<<"Prime factors:\n";
	i=0;
	while(C[i]){
		cout<<C[i]<<" = ";primefac(C[i]);
		i++;
	}
	return 0;
}
