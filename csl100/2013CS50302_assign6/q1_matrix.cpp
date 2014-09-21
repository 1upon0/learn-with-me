#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
const int N=6;

void matmult(float A[N][N],float B[N][N],float C[N][N]){
	int i,j,k;
	float s;
	float *t1,*t2;
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
			s=0;
			t1=A[i];//cache the base address of the row
			t2=&B[0][j];//cache the base address of the column
			for(k=0;k<N;k++){
				s+=*t1**t2;
				t1++;//the next element in row. saves a multiplication op
				t2+=N;//the next element in column. saves a multiplication op at the cost of an addition op
			}
			C[i][j]=s;
		}
	}
}

void matmult_trans(float A[N][N],float B[N][N],float C[N][N]){
	int i,j,k;
	float s;
	float *t1,*t2;
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
			s=0;
			t1=A[i];//cache the base address of the row
			t2=B[j];//cache the base address of the column
			for(k=0;k<N;k++){
				s+=*t1**t2;
				t1++;//the next element in row. saves a multiplication op
				t2++;//the next element in column. saves a multiplication op at the cost of an addition op
			}
			C[i][j]=s;
		}
	}
}
void matread(float A[N][N],char *file){
	ifstream fs(file);
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			fs>>A[i][j];
}
void matprint(float A[N][N]){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++)
			cout<<A[i][j]<<"\t"<<" ";
		cout<<endl;
	}
}
void toidentity(float A[N][N]){
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			A[i][j]=i==j?1:0;
}
void matcopy(float A[N][N],float B[N][N]){
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			A[i][j]=B[i][j];
}
int main()
{
	float A[N][N],B[N][N],C[N][N],Q[N][N],R[N][N];
	float tmp;
	int i,j;
	char again='y';
	while(again=='y'){
		matread(A,"matrix.txt");
		toidentity(Q);
		toidentity(R);
		cout.precision(2);
		cout<<fixed;
		cout<<"Matrix A:\n";matprint(A);
		cout<<"Matrix R:\n";matprint(R);
		cout<<"Matrix Q:\n";matprint(Q);
		
		for(i=1;i<N;i++){
			for(j=0;j<i;j++){
				toidentity(R);
				tmp=sqrt(A[j][j]*A[j][j]+A[i][j]*A[i][j]);
				R[i][i]=R[j][j]=A[j][j]/tmp;
				R[j][i]=A[i][j]/tmp;
				R[i][j]=-R[j][i];
				matmult(R,A,B); //B=RxA
				matmult_trans(Q,R,C); //C=Qx(R_t)
				matcopy(A,B);//A=B
				matcopy(Q,C);//Q=C
				cout<<"\n-----["<<i<<","<<j<<"]-----\n";
				cout<<"Matrix A:\n";matprint(A);
				cout<<"Matrix R:\n";matprint(R);
				
			}
		}
		matmult(Q,A,C); //C=QxA
		cout<<"Matrix QxA:\n";matprint(C);
		
		cout<<"\nRun again?[y]:";
		cin>>again;
	}
	return 0;
}

