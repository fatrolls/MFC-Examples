#include "stdafx.h"
#include "geometry.h"
#include <math.h>


/****************************************************************************
*                                    Diagonal
* Inputs:
*       int & length: Current length
*       CPoint pt: Desired point
* Result: void
*       
* Effect: 
*       If distance( CPoint(0,0), pt) > length, set length to the new distance
****************************************************************************/

void MaxDiagonal(int & length, CPoint start, CPoint pt)
    {
     int n = distance(start, pt);
     if(abs(n) > length)
        length = abs(n);
    } // MaxDiagonal

/****************************************************************************
*                                    distance
* Inputs:
*       CPoint start: Starting point
*       CPoint end: Ending point
* Result: int
*       The distance between the two points
****************************************************************************/

int distance(CPoint start, CPoint end)
    {
     CSize sz = start - end;
     double d = sqrt((double)(sz.cx * sz.cx) + (double)(sz.cy * sz.cy));
     return (int)(d + 0.5);
    } // distance
