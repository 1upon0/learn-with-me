#ifndef LAB9_PHYSICS
#define LAB9_PHYSICS
#include <vector>
#include <X11/Xlib.h>
using namespace std;
class vec2{
	public:
	float x,y;
	vec2(XPoint p){
		x=p.x;y=p.y;
	}
	vec2(float a=0,float b=0);
	const float magSq();
	const float mag();
	const vec2 normalized();
	vec2 normalize();
	//vec2 scale(float 
	const float operator * (const vec2 &b);
	const vec2 operator * (const float &b);
	const vec2 operator + (const vec2 &b);
	const vec2 operator - (const vec2 &b);
	const vec2 operator - ();
	operator XPoint();
	vec2 rotated(float t);
	vec2 rotate(float t);
};
class line2{
	public:
	float a,b,c;
	line2(float _a=1,float _b=1,float _c=0);
	line2(vec2 A,vec2 B);
	line2(float m,float _c);
	const float M();
	const float C();
	float signedDistance(vec2 p);
	float distance(vec2 p);
};
struct color{
	int r,g,b;
	color(int R=0,int G=0,int B=0);
	operator XColor ();
};
struct tri2{
	vec2 p[3];
	XColor c;
	int z;
	tri2();
	tri2(vec2 _a,vec2 _b,vec2 _c,int Z=0);
	tri2(vec2 _a,vec2 _b,vec2 _c,XColor C,int Z=0);
};
struct poly2{
	vector<vec2> p;
	XColor c;
	int z;
	poly2(){
		z=0;c=color(128,128,128);
	}
};
class renderer;
class body2{
	public:
	vec2 pos,vel,acc,ppos;
	float theta,omega,alpha,ptheta;
	vector<tri2> tris;
	
	void update(float dt);
	void load_hexagon(int size);
	float min_dist(line2 l,float size);
	void draw(renderer *r);
};
#endif
