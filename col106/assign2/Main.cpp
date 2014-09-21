
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "Point.h"
#include "Maze.h"
#include "DequeADT.h"
//#include "DequeSTL.h"
#include "DequeSTL.cpp"
#include "DequeArray.cpp"
//#include "MazeSolver.cpp"

using namespace std;

void solve(Maze * maze, DequeADT<Point> * dq);
void verifySolution(Maze * maze, string path);

int main(int argc, char **argv) {

	cout << "COL 106 Maze Solver" << endl;
	cout << "===================" << endl;

	if(argc != 3 && argc != 4)
	{
		cout << endl << "Usage : ./a.out <absolute-path-to-mazefile> <deque-type>" << endl;
		cout << "deque-type = 0 for stl::deque (Section 1), deque-type = 1 for user-defined deque (Section 2)" << endl;
		exit(1);
	}

        cout << endl << "input filename : " << argv[1] << endl;

	Maze * maze = new Maze(argv[1]);
	DequeADT<Point> * dq;
	if(atoi(argv[2]) == 0)
	{
		dq = new DequeSTL<Point>();
	}
	else
	{
		dq = new DequeArray<Point>();
	}

	cout << endl << "solving maze .... " << endl;
	solve(maze, dq);

	maze->print();

	if(argc == 4)
	{
		cout << endl << "verifying solution .... " << endl;
		verifySolution(maze, argv[3]);
	}
}

void solve(Maze * maze, DequeADT<Point> * dq)
{
	if(!maze)return;
	Point pt[4],p2,p1=maze->getStartPoint(),end=maze->getEndPoint();
	unsigned int d[4],d1;
	dq->push_back(p1);
	while(!dq->empty()){
		d[0]=d[1]=d[2]=d[3]=32767;
		p1=dq->front();
		if(p1.isEqual(end))
			break;
		maze->setVisited(p1);
		dq->pop_front();
		pt[0]=Point(p1.getRow(),p1.getColumn()-1);
		pt[1]=Point(p1.getRow(),p1.getColumn()+1);
		pt[2]=Point(p1.getRow()-1,p1.getColumn());
		pt[3]=Point(p1.getRow()+1,p1.getColumn());
		for(int i=0;i<4;i++){
			if(maze->isInBounds(pt[i])&&!maze->isWall(pt[i])&&!maze->isVisited(pt[i]))
				d[i]=pt[i].distanceFrom(end);
		}
		/*for(int i=0;i<3;i++)
			for(int j=i+1;j<4;j++)
				if(d[j]<d[i]){
					d1=d[i];
					d[i]=d[j];
					d[j]=d1;
					p2=pt[i];					
					pt[i]=pt[j];
					pt[j]=p2;
				}
		d1=d[0];
		*/
		d1=p1.distanceFrom(end);
		
		for(int i=0;i<4;i++){
			if(d[i]==32767)
				continue;
			if(d[i]>=d1)
				dq->push_back(pt[i]);
		}
		for(int i=3;i>=0;i--){
			if(d[i]==32767)
				continue;
			if(d[i]<d1)
				dq->push_front(pt[i]);
		}
	}
}

void verifySolution(Maze * maze, std::string path)
{
	Maze * correct_solution = new Maze(path);

	if(maze->getNumRows() != correct_solution->getNumRows() || maze->getNumColumns() != correct_solution->getNumColumns())
	{
		cout << "dimension mismatch between input and correct output mazes" << endl;
		exit(1);
	}

	for(int i = 0; i < maze->getNumRows(); i++)
	{
		for(int j = 0; j < maze->getNumColumns(); j++)
		{
			Point p;
			p.setRow(i);
			p.setColumn(j);
			if(maze->isVisited(p) != correct_solution->isVisited(p) && !p.isEqual(maze->getStartPoint()))
			{
				cout << "incorrect solution" << endl;
				cout << "mismatch at : (" << i << "," << j << ")" << endl;
				exit(0);
			}
		}
	}

	cout << "correct solution!" << endl;
}
