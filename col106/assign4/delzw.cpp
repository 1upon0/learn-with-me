#include<fstream>
#include<iostream>
#include<iomanip>
#include<vector>
typedef unsigned long ulong;
typedef unsigned char uchar;
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
  vector<uchar> s;
  ulong h;
  vector< vector<uchar> > strings;
  s.push_back(0);
  for(int i=0;i<256;i++){
    s[0]=i;
    strings.push_back(s);
  }
  ulong tmp;
  h=0;int first=1;
  s.clear();
  ulong b_read=0,kb_read=0;
  while(fi.read((char*)&h,3))
  {
   b_read+=3;
   //cout<<h<<"\t";
    if(b_read>=1024){
      kb_read+=1;b_read=0;
      if(kb_read%100){
        cout<<"                                             \r";        
        cout<<(kb_read/1024.f)<<std::setprecision(2)<<"mb \r";
      }
    }
    if(strings.size()>h){
      fo.write((char*)&(strings[h][0]),strings[h].size());
      
      s.push_back(strings[h][0]);
      if(s.size()>1)strings.push_back(s);
      
      s=strings[h];
    }else{
      s.push_back(s[0]);
      strings.push_back(s);
      fo.write((char*)&(strings[h][0]),strings[h].size());
      s=strings[h];
    }
  }
  return 0;
}