#include<fstream>
#include<iomanip>
#include"hash.h"
using namespace std;
int main(int argc,char **argv){
  if(argc<3){
    cout<<"Usage:\ndelzw <input file> <output file>";
    return 0;
  }

  cout<<"Input: "<<argv[1]<<endl;
  cout<<"Output: "<<argv[2]<<endl;
  fstream fi(argv[1],ios::binary|ios::in);
  fstream fo(argv[2],ios::binary|ios::out);
  char c;vector<uchar> s;
  hashTable T;ulong h;
  s.push_back('a');
  for(int i=0;i<256;i++){
    s[0]=i;
    T.insert(s);
  }
  ulong tmp;
  h=0;int first=1;
  s.clear();
  ulong b_read=0,kb_read=0;
  while(fi.read((char*)&h,3))
  {
   b_read+=3;
    if(b_read>=1024){
      kb_read+=1;b_read=0;
      if(kb_read%100){
        cout<<"                                             \r";        
        cout<<(kb_read/1024.f)<<std::setprecision(2)<<"mb "<<(T.occupied*100.0/MAX_CODE)<<std::setprecision(2)<<"\r";
      }
    }
    if(T.can_retrieve(h)){
      fo.write((char*)&(T.T[h]->at(0)),T.T[h]->size());
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
      fo.write((char*)&(T.T[h]->at(0)),T.T[h]->size());
      s=*T.T[h];
    }
    first=0;
  }
  return 0;
}