#ifndef LAB9_RENDERER
#define LAB9_RENDERER
#include "physics.h"
#include <X11/Xlib.h>
#include <unistd.h>
#include <vector>
using namespace std;
class renderer{
public:
	vector<tri2> tris;
	float theta,Scale;vec2 origin;
	Display *dsp;Window win;GC gc;Colormap colormap;
	renderer();
	~renderer();
	void init(int h=600,int w=800);
	void scale(float c=1.f);
	void translate(vec2 o=vec2(0,0));
	void rotate(float t=0);
	void tri(tri2 t);
	void poly(vector<vec2> *p,XColor c,int z=0);
	void render();
};
#endif
