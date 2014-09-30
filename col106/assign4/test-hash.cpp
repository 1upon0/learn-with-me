#include<iostream>
#include"hash.h"
using namespace std;
int main()
{
  int in=1;ulong h;
  string s;
  hashTable T;
  while(in){
    cout<<"1-Insert 2-Find 3-Delete 4-Print 0-Exit\n";
    cin>>in;
    if(in==1)
    {
      cin>>s;
      cout<<"Inserted at "<<T.insert(s)<<endl;
    }else if(in==2){
      cin>>s;
      if(T.find(s,h))
        cout<<"Found at "<<h<<endl;
      else
        cout<<"Not found!\n";
    }else if(in==3){
      cin>>s;
      if(T.erase(s))
        cout<<"Deleted\n";
      else
        cout<<"Not found!\n";
    }else if(in==4){
      T.print();
    }
  }
  return 0;
}