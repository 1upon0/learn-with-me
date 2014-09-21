#include<X11/Xlib.h>  // preceede most other headers!
#include <unistd.h>

int main(){

  Display *dsp = XOpenDisplay( NULL );

  if( !dsp ){ return 1; }


  int screenNumber = DefaultScreen(dsp);
  unsigned long white = WhitePixel(dsp,screenNumber);
  unsigned long black = BlackPixel(dsp,screenNumber);
  Colormap thecolormap;
  XColor xcolourpoly;
  XColor xcolourrec;
  XColor xcolourcir;
  Window win = XCreateSimpleWindow(dsp,
                               DefaultRootWindow(dsp),
                               0, 0,   // origin
                               400, 400, // size
                               0, white, // border
                               white );  // backgd
  thecolormap = DefaultColormap(dsp,screenNumber);

  XMapWindow( dsp, win );


  long eventMask = StructureNotifyMask;
  XSelectInput( dsp, win, eventMask );

  XEvent evt;
  do{
    XNextEvent( dsp, &evt );   // calls XFlush
  }while( evt.type != MapNotify );


  GC gc = XCreateGC( dsp, win,
                     0,        // mask of values
                     NULL );   // array of values
  XSetForeground( dsp, gc, black );


//  XDrawLine(dsp, win, gc, 10, 10,390,390); //from-to
//  XDrawLine(dsp, win, gc, 10,390,390, 10); //from-to
   int xpos_rec = 100;
   int ypos_rec = 100;

   /* Draw a red filled polygon with a black border */
   XPoint v[5];
   v[0].x = 0; v[0].y = 400;
   v[1].x = 150; v[1].y = 250;
   v[2].x = 250; v[2].y = 250;
   v[3].x = 300; v[3].y = 150;
   v[4].x = 450; v[4].y = 400;
   xcolourpoly.red = 65535; xcolourpoly.green = 10000; xcolourpoly.blue = 10000;
   xcolourpoly.flags = DoRed | DoGreen | DoBlue;
   XAllocColor(dsp,thecolormap,&xcolourpoly);
   XSetForeground(dsp,gc,xcolourpoly.pixel);
   XFillPolygon(dsp,win,gc,v,5,Complex,CoordModeOrigin);
   XSetForeground(dsp,gc,black);
   int i;
   for (i=0;i<5;i++) {
   	XDrawLine(dsp,win,gc,
       		v[i].x,v[i].y,v[(i+1)%5].x,v[(i+1)%5].y);
   }
   XFlush(dsp);
   
   //Setting color properties for the rectangle
   xcolourrec.red = 32000; xcolourrec.green = 65000; xcolourrec.blue = 32000;
   xcolourrec.flags = DoRed | DoGreen | DoBlue;
   XAllocColor(dsp,thecolormap,&xcolourrec);
   
   //Setting color properties for the rectangle
   xcolourcir.red = 32000; xcolourcir.green = 32000; xcolourcir.blue = 65000;
   xcolourcir.flags = DoRed | DoGreen | DoBlue;
   XAllocColor(dsp,thecolormap,&xcolourcir);
   	
   while(1) {
   
	//Clearing the previous circle and rectangle
	//XClearArea(dsp, win, xpos_rec, ypos_rec, 50, 50, 0);
	XSetForeground(dsp,gc,white);
	XFillRectangle(dsp,win,gc,xpos_rec,100,50,50);
	XFillArc( dsp, win,gc, xpos_rec ,50, 20 * 2, 20 * 2, 0, 360 * 64 );

	//Drawing the rectangle
	xpos_rec = (xpos_rec+1)%400;
	XSetForeground(dsp,gc,xcolourrec.pixel);
   	XFillRectangle(dsp,win,gc,xpos_rec,100,50,50);

	//Drawing the circle
	XSetForeground(dsp,gc,xcolourcir.pixel);
	XFillArc( dsp, win,gc, xpos_rec ,50, 20 * 2, 20 * 2, 0, 360 * 64 );

	XFlush(dsp);
	usleep(10000);
  }


  /*eventMask = ButtonPressMask|ButtonReleaseMask;
  XSelectInput(dsp,win,eventMask); // override prev
 
  do{
    XNextEvent( dsp, &evt );   // calls XFlush()
  }while( evt.type != ButtonRelease );
  */

  XDestroyWindow( dsp, win );
  XCloseDisplay( dsp );
	
  return 0;
}
