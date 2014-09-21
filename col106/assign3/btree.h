template<typename T>
class btree{
public:
  class node{
  public:
    T d;int h;
    node *p,*l,*r;
    node(){
      p=l=r=0;h=0;
    }
    void remove(node *n){
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
        p->r=n->r;
        if(n==n->p->r)
          n->p->r=p;
        else if(n==n->p->l)
          n->p->l=p;
        delete n;
        remove(_t);
      }else{
        if(n==n->p->r)
          n->p->r=0;
        else if(n==n->p->l)
          n->p->l=0;
        delete n;
      }
    }
    node* insert(const T &_d){
      if(_d>d)
      {
        if(r)
          return r->insert(_d);
        else
        {
          r=new node();
          r->d=_d;
          r->p=this;
          return r;
        }
      }else{
        if(l)
          return l->insert(_d);
        else
        {
          l=new node();
          l->d=_d;
          l->p=this;
          return l;
        }
      }
    }
    node* find(const T &_d){
      if(_d==d)
        return this;
      if(_d>d)
      {
        if(r)
          return r->find(_d);
        else
          return 0;
      }else{
        if(l)
          return l->find(_d);
        else
          return 0;
      }
    }
  };

  node *root;
  btree(){
    root=0;
  }
  node* insert(const T &d){
    if(!root)
    {
      root=new node();
      root->d=d;
      return 0;
    }else
      return root->insert(d);
  }
  void remove(node *n){
    if(!root)
      return;
    root->remove(n);
  }
  node* find(const T &d){
    if(!root)
      return 0;
    return root->find(d);
  }
};
