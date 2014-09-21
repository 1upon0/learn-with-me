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
		line2 l;int i;
		cur_slope=slope_t=0;
		for(i=0;i<terrain.size()-1;i++)
		{
			l=line2(terrain[i],terrain[i+1]);			
			slopes.push_back(l);
		}		
		poly2 t;
		t.c=color(0,200,250);
		t.z=-1000;
		t.p.push_back(vec2(0,0));
		t.p.push_back(vec2(w,0));
		t.p.push_back(vec2(w,h));
		t.p.push_back(vec2(0,h));
		r->poly(t);
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
