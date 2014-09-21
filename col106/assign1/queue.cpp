#include <iostream>
#include <fstream>
typedef unsigned int uint;
using namespace std;
template<typename Obj>
class clist{
	class node{
		public:
		Obj data;
		node *next;
		node(){next=0;}
	};
	node *_front,*_end;
	void destroy(){
		while(_front)
			pop_front();
	}
	public:
	clist(){
		_front=_end=NULL;
	}
	~clist(){destroy();}
	clist(const clist<Obj> &b){
		node *n1;
		n1=b._front;
		_front=_end=NULL;
		push_back(n1->data);
		n1=n1->next;
		while(n1!=b._front)
			push_back(n1->data);
	}
	const clist& operator =(const clist &b){
		destroy();
		node *n1;
		n1=b._front;
		_front=_end=NULL;
		push_back(n1->data);
		n1=n1->next;
		while(n1!=b._front)
			push_back(n1->data);
	}
	void push_back(const Obj &data){
		node *n=_front;
		if(!n){
			_front=new node();
			_front->data=data;
			_end=_front->next=_front;
			return;
		}
		_end->next=new node();
		_end->next->data=data;
		_end->next->next=_front;
		_end=_end->next;
	}
	void push_front(const Obj &data){
		node *n=_front;
		if(!n){
			_front=new node();
			_front->data=data;
			_end=_front->next=_front;
			return;
		}
		_end->next=new node();
		_end->next->data=data;
		_end->next->next=_front;
		_front=_end->next;
	}
	Obj pop_front(){
		if(_front==NULL)
			throw "Empty Queue Exception";
		Obj o=_front->data;
		node *n=_front->next;
		if(n==_front)
			n=NULL;
		delete _front;
		_front=n;
		_end->next=_front;
		return o;
	}
	Obj& front(){
		if(_front==NULL)
			throw "Empty Queue Exception";
		return front->data;
	}
	bool isEmpty() const{
		return _front==NULL;
	}
	uint size() const{
		if(!_front)
		    return 0;
		node *n=_front->next;uint size=1;
		while(n!=_front)
			n=n->next,size++;
		return size;
	}
	void print(){
		cout<<"Current State: ";
		node *n=_front;
		if(!_front)
			cout<<"empty\n";
		else{
			cout<<"sized "<<size()<<endl;
			cout<<n->data;n=n->next;
			while(n!=_front){
				cout<<" -> "<<n->data;n=n->next;
			}
			cout<<endl;
		}
	}
};

template<typename Obj>
class queue{
	clist<Obj> l;
	public:
	queue(){}
	void enqueue(const Obj &data){
		l.push_back(data);
	}
	Obj dequeue(){
		return l.pop_front();
	}
	Obj& front(){
		return l.front();
	}
	bool isEmpty() const{
		return l.isEmpty();
	}
	uint size() const{
		return l.size();
	}
	void print(){
		l.print();
	}

};
int main(){
	try{
		queue<int> q;
		int i=1;
		cout<<"Enter 0 to exit, -1 to dequeue, -2 to print state and +ve integers to queue\n";
		while(i!=0)
		{
			cin>>i;
			if(i==-1)
				cout<<"Dequeued: "<<q.dequeue()<<endl;
			else if(i==-2)
				q.print();
	  		else if(i>0)
				q.enqueue(i);
		}
	}
	catch(const char *error)
	{
		cout<<"ERROR: "<<error<<endl;
	}
}
