#include "windows.h"
#include <GL/GL.h>
#include <GL/GLU.h>
void MidpointLine(int x0,int y0,int x1,int y1)
{
	int a, b, delta1, delta2, d,x, y;
	a=y0-y1;  b=x1-x0;
	d=2*a+b; 	
	delta1=2*a; 
	delta2=2*(a+b); 	
	x=x0;  y=y0;
	glBegin(GL_POINTS);
	glVertex2s(x,y); 
	glEnd();

	while(x<x1){
		if(d<0){
			x++; y++; d += delta2;
		}else{
			x++;  d += delta1;
		}
		glBegin(GL_POINTS);
		glVertex2s(x,y); 
		glEnd();
	} //End While
} //End MidpointLine 		

void Bresenham(Screen &s,
			   unsigned x1, unsigned y1,
			   unsigned x2, unsigned y2)
{
	int dx  = x2 - x1,
		dy  = y2 - y1,
		y   = y1,
		eps = 0;

	for ( int x = x1; x <= x2; x++ )  {
		gl_Point(x,y);
		eps += dy;
		if ( (eps << 1) >= dx )  {
			y++;  eps -= dx;
		}
	}
}


float x1, xr, yt, yb;
unsigned char code(float x, float y)
{
	unsigned char c = 0;
	if (x < xl)  c = c|1;
	else if (x > xr)  c = c|2;
	if (y < yb)  c = c|4;
	else if (y > yt)  c = c|8;
	return c;
}

void clip(float x0, float y0, float x2, float y2)
{
	unsigned char c1, c2, c;
	float x, y, wx, wy;
	c1 = code(x0, y0);
	c2 = code(x2, y2);
	while ((!(c1 == 0)) || (!(c2 == 0))) {
		if ((c1& c2)) return;
		c = c1;
		if (c == 0)  c = c2;
		wx=x2-x0;  wy=y2-y0;
		if ((c & 1) == 1) {
			y = y0 + wy * (xl - x0) /wx;
			x = xl;
		}
		else if ((c & 2) == 2)  {
			y = y0 +wy * (xr - x0) /wx;
			x = xr;
		}
		else if ((c & 4) == 4) {
			x = x0 +wx * (yb - y0) /wy;
			y = yb;
		}
		else if ((c & 8) == 8)  {
			x = x0 +wx * (yt - y0) / wy;
			y = yt;
		}
		if (c == c1)  {
			x0 = x; 
			y0 = y;
			c1 = code(x0, y0);
		}
		else  {
			x2 = x;  
			y2 = y;
			c2 = code(x2, y2);
		}
	}// While()
	glLine(int(x0), int(y0), int(x2), int(y2));
}

double ts,te;
int Cyrus_Beck (int k,double A[][2],
				double N[][2],double x[2],
				double y[2],double *ts,double *te)
{
	int i,j;
	double t,dn,nw,D[2],W[2];
	*ts=0;*te=1;
	for(i=0;i<k;i++) 	
	{
		dn=N[i][0]*(x[1]- x[0])
			+N[i][1]* (y[1]-y[0]);
		nw=N[i][0]* (x[0]-A[i][0])
			+N[i][1]* (y[0]- A[i][1]);

		if(fabs(dn)<1.0e-6)
		{   if(nw<0)   return 0; }
		else  {
			t=-nw/dn;
			if(dn<0)  {
				if(t< *te)
					*te=t;
			}
			else 
				if(t> *ts)	
					*ts=t;
		}
		if(*ts>*te)	
			return 0;
	}
	return 1;
}
double ts,te;double xL,xR,yB,yT;
bool visible=false;
void Liang_Barsky (double x[2],
				   double y[2],double *ts,double *te) 
{  
	double dx,dy;
	visible=false;
	dx=x[1]-x[0];  dy= y[1]-y[0];
	*ts=0; *te=1;
	if(clipt(-dx,x[0]-xL,ts,te))
		if(clipt(dx,xR-x[0],ts,te))
			if(clipt(-dy,y[0]-yB,ts,te))
				if(clipt(dy,yT-y[0],ts,te)) 
					visible=true;
}

bool clipt (double r,double s,double * ts,double *te) 
{   
	double t;
	if(r<0)  {	t=s/r;
	if(t>* te)  {return false;}
	else  if(t>* ts)  { *ts=t;}
	}
	else  
		if(r>0) {
			t=s/r;
			if(t<*ts)   {return false;}
			else   if(t<* te)  { *te=t;}
		}
		else  if(s<0)     {return false;}
		return true;
} 
