#include <iostream>
using namespace std;
template<typename T>
class avltree{
public:
  class node{
  public:
    T d;int h;
    node *p,*l,*r;
    node(){
      p=l=r=0;h=1;
    }
    int dh(){
      int dh=0;
      if(r&&l)
        dh=r->h - l->h;
      else if(r)
        dh=r->h;
      else if(l)
        dh=- l->h;
      else
        dh=0;
      return dh;
    }
    node* insert(const T &_d){
      if(_d>d)
      {
        if(r)
          return r->insert(_d);
        r=new node();
        r->d=_d;
        r->p=this;
        return r;
      }
      if(l)
        return l->insert(_d);
      l=new node();
      l->d=_d;
      l->p=this;
      return l;
    }
    node* find(const T &_d){
      if(_d==d)
        return this;
      if(_d>d)
        if(r)
          return r->find(_d);
      if(l)
        return l->find(_d);
      return 0;
    }
    void print(int tab=0){
      int i=0;
      for(i=0;i<tab;i++)cout<<"  ";
      cout<<"> "<<d;
      if(1){
        cout<<" ("<<h<<") ";
        if(p)
         cout<<p->d;
        else cout<<"-";
      }
      cout<<endl;
      if(l)
        l->print(tab+1);
      else{
        for(i=0;i<tab;i++)cout<<"  ";
        cout<<"  -\n";
      }
      if(r)
        r->print(tab+1);
      else{
        for(i=0;i<tab;i++)cout<<"  ";
        cout<<"  -\n";
      }
    }
  };

  node *root;
  avltree(){
    root=0;
  }
   node* insert(const T &d){
    if(!root)
    {
      root=new node();
      root->d=d;
      return 0;
    }else{
      node *n=root->insert(d);
      update_heights(n);
      balance_insert(n);
      return n;
    }
  }
  void remove(node *n){
    if(!root)
      return;
    node *p=do_remove(n);
    if(p){
      p->h=p->dh();
      if(p->h<0)p->h=-p->h;
      p->h++;
      update_heights(p);
      balance_remove(p);
    }
    else root=0;
  }
  node* find(const T &d){
    if(!root)
      return 0;
    return root->find(d);
  }
  void print(){
    if(root)
      root->print();
    else
      cout<<"Tree is empty!\n";
  }
private:
  void update_heights(node *n,node *t=0){
    int h;
    while((n=n->p)!=t){
      if(n->l&&n->r)
        h=(n->r->h > n->l->h)?n->r->h:n->l->h;
      else if(n->l)
        h=n->l->h;
      else
        h=n->r->h;
      n->h=1+h;
    }
  }
  void rotate_l(node *p){
    node *t,*n=p->r;
    p->r=n->l;
    if(n->l)
      n->l->p=p;
    n->l=p;
    t=p->p;
    p->p=n;
    n->p=t;
    if(t){
      if(t->r==p)
       t->r=n;
      else
       t->l=n;
    }
    p->h-=2;
     if(p==root)
      root=n;
  }
  void rotate_r(node *p){
    node *t,*n=p->l;
    p->l=n->r;
    if(n->r)
      n->r->p=p;
    n->r=p;
    t=p->p;
    p->p=n;
    n->p=t;
    if(t){
      if(t->r==p)
       t->r=n;
      else
       t->l=n;
    }
    p->h-=2;
    if(p==root)
      root=n;
  }
  bool balance_node(node *n){//balances a node when both its children are balanced
    int dh=n->dh();
    if(dh==2){//r-imbalance!
      if(n->r->dh()>=0){//r-r imb
        rotate_l(n);
      }
      else{//r-l imb
        //as n is not originally imbalanced, but we rotate it!
        n->r->h+=1;
        n->r->l->h+=1;
        rotate_r(n->r);
        rotate_l(n);
      }
      return true;
    }if(dh==-2){//l-imbalance!
      if(n->l->dh()<=0)//l-l imb
        rotate_r(n);
      else{//l-r imb
        n->l->h+=1;
        n->l->r->h+=1;
        rotate_l(n->l);
        rotate_r(n);
      }
      return true;
    }
    return false;
  }
  void balance_insert(node *n){
    while(n=n->p)
      if(balance_node(n))
        break;
    if(n)
      update_heights(n);
  }
  void balance_remove(node *n){
    node *_n=n;
    balance_node(n);
   // update_heights(_n);
   // print();
    while(n=n->p)
      balance_node(n);//,update_heights(_n);//,print();
  }
  node* do_remove(node *n){
    node *t=0,*_t=0,*p=0;
    t=n->r;
    while(t){
      _t=t;
      t=t->l;
    }
    if(!_t)
    {
      t=n->l;
      while(t){
        _t=t;
        t=t->r;
      }
    }
    if(_t)
    {
      p=new node();
      p->d=_t->d;
      p->l=n->l;
      if(p->l)
        p->l->p=p;
      p->r=n->r;
      if(p->r)
        p->r->p=p;
      p->p=n->p;
      p->h=n->h;
      if(n->p){
        if(n==n->p->r)
          n->p->r=p;
        else
          n->p->l=p;
      }
      if(n==root)
        root=p;
      n->r=n->l=0;
      delete n;
      return do_remove(_t);
    }else{
      if(n->p){
        if(n==n->p->r)
          n->p->r=0;
        else
          n->p->l=0;
        p=n->p;
      }else p=0;
      delete n;
      return p;
    }
  }
};
