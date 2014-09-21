/*
 * @author Yash Gupta (cs5130302)
 * @desc lab4-1-sin/cos calculation
 */

#include <iostream>
using namespace std;
int main()
{
	int n,i;
	double x,xx=1,v=0;//xx stores the next term of the series.
	cout<<"\nEnter 1 for sin and 2 for cos calculation:";
	cin>>n;
	cout<<"\nEnter the angle in radians:";
	cin>>x;	
	if(n==1){
		xx=x;
		for(i=1;;i++){
			if(i%2==0)//alternate terms are -ve
				v+=xx;
			else
				v-=xx;
   			if(xx<0.0001)//if the next term in series is less than threshold, break;
				break;
			xx*=x*x/(i*2)/(i*2+1);//differentially calculate the next term, for better efficiency.

		}
		cout<<"sin("<<x<<")="<<v<<"\n Took "<<i<<" terms\n";
	}else if(n==2){
		xx=1;
		for(i=1;;i++){
			if(i%2==1)
				v+=xx;
			else
				v-=xx;
			if(xx<0.0001)
				break;
			xx*=x*x/(i*2-1)/(i*2);
		}
		cout<<"cos("<<x<<")="<<v<<"\n Took "<<i<<" terms\n";	
	}else
		cout<<"Invalid Input\n";
	return 0;
}
