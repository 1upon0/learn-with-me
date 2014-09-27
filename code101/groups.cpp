#include <stdio.h>
#include<string.h>
inline long intin(long *a)
{
	char c = 0;
	while(c<33)
		c = getc(stdin);
	*a = 0;
	while(c>33)
	{
		*a = *a*10 + c - '0';
		c = getc(stdin);
	}
	return c;
}
void sort(long *a,int n){
	long t;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[i]>a[j]){
				t=a[i];a[i]=a[j];a[j]=t;
			}
}
void sort2(long *a,long *b,int n){
	long t;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[i]>a[j]){
				t=a[i];a[i]=a[j];a[j]=t;
				t=b[i];b[i]=b[j];b[j]=t;
			}
}
#define INT_MAX 32767
int main()
{
	long N,n,p[50],s[50],i;
	long long P,P1,nP;
	intin(&N);
	while(N--){
		intin(&n);
		for(i=0;i<n;i++)
			intin(p+i);
		for(i=0;i<n;i++)
			intin(s+i);
		sort2(s,p,n);
		nP=0;P=0;
		for(i=n-1;i>=0;i--){
			nP+=p[i];
			P1=s[i]*nP;
			if(P1>P)P=P1;
		}
		if(N==0)printf("%lld",P);
		else printf("%lld\n",P);
	}
}
