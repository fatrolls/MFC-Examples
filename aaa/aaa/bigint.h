/*
  Module:  BIGINT.H

  Author:  William A. Rossi
           175 Burnt Hill Rd
           Hope, RI 02831

           bill@rossi.com

  Version: 1.0

  Release Date: 31-AUG-1995

  Description:  BIGINT is an unsigned N-bit integer math class for the
                C++ programming language.

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
#ifndef BIGINT_DEFINITIONS_INCLUDED
#define BIGINT_DEFINITIONS_INCLUDED
#include <stdlib.h>
#include <string.h>
#ifdef __BORLANDC__
#include <mem.h>
#endif

/*************** BIGINT user defines ***************************/

#define BIGINT_TOTAL_BITS 128    // Produces 38   decimal digits
//#define BIGINT_TOTAL_BITS 256    // Produces 77   decimal digits
//#define BIGINT_TOTAL_BITS 4096   // Produces 1000 decimal digits
//#define BIGINT_TOTAL_BITS 8192   // Produces 2000 decimal digits
//#define BIGINT_TOTAL_BITS 16384  // Produces 4000 decimal digits
//#define BIGINT_TOTAL_BITS 32768  // Produces 8000 decimal digits
//#define BIGINT_TOTAL_BITS 65536  // Produces 18000 decimal digits


/**************** Begin BIGINT definitions *********************/

#define BIGINT_BASE_BITS 32         // Number of bits in base type
#define BIGINTSIZE (BIGINT_TOTAL_BITS / BIGINT_BASE_BITS)
#define BIGINT_BASE_MAX 0xFFFFFFFF  // Maximum value of base type
typedef unsigned long BIGINT_BASE;  // The base type.

/* Store temporaries as static unless required to be re-enerant */

#if defined(MULTI_THREAD)
#define BIGINT_TEMPORARY
#else
#define BIGINT_TEMPORARY static
#endif

class bigint
{
 private:

  /* Useful constants */
  static bigint zero, one, two;
 public:
  BIGINT_BASE data[BIGINTSIZE];  /* Little endian data */

  /* Constructors and conversion operators */

  inline bigint(BIGINT_BASE q);
  inline bigint();
  inline operator BIGINT_BASE();

  /* General purpose mathematical methods */

  bigint operator*(bigint q);
//  bigint& bigint::operator*=(bigint q);
  inline bigint operator/(const bigint& q);
  inline bigint operator%(const bigint& q);
  bigint Divide(bigint dividend, bigint divisor, bigint *remainder);
  bigint operator+(const bigint& q);
  bigint& operator++(int); // Post increment operator
  bigint& operator++();    // Pre increment operator
  bigint& operator+=(const bigint& q);
  bigint operator-(const bigint& q);
  bigint operator-();
  bigint& operator--(int); // Post decrement operator
  bigint& operator--();    // Pre decrement operator
  bigint& operator-=(const bigint& q);
  bigint sqrt();

  /* Bitwise boolean operators */

  bigint operator&(const bigint& q);
  bigint operator|(const bigint& q);
  bigint operator^(const bigint& q);
  bigint& operator&=(const bigint& q);
  bigint& operator|=(const bigint& q);
  bigint& operator^=(const bigint& q);
  bigint operator~();
  bigint operator>>(int shift);
  bigint operator<<(int shift);
  bigint& operator>>=(int shift);
  bigint& operator<<=(int shift);

  /* Comparison operators */

  inline int operator==(const bigint& q);
  inline int operator!=(const bigint& q);
  int operator<(const bigint& q);
  int operator>(const bigint& q);
  int operator<=(const bigint& q);
  int operator>=(const bigint& q);
};

/****** Inline functions ********/

/* the following constructor converts the base type, BIGINT_BASE, to
   a bigint */

bigint::bigint(BIGINT_BASE q)
{
  memset(data, 0, BIGINTSIZE * sizeof(BIGINT_BASE));
  data[0] = q;
}

/* This is the default constructor which makes the useful constants
   zero, one, and two the first time it is called.  These are used by
   several methods, and are never modified */

bigint::bigint()
{
  static char once = 0;
  if (!once)
  {
    once++;
    zero = (bigint) 0;
    one = (bigint) 1;
    two = (bigint) 2;
  }
}

/* This operator converts a bigint back to a base type.  It only works
   properly if the bigint is less than BIGINT_BASE_MAX, and it is up
   to the user to ensure that this condition is met */

bigint::operator BIGINT_BASE()
{
  return data[0];
}

/* operator/ and operator% simply wrap calls to the member function
   Divide().  */

bigint bigint::operator/(const bigint& q)
{
  return Divide(*this, q, NULL);
}

bigint bigint::operator%(const bigint& q)
{
  bigint Result;

  Divide(*this, q, &Result);

  return Result;
}

/* operator== and operator!= wrap calls to memcmp, the idea being that
   if two bigints have the same data, then they are equal */

int bigint::operator==(const bigint& q)
{
  return (memcmp(data, q.data, BIGINTSIZE * sizeof(BIGINT_BASE)) == 0);
}

int bigint::operator!=(const bigint& q)
{
  return (memcmp(data, q.data, BIGINTSIZE * sizeof(BIGINT_BASE)) != 0);
}

/*************************************************************/
/**************** End BIGINT definitions *********************/
/*************************************************************/
#endif
