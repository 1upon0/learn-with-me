#include<fstream>
#include<string>
#include"hash.h"
using namespace std;
int main(int argc,char **argv){
  fstream fi("input.txt",ios::binary|ios::in);
  fstream fo("input.lzw",ios::binary|ios::out);
  char c,C[2]="a";string s="";
  hashTable T;ulong h;
 for(int i=0;i<256;i++){
    C[0]=i;
    T.insert(C);
  } h=0;
  string t,ss;
  while(fi.read(&c,1)){
    s.push_back(c);
    if(!T.find(s,h)){
      fo.write((char*)&h,3);
      //cout<<t<<"="<<h<<endl;
      T.insert(s);
      s="";s.push_back(c);
      T.find(s,h);
      t=s;
    }else{
      t=s;
    }
  }
  fo.write((char*)&h,4);
  //cout<<t<<"="<<h<<endl;
  return 0;
}