#include<fstream>
#include<string>
#include"hash.h"
using namespace std;
int main(int argc,char **argv){
  fstream fi("input.lzw",ios::binary|ios::in);
  fstream fo("output.txt",ios::binary|ios::out);
  char c,C[2]="a";string s="";
  hashTable T;ulong h;
  for(int i=0;i<256;i++){
    C[0]=i;
    T.insert(C);
  }
  ulong tmp;
  h=0;int first=1;
  while(fi.read((char*)&h,3))
  {
   // cout<<h<<endl;
    if(T.can_retrieve(h)){
      fo<<*T.T[h];
      if(!first){
        s.push_back((*T.T[h])[0]);
        if(!T.find(s,tmp))
        {  
          T.insert(s);
        }
      }
      s=*T.T[h];
    }else{
      s.push_back(s[0]);
      T.insert(s);
      fo<<*T.T[h];
      s=*T.T[h];
    }
    first=0;
  }
  return 0;
}