// Fourier.cpp: implementation of the Fourier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fourier.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
 * fft.cpp
 *
 * loic fonteneau 15-feb-2001
 * Perform discrete FFT
 *
 * Original code : Don Cross <dcross@intersrv.com>
 * http://www.intersrv.com/~dcross/fft.html
 *
 */

#ifndef NULL
#define NULL '\0'
#endif



//////////////////////////////////////////////////////////////////////////////////////
// do the fft for double numbers
//////////////////////////////////////////////////////////////////////////////////////

void fft_double (unsigned int p_nSamples, bool p_bInverseTransform, double *p_lpRealIn, double *p_lpImagIn, double *p_lpRealOut, double *p_lpImagOut)
{

	if(!p_lpRealIn || !p_lpRealOut || !p_lpImagOut) return;


	unsigned int NumBits;
	unsigned int i, j, k, n;
	unsigned int BlockSize, BlockEnd;

	double angle_numerator = 2.0 * PI;
	double tr, ti;

	if( !IsPowerOfTwo(p_nSamples) )
	{
		return;
	}

	if( p_bInverseTransform ) angle_numerator = -angle_numerator;

	NumBits = NumberOfBitsNeeded ( p_nSamples );


	for( i=0; i < p_nSamples; i++ )
	{
		j = ReverseBits ( i, NumBits );
		p_lpRealOut[j] = p_lpRealIn[i];
		p_lpImagOut[j] = (p_lpImagIn == NULL) ? 0.0 : p_lpImagIn[i];
	}


	BlockEnd = 1;
	for( BlockSize = 2; BlockSize <= p_nSamples; BlockSize <<= 1 )
	{
		double delta_angle = angle_numerator / (double)BlockSize;
		double sm2 = sin ( -2 * delta_angle );
		double sm1 = sin ( -delta_angle );
		double cm2 = cos ( -2 * delta_angle );
		double cm1 = cos ( -delta_angle );
		double w = 2 * cm1;
		double ar[3], ai[3];

		for( i=0; i < p_nSamples; i += BlockSize )
		{

			ar[2] = cm2;
			ar[1] = cm1;

			ai[2] = sm2;
			ai[1] = sm1;

			for ( j=i, n=0; n < BlockEnd; j++, n++ )
			{

				ar[0] = w*ar[1] - ar[2];
				ar[2] = ar[1];
				ar[1] = ar[0];

				ai[0] = w*ai[1] - ai[2];
				ai[2] = ai[1];
				ai[1] = ai[0];

				k = j + BlockEnd;
				tr = ar[0]*p_lpRealOut[k] - ai[0]*p_lpImagOut[k];
				ti = ar[0]*p_lpImagOut[k] + ai[0]*p_lpRealOut[k];

				p_lpRealOut[k] = p_lpRealOut[j] - tr;
				p_lpImagOut[k] = p_lpImagOut[j] - ti;

				p_lpRealOut[j] += tr;
				p_lpImagOut[j] += ti;

			}
		}

		BlockEnd = BlockSize;

	}


	if( p_bInverseTransform )
	{
		double denom = (double)p_nSamples;

		for ( i=0; i < p_nSamples; i++ )
		{
			p_lpRealOut[i] /= denom;
			p_lpImagOut[i] /= denom;
		}
	}

}


//////////////////////////////////////////////////////////////////////////////////////
// check is a number is a power of 2
//////////////////////////////////////////////////////////////////////////////////////

bool IsPowerOfTwo( unsigned int p_nX )
{

	if( p_nX < 2 ) return false;

	if( p_nX & (p_nX-1) ) return false;

    return true;

}



//////////////////////////////////////////////////////////////////////////////////////
// return needed bits for fft
//////////////////////////////////////////////////////////////////////////////////////

unsigned int NumberOfBitsNeeded( unsigned int p_nSamples )
{

	int i;

	if( p_nSamples < 2 )
	{
		return 0;
	}

	for ( i=0; ; i++ )
	{
		if( p_nSamples & (1 << i) ) return i;
    }

}



//////////////////////////////////////////////////////////////////////////////////////
// ?
//////////////////////////////////////////////////////////////////////////////////////

unsigned int ReverseBits(unsigned int p_nIndex, unsigned int p_nBits)
{

	unsigned int i, rev;

	for(i=rev=0; i < p_nBits; i++)
	{
		rev = (rev << 1) | (p_nIndex & 1);
		p_nIndex >>= 1;
	}

	return rev;

}



//////////////////////////////////////////////////////////////////////////////////////
// return a frequency from the basefreq and num of samples
//////////////////////////////////////////////////////////////////////////////////////

double Index_to_frequency(unsigned int p_nBaseFreq, unsigned int p_nSamples, unsigned int p_nIndex)
{

	if(p_nIndex >= p_nSamples)
	{
		return 0.0;
	}
	else if(p_nIndex <= p_nSamples/2)
	{
		return ( (double)p_nIndex / (double)p_nSamples * p_nBaseFreq );
	}
	else
	{
		return ( -(double)(p_nSamples-p_nIndex) / (double)p_nSamples * p_nBaseFreq );
	}


}

