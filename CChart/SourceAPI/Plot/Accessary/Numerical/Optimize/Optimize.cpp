#include "StdAfx.h"
#include "Optimize.h"

void FindMin2D(void (*objfun)(double *, double &), double *xlb, double *xub, double *x, double &y)
{
	double val;
	
	int i,j;
	double gap1,gap2,dx1,dx2;
	gap1=xub[0]-xlb[0];
	gap2=xub[1]-xlb[1];
	dx1=gap1/1000;
	dx2=gap2/1000;
	
	double xv[2];
	xv[0]=xlb[0];
	xv[1]=xlb[1];
	objfun(xv,y);
	for(i=0; i<1000; i++)
	{
		xv[0]=xlb[0]+i*dx1;
		for(j=0; j<1000; j++)
		{
			xv[1]=xlb[1]+j*dx2;
			objfun(xv,val);
			if(val < y)
			{
				x[0]=xv[0];
				x[1]=xv[1];
				y=val;
			}

			if(gap2==0.0)break;
		}
		if(gap1==0.0)break;
	}
}