#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef char uchar;
#define MAX_HASH ((ulong)0xFFFFFFFB)
#define RESERVED_HASH ((ulong)0xFFFFFFFB)
class hashTable{
public:
  vector<vector<uchar>*> strings;
  vector<ulong> lookup;ulong occupied,error_state,allocated;
  hashTable(){occupied=0;
    allocated=257;
    lookup.resize(allocated,RESERVED_HASH);
    error_state=0;}
  ~hashTable(){
    for(ulong i=0;i<strings.size();i++)
      if(strings[i])delete strings[i];
  }
  ulong hash(const vector<uchar> &s)const{
    ulong h=0;ushort i=0;
    for(i=0;i<s.size();i++){
      h=(h*251+s[i])%allocated;
    }
    h=h%allocated;
    return h;
  }
  bool resize(){
    if(allocated==MAX_HASH){
      throw "Hash table can't store more values";
      return false;
    }
    if(allocated>=(MAX_HASH-1)/2)
      allocated=MAX_HASH;
    else
      allocated=allocated*2+1;
    lookup.clear();
    lookup.resize(allocated,RESERVED_HASH);
    occupied=0;
    for(ulong i=0;i<strings.size();i++){
      insert(*strings[i],true);
    }
    return true;
  }
  ulong insert(const vector<uchar> &s,bool rehashing=false){
    if(occupied>allocated*0.7){
      cout<<"Trying to resize\n";
      if(!resize())
        return RESERVED_HASH;
    }
    ulong h=hash(s),i=1,h0;h0=h;
    //cout<<occupied<<"\t";
    while(lookup.size()<=h)//extend table to h
      lookup.push_back(RESERVED_HASH);
    while(lookup[h]!=RESERVED_HASH){
      h=(h0+i*i)%allocated;
      if(i==allocated/2){
        cout<<"Probing failed...resizing"<<endl;
        if(resize())
          return insert(s);
        return RESERVED_HASH;
      }
      i++;
      while(lookup.size()<=h)//extend table to h
        lookup.push_back(RESERVED_HASH);
    }
    if(!rehashing){
      strings.push_back(new vector<uchar>(s));
    }
    lookup[h]=occupied;
    //cout<<&(s[0])<<"="<<h<<"\n";
    return occupied++;  
  }
  int equal(const vector<uchar> &a,const vector<uchar> &b)const{
    int s=a.size();
    if(s!=b.size())
      return 0;
    for(ushort i=0;i<s;i++)
      if(a[i]!=b[i])
        return 0;
    return 1;
  }
  int find(const vector<uchar> &s,ulong &index) const{
   ulong h=hash(s);
   ulong i=1,h0=h;
    if(lookup.size()<=h)
      return 0;
    while(lookup[h]!=RESERVED_HASH){
      if(equal(*strings[lookup[h]],s)){
        index=lookup[h];
        return 1;
      }
      h=(h0+i*i)%allocated;
      if(i==allocated/2)
        return 0;
      i++;
      if(lookup.size()<=h)
        return 0;
    }
    return 0;
  }
  void print() const{
    cout<<"Total occupied:"<<(occupied/allocated*100.f)<<"% of "<<allocated<<endl;
    for(ulong i=0;i<strings.size();i++)
      {
        cout<<i<<"\t";
        for(int j=0;j<strings[i]->size();j++)
          cout<<(int)(strings[i]->at(j))<<" ";
        cout<<endl;
      }
    cout<<"End of dump\n";
  }
};