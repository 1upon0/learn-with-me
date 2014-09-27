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
#define INT_MAX 32767
int main()
{
	long N,i,k,l,m;
	intin(&N);
	while(N--){
		intin(&i);
		k=1;l=0;m=1;
		while(i>0){
			if(l==k){			
				if(k==1){
					m++;
					k=m+1;
				}
				k--;
				l=0;
			}
			l+=k;
			i-=k;
			//121321432154321
		}
		printf("%d\n",k);
	}
}
