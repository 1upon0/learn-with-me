#include <iostream>
#include <vector>
#include <fstream>
#include <string>
//#include "../timer.h"
#include <sstream>
#include <algorithm>
using namespace std;
typedef unsigned long long ullong;
typedef unsigned int uint;
//2 bits per variable
class minterm{
public:

char *m;int n;
	minterm(int size,ullong val=0){
		n=size;
		m=new char[size];
		setto(val);
	}
	minterm(const minterm &b){
		n=b.n;
		m=new char[n];
		for(uint i=0;i<n;++i)
			m[i]=b.m[i];
	}
	~minterm(){
		delete []m;
	}
	minterm operator =(const minterm &b){
		n=b.n;
		delete []m;
		m=new char[n];
		for(int i=0;i<n;++i)
			m[i]=b.m[i];
		return *this;
	}
	void setto(ullong a){
		if(n>sizeof(ullong)<<3)
			throw("ullong cant store big minterms!");
		for(int i=0;i<n;++i)
			set(i,(a&(1<<i))>>i);
	}
	 void set(int n,char state){
		m[n]=state;
	}
	 operator ullong()const{
		if(n>sizeof(ullong)<<3)
			throw("ullong cant store big minterms!");
		ullong r=0;
		for(int i=0;i<n;++i)
			r|=m[i]==1?((ullong)1)<<i:0;
		return r;
	}
	void print(ostream& ft=std::cout)const{
		uint s;
		for(int i=n-1;i>=0;--i){
			ft<<(char)(m[i]==2?'-':m[i]+'0');
		}
	}
	 char status(int n)const{
		return m[n];
	}
	uint is_near(const minterm &b)const{
		int N=0,nm;
		for(int i=0;i<n;++i)
			if(m[i]!=b.m[i])
				++N,nm=i;
		return N==1?nm:-1;
	}
	 uint is_equal(const minterm &b)const{
		for(int i=0;i<n;++i)
			if(m[i]!=b.m[i])
				return 0;
		return 1;
	}
	bool operator ==(const minterm &b)const{
		for(uint i=0;i<n;++i)
			if(m[i]!=b.m[i])
				return 0;
		return 1;
	}
	 uint contains(minterm &b) const{
		for(int i=0;i<n;++i){
			if(m[i]!=2&&m[i]!=b.m[i])
				return 0;
		}
		//print();cout<<" contains ";b.print();cout<<endl;
		return 1;
	}
	 uint num_dashes() const{
		int nm=0;
		for(int i=0;i<n;++i)
			if(m[i]==2)++nm;
		return nm;
	}
};
vector<minterm> min_step1(const vector<minterm> &exp,int n){
	vector<minterm> exp1;bool minimized=0;
	int *covered;
	vector<uint> *divs;int i,j,k,l,i1;
	divs=new vector<uint>[n+1];
	covered=new int[exp.size()];
	for(i=0;i<exp.size();i++){
		k=0;covered[i]=0;
		for(j=0;j<n;j++)
			k+=exp[i].status(j)==1?1:0;
		divs[k].push_back(i);
	}
	//cout<<"divs "<<microtime()<<endl;

	for(j=0;j<n;j++){
		i1=exp1.size();
		if(i1>0)--i1;
		for(i=0;i<divs[j].size();i++){
			for(k=0;k<divs[j+1].size();k++){
				
				if((l=exp[divs[j][i]].is_near(exp[divs[j+1][k]]))>=0)
				{
                    minimized=1;
                    minterm tmp(exp[divs[j][i]]);
                    tmp.set(l,2);
                    if(find(exp1.begin()+i1,exp1.end(),tmp)==exp1.end())
                    	exp1.push_back(tmp);
					covered[divs[j][i]]=covered[divs[j+1][k]]=1;
				}
			}
		}
		//cout<<exp1.size()<<endl;
		//cotut<<"j= "<<j<<"  "<<microtime()<<endl;
	}
	delete []divs;
	for(i=0;i<exp.size();i++)
		if(!covered[i]){
			exp1.push_back(exp[i]);
		}
	delete []covered;
	//cout<<"completed: "<<microtime()<<endl;
	if(minimized)
 		return min_step1(exp1,n);
	return exp1;
}
void min_step2(vector<minterm> orig,vector<minterm> &exp,int n){
	int i,j,l,min_minterm;
	vector< vector<int> > containers;
	vector<minterm> out;
	ullong num_containers;
	while(1){
		containers.clear();
		min_minterm=0;
		num_containers=(ullong(1)<<63);
		for(i=0;i<orig.size();i++)
		{
			containers.push_back(vector<int>());
			for(j=0;j<exp.size();j++)
				if(exp[j].contains(orig[i]))
					containers[i].push_back(j);
			if(containers[i].size()<num_containers)
			{
				num_containers=containers[i].size();
				min_minterm=i;
			}
		}
		l=-1;
		for(j=0;j<num_containers;j++)
			if(l==-1||exp[containers[min_minterm][j]].num_dashes()>exp[l].num_dashes())
				l=containers[min_minterm][j];
		out.push_back(exp[l]);
		exp.erase(exp.begin()+l);
		for(l=0;l<orig.size();l++)
			if(out.back().contains(orig[l])){
				orig.erase(orig.begin()+l--);	
			}
		if(orig.empty())
			break;
	}
	exp=out;
}
void read_exp(vector<minterm> &exp,vector<minterm> &dc,int &bits){
	ifstream fs("input.txt");
	if(!fs)
		throw "Could not open input file to read!";
	string line;
	int mode=0;
	ullong m;
	char tmp[50];
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
	if(!ft)
		throw "Could not open output file to write!";
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
	int bits=9;
	read_exp(exp,dc,bits);
	//for(ullong j=0;j<ullong(1)<<bits;j++)
	//	exp.push_back(minterm(bits,j));
	for(i=0;i<exp.size();i++){
	    exp_orig.push_back(exp[i]);
	}
	for(i=0;i<dc.size();i++){
        exp.push_back(dc[i]);
	}
	//microtime();
	exp=min_step1(exp,bits);
	min_step2(exp_orig,exp,bits);
	//cout<<"time taken: "<<microtime()<<endl;
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
