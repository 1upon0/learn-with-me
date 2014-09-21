//#include "DequeArray.h"

#include "DequeADT.h"

#include <deque>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class DequeArray : public DequeADT<T> {
	private:
		//TODO add private members here
		T *data;
		int s,a,f;
		void expand();
	public:
		DequeArray();
		~DequeArray();

		void push_front (const T& val);
		void push_back (const T& val);	
		void clear();
		bool empty();	
		T front();	
		T back();	
		T at(int index);	
		void pop_front();	
		void pop_back();	
		int size();
		//void print();

};

template <class T>
DequeArray<T>::DequeArray()
{
	//TODO
	s=0;f=0;a=10;
	data=new T[10];
}
template <class T>
DequeArray<T>::~DequeArray()
{
	clear();
	delete []data;
}
template <class T>
void DequeArray<T>::expand(){
	T *tmp=new T[a*2];int j;
	for(int i=0;i<s;i++){
		j=i+f;
		if(j<0)
			j=j+a;
		if(j>=a)
			j-=a;
		tmp[i]=data[j];
	}
	delete []data;
	data=tmp;
	f=0;
	a*=2;
}
template <class T>
void DequeArray<T>::push_front (const T& val)
{
	if(s==a)
		expand();
	f--;
	if(s==0)
		f=0;
	if(f<0)
		f=a+f;
	data[f]=val;
	s++;
}

template <class T>
void DequeArray<T>::push_back (const T& val)
{
	if(s==a)
		expand();
	int l=f+s;
	if(s==0)
		l=f=0;
	if(l>=a)
		l=l-a;
	data[l]=val;
	s++;
}

template <class T>
void DequeArray<T>::clear()
{
	//TODO
	delete []data;
	data=new T[10];
	f=s=0;a=10;
}
	
template <class T>
bool DequeArray<T>::empty()
{
	//TODO
	return s==0;
}
	
template <class T>
T DequeArray<T>::front()
{
	if(!s)
	{
		cout<<"Error: access from empty deque";
		exit(0);
	}
	return data[f];
}
	
template <class T>
T DequeArray<T>::back()
{
	if(!s)
	{
		cout<<"Error: access from empty deque";
		exit(0);
	}
	int l=f+s-1;
	if(l>=a)
		l-=a;
	return data[l];
}
	
template <class T>
T DequeArray<T>::at(int index)
{
	if(!s)
	{
		cout<<"Error: access from empty deque";
		exit(0);
	}
	if(index>=s)
	{
		cout<<"Error: access outside bounds of deque";
		exit(0);
	}
	index+=f;
	if(index>=a)
		index-=a;
	return data[index];
}
	
template <class T>
void DequeArray<T>::pop_front()
{
	if(!s){
		cout<<"Error: pop from Empty Deque";
		exit(0);
	}
	f++;
	if(f==a)
		f=0;
	s--;
}
	
template <class T>
void DequeArray<T>::pop_back()
{
	if(!s){
		cout<<"Error: pop from Empty Deque";
		exit(0);
	}
	s--;
}
	
template <class T>
int DequeArray<T>::size()
{
	return s;
}

/*
template <typename T>
void DequeArray<T>::print()
{
	for(int i = 0; i < dq->size(); i++)
	{
		cout << dq->at(i) << endl;
	}
}*/
