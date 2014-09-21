#include <iostream>
#include "stack.h"
using namespace std;
int main(){
	try{
		stack<int> s;
		int i=1;
		cout<<"Enter 0 to exit, -1 to pop, -2 to print state and +ve integers to push\n";
		while(i!=0)
		{
			cin>>i;
			if(i==-1)
				cout<<"Popped: "<<s.pop()<<endl;
			else if(i==-2)
				s.print();
	  		else if(i>0)
				s.push(i);
		}
	}
	catch(const char *error)
	{
		cout<<"ERROR: "<<error<<endl;
	}
}