#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;
typedef unsigned long ulong;
float graph[100][100];
string planets[100];
float X[100];
float Y[100];
float Z[100];
float dp[0xfffffful][20]={0};
void cost(int i,ulong s){
  if(__builtin_popcount(s)==2)
  {
    dp[i][s]=graph[0][i];
    return;
  }
  float min=0xffff,tmp;
  for(int j=1;j<=N;j++)
  {  
    if(j==i)
      continue;
    if(!dp[s-1<<i][j])
      cost(j,s-1<<i);
    dp[s-1<<i][j];
    if(min>tmp){

    }
  }

}

int main(){
  int N,i,j;
  string tmp;
  cin>>N;
  planets[0]="Earth";
  graph[0][0]=X[0]=Y[0]=Z[0]=0;
  for(i=1;i<=N;i++){
    getline(cin,planets[i],',');
    getline(cin,tmp,',');
    sscanf(&tmp[0],"%f",X+i);
    getline(cin,tmp,',');
    sscanf(&tmp[0],"%f",Y+i);
    getline(cin,tmp);
    sscanf(&tmp[0],"%f",Z+i);
    graph[i][i]=0;
   // cout<<planets[i]<<" "<<X[i]<<" "<<Y[i]<<" "<<Z[i]<<endl;
  }
  for(i=0;i<=N-1;i++){
    for(j=i+1;j<=N;j++){
      graph[i][j]=graph[j][i]=sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j])+(Z[i]-Z[j])*(Z[i]-Z[j]));
    }
  }
  float c=cost(0,ulong(1<<(N+2))-1);
}