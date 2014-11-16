#include "PriorityQueueADT.h"
#include "comparator.h"
#include "Point.h"

#include <iostream>

using namespace std;

class PriorityQueueArray : public PriorityQueueADT {
	private:
		//TODO add private members here
		Point *pts;
		int allocated,used;
		mycomparison comp;
		void expand();
		void perc_down(int n);
		void perc_up(int n);
	public:
		PriorityQueueArray(Point *destination);

		void push (const Point& val);
		bool empty();
		Point top();
		void pop();
		int size();

};
void PriorityQueueArray::expand(){
	Point *tmp=new Point[allocated*2];
	for(int i=1;i<=used;i++)
		tmp[i]=pts[i];
	delete []pts;
	pts=tmp;
	allocated*=2;
}
void PriorityQueueArray::perc_up(int n){
	Point t;
	for(int i=n/2;i>0;i/=2){
		if(comp(pts[i],pts[n]))
		{
			t=pts[i],pts[i]=pts[n],pts[n]=t;
			n=i;
		}else
			break;
	}
}

void PriorityQueueArray::perc_down(int n){
	Point t;bool c1,c2;
	for(int i=n*2;i<=used;i*=2){
		c1=comp(pts[i],pts[n]);
		c2= (i==used)?true:comp(pts[i+1],pts[n]);
		if(c1&&c2)
			break;
		if(!c1&&c2)
		{
			t=pts[i],pts[i]=pts[n],pts[n]=t;
			n=i;
		}else if(c1&&!c2 || !comp(pts[i+1],pts[i]))
		{
			t=pts[i+1],pts[i+1]=pts[n],pts[n]=t;
			n=i+1;
		}else{
			t=pts[i],pts[i]=pts[n],pts[n]=t;
			n=i;
		}
	}
}
PriorityQueueArray::PriorityQueueArray(Point *destination):comp(destination)
{
	//TODO
	allocated=10;
	used=0;
	pts=new Point[allocated];
}


void PriorityQueueArray::push (const Point& val)
{
	//TODO
	if(allocated==used+1)
		expand();
	used++;
	pts[used]=val;
	perc_up(used);
}
	
bool PriorityQueueArray::empty()
{
	return (used==0);
}
	
Point PriorityQueueArray::top()
{
	//TODO
	return pts[1];
}
	
void PriorityQueueArray::pop()
{
	if(used==0){
		throw "cannot pop from empty queue!";
		return;
	}
	pts[1]=pts[used];
	used--;
	perc_down(1);
}
	
int PriorityQueueArray::size()
{
	return used;
}

/*
template <typename T>
void DequeSTL<T>::print()
{
	for(int i = 0; i < dq->size(); i++)
	{
		cout << dq->at(i) << endl;
	}
}*/
