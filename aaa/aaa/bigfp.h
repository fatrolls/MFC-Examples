/*
  Module:  BIGFP.H

  Author:  William A. Rossi
           175 Burnt Hill Rd
           Hope, RI 02831

           bill@rossi.com

  Version: 1.0

  Release Date: 31-AUG-1995

  Description:  BIGFP is a floating point math class based on BIGINT
                for the C++ programming language.

  *********************************************************************

  The code contained in this file is in the public domain. Specifically,
  I give to the public domain all rights for future licensing of the
  source code, all resale rights, and all publishing rights.

  If you find this code useful, or have any comments I can be reached by
  email and snail mail at the above addresses.

  Disclaimer of Warranty

  THIS PACKAGE IS RELEASED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
  EXPRESSES OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
  YOU ASSUME THE ENTIRE RISK OF USING THE PROGRAM AND THE COST OF ALL
  NECESSARY SERVICING, REPAIR OR CORRECTION.

  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
  WILL THE AUTHOR BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
  GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF
  THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
  TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED
  BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH
  ANY OTHER PROGRAMS), EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGES.

*/
#ifndef BIGFP_DEFINITONS_INCLUDED
#define BIGFP_DEFINITONS_INCLUDED

#include "bigint.h"

//typedef signed char BIGFP_EXP;
//#define BIGFP_MAX_EXP 127
//#define BIGFP_MIN_EXP -128

typedef signed short BIGFP_EXP;
#define BIGFP_MAX_EXP 32767
#define BIGFP_MIN_EXP -32768

#define BIGFP_RADIX 10

#if defined(MULTI_THREAD)
#define BIGFP_TEMPORARY
#else
#define BIGFP_TEMPORARY static
#endif

class bigfp
{
 private:

  public:
    bigint Mant;
    BIGFP_EXP Exp;
    signed char Sign; // Sign of number -- takes on values of +/- 1
    static int MaxDigits;
    static int HalfDigits;

    int SignificantDigits();
    bigint PowerR(int n);
    void Normalize();
    void DeNormalize();
    void Align(bigfp *p, bigfp *q);
    void HalfPrecision();
    void MultAdjust(bigfp *p, bigfp *q);

    bigfp operator+(const bigfp& a);
    bigfp operator-(const bigfp& a);
    bigfp operator*(const bigfp& a);
    bigfp operator/(const bigfp& a);
    int operator<=(bigfp& q);
    int operator>=(bigfp& q);
    int operator<(bigfp& a);
    int operator>(bigfp& a);
    int operator!=(bigfp& q);
    int operator==(bigfp& q);

    bigfp sqrt();
    bigfp sine();
    bigfp cosine();
    bigfp tangent();

    bigfp ascii2bigfp(char *fpdecimal);
    void bigfp2ascii(char *fpdecimal);

    bigfp();
};
#endif
