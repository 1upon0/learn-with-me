#include "game.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <math.h>
#define MAX_FPS (1e6/32)
using namespace std;
void game::read_file(char *fs){
	ifstream f(fs);
	string sLine;
	int mode=-1,line_no=0;
	while(getline(f,sLine)){
		line_no++;
		cout<<"#"<<line_no<<" ";
		if(sLine[0]=='#')//comment line
			continue;
		if(sLine[0]=='>')//new section starts after this line
		{
			string command=sLine.substr(1);
			if(command=="TERRAIN")
				mode=0,cout<<"Reading Terrain\n";
			if(command=="TREES")
				mode=1,cout<<"Reading Trees\n";
			if(command=="BALL")
				mode=2,cout<<"Reading Ball settings\n";
			if(command=="WINDOW")
				mode=3,cout<<"Reading Window settings\n";
			continue;
		}else{
			int i,x,y,z;
			istringstream issLine(sLine);		
			switch(mode){
				case 0:
					issLine>>x>>y;
					if(issLine){
						terrain.push_back(vec2(x,y));
					}
					else
						cout<<"Formatting error on line "<<line_no<<endl;
				break;
				case 1:{
					issLine>>z;i=0;
					if(!issLine){
						cout<<"Formatting error on line "<<line_no<<endl;
						break;
					}
					vector<tri2> *tree=new vector<tri2>();
					tri2 t;
					trees.push_back(tree);
					t.z=z;
					t.c=color(30,200,100);
					while(issLine>>x>>y){
						if(!issLine){
							cout<<"Formatting error on line "<<line_no<<endl;
							break;
						}
						t.p[i%3]=vec2(x,y);
						if(i%3==2)
							tree->push_back(t);
						i++;
					}}
				break;
				case 2:
					issLine>>size>>speed;
					if(!issLine){
						cout<<"Formatting error on line "<<line_no<<endl;
						break;
					}
					cout<<"Size of ball:"<<size<<endl;
					ball.load_hexagon(size);
				break;
				case 3:
					issLine>>x>>y;//window size
					if(!issLine){
						cout<<"Formatting error on line "<<line_no<<endl;
						break;
					}
					w=x;
					h=y;
				break;
			}
		}
	}
	cout<<terrain.size()<<endl;
	cout<<trees.size()<<endl;
}
#include <sys/time.h>

long microtime()
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL) != 0)
			return 0;
	return (tv.tv_sec * 1000000) + tv.tv_usec;
}
long game::time(){
  static long t=microtime();
  long t1;
  t1=microtime();
  long us = (t1 - t);//*1000.0 / CLOCKS_PER_SEC;
  t=t1;
  return us;
}
void game::play(){
	static long dT=0,dt=0,n_frames=0;
	dt=time();
	dT+=dt;
	n_frames++;
	
	int i=0;
	ball.ppos=ball.pos;
	ball.ptheta=ball.theta;
	
	
	poly2 t;
	t.p.push_back(vec2(0,h));
	for(int i=0;i<terrain.size();i++){
		t.p.push_back(terrain[i]);
	}
	t.p.push_back(vec2(w,h));
	t.c=color(150,100,60);
	t.z=0;
	r->poly(t);
	
	
	if(on_hill){
		static vec2 spos,r1;static float r,theta_max,theta_init;
		if(slope_t==0){
			spos=ball.pos;
			theta_init=ball.theta;
			vec2 r2=terrain[cur_slope+1]-terrain[cur_slope];
			r2.normalize();
			r2.rotate(PI/2);
			r1=spos-terrain[cur_slope];
			r=r1.mag();
			r2=r2*r;			
			theta_max=acos((r1*r2)/(r*r));
		}
		ball.pos=terrain[cur_slope]+r1.rotated(-theta_max*slope_t);
		ball.theta=theta_init-theta_max*slope_t;
		slope_t+=dt*speed/r/theta_max/1.0e6;
		if(slope_t>=1.0)
		{
			on_hill=0;slope_t=0;
		}			
	}else{
		vec2 pos=terrain[cur_slope];
		vec2 slope=terrain[cur_slope+1]-terrain[cur_slope];
		
		pos=pos+slope*slope_t;
		
		 
		slope_t+=speed/slope.mag()*dt/1.0e6;
		
		slope.normalize();
		slope.rotate(PI/2);
		pos=pos+slope*size;
		ball.theta-=speed/size*dt/1.0e6;
		ball.pos=pos;
		
		float min_dist=ball.min_dist(slopes[cur_slope],size);
		float min_dist2=slopes[cur_slope+1].distance(ball.pos);
		ball.pos=pos-slope*min_dist;
		if(min_dist2<=size&&slopes[cur_slope].M()>slopes[cur_slope+1].M()){
			cur_slope++;
			vec2 r=ball.pos-terrain[cur_slope];
			vec2 tangent=(terrain[cur_slope+1]-terrain[cur_slope]);
			float ll=tangent.magSq();
			slope_t=r*tangent/ll;
		}
		if(slope_t>=1.0){
			cur_slope++;
			slope_t=0; 
			if(cur_slope>=slopes.size())
				cur_slope=0;
			else{
				if(slopes[cur_slope].M()>slopes[cur_slope-1].M()){
					slope_t=0;
					on_hill=1;				
				}
			}
		}	
	}
	ball.draw(r);

	for(int k=0;k<trees.size();k++)
	{
		for(int j=0;j<trees[k]->size();j++){
			r->tri((*trees[k])[j]);
		}
	}
	r->render();
	if(dt>MAX_FPS)
		dt=MAX_FPS;
	usleep(MAX_FPS-dt);
	if(dT>10e6){
		cout<<"FPS:"<<(n_frames*1.0e6/dT)<<endl;
		n_frames=dT=0;	
	}
	play();
}
