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
void asort2(long *a,long *b,int n){
	long t;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[i]<a[j]){
				t=a[i];a[i]=a[j];a[j]=t;
				t=b[i];b[i]=b[j];b[j]=t;
			}
}
void print_arr(long *a,int n){
	int i=0;
	while(n--){
		if(n!=0)
			printf("%d ",a[i]);
		else
			printf("%d\n",a[i]);
		i++;
	}
}
#define INT_MAX 32767
int main()
{
	long N,n,d[50],ds[50],dsp[50],nS,i,j,k,t;
	intin(&N);
	while(N--){
		intin(&n);
		for(i=0;i<n;i++){
			intin(d+i);
		//	ds[i]=d[i];dsp[i]=i;
		}
		intin(&nS);
		//asort2(ds,dsp,n);
		for(i=0;i<n;i++){
			k=i;
            for(j=i+1;j<n;j++){
				if(d[j]>d[k]&&nS>=j-i){
					k=j;
				}
			}
			nS-=k-i;
			t=d[k];
			for(j=k;j>i;j--){
				d[j]=d[j-1];
			}
			d[i]=t;
		}
		print_arr(d,n);
	}
}
