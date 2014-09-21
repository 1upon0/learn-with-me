#include "renderer.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
renderer::renderer(){
	dsp=0;
	win=0;
	gc=0;
}
void renderer::init(int w,int h){
	dsp=XOpenDisplay( NULL );
	if( !dsp ){ std::cout<<"ERROR: could not open display\n";
	return; }
	int screenNumber = DefaultScreen(dsp);
	unsigned long white = WhitePixel(dsp,screenNumber);
	unsigned long black = BlackPixel(dsp,screenNumber);
	
	win = XCreateSimpleWindow(dsp,
							   DefaultRootWindow(dsp),
							   0, 0,   // origin
							   w,h, // size
							   0, black, // border
							   white );  // backgd
	colormap = DefaultColormap(dsp,screenNumber);

	XMapWindow( dsp, win );


	long eventMask = StructureNotifyMask;
	XSelectInput( dsp, win, eventMask );

	XEvent evt;
	do{
	XNextEvent( dsp, &evt );   // calls XFlush
	}while( evt.type != MapNotify );


	gc = XCreateGC( dsp, win,
					 0,        // mask of values
					 NULL );   // array of values
//	XSetForeground( dsp, gc, black );
	Scale=1;origin=vec2(0,0);
	theta=0;
}
renderer::~renderer(){
	if(dsp){
		if(win)
			XDestroyWindow( dsp, win );
		XCloseDisplay( dsp );
	}
}
void renderer::scale(float c){
	Scale=c;
}
void renderer::translate(vec2 o){
	origin=o;
}
void renderer::rotate(float t){
	theta=t;
}
void renderer::tri(tri2 t)
{
	poly2 p;
	t.p[0].rotate(theta);
	t.p[1].rotate(theta);
	t.p[2].rotate(theta);
	t.p[0]=t.p[0]+origin;
	t.p[1]=t.p[1]+origin;
	t.p[2]=t.p[2]+origin;
	p.p.push_back(t.p[0]);
	p.p.push_back(t.p[1]);
	p.p.push_back(t.p[2]);
	p.z=t.z;
	p.c=t.c;
	polys.push_back(p);
}
void renderer::poly(vector<vec2> *p,XColor c,int z)
{
	poly2 po;
	po.c=c;po.z=z;
	for(int i=0;i<p->size();i++)
		po.p.push_back((*p)[i]);
	polys.push_back(po);
}
void renderer::poly(const poly2 &p)
{
	polys.push_back(p);
}
int polys_comp(const poly2 &a,const poly2 &b){
	return a.z>b.z;//descending order, as we draw from the back.
}
void renderer::render(){
	
	//TODO: Sort!
	sort(polys.begin(),polys.end(),polys_comp);
	XPoint *p=0;int i,n=0;	poly2 t;
	while(!polys.empty())
	{
		t=polys.back();
		polys.pop_back();
		if(n<t.p.size()){
			if(p)
				delete p;
			n=t.p.size();
			p=new XPoint[n];
		}
		for(i=0;i<t.p.size();i++)
			p[i]=t.p[i];
		XAllocColor(dsp,colormap,&(t.c));
		XSetForeground(dsp,gc,t.c.pixel);
		XFillPolygon(dsp,win,gc,p,t.p.size(),Complex,CoordModeOrigin);
	}
	delete p;
	XFlush(dsp);
}
