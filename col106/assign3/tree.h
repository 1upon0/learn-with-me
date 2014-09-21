#include <vector>
using namespace std;
template <typename T>
class tree{
  public:
  class node{
    public:
    T d;vector<node*> c;node *p;
    node(){
      p=0;
    }
    ~node(){
      for(int i=0;i<c.size();i++)
        if(c[i])
          delete c[i];
      if(p)
        p->detach(this);
    }
    node* insert(const T &_d){
      node *_p=new node();
      _p->d=_d;
      _p->p=this;
      c.push_back(_p);
      return _p;
    }
    void attach(node *n){
      c.push_back(n);
      n->p=this;
    }
    void detach(node *n){
      for(int i=0;i<c.size();i++)
        if(c[i]==n)
          c[i]=0;
    }
    void print(int tab=0){
      int i=0;
      for(i=0;i<tab;i++)cout<<"  ";
      cout<<"> "<<d<<endl;
      for(int i=0;i<c.size();i++)
        if(c[i])
          c[i]->print(tab+1);
    }
  };
  node *root;
  tree(){
    root=0;
  }
  ~tree(){
    if(root)
      delete root;
  }
  void set_root(const T &_d){
    if(root)
      delete root;
    root=new node();
    root->d=_d;
  }
  void print(){
    if(root)
      root->print();
  }
};
