///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2006-2008 Ernest Laurentin (http://www.ernzo.com/)
//
//  This software is provided 'as-is', without any express or implied
//  warranty. In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//
//  File:       FFT.hpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
//  Based on 1998 original version by: Don Cross <dcross@intersrv.com>
///////////////////////////////////////////////////////////////////////////////
#ifndef FFT_HPP
#define FFT_HPP
#include <exception>
#include <math.h>

// Ernzo::DSP
namespace Ernzo { namespace DSP {

static const double DDC_PI = 3.14159265358979323846;

/**
 * FFT class - static implementation only
 * based on 1998 original version by: Don Cross <dcross@intersrv.com>
 */
class FFT
{
public:
    /**
     * Verifies a number is a power of two
     * @param x Number to check
     * @return true if number is a power two (i.e.:1,2,4,8,16,...)
     */
    static bool IsPowerOfTwo ( size_t x )
    {
        return ((x != 0) && (x & (x-1)) == 0);
    }

    /**
     * Get Next power of number.
     * @param x Number to check
     * @return A power of two number
     */
    static size_t NextPowerOfTwo(size_t x)
    {
       x = x - 1;
       x = x | (x >> 1);
       x = x | (x >> 2);
       x = x | (x >> 4);
       x = x | (x >> 8);
       x = x | (x >> 16);
       return x + 1;
    }

    /**
     * Get Number of bits needed for a power of two
     * @param PowerOfTwo Power of two number
     * @return Number of bits
     */
    static size_t NumberOfBitsNeeded( size_t PowerOfTwo )
    {
        if ( PowerOfTwo > 0 )
        {
            for(size_t i = 0; ; i++ )
            {
                if ( PowerOfTwo & (1 << i) )
                    return i;
            }
        }
        return 0; // error
    }

    /**
     * Reverse bits
     * @param index Bits
     * @param NumBits Number of bits to reverse
     * @return Reverse Bits
     */
    static size_t ReverseBits( size_t index, size_t NumBits )
    {
        size_t i, rev;

        for ( i=rev=0; i < NumBits; i++ )
        {
            rev = (rev << 1) | (index & 1);
            index >>= 1;
        }

        return rev;
    }

    /**
     * Return index to frequency based on number of samples
     * @param Index sample index
     * @param NumSamples number of samples
     * @return Frequency index range
     */
    static double IndexToFrequency( size_t Index, size_t NumSamples )
    {
        if ( Index >= NumSamples )
            return 0.0;
        else if ( Index <= NumSamples/2 )
            return (double)Index / (double)NumSamples;

        return -(double)(NumSamples-Index) / (double)NumSamples;
    }

    template<typename T>
    static void Compute(size_t NumSamples, T *pRealIn, T *pImagIn,
                        T *pRealOut, T *pImagOut, bool bInverseTransform = false);

    template<typename T>
    static void Norm(size_t NumSamples, T *pReal, T *pImag, T* pAmpl);

    template<typename T>
    static double PeakFrequency(size_t NumSamples, const T *pAmpl, double samplingRate, size_t& index);
};


/**
 * Compute FFT
 * @param NumSamples Number of samples (must be power two)
 * @param pRealIn Real samples
 * @param pImagIn Imaginary (optional, may be NULL)
 * @param pRealOut Real coefficient output
 * @param pImagOut Imaginary coefficient output
 * @param bInverseTransform when true, compute Inverse FFT
 */
template<typename T>
void FFT::Compute(size_t NumSamples, T *pRealIn, T *pImagIn,
                  T *pRealOut, T *pImagOut, bool bInverseTransform)
{
    size_t NumBits;    /* Number of bits needed to store indices */
    size_t i, j, k, n;
    size_t BlockSize, BlockEnd;

    double angle_numerator = 2.0 * DDC_PI;
    double tr, ti;     /* temp real, temp imaginary */

    if ( !pRealIn || !pRealOut || !pImagOut )
    {
        // error
        throw std::exception("Invalid argument");
    }
    if ( !IsPowerOfTwo(NumSamples) )
    {
        // error
        throw std::exception("Number of samples must be power of 2");
    }

    if ( bInverseTransform )
        angle_numerator = -angle_numerator;

    NumBits = NumberOfBitsNeeded ( NumSamples );

    /*
    **   Do simultaneous data copy and bit-reversal ordering into outputs...
    */
    for ( i=0; i < NumSamples; i++ )
    {
        j = ReverseBits ( i, NumBits );
        pRealOut[j] = pRealIn[i];
        pImagOut[j] = static_cast<T>((pImagIn == NULL) ? 0.0 : pImagIn[i]);
    }

    /*
    **   Do the FFT itself...
    */
    BlockEnd = 1;
    for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
    {
        double delta_angle = angle_numerator / (double)BlockSize;
        double sm2 = sin ( -2 * delta_angle );
        double sm1 = sin ( -delta_angle );
        double cm2 = cos ( -2 * delta_angle );
        double cm1 = cos ( -delta_angle );
        double w = 2 * cm1;
        double ar[3], ai[3];

        for ( i=0; i < NumSamples; i += BlockSize )
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
                tr = ar[0]*pRealOut[k] - ai[0]*pImagOut[k];
                ti = ar[0]*pImagOut[k] + ai[0]*pRealOut[k];

                pRealOut[k] = static_cast<T>( pRealOut[j] - tr);
                pImagOut[k] = static_cast<T>( pImagOut[j] - ti);

                pRealOut[j] += static_cast<T>(tr);
                pImagOut[j] += static_cast<T>(ti);
            }
        }

        BlockEnd = BlockSize;
    }

    /*
    **   Need to normalize if inverse transform...
    */
    if ( bInverseTransform )
    {
        T denom = static_cast<T>(NumSamples);

        for ( i=0; i < NumSamples; i++ )
        {
            pRealOut[i] /= denom;
            pImagOut[i] /= denom;
        }
    }
}

/**
 * Calculate normal (power spectrum)
 * @param NumSamples Number of samples
 * @param pReal Real coefficient buffer
 * @param pImag Imaginary coefficient buffer
 * @param pAmpl Working buffer to hold amplitude Xps(m) = | X(m)^2 | = Xreal(m)^2  + Ximag(m)^2
 */
template<typename T>
void FFT::Norm(size_t NumSamples, T *pReal, T *pImag, T* pAmpl)
{
    if ( !pReal || !pImag || !pAmpl )
    {
        // error
        throw std::exception("Invalid argument");
    }

    // Calculate amplitude values in the buffer provided
    for (size_t i=0; i<NumSamples; i++ )
    {
        pAmpl[i] = pReal[i]*pReal[i] + pImag[i]*pImag[i];
    }
}

/**
 * Find Peak frequency in Hz
 * @param NumSamples Number of samples
 * @param pAmpl Current amplitude
 * @param samplingRate Sampling rate in samples/second (Hz)
 * @param index Frequency index
 * @return Peak frequency in Hz
 */
template<typename T>
double FFT::PeakFrequency(size_t NumSamples, const T *pAmpl, double samplingRate, size_t& index)
{
    const size_t N = NumSamples>>1;   // number of positive frequencies. (numSamples/2)

    if ( !pAmpl )
    {
        // error
        throw std::exception("Invalid argument");
    }

    double maxAmpl = -1.0;
    double peakFreq = -1.0;
    index = 0;

    for ( size_t i = 0; i < N; i++ )
    {
        if ( pAmpl[i] > maxAmpl )
        {
            maxAmpl = pAmpl[i];
            index = i;
            peakFreq = static_cast<double>(i);
        }
    }

    return samplingRate * peakFreq / static_cast<double>(NumSamples);
}


/* End of namespace */
} }

#endif //FFT_HPP