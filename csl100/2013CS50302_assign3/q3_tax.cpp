/**
 * @author	Yash Gupta (2013cs50302)
 * @desc	Calculates income tax
 */

/*
It is not clear whether to apply tax slab wise 
i.e. 	30% for income excess of 500k,
		20% for income excess of 200k, below 500k,
		10% for income excess of 50k, below 200k.
if the specs are followed anyways, the tax for 200k, 500k will be 0 and someone with a higher income could pay lesser tax than lower income.
eg: 200,010 pays Rs 2 tax, while 100,000 pays Rs. 5000 tax.
*/
 #include <iostream>
using namespace std;
int main(){
	float fTax=0,fBiz,fCharity,fIncome;
	cout<<"\nEnter income:";
	cin>>fIncome;
	cout<<"Enter amount donated to charity:";
	cin>>fCharity;
	cout<<"\nEnter amount spent as business expenses:";
	cin>>fBiz;
	if(fBiz>1e4)	//biz expenses upto 10k are allowed and not counted.
		fBiz=1e4;
	fIncome-=fBiz;	//deduct buziness expense from taxable income
	fIncome-=fCharity;	//deduct charity
	if(fIncome<0){	//invalid input?
		cout<<"\nWARNING: Charity/Business expenses Exceeds income";fIncome=0;
	}
	if(fIncome>5e5)	
		fTax+=(fIncome-5.0e5f)*0.3,fIncome=5e5;
	if(fIncome>2e5)
		fTax+=(fIncome-2.0e5f)*0.2,fIncome=2e5;
	if(fIncome>5e4)
		fTax+=(fIncome-5.0e4f)*0.1,fIncome=5e4;
	cout<<"\nIncome tax applicable:"<<fTax<<endl;
	return 0;
}
