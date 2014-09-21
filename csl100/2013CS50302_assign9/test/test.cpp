#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;
long microtime()
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL) != 0)
			return 0;
	return (tv.tv_sec * 1000000) + tv.tv_usec;
}
int randnum(int a,int b){
	return rand()%(b-a+1)+a;
}
void write(int w,int h,int size,int *terrain,int N){
	ofstream f("input.txt");
	f<<">WINDOW\n"<<w<<" "<<h<<endl;
	f<<">BALL\n"<<size<<" "<<110<<endl;
	f<<">TERRAIN\n";
	for(int i=0;i<N;i++)
		f<<terrain[2*i]<<" "<<terrain[2*i+1]<<endl;
	f<<">TREES\n";
}
int main(){
	int h,w,size;
	srand(microtime());
	h=randnum(400,600);
	w=randnum(600,800);
	int N=w*randnum(3,6)/100.0;
	size=w*randnum(80,160)/100/N;
	int *terrain;
	terrain=new int[2*N];	
	int passes=20;float a=1,f=1,A=h/2;
	for(int j=0;j<passes;j++)
	{
		f=randnum(51,500)/50.0;//total oscillations

		a=A*(randnum(50,85)/100.0)/f;
		A-=a;
		for(int i=0;i<N;i++){
			if(j==0){
				if(i==0)
					terrain[2*i]=0;
				else if(i==N-1)
					terrain[2*i]=w;
				else
					terrain[2*i]=(i+randnum(-5,5)/20.0)*w/N;
				terrain[2*i+1]=h/2;
			}
			terrain[2*i+1]+=a*sin(f*i*2*M_PI/N);
		}
	}
	write(w,h,size,terrain,N);
	return 0;
}
