/**
 * @author	Yash Gupta (2013cs50302)
 * @desc	Calculates sin/cos of an angle
 */
 
#include <iostream>
using namespace std;
#define PI2	(2.0*3.14159266)
int main()
{
	int c;double x,x0,v=0,xx=1;
	cout<<endl<<"Enter 1 for sin and 2 for cos calculation:";
	cin>>c;
	cout<<"Enter the angle in radians:";
	cin>>x0;
	//to improve results, limit x to -pi to pi, as for 5 terms only, higher values give too much error.
	if(x0>0)
		x=x0-int(x0/PI2)*PI2;
	else
		x=x0-int(x0/PI2-1)*PI2;
	if(x0>PI2/2)
	    x=x-PI2;
	cout<<"Converted "<<x0<<" to "<<x<<" for accurate results\n";
	if(c==1){
		xx=x;//first term
		v =	xx;	
		
		xx*=x*x/3/2; //2nd term
		v+=-xx;
		
		xx*=x*x/5/4; //3rd term
		v+=	xx;
		
		xx*=x*x/7/6; //4th term
		v+=-xx;
		
		xx*=x*x/9/8; //5th term
		v+=xx;

		cout<<"Sin("<<x0<<")="<<v;
	}else if(c==2){
		
		xx=1;
		v =	xx;		//term 1
		
		xx*=x*x/2;	//term 2
		v+=-xx;
		
		xx*=x*x/4/3;//term 3
		v+=	xx;
		
		xx*=x*x/6/5;//term 4
		v+=-xx;
		
		xx*=x*x/8/7;//term 5
		v+= xx;

		cout<<"Cos("<<x0<<")="<<v;
	}else
		cout<<"Invalid Input!";
	cout<<endl;
	return 0;
}
