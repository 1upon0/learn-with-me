#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long ulong;
typedef unsigned short ushort;
#define MAX_CODE ((1<<24)-1)
class hashTable{
public:
  vector<string*> T;ulong occupied,error_state;
  hashTable(){occupied=0;error_state=0;}
  ~hashTable(){
    for(ulong i=0;i<T.size();i++)
      if(T[i])delete T[i];
  }
  static ulong hash(const string &s){
    ulong h=0;char c;ushort i=0;
    for(i=0;i<s.length();i++){
      h+=(h*67+(s[i]-'a'));
      h=h%MAX_CODE;
    }
    return h;
  }
  ulong insert(const string &s){
    error_state=0;
    ulong h=hash(s),i=1,h0;h0=h;
    while(T.size()<=h)//extend table to h
      T.push_back(0);
    while(T[h] && *T[h]!=""){
      h=(h0+i*i)%MAX_CODE;
      if(i>=MAX_CODE){
        error_state=1;
        cout<<"table full! "<<occupied<<endl;
        return 0;
      }
      i++;
      while(T.size()<=h)//extend table to h
        T.push_back(0);
    }
    T[h]=new string(s);
    occupied++;
    return h;  
  }
  int find(const string &s,ulong &H) const{
   ulong h=hash(s);
   ulong i=1,h0=h;
    if(T.size()<=h)
      return 0;
    while(T[h]){
      if(*T[h]==s){
        H=h;
        return 1;
      }
      h=(h0+i*i)%MAX_CODE;
      if(i==MAX_CODE)
        return 0;
      i++;
      if(T.size()<=h)
        return 0;
    }
    return 0;
  }
  int can_retrieve(ulong h){
    if(T.size()<=h)
      return 0;
    if(!T[h])
      return 0;
    return 1;
  }
  int erase(const string &s){
    error_state=0;
    ulong h;
    if(find(s,h))
    {
      *T[h]="";
      return 1;
    }
    return 0;
  }
  void print() const{
    cout<<"Total occupied:"<<occupied<<endl;
    for(ulong i=0;i<T.size();i++)
      if(T[i])cout<<i<<"\t"<<*T[i]<<endl;
    cout<<"End of dump\n";
  }
};