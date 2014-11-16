#include<fstream>
#include<iomanip>
#include<string>
#include"hash.h"
using namespace std;
int main(int argc,char **argv){
  if(argc<3){
    cout<<"Usage:\nlzw <input file> <output file>";
    return 0;
  }
  cout<<"Input: "<<argv[1]<<endl;
  cout<<"Output: "<<argv[2]<<endl;
  fstream fi(argv[1],ios::binary|ios::in);
  fstream fo(argv[2],ios::binary|ios::out);
  uchar c;
  vector<uchar> s;
  hashTable T;ulong h;
  s.push_back(0);
  for(int i=0;i<256;i++){
    s[0]=i;
    T.insert(s);
  }
  h=0;s.clear();
  ulong b_read=0,kb_read=0;
  while(fi.read(&c,1)){
    b_read+=1;
    if(b_read==1024){
      kb_read+=1;b_read=0;
      if(kb_read%100){
        cout<<"                                             \r";
        cout<<(kb_read/1024.f)<<std::setprecision(2)<<"mb "<<(T.occupied*100.0/T.allocated)<<std::setprecision(2)<<"\r";
      }
    }
    s.push_back(c);
    if(!T.find(s,h)){
    //  cout<<h<<'\t';
      fo.write((char*)&h,3);
      T.insert(s);
      s.clear();
      s.push_back(c);
      
      T.find(s,h); 
    }
  }
  //cout<<h<<'\t';
  fo.write((char*)&h,3);
  cout<<"\nDone";
  //T.print();
  return 0;
}
