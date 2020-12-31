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

#include "stdafx.h"
#include <math.h>
#include "PlotUtility.h"
#include <commdlg.h>

// Rounds any number to any number. i.e. round 1.9
// to the nearest 0.4 yields 2.0
double	RoundToRange( double value, double range )
{
	double		half = range / 2;
	double		scale = value / range;
	double		mantissa;
	long		exponent;
	int			sign = value>0?1:-1;

	mantissa = scale - (long) scale;
	exponent = (long) scale;

	if( sign > 0 )
	{
		if( fabs( mantissa ) >= 0.5 )
			return range * (exponent + sign);
		else
			return range * exponent;
	}
	else
	{
		if( fabs( mantissa ) > 0.5 )
			return range * (exponent + sign);
		else
			return range * exponent;
	}
}

int				GetMagnitude( double value )
{
	if(value == 0.0)
		return 0;
	else
	{
		return (int)floor(log10(fabs(value)));
	}
}

double			RoundToInt( double value )
{
	if(value == 0)
		return 0.0;
	else if(value > 0)
		return floor(value + 0.5);
	else
		return ceil(value - 0.5);
}

double			Round( double value, int level )
{
	if(value == 0.0)return 0.0;
	int mag = GetMagnitude(value);
	double remain = value * pow(10.0, -mag + level);
	remain = RoundToInt(remain);
	return remain * pow(10.0, mag - level);
}

// This algorithm comes from a paper by Dorothy Pugh (KarlG87710@aol.com)
// "A Robust Generalized Axis-Scaling Macro", presumably from the proceedings
// of the Southeast SAS Users Group Conference and was translated from
// SAS macro langauge to C by yours truly.

void	GetOptimalRange( double *inRange, double *outRange, bool exactRange )
{
	int			nTicks, nMinor;

	GetOptimalRange( inRange, outRange, &nTicks, &nMinor, exactRange );
}

void	GetOptimalRange( double *inRange, double *outRange,
								int *nTicks, int *nMinor, bool exactRange )
{
	double		wasted = 0.8, margin = 0.01;

	if( exactRange == true ) { wasted = 0.9; margin = 0.00; }

	GetOptimalRangePrivate( inRange, outRange, nTicks, nMinor, margin, wasted );
}

void	GetOptimalRangePrivate( double *inRange, double *outRange,
								int *nTicks, int *nMinor, double margin, double wasted )
{
	const double	cutPoint1 = 1.0, cutPoint2 = 1.25, cutPoint3 = sqrt( 10. );
	const int		maxTick = 11, minTick = 3;

	double		mantissa, range, temp, interval, min, max;
	double		oldNew, tickTest, oldMax = inRange[1], oldMin = inRange[0];
	int			rexp, minorTick = 0, flag;
	long		test;

	temp = log10( fabs( inRange[1] - inRange[0] ) );

	mantissa = pow( 10.0, temp - (int)temp );
	rexp = (int) temp;

	// Which cut point regime do we belong in?
	if( mantissa >= cutPoint3 )
	{
		interval = pow( 10.0, rexp );
		minorTick = 9;
	}
	else if( mantissa >= cutPoint2 )
	{
		interval = 0.5 * pow( 10.0, rexp );
		minorTick = 4;
	}
	else
	{
		interval = pow( 10.0, rexp-1 );
		minorTick = 9;
	}
	max = RoundToRange( inRange[1] + (0.5 + margin) * interval, interval );
	min = RoundToRange( inRange[0] - (0.5 + margin) * interval, interval );

	// check tick ranges and axis spacing
	flag = 0;
	range = max - min;
	oldNew = (inRange[1]-inRange[0])/range;
	tickTest = RoundToRange( 1. + (max-min-interval)/(0.5*interval),1. );

	if( oldNew < wasted && tickTest <= maxTick && margin <= 0.01 &&
		oldMax < (max - 0.5*interval) && oldMin > (min + 0.5 * interval) )
	{
		max = max - 0.5 * interval;
		min = min + 0.5 * interval;
		interval = 0.5 * interval;
		flag = 1;
		if( minorTick == 9 ) minorTick = 4;
	}

	// Moderate number of tick marks
	test = (long)RoundToRange( (max - min) / interval, 1. );

	while( test >= maxTick && flag == 0 )
	{
		if( test % 2 != 0 ) max = max + interval;

		interval = 2 * interval;
		test = (long)RoundToRange((max-min)/interval,1.);
		if( minorTick == 4 ) minorTick = 9;
	}

	while( test <= minTick && flag == 0 )
	{
		if( test <= 3 ) interval = 0.5 * interval;

		test = (long)RoundToRange( (max-min) / interval, 1. );
		if( minorTick == 9 ) minorTick = 4;
	}

	// Done!
	outRange[0] = min;
	outRange[1] = max;
	*nTicks = (int)fabs(RoundToRange( (max-min) / interval, 1. ))-1;
	*nMinor = minorTick+1;
}

// This does a silly, but useful check for an optimal tick interval
// given a known range. It tries to find the interval set with
// the least remainder. The order is from my head, and what
// I think works best. There's no other good reason for the order.
double		GetTickOptimalTickInterval( double lower, double upper )
{
	
	double		range = fabs(upper - lower);
	double		error = 1e30, minError = 1e30, logi;

	const int			tries[] = { 7, 6, 8, 4, 9, 5, 10, 3, 2 };
	const int			divTries[] = {5, 4, 3, 8, 6, 7, 2, 9, 10 };

	int			minIndex = 1, i;

	for( i = 0; i < 9; i++ )
	{
		// Take log base i of range
		logi = log( range ) / log( (double)tries[i] );

		// See how its error compares to others
		error = fabs(logi - (long) logi);

		if( error < minError )
		{
			minError = error;
			minIndex = tries[i];
		}

		error = fabs(range / divTries[i] - RoundToRange(range / divTries[i], 1.));

		if( error < minError )
		{
			minError = error;
			minIndex = divTries[i];
		}
	}

	return range / (double)minIndex;
}

// Simply gets the number of tick marks, major and minor, given
// the exact specified range
void	GetOptimalRangeExact( double *inRange, double *outRange,
								int *nTicks, int *nMinor )
{
	double		temp, tempRange;

	temp = GetTickOptimalTickInterval( inRange[0], inRange[1] );
	*nTicks = (int)fabs(RoundToRange((inRange[1] - inRange[0]) / temp, 1. )) - 1;

	tempRange = temp;
	temp = GetTickOptimalTickInterval( inRange[0], inRange[0] + temp );
	*nMinor = (int)fabs(RoundToRange( tempRange / temp, 1. ));

	// Done!
	outRange[0] = inRange[0];
	outRange[1] = inRange[1];
}
