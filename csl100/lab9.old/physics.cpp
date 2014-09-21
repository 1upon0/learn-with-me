#include "physics.h"
#include "renderer.h"
#include <math.h>

vec2::vec2(float a,float b){
	x=a;y=b;
}
const float vec2::magSq(){
	return x*x+y*y;
}
const float vec2::mag(){
	return sqrt(x*x+y*y);
}
const vec2 vec2::normalized(){
	float t=mag();t=1.f/t;
	return vec2(x*t,y*t);
}
vec2 vec2::normalize(){
	float t=mag();t=1.f/t;
	x*=t;
	y*=t;
	return *this;
}
const float vec2::operator * (const vec2 &b){
	return x*b.x+y*b.y;
}
const vec2 vec2::operator * (const float &b){
	return vec2(x*b,y*b);
}
const vec2 vec2::operator + (const vec2 &b){
	return vec2(x+b.x,y+b.y);
}
const vec2 vec2::operator - (const vec2 &b){
	return vec2(x-b.x,y-b.y);
}
const vec2 vec2::operator - (){
	return vec2(-x,-y);
}
vec2::operator XPoint(){
	XPoint pt;pt.x=x;pt.y=y;
	return pt;
}
vec2 vec2::rotated(float t){
	float c=cos(t),s=sin(t);
	return vec2(x*c+y*s,-x*s+y*c);
}
vec2 vec2::rotate(float t){
	float c=cos(t),s=sin(t);
	float x1;
	x1=x*c+y*s;
	y=-x*s+y*c;
	x=x1;
}



line2::line2(float _a,float _b,float _c){
	a=_a;
	b=_b;c=_c;
}
line2::line2(vec2 A,vec2 B){
	//0=-(y-y0)(x0-x1)+(x-x0)(y0-y1);
	a=(B.y-A.y);
	b=-(B.x-A.x);
	c=B.y*(B.x-A.x)-B.x*(B.y-A.y);
}
line2::line2(float m,float _c){
	//mx-y+c=0;
	a=m;
	b=-1;
	c=_c;
}
const float line2::M(){
	return -a/b;
}
const float line2::C(){
	return -c/b;
}
float line2::signedDistance(vec2 p){
	float d=(p.x*a+p.y*b+c)/sqrt(a*a+b*b);
	return d;
}
float line2::distance(vec2 p){
	float d=(p.x*a+p.y*b+c)/sqrt(a*a+b*b);
	return d>0?d:-d;
}


color::color(int R,int G,int B){
	r=R,g=G,b=B;
}
color::operator XColor (){
	XColor c;
	c.red = r*255; c.green = g*256; c.blue = b*256;
	c.flags = DoRed | DoGreen | DoBlue;
	return c;
}



tri2::tri2(){
	z=0;
	c=color(128,128,128);
}
tri2::tri2(vec2 _a,vec2 _b,vec2 _c,int Z){
	z=Z;
	c=color(128,128,128);
	p[0]=_a;
	p[1]=_b;
	p[2]=_c;
} 
tri2::tri2(vec2 _a,vec2 _b,vec2 _c,XColor C,int Z){
	z=Z;
	c=C;
	p[0]=_a;
	p[1]=_b;
	p[2]=_c;
}



void body2::update(float dt){
	ppos=pos;
	ptheta=theta;
	
	vel=vel+acc*dt;
	pos=pos+vel*dt;
	
	omega=omega+alpha*dt;
	theta=theta+omega*dt;
}
void body2::load_hexagon(int size){
	vec2 hex[6]={
		vec2(-size,0),
		vec2(size*-0.5,size*0.866),
		vec2(size*0.5,size*0.866),
		vec2(size,0),
		vec2(size*0.5,size*-0.866),
		vec2(size*-0.5,size*-0.866)
	};
	vec2 o(0,0);
	tris.push_back(tri2(hex[0],hex[1],o,color(200,0,0),1));
	tris.push_back(tri2(hex[1],hex[2],o,color(100,100,0),1));
	tris.push_back(tri2(hex[2],hex[3],o,color(0,200,0),1));
	tris.push_back(tri2(hex[4],hex[5],o,color(0,100,100),1));
	tris.push_back(tri2(hex[5],hex[0],o,color(0,0,200),1));
	tris.push_back(tri2(hex[3],hex[4],o,color(100,0,100),1));
}
float body2::min_dist(line2 l,float size){
	vec2 hex[6]={
		vec2(-size,0),
		vec2(size*-0.5,size*0.866),
		vec2(size*0.5,size*0.866),
		vec2(size,0),
		vec2(size*0.5,size*-0.866),
		vec2(size*-0.5,size*-0.866)
	};
	float min=10000,d;
	for(int i=0;i<6;i++){
		hex[i].rotate(theta);
		d=l.distance(hex[i]+pos);
		if(d<min)
			min=d;
	}
	return min;
}
void body2::draw(renderer *r){
	r->translate(pos);
	r->rotate(theta);
	for(int i=0;i<tris.size();i++){
		r->tri(tris[i]);
	}
	r->translate();
	r->rotate();
}
