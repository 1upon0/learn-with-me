#include<iostream>
using namespace std;main(){int n,k,N,s,l;cin>>N;while(N--){cin>>k>>n;
  for(int i=s=0;i<n;i++){
    l=__builtin_popcount(i^(i+1));
    cout<<l<<endl;
    s+=l;
  }

  cout<<s<<endl;}}