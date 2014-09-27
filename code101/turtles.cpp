#include<iostream>
main(){long N,i,k,l,m;std::cin>>N;while(N--){std::cin>>i;l=0;m=k=1;while(i>0){if(l==k){if(k==1)k=++m+1;k--;l=0;}l+=k,i-=k;}std::cout<<k<<"\n";}}