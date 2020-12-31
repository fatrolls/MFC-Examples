/*
  Module:  TSTBGINT.CPP

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
#include <cstdio>//.h
#include <time.h>
#include "bigint.h"

void TestDivisibility(const bigint& q)
{
  int i;
  long sum = 0;

  for (i=0; i<BIGINTSIZE; i++)
  {
    sum += ((q.data[i]) & 0xf);
    sum += ((q.data[i]>>4) & 0xf);
    sum += ((q.data[i]>>8) & 0xf);
    sum += ((q.data[i]>>12) & 0xf);
  }
  if (sum%5 || q.data[0] & 1)
    printf("Failed Divisibilty test sum = %X, data[0] = %X\n", sum, q.data[0]);
  else
    printf("Passed Divisibilty test sum = %X, data[0] = %X\n", sum, q.data[0]);
}

void print_bigint(const bigint& sq)
{
  static bigint billion(1000000000l);
  static bigint zero(0);
  static bigint digit;
  static bigint q;
  BIGINT_BASE decimaldigit;
  ldiv_t divideresult;
  int i;
  char *decimal_array;
  char tmp;
  char *p;

  decimal_array = new char[8000];
  q = sq;
  p = decimal_array+3999;
  *p = 0;
  p--;

  if (q == zero)  // Special case
  {
    *p = '0';
    p--;
  }

  for (;q>zero;)
  {
    q = q.Divide(q, billion, &digit);
    decimaldigit = digit;
    for(i=0; i<9; i++)
    {
      divideresult = ldiv(decimaldigit, 10);
      *p = divideresult.rem + 0x30;
      p--;
      decimaldigit = divideresult.quot;
    }
  }

  for (p++; *p=='0'; p++) // Strip off leading zeros.
  {
  }

  if (*p == 0)
    p--;

  printf("%s", p);
  delete decimal_array;
}

void sqr2demo(void)
{
  bigint a, b, c, d, zero;
  int i;
  time_t start_time;

  start_time = time(NULL);
  printf("\n\nComputing 2 E 1000 -- time = %ld\n", time(NULL)-start_time);
  fflush(stdout);

  a = (bigint) 2;
  b = (bigint) 10;

  zero = 0;
//  for (i=0; i<18020; i++)
//  for (i=0; i<8020; i++)
//  for (i=0; i<4020; i++)
//  for (i=0; i<2010; i++)
//  for (i=0; i<1020; i++)
  for (i=0; i<1016; i++)
//  for (i=0; i<210; i++)
  {
    a = a * b;
  }

  printf("\n\nComputing square root of 2 -- time = %ld\n", time(NULL)-start_time);
  fflush(stdout);

  c = a.sqrt();

  /* Do a sanity check here to make sure our result is correct */

  d = c * c;

  if (d > a)
    d = d - a;
  else
    d = a - d;

  d >>= 1;
  if (d > c)
    printf("Sanity check on sqr(2) failed\n");
  else
    printf("Sanity check on sqr(2) passed\n");
  fflush(stdout);

  d = a / c;  /* d should now be appoximately equal to c */

  if (d > c)
    d = d - c;
  else
    d = c - d;

  if (d > b)
    printf("Sanity check on sqr(2) failed\n");
  else
    printf("Sanity check on sqr(2) passed\n");
  fflush(stdout);


  printf("time = %ld\n", time(NULL)-start_time);
  printf("Converting to decimal sqrt(2) = \n");
  fflush(stdout);
  print_bigint(c);
  printf("\n");
  printf("time = %ld\n", time(NULL)-start_time);
  fflush(stdout);


  /* Do a sanity check here to make sure our result is correct */

  d = c * c;

  if (d > a)
    d = d - a;
  else
    d = a - d;

  d >>= 1;
  if (d > c)
    printf("Sanity check on sqr(2) failed\n");
  else
    printf("Sanity check on sqr(2) passed\n");
  fflush(stdout);

  d = a / c;  /* d should now be appoximately equal to c */

  if (d > c)
    d = d - c;
  else
    d = c - d;

  if (d > b)
    printf("Sanity check on sqr(2) failed\n");
  else
    printf("Sanity check on sqr(2) passed\n");
  fflush(stdout);

}
