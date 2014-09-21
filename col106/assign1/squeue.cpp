#include "stack.h"
#include <iostream>
using namespace std;
template <typename Obj>
class squeue{
	stack<Obj> q,d;
	void transfer(){
		while(!q.isEmpty()){
			d.push(q.pop());
		}
	}
	public:
	uint size(){
		return q.Size()+d.Size();
	}
	bool isEmpty(){
		return q.isEmpty()&&d.isEmpty();
	}
	Obj &front(){
		if(d.isEmpty())
			transfer();
		return d.top();
	}
	Obj dequeue(){
		if(d.isEmpty())
			transfer();
		return d.pop();
	}
	void enqueue(const Obj &o){
		q.push(o);
	}
	void print(){
		cout<<"Current State: ";
		if(isEmpty())
			cout<<"empty\n";
		else{
			cout<<"sized "<<size()<<endl;
			cout<<"Queue stack:\n";
				q.print();
			cout<<"Dequeue stack:\n";
				d.print();
		}
	}
};
int main(){
	try{
		squeue<int> q;
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