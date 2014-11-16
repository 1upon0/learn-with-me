#include<iostream>
#define r return
#define z int
z k,A[4];using namespace std;z f(z s,z p,z t){if(k==t){if(!s&&p==1)r 1;r 0;}for(z i=1;i<=s;i++){A[t]=i;if(!(p%i)&&f(s-i,p/i,t+1))r 1;}r 0;}main(){z s,p,N;cin>>N;while(N--){cin>>s>>p>>k;if(f(s,p,0))for(s=0;s<k;s++)cout<<A[s]<<" ";else cout<<"NO";cout<<"\n";}}