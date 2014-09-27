#include <iostream>
#include <string>
#include "avltree.h"
#include "tree.h"
#include <queue>
using namespace std;
typedef unsigned int uint;
typedef unsigned long ulong;
class emp{
  string n;int l;
  ulong h;
public:
  emp(){
    l=1;h=hash("");
  }
  int lvl()
  {
    return l;
  }
  void set(const string &_n="",int _l=1){
    n=_n;
    l=_l;
    h=hash(n);
  }
  void dump(){
    cout<<n<<", "<<l<<", "<<h<<endl;
  }
  static ulong hash(const string &s){
    //uint h=level&0xffff;
    ulong l=0;char c;
    for(int i=0;i<s.length();i++){
      c=s[i];
      if(c>'a')
        c='a'+26;
      l|=((c-'a')%29)<<(i*5)%32;
    }
    return l;
    //return (ulong(h)<<16)|(l&0xffff);
  }
  bool operator > (const emp &b)const{
    return n>b.n;
  }
  bool operator < (const emp &b)const{
    return n<b.n;
  }
  bool operator == (const emp &b)const{
    return n==b.n;
  }
  operator const char*() const{
    return &(n[0]);
  }
};
struct emp_node{
  tree<emp>::node *n;
  bool operator > (const emp_node &b)const{
    return n->d>b.n->d;
  }
  bool operator < (const emp_node &b)const{
    return n->d<b.n->d;
  }
  bool operator == (const emp_node &b)const{
    return n->d==b.n->d;
  }
  operator const char*(){
    return n->d;
  }
};
int main(){
  avltree<emp_node> en_bt;
  avltree<emp_node>::node *en_btn=0,*en_btn1=0;
  tree<emp> e_t;
  tree<emp>::node *e_tn=0,*e_tn1=0,*e_tn2=0;
	string s,t;int c=1;
	emp e;emp_node en;
  e_tn=new tree<emp>::node();
  cout<<"Enter CEO name:\n";
  cin>>s;
  e.set(s,1);
  e_t.set_root(e);
  en.n=e_t.root;
  en_bt.insert(en);
    cout<<"\nEnter:\n1 to add an employee\n2 to delete\n3 to find lowest common boss\n4 to print the employees according to level\n5 to print the tree structure\n6 to print avltree\n0 to exit\n\n";

  while(c!=0){
    cout<<"\nEnter your choice:\n";
    cin>>c;
    if(c==1){
      cout<<"Enter name of new employee:\n";cin>> s;
      cout<<"Enter name of "<<s<<"'s boss:\n";cin>> t;
      e.set(t);

      e_tn->d=e;
      en.n=e_tn;
      en_btn=en_bt.find(en);
      if(en_btn){
        e.set(s,en_btn->d.n->d.lvl()+1);
        en.n=en_btn->d.n->insert(e);
        en_bt.insert(en);
        cout<<"Successfully Inserted!\n";
      }else
        cout<<"Boss "<<t<<" not found!\n";
    }else if(c==2){
      cout<<"Enter name of employee to be removed:\n";cin>> t;
      cout<<"Enter name of replacement boss for "<<t<<"'s subordinates:\n";cin>> s;
      e.set(t);
      e_tn->d=e;
      en.n=e_tn;
      en_btn=en_bt.find(en);
      if(!en_btn){
        cout<<t<<" was not found!\n";
        continue;
      }
      if(!en_btn->d.n->p){
        cout<<"Can't remove CEO!\n";
        continue;
      }
      e_tn1=en_btn->d.n; //the fired employee and his tree

      e.set(s);
      e_tn->d=e;
      en.n=e_tn;
      en_btn1=en_bt.find(en);
      if(!en_btn1){
        cout<<"Replacement "<<s<<" was not found!\n";
        continue;
      }
      if(en_btn1==en_btn){
        cout<<"Replacement and fired emplyee cant be same!\n";
        continue;
      }
      e_tn2=en_btn1->d.n; //the replacement
      if(e_tn2->d.lvl()!=e_tn1->d.lvl())
      {
        cout<<"Replacement and fired emplyee should be of same level!\n";
        continue;
      }
      e_tn1->p->detach(e_tn1);
      en_bt.remove(en_btn);
      cout<<"Successfully Removed "<<t<<"!\n";

      for(int i=0;i<e_tn1->c.size();i++)
        e_tn2->attach(e_tn1->c[i]);
      e_tn1->c.clear();
      delete e_tn1;

      cout<<"Successfully transferred employees to "<<s<<"!\n";
    }else if(c==3){
      cout<<"Enter name of employee A:\n";cin>> t;
      cout<<"Enter name of employee B:\n";cin>> s;
      e.set(t);
      e_tn->d=e;
      en.n=e_tn;
      en_btn=en_bt.find(en);
      if(!en_btn){
        cout<<t<<" was not found!\n";
        continue;
      }
      e_tn1=en_btn->d.n->p;

      e.set(s);
      e_tn->d=e;
      en.n=e_tn;
      en_btn=en_bt.find(en);
      if(!en_btn){
        cout<<t<<" was not found!\n";
        continue;
      }
      e_tn2=en_btn->d.n->p;
      tree<emp>::node *n1;
      while(e_tn1){
        n1=e_tn2;
        while(n1){
          if(n1==e_tn1)
            break;
          n1=n1->p;
        }
        if(n1==e_tn1)
            break;
        e_tn1=e_tn1->p;
      }
      if(e_tn1){
        cout<<"Lowest common boss of A & B is "<<e_tn1->d<<"\n";
      }else
        cout<<"There is no Lowest common boss for A & B\n";
    }else if(c==4){
      queue<tree<emp>::node*> q;
      q.push(e_t.root);int pl=0;
      while(!q.empty()){
        e_tn1=q.front();
        q.pop();
        if(e_tn1){
          for(int i=0;i<e_tn1->c.size();i++)
            q.push(e_tn1->c[i]);
          if(pl!=e_tn1->d.lvl())
            cout<<"\nLevel "<<e_tn1->d.lvl()<<":\n";
          else cout<<", ";
          pl=e_tn1->d.lvl();
          cout<<e_tn1->d;
        }
      }cout<<endl;
    }else if(c==5){
      e_t.print();
    }else if(c==6){
      en_bt.print();
    }
	}
  cout<<"You chose to exit.\n";
  return 0;
}
