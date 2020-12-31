/*
  Module:  BIGINT.CPP

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
#include "bigint.h"

/********** Global constants ***************/

bigint bigint::zero;
bigint bigint::one;
bigint bigint::two;

/* operator>>()
   operator<<()
   operator>>=()
   operator<<=()

   These are the shift operators.  They are fundamenal operators
*/

bigint bigint::operator>>(int shift)
{
  BIGINT_TEMPORARY bigint a, t;
  BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);
  int i, j;

  t = *this;

  for (i=0; i<shift; i++)
  {
    a.data[BIGINTSIZE-1] = t.data[BIGINTSIZE-1] >> 1;
    for (j=BIGINTSIZE-2; j>=0; j--)
    {
      a.data[j] = t.data[j] >> 1;
      if ((t.data[j+1] & 1) != 0)
        a.data[j] |= msb;  /* Set most sig. bit */
    }
    t = a;
  }

  return a;
}

bigint bigint::operator<<(int shift)
{
  BIGINT_TEMPORARY bigint a, t;
  BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);
  int i, j;

  t = *this;

  for (i=0; i<shift; i++)
  {
    a.data[0] = t.data[0] << 1;
    for (j=1; j<BIGINTSIZE; j++)
    {
      a.data[j] = t.data[j] << 1;
      if ((t.data[j-1] & msb) != 0)
        a.data[j] |= 1;  /* Set least sig. bit */
    }
    t = a;
  }

  return a;
}

bigint& bigint::operator>>=(int shift)
{
  BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);
  BIGINT_BASE carry;
  int i, j;

  for (i=0; i<shift; i++)
  {
    carry = data[BIGINTSIZE-1] & 1;
    data[BIGINTSIZE-1] >>= 1;
    for (j=BIGINTSIZE-2; j>=0; j--)
    {
      if (carry)
      {
        carry = data[j] & 1;
        data[j] >>= 1;
        data[j] |= msb;
      }
      else
      {
        carry = data[j] & 1;
        data[j] >>= 1;
      }
    }
  }

  return *this;
}

bigint& bigint::operator<<=(int shift)
{
  BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);
  BIGINT_BASE carry;
  int i, j;

  for (i=0; i<shift; i++)
  {
    carry = data[0] & msb;
    data[0] <<= 1;
    for (j=1; j<BIGINTSIZE; j++)
    {
      if (carry)
      {
        carry = data[j] & msb;
        data[j] <<= 1;
        data[j] |= 1;
      }
      else
      {
        carry = data[j] & msb;
        data[j] <<= 1;
      }
    }
  }

  return *this;
}

// This code has the carry bug fixed.
/* operator+():
   This is the addition operators, and is one of the fundamental
   operations -- i.e. it calls no other bigint operators.

   Since C and C++ provide no facility for determinine if the carry
   flag is set as a result of addition, some gyrations have to be made
   to make this determination.  These gyrations are described below:

   If the incoming carry flag is clear then:
     If either addend is less than the sum, set the carry flag,
     otherwise clear it.
   If the incoming carry flag is set then:
     If either addend is less than OR EQUAL TO the sum, set the
     carry flag, otherwise clear it.

   In ealier attempts at this operator, I failed to observe the
   subtle difference in behavior depending on whether the carry
   from the privious add was set or clear.  This was, of course,
   causing the add to fail occasionally.  It is fixed now however.
*/
bigint bigint::operator+(const bigint& q)
{
  BIGINT_TEMPORARY bigint result;
  BIGINT_BASE carry = 0;
  int i;

  for (i=0; i<BIGINTSIZE; i++)
  {
    result.data[i] = data[i] + q.data[i] + carry;
    if (carry == 0)
    {
      if (result.data[i] < data[i] || result.data[i] < q.data[i])
        carry=1;
      else
        carry=0;
    }
    else
    {
      if (result.data[i] <= data[i] || result.data[i] <= q.data[i])
        carry=1;
      else
        carry=0;
    }
  }

  return result;
}

/* operator+=()

   The += operator gets its own special code since it can be done more
   efficently than adding since a temporary object to store the result
   is not needed.  The general operation is similar to operator+().
*/

bigint& bigint::operator+=(const bigint& q)
{
  BIGINT_BASE carry = 0, prevdigit;
  int i;

  for (i=0; i<BIGINTSIZE; i++)
  {
    prevdigit = data[i];
    data[i] = data[i] + q.data[i] + carry;
    if (carry == 0)
    {
      if (data[i] < prevdigit || data[i] < q.data[i])
        carry=1;
      else
        carry=0;
    }
    else
    {
      if (data[i] <= prevdigit || data[i] <= q.data[i])
        carry=1;
      else
        carry=0;
    }
  }

  return *this;
}

/* operator++() and operator++(int)

   The increment operators can be coded much more efficently than + or
   +=.  The thory of operation is somewhat different too, it goes as
   follows.  This takes advantage of the fact that it is much easier to
   determine when carrys occur in increments than in general addition.

   Starting with the least significant digit:

   Increment a digit.
     If it becomes zero, increment the next digit.

*/

bigint& bigint::operator++()  /* Pre Increment operator -- faster than add */
{
  int i;

  data[0]++;
  for (i=1; i<BIGINTSIZE; i++)
    if (data[i-1] == 0)
      data[i]++;
    else
      break;

  return *this;
}

bigint& bigint::operator++(int)  /* Post Increment operator -- faster than add */
{
  int i;

  data[0]++;
  for (i=1; i<BIGINTSIZE; i++)
    if (data[i-1] == 0)
      data[i]++;
    else
      break;

  return *this;
}

/* operator-()  The negation operator

   This simply negates a number.  Since bigint is an unsigned number
   class, what does negate mean here?  It means to find the a number B
   that when added to A produces zero.  This is done by finding the
   2's complement of A, which is equal to ~A++;
*/

bigint bigint::operator-()  /* Negates a number */
{
  BIGINT_TEMPORARY bigint result;
  int i;

  for (i=0; i<BIGINTSIZE; i++)
    result.data[i] = ~data[i];

  result = result + one;

  return result;
}

/* operator-() subtaction operator
   operator--()
   operator-=()
   operator-=(int)

   These all work quite similarly to the addition and increment
   operators.
*/

bigint bigint::operator-(const bigint& q)
{
  BIGINT_TEMPORARY bigint result;
  BIGINT_BASE borrow = 0;
  int i;

  for (i=0; i<BIGINTSIZE; i++)
  {
    result.data[i] = data[i] - q.data[i] - borrow;

    if (borrow == 0)
    {
      if (data[i] < q.data[i])
        borrow=1;
      else
        borrow=0;
    }
    else
    {
      if (data[i] <= q.data[i])
        borrow=1;
      else
        borrow=0;
    }
  }

  return result;
}

bigint& bigint::operator-=(const bigint& q)
{
  BIGINT_BASE borrow = 0, prevdigit;
  int i;

  for (i=0; i<BIGINTSIZE; i++)
  {
    prevdigit = data[i];
    data[i] = data[i] - q.data[i] - borrow;
    if (borrow == 0)
    {
      if (prevdigit < q.data[i])
        borrow=1;
      else
        borrow=0;
    }
    else
    {
      if (prevdigit <= q.data[i])
        borrow=1;
      else
        borrow=0;
    }
  }

  return *this;
}

bigint& bigint::operator--()  /* Pre Decrement operator -- faster than add */
{
  int i;

  data[0]--;
  for (i=1; i<BIGINTSIZE; i++)
    if (data[i-1] == BIGINT_BASE_MAX)
      data[i]--;
    else
      break;

  return *this;
}

bigint& bigint::operator--(int)  /* Post Decrement operator -- faster than add */
{
  int i;

  data[0]--;
  for (i=1; i<BIGINTSIZE; i++)
    if (data[i-1] == BIGINT_BASE_MAX)
      data[i]--;
    else
      break;

  return *this;
}

/* operator<()
   operator>()
   operator<=()
   operator>=()

   These operators compare two numbers starting at the most significant
   digit, and working back to the least significant.  The differ only
   in the return codes they produce.
*/

int bigint::operator<(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
  {
    if (data[i] < q.data[i])
      return 1;
    if (data[i] > q.data[i])
      return 0;
  }
  return 0;
}

int bigint::operator>(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
  {
    if (data[i] < q.data[i])
      return 0;
    if (data[i] > q.data[i])
      return 1;
  }
  return 0;
}

int bigint::operator<=(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
  {
    if (data[i] < q.data[i])
      return 1;
    if (data[i] > q.data[i])
      return 0;
  }
  return 1;
}

int bigint::operator>=(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
  {
    if (data[i] < q.data[i])
      return 0;
    if (data[i] > q.data[i])
      return 1;
  }
  return 1;
}

/* operator&()
   operator|()
   operator^()
   operator&=()
   operator|=()
   operator^=()
   operator~()

   These operators perform the corresponding bitwise operations, on a
   per digit basis.
*/

bigint bigint::operator&(const bigint& q)
{
  BIGINT_TEMPORARY bigint result;
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    result.data[i] = data[i] & q.data[i];

  return result;
}

bigint bigint::operator|(const bigint& q)
{
  BIGINT_TEMPORARY bigint result;
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    result.data[i] = data[i] | q.data[i];

  return result;
}

bigint bigint::operator^(const bigint& q)
{
  BIGINT_TEMPORARY bigint result;
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    result.data[i] = data[i] ^ q.data[i];

  return result;
}

bigint& bigint::operator&=(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    data[i] = data[i] & q.data[i];

  return *this;
}

bigint& bigint::operator|=(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    data[i] = data[i] | q.data[i];

  return *this;
}

bigint& bigint::operator^=(const bigint& q)
{
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    data[i] = data[i] ^ q.data[i];

  return *this;
}

bigint bigint::operator~()
{
  BIGINT_TEMPORARY bigint result;
  int i;

  for (i=(BIGINTSIZE-1); i>=0; i--)
    result.data[i] = ~data[i];

  return result;
}

/* operator*()

   This operator performs multiplication by shift and add.
*/

bigint bigint::operator*(bigint q)
{
  BIGINT_TEMPORARY bigint t;
  BIGINT_TEMPORARY bigint p;

  p = zero;
  t = *this;

  do
  {
    if ((q.data[0] & 1) != 0)
      p += t;
    q >>= 1;
    t <<= 1;
  } while (q != zero);
  return p;
}

#if 0
// There is a bug in operator*=() at the moment//...
// It does not produce the same results as operator*().
bigint& bigint::operator*=(bigint q)
{
  BIGINT_TEMPORARY bigint t;
  BIGINT_TEMPORARY bigint& p=*this;

  t = *this;
  p = zero;

  do
  {
    if ((q.data[0] & 1) != 0)
      p += t;
    q >>= 1;
    t <<= 1;
  } while (q != zero);
  return *this;
}
#endif

bigint bigint::Divide(bigint a, bigint b, bigint *remainder)
{
  BIGINT_TEMPORARY bigint c, d;
  BIGINT_TEMPORARY BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);
  int i, shiftcnt=0;

  /* Check for attempt to divide by zero */

  if (b == zero)
    shiftcnt = 1 / shiftcnt;  // Force a divide by zero exception. (shiftcnt=0)

  c=zero;
  d=b;             /* Store the divisor in D */

  /* Left shift B until it is greater than or equal to A */
  while (b<a && ((b.data[BIGINTSIZE-1] & msb) == 0))
  {
    b <<= 1;
    shiftcnt++;
  }

  if (b>a)      /* If B is greater than A, right shift B */
  {
    b >>= 1;
    shiftcnt--;
  }

  for(i=0; i<=shiftcnt; i++)
  {
    if (b<=a)    /* If B is greater than A, then the bit is a 1 */
    {
      a -= b;     /* Subtract B from A */
      b >>= 1;  /* Right shift B     */
      c <<= 1;  /* Left shift quotient */
      c++;       /* Increment quotient  */
    }
    else
    {
      b >>= 1;  /* Bit is 0, right shift B, left shift quotient */
      c <<= 1;
    }
  }

  if (remainder != NULL)
    *remainder = a;

  return c;
}


bigint bigint::sqrt()        /* returns the square root of this */
{
  BIGINT_TEMPORARY bigint x,y,dx;
  bigint mask = two;
  int i,j;

  mask = -mask;

  y = *this;

  for (i=0,x=y;x!=zero;x>>=1,i++);
  for (j=0,x=y;j<(unsigned long)(i>>1);x>>=1,j++);

  do
  {
    /* We are really performing the fuction:
     dx = (y/x - x) / 2;
       below, but since these are unsigned numbers,
       we MUST do the subtraction last in order for
       the x = x + dx;  equation to work properly. */

    dx = (y>>1)/x - (x>>1);
    x = x + dx;
  } while ((dx &= mask) != zero);

  return x;
}

/*********************  Class definitions end here *******************/
