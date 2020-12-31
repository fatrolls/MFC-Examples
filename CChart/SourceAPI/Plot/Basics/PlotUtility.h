/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2011 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */

#ifndef __PLOTUTILITY_H_122333444455555__
#define __PLOTUTILITY_H_122333444455555__

double			RoundToRange( double value, double range );
int				GetMagnitude( double value );
double			RoundToInt( double value );
double			Round( double value, int level );

void			GetOptimalRange( double *inRange, double *outRange, bool exactRange);
void			GetOptimalRange( double *inRange, double *outRange,	int *nTicks, int *nMinor, bool exactRange );
void			GetOptimalRangePrivate( double *inRange, double *outRange,	int *nTicks, int *nMinor, double margin, double wasted );
void			GetOptimalRangeExact( double *inRange, double *outRange,int *nTicks, int *nMinor );
double			GetTickOptimalTickInterval( double lower, double upper );

#endif