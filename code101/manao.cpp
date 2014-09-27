#include <stdio.h>
#include<string.h>
#include<vector>
using namespace std;
inline long intin(long *a)
{
	char c = 0;
	while(c<33)
		c = getc(stdin);
	*a = 0;
	while(c>33)
	{
		*a = *a*10 + c - '0';
		c = getc(stdin);
	}
	return c;
}
void sort(long *a,int n){
	long t;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[i]>a[j]){
				t=a[i];a[i]=a[j];a[j]=t;
			}
}
void print_arr(long *a,int n){
	int i=0;
	while(n--){
		if(n!=0)
			printf("%d ",a[i]);
		else
			printf("%d\n",a[i]);
		i++;
	}
}
#define abs(x) ((x)>0?(x):-(x))
class node{
public:
	int x1,x2,y,cost,traveled;
	vector<node*> children;
	node(int _x1=0,int _x2=0,int _y=0){
	traveled=0;traveled=0;
	cost=32767;
	x2=_x2;
	x1=_x1;y=_y;
	}
	void add_child(node *c){
		children.push_back(c);
	}
	int traverse_to(node *tar,int l=0){
		//for(int i=0;i<l;i++)printf("-");
		//printf("%d %d %d\n",x1,y,cost);
		if(l==0)cost=0;
		if(this==tar){
			return cost;
		}
		int c1,c2,c=32767;
		for(int i=0;i<children.size();i++)
		{	
			c2=cost;
			if(c2<abs(children[i]->y-y))
				c2=abs(children[i]->y-y);
            if(c2<children[i]->cost)
				children[i]->cost=c2;
		}
		if(traveled)
		    return -1;
		traveled=1;
		for(int i=0;i<children.size();i++)
		{
			c1=children[i]->traverse_to(tar,l+1);
			if(c1==-1)
			    continue;
			if(c1<c)
				c=c1;
		}
		//for(int i=0;i<l;i++)printf("-");
		//printf("%d %d %d\n",x1,y,c);
		return c;
	}
};
int main()
{
	char map[50][51];
	long H,W,cX,cY;
	vector<node*> nodes;
	node *coin,*ground;
	intin(&H);
	for(int i=0;i<H;i++){
		gets(map[i]);
	}
	intin(&cY);cY--;
	intin(&cX);cX--;
	W=strlen(map[0]);
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++)
		{
			if(map[i][j]=='X'){

				if(j>0&&map[i][j-1]=='X'){
                    if(cY==i&&cX==j)
						coin=nodes.back();
					nodes.back()->x2=j;
					continue;
				}
				node *n=new node(j,j,i);
				nodes.push_back(n);
				if(cY==i&&cX==j){
					coin=n;
				}
				if(i==H-1)
					ground=n;
			}
		}
	}
	for(int i=0;i<nodes.size()-1;i++){
		for(int j=i+1;j<nodes.size();j++){
			if(
				(nodes[i]->x1>=nodes[j]->x1&&nodes[i]->x1<=nodes[j]->x2) ||
				(nodes[i]->x2>=nodes[j]->x1&&nodes[i]->x2<=nodes[j]->x2)||
				(nodes[j]->x1>=nodes[i]->x1&&nodes[j]->x1<=nodes[i]->x2) ||
				(nodes[j]->x2>=nodes[i]->x1&&nodes[j]->x2<=nodes[i]->x2)){
					nodes[i]->add_child(nodes[j]);
					nodes[j]->add_child(nodes[i]);
				}
		}
	}
	printf("%d",coin->traverse_to(ground));
}
