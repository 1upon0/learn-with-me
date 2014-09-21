#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "../timer.h"
#include <sstream>
#include <algorithm>
using namespace std;
typedef unsigned long long ullong;
typedef unsigned int uint;
//2 bits per bit
class minterm{
public:

char *m;int nm;
	minterm(int size,ullong val=0){
		nm=size;
		m=new char[size/4+1];
		for(int i=0;i<size/4+1;++i)m[i]=0;
		setto(val);
	}
	minterm(const minterm &b){
		nm=b.nm;
		uint a=nm/4+1;
		m=new char[a];
		for(uint i=0;i<a;++i)
			m[i]=b.m[i];
	}
	~minterm(){
		delete []m;
	}
	minterm operator =(const minterm &b){
		nm=b.nm;
		delete m;
		uint a=nm/4+1;
		m=new char[a];
		for(int i=0;i<a;++i)
			m[i]=b.m[i];
		return *this;
	}
	void setto(ullong a){
		if(nm>sizeof(ullong)*8)
			throw("ullong cant store big minterms!");
		for(int i=0;i<nm;++i)
			set(i,(a&(1<<i))>>i);
	}
	void set(int n,char state){
		uint a=n/4;
		char b=1<<((n-4*a)*2);
		m[a]&=~(char)(b<<1|b);
		if(state==2)
			m[a]|=b<<1;
		else if(state)
			m[a]|=b;
	}
	operator ullong()const{
		if(nm>sizeof(ullong)*8)
			throw("ullong cant store big minterms!");
		ullong r=0;
		for(int i=0;i<nm;++i)
			r|=status(i)==1?((ullong)1)<<i:0;
		return r;
	}
	void print(ostream& ft=std::cout)const{
		uint s;
		for(int i=nm-1;i>=0;--i){
			s=status(i);
			ft<<(s==1?'1':(s==2?'-':'0'));
		}
	}
	char status(int n)const{
		uint b=n/4;
		char a=char(1)<<((n-b*4)*2);
		if(m[b]&a<<1)
			return 2;
		return m[b]&a?1:0;
	}
	uint is_near(minterm &b)const{
		int n=0,m;
		for(int i=0;i<nm;++i)
			if(status(i)!=b.status(i))
				++n,m=i;
		return n==1?m:-1;
	}
	uint is_equal(const minterm &b)const{
		int a=nm/4+1;
		for(int i=0;i<a;++i)
			if(m[i]!=b.m[i])
				return 0;
		return 1;
	}
	bool operator ==(const minterm &b)const{
		return is_equal(b);
	}
	uint contains(minterm &b) const{
        int n=0;int si;
		for(int i=0;i<nm;++i){
			si=status(i);
			if(si!=2&&si!=b.status(i))
				return 0;
		}
		return 1;
	}
	uint num_dashes() const{
		int n=0;
		for(int i=0;i<nm;++i)
			if(status(i)==2)++n;
		return n;
	}
};
void min_step1(vector<minterm> &exp,int n){
	vector<minterm> exp1;bool minimized=0;
	int *covered;
	vector<uint> *divs;int i,j,k,l;
	divs=new vector<uint>[n+1];
	covered=new int[exp.size()];
	for(i=0;i<exp.size();i++){
		k=0;covered[i]=0;
		for(j=0;j<n;j++)
			k+=exp[i].status(j)==1?1:0;
		divs[k].push_back(i);
	}
	for(j=0;j<n;j++)
		for(i=0;i<divs[j].size();i++)
			for(k=0;k<divs[j+1].size();k++)
				if((l=exp[divs[j][i]].is_near(exp[divs[j+1][k]]))>=0)
				{
                    minimized=1;
                    minterm tmp(exp[divs[j][i]]);
                    tmp.set(l,2);
                    if(find(exp1.begin(),exp1.end(),tmp)==exp1.end())
                    	exp1.push_back(tmp);
					covered[divs[j][i]]=covered[divs[j+1][k]]=1;
				}
	delete []divs;
	for(i=0;i<exp.size();i++)
		if(!covered[i]){
			exp1.push_back(exp[i]);
		}
	delete []covered;
 exp=exp1;
 //cout<<minimized<<" "<<microtime()<<endl;
 if(minimized)
    min_step1(exp,n);
}
void min_step2(vector<minterm> orig,vector<minterm> &exp,int n){
	int i,j,l;
	vector<int> containers;
	vector<minterm> out;
	while(1){
		containers.clear();
		for(j=0;j<exp.size();j++)
			if(exp[j].contains(orig.back()))
				containers.push_back(j);
		l=-1;
		for(j=0;j<containers.size();j++)
			if(l==-1||exp[containers[j]].num_dashes()>exp[l].num_dashes())
				l=containers[j];
		out.push_back(exp[l]);
		exp.erase(exp.begin()+l);
		for(l=0;l<orig.size();l++)
			if(out.back().contains(orig[l]))
				orig.erase(orig.begin()+l--);
		if(orig.empty())
			break;
	}
	exp=out;
}
void read_exp(vector<minterm> &exp,vector<minterm> &dc,int &bits){
	ifstream fs("input.txt");
	string line;
	int mode=0;
	ullong m;
	char tmp[50];
	fs>>tmp>>
	
	bits=-1;
	istringstream iss;
	while(getline(fs,line)){
		if(line[0]=='#')
			continue;
		if(line[0]=='.'){
			switch(line[1]){
				case 'i':
				mode=1;
				iss.clear();
				iss.str(line.substr(2));
				iss>>bits;
				break;
				case 'm':
				mode=2;
				break;
				case 'd':
				mode=3;
				break;
				default://invalid data type
				throw "Input file format invalid. Invalid identifier";
				mode=0;
			}
		}
		else if(mode==2){
			if(bits==-1)
				throw "Input file format invalid. Number of variables missing before minterms";
			iss.clear();
			iss.str(line);
			while(iss>>m){
				exp.push_back(minterm(bits,m));
			}
		}else if(mode==3){
			if(bits==-1)
				throw "Input file format invalid. Number of variables missing before dont cares";
			iss.clear();
			iss.str(line);
			while(iss>>m)
				dc.push_back(minterm(bits,m));
		}
	}
}
void output_exp(vector<minterm> &exp,vector<minterm> &exp_orig,vector<minterm> &dc,int bits){
	ofstream ft("output.txt");
	ft<<".i "<<bits<<endl;
	ft<<".m"<<endl;
	for(int i=0;i<exp_orig.size();i++){
		ft<<(ullong)exp_orig[i];
		if(i<exp_orig.size()-1)
			ft<<' ';
	}
	ft<<endl<<".d"<<endl;
	for(int i=0;i<dc.size();i++){
		ft<<(ullong)dc[i];
		if(i<dc.size()-1)
			ft<<' ';
	}
	ft<<endl<<".p "<<exp.size()<<endl;
	for(int i=0;i<exp.size();i++){
		exp[i].print(ft);
		ft<<endl;
	}
	ft<<".end";
}
int main(){
	try{
	int i;
	vector<minterm> exp,exp_orig;
	vector<minterm> dc,out;
	int bits=8;
	read_exp(exp,dc,bits);
//	for(ullong j=0;j<ullong(1)<<bits;j++)
//		if(!random(4))exp.push_back(minterm(bits,j));

	for(i=0;i<exp.size();i++){
	    exp_orig.push_back(exp[i]);
	}
	for(i=0;i<dc.size();i++){
        exp.push_back(dc[i]);
	}
	cout<<"Step:0\n";
	for(i=0;i<exp.size();i++){
	   exp[i].print();cout<<" ";
	}cout<<endl;
	microtime();
	min_step1(exp,bits);
	cout<<"Step1 time: "<<microtime()<<endl;
	cout<<"Step:1\n";
	for(i=0;i<exp.size();i++){
	   exp[i].print();cout<<" ";
	}cout<<endl;
	microtime();
	min_step2(exp_orig,exp,bits);
	cout<<"Step2 time: "<<microtime()<<endl;
	cout<<"Step:2\n";
	for(i=0;i<exp.size();i++){
	   exp[i].print();cout<<" ";
	}cout<<endl;
	for(int j=0;j<dc.size();j++){
		for(i=0;i<exp.size();i++){
			if(exp[i].is_equal(dc[j])){
				exp.erase(exp.begin()+i);
				i--;
			}
		}
	}
	output_exp(exp,exp_orig,dc,bits);
	}catch(const char *err){
		cout<<endl<<"ERROR:"<<err<<endl;
	}
}
