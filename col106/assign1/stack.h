#include <iostream>
typedef unsigned int uint;
using namespace std;
template<typename Obj>
class stack{
	Obj *data;
	uint size,allocated;
	public:
	stack(uint initial_size=1){
		data=new Obj[initial_size];
		size=0;
		allocated=initial_size;
	};
	~stack(){
		delete []data;
	}
	stack(const stack &b){
		size=b.size;
		allocated=b.allocated;
		data=new Obj[allocated];
		for(int i=0;i<size;i++)
			data[i]=b.data[i];
	}
	const stack& operator =(const stack &b){
		delete []data;
		size=b.size;
		allocated=b.allocated;
		data=new Obj[allocated];
		for(int i=0;i<size;i++)
			data[i]=b.data[i];
	}
	void push(const Obj &o){
		if(size==allocated)
		{
			Obj *data2=new Obj[allocated*2];
			for(uint i=0;i<allocated;i++)
				data2[i]=data[i];
			delete []data;
			data=data2;
			allocated*=2;
		}
		data[size]=o;
		size++;
	}
	Obj pop(){
		if(size==0)
			throw "Empty Stack Exception";
		return data[--size];		
	}
	Obj& top(){
		if(size==0)
			throw "Empty Stack Exception";
		return data[size-1];		
	}
	bool isEmpty(){
		return size==0;
	}
	uint Size(){
		return size;
	}
	void print(){
		cout<<"Size: "<<size<<endl;
		if(size){
			cout<<data[0];
			for(int i=1;i<size;i++)
				cout<<" <- "<<data[i];
		}else cout<<"empty";
		cout<<endl;
	}
};
