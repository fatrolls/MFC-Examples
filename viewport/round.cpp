#include "stdafx.h"
#include "round.h"

/****************************************************************************
*                                    roundUp
* Inputs:
*       int n: value to round
*       int delta: value to round to
* Result: int
*       
* Effect: 
*       The integer i where i % delta == 0 and i >= n
*       same sign as n
* Examples:
*       -150    50      -150
*       -151    50      -200
*       150     50      150
*       151     50      200
****************************************************************************/

int roundUp(int n, int delta)
    {
     ASSERT(delta > 0);
     delta = abs(delta);
     return ((n + (delta - 1)) / delta) * delta;
    } // roundUp

/****************************************************************************
*                                    roundDown
* Inputs:
*       int n: value to round
*       int delta: value to round to
* Result: int
*       
* Effect: 
*       The integer i where i % delta == 0 such that i <= n
*       same sign as n
* Examples:
*       -150    50      -150
*       -175    50      -200
*       150     50      150
*       175     50      150
****************************************************************************/

int roundDown(int n, int delta)
    {
     ASSERT(delta > 0);
     delta = abs(delta);
     if(n <= 0)
        return (((n - (delta - 1)) / delta) * delta);
     else
        return ((((n + (delta - 1)) / delta) - 1) * delta);
    } // roundDown


/****************************************************************************
*                                    span
* Inputs:
*       long & start: starting value
*       long & end: ending value
*       int delta: rounding interval
* Result: void
*       
* Effect: 
*      Computes the updated start/end pair expanded to span the region
****************************************************************************/

void span(long & start, long & end, int delta)
    {
     if(start > end)
        { /* RU<---...--->RD */
         start = roundUp(start, delta);
         end = roundDown(end, delta);
        } /* RU<---...--->RD */
     else
        { /* RD<---...--->RU */
         start = roundDown(start, delta);
         end = roundUp(end, delta);
        } /* RD<---...--->RU */
     } // span
