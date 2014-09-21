#include "renderer.h"
#include <iostream>
#include <algorithm>
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
							   10, black, // border
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
	t.p[0].rotate(theta);
	t.p[1].rotate(theta);
	t.p[2].rotate(theta);
	t.p[0]=t.p[0]+origin;
	t.p[1]=t.p[1]+origin;
	t.p[2]=t.p[2]+origin;
	tris.push_back(t);
}
void renderer::poly(vector<vec2> *p,XColor c,int z)
{
	tri2 t;
	for(int i=2;i<p->size();i++){
		t=tri2((*p)[i-2],(*p)[i-1],(*p)[i],c,z);
		t.p[0].rotate(theta);
		t.p[1].rotate(theta);
		t.p[2].rotate(theta);
		t.p[0]=t.p[0]+origin;
		t.p[1]=t.p[1]+origin;
		t.p[2]=t.p[2]+origin;
		tris.push_back(t);
	}
}
int tris_comp(const tri2 &a,const tri2 &b){
	return a.z>b.z;//descending order, as we draw from the back.
}
void renderer::render(){
	
	//TODO: Sort!
	sort(tris.begin(),tris.end(),tris_comp);
	XPoint p[3];tri2 t;
	
	while(!tris.empty())
	{
		t=tris.back();
		tris.pop_back();
		XAllocColor(dsp,colormap,&(t.c));
		XSetForeground(dsp,gc,t.c.pixel);
		p[0]=t.p[0];
		p[1]=t.p[1];
		p[2]=t.p[2];
		XFillPolygon(dsp,win,gc,p,3,Convex,CoordModeOrigin);
	}
	XFlush(dsp);
}
