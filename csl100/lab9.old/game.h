#ifndef LAB9_GAME
#define LAB9_GAME
#include "physics.h"
#include "renderer.h"
#include <vector>
#define PI (3.14159265)
class game{
	public:
	renderer *r;
	vector< vector<tri2>* > trees;
	vector<vec2> terrain;
	vector<line2> slopes;
	int cur_slope;float slope_t;
	body2 ball;
	float speed;
	int h,w,size,on_hill;
	game(renderer *_r,char *fs){
		r=_r;on_hill=0;
		speed=100;
		h=600;size=60;
		w=800;
		read_file(fs);
		r->init(w,h);
		r->render();
		line2 l;
		cur_slope=slope_t=0;
		int i;
		for(i=0;i<terrain.size()-1;i++)
		{
			l=line2(terrain[i],terrain[i+1]);			
			slopes.push_back(l);
		}
		tri2 t;
		t.c=color(0,200,250);
		t.z=-1000;
		t.p[0]=vec2(0,0);
		t.p[1]=vec2(0,h);
		t.p[2]=vec2(w,h);
		r->tri(t);
		t.p[1]=vec2(w,0);
		r->tri(t);
		
		t.c=color(150,70,10);
		t.z=0;
		for(i=0;i<terrain.size()-1;i++){
			t.p[0]=terrain[i];
			t.p[1]=terrain[i+1];
			t.p[2]=vec2(terrain[i].x,h);
			r->tri(t);
			t.p[0]=terrain[i+1];
			t.p[1]=vec2(terrain[i].x,h);
			t.p[2]=vec2(terrain[i+1].x,h);
			r->tri(t);
		}
	}
	~game(){
		int i;
		for(i=0;i<trees.size();i++)
			delete trees[i];
	}
	long time();
	void read_file(char *fs);
	void play();
};
#endif
