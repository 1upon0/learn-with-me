
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

#include "Point.h"
#include "Maze.h"
#include "PriorityQueueADT.h"
#include "PriorityQueueSTL.cpp"
#include "PriorityQueueArray.cpp"

using namespace std;

void solve(Maze * maze, PriorityQueueADT * pq);
void verifySolution(Maze * maze, string path);

int main(int argc, char **argv) {

	cout << "COL 106 Maze Solver" << endl;
	cout << "===================" << endl;

	if(argc != 3 && argc != 4)
	{
		cout << endl << "Usage : ./a.out <absolute-path-to-mazefile> <priority-queue-type>" << endl;
		cout << "priority-queue-type = 0 for stl::priority-queue (Part A), priority-queue-type = 1 for user-defined priority-queue (Part B)" << endl;
		exit(1);
	}

        cout << endl << "input filename : " << argv[1] << endl;

	Maze * maze = new Maze(argv[1]);
	Point destination = maze->getEndPoint();

	PriorityQueueADT * pq;
	if(atoi(argv[2]) == 0)
	{
		pq = new PriorityQueueSTL(&destination);
	}
	else
	{
		pq = new PriorityQueueArray(&destination);
	}

	cout << endl << "solving maze .... " << endl;
	solve(maze, pq);

	maze->print();

	if(argc == 4)
	{
		cout << endl << "verifying solution .... " << endl;
		verifySolution(maze, argv[3]);
	}
}

void solve(Maze * maze, PriorityQueueADT * pq)
{
	if(!maze)
		return;
	Point pt[4],p1=maze->getStartPoint(),end=maze->getEndPoint();
	pq->push(p1);
	while(!pq->empty()){
		p1=pq->top();
		if(p1.isEqual(end)){
			cout<<"maze solved!!\n\n";
			return;
		}
		maze->setVisited(p1);
		pq->pop();
		pt[0]=Point(p1.getRow()-1,p1.getColumn());
		pt[1]=Point(p1.getRow()+1,p1.getColumn());
		pt[2]=Point(p1.getRow(),p1.getColumn()+1);
		pt[3]=Point(p1.getRow(),p1.getColumn()-1);
		for(int i=0;i<4;i++){
			if(maze->isInBounds(pt[i])&&!maze->isWall(pt[i])&&!maze->isVisited(pt[i]))
				pq->push(pt[i]);
		}
	}
	cout<<"maze not solved\n\n";
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
