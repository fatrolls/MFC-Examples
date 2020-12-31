/*
  Module:  BIGFP.CPP

  Author:  William A. Rossi
           598 Maple St
           Franklin, MA 02038

           bill@rossi.com

  Version: 1.1

  Release Date: 31-AUG-1995  Release version 1.0
                26-SEP-1996  Release version 1.1

  Description:  BIGFP is a floating point math class based on BIGINT
                for the C++ programming language.

  Revision History:

  26-SEP-1996  W. Rossi
               SPR #1:  Fixed subtract bug
               SPR #2:  Divide by zero trap in MultAdjust()
               SPR #3:  NOT FIXED: Exponent overflow int sine() and cosine()
  25-OCT-1996  W. Rossi
               SPR #4:  Fixed calculation of MaxDigits and HalfDigits

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

#include "bigfp.h"

int bigfp::MaxDigits;
int bigfp::HalfDigits;

bigfp::bigfp()
{
  static int once = 0;

  if (once == 0)
  {
    once++;

    Mant = ~(bigint) 0;
//  MaxDigits = SignificantDigits();  SPR #4
    MaxDigits = SignificantDigits() - 1;

    Mant = Mant >> (BIGINT_TOTAL_BITS / 2);
//  HalfDigits = SignificantDigits(); SPR #4
    HalfDigits = SignificantDigits() - 1;
  }
  Sign = 1;
  Exp = 0;
}

/* SignificantDigits():

   Counts the number of digits (base BIGFP_RADIX) in the Mantissa.
   It does this by the efficent method of finding the greatest number
   N than satisfys the following equation:

   q >= R ** (2 ** N);

   Once N is known, and hence the number of digits in N, then q is divide
   by R ** (2 ** N), and the process is repeated until q < R.

*/

int bigfp::SignificantDigits()
{
  BIGFP_TEMPORARY bigint radix;
  BIGFP_TEMPORARY bigint max, min, tmp;
  int digits=0;
  BIGINT_BASE d;
  BIGINT_BASE mask;

  mask = BIGINT_BASE_MAX;    // Handle event when odd # of words in bigint.
#if (BIGINTSIZE & 1)
  mask = mask ^ (mask >> (BIGINT_BASE_BITS/2));
#endif

  radix = (bigint) BIGFP_RADIX;
  tmp = Mant;

  do
  {
    max = radix;
    min = (bigint) 1;
    d = 0;

    if (tmp == (bigint) 0)  // Special Case
      return digits;

    while (max <= tmp)
    {
      if (d == 0)
        d = 1;
      else
        d <<= 1;
      min = max;
      if (max.data[BIGINTSIZE/2] & mask) // If a multiply overflow would occur
        break;
      max = max * max;
    }

    digits += d;

    tmp = tmp / min;  // Get the uncounted digits in tmp
  } while (tmp >= radix);

  digits++;

  return digits;
}

/* Power R computes R**N. */

bigint bigfp::PowerR(int n)
{
  BIGFP_TEMPORARY bigint radix;
  BIGFP_TEMPORARY bigint result, tmpmult;
  int pwr = BIGINT_TOTAL_BITS;
  int i;


  if (n == 0)  /* Special case */
  {
    result = (bigint) 0;
    return result;
  }

  radix = BIGFP_RADIX;
  result = (bigint) 1;

  do
  {
    while ((pwr & n) == 0)
    {
      pwr >>= 1;
      if (pwr == 0)
        return result;
    }

    i = pwr;
    pwr >>= 1;
    tmpmult = radix;
    while (i > 1)
    {
      i >>= 1;
      tmpmult = tmpmult * tmpmult;
    }

    result = result * tmpmult;
  } while (pwr);

  return result;
}

void bigfp::Normalize()
{
  BIGFP_TEMPORARY bigint radix;
  BIGFP_TEMPORARY bigint max, min, tmp, zero;
  int digits=0;
  BIGINT_BASE d;
  BIGINT_BASE mask;

  zero = bigint(0);
  mask = BIGINT_BASE_MAX;    // Handle event when odd # of words in bigint.
#if (BIGINTSIZE & 1)
  mask = mask ^ (mask >> (BIGINT_BASE_BITS/2));
#endif

  radix = (bigint) BIGFP_RADIX;
  tmp = Mant;

  if (tmp == zero)  // Special Case
  {
    Exp = 0;
    return;
  }

  do
  {
    max = radix;
    min = (bigint) 1;
    d = 0;

    if (tmp == zero)  // Special Case
    {
      Exp += digits;
      return;
    }

    while (tmp % max == zero)
    {
      if (d == 0)
        d = 1;
      else
        d <<= 1;
      min = max;
      if (max.data[BIGINTSIZE/2] & mask) // If a multiply overflow would occur
        break;
      max = max * max;
    }

    digits += d;

    tmp = tmp / min;
  } while (d);

  Mant=tmp;
  Exp += digits;
}

void bigfp::DeNormalize()
{
  BIGFP_TEMPORARY bigint multiplier;
  int digits, multexp;


  digits = SignificantDigits();
  multexp = MaxDigits - digits - 1;

  if (multexp <= 0)
    return;
  multiplier = PowerR(multexp);

  Mant = Mant * multiplier;
  Exp = Exp - multexp;
}

void bigfp::Align(bigfp *p, bigfp *q)
{
  BIGFP_TEMPORARY bigint multiplier;
  bigfp *a, *b;
  int expdiff;
  int bdigits, multexp;

  p->Normalize();
  q->Normalize();

  if (p->Exp == q->Exp)
    return;

  if (p->Exp > q->Exp)
  {
    a = q;
    b = p;
  }
  else
  {
    a = p;
    b = q;
  }

  /* a now points to the arg with the smaller exponent */

  expdiff = b->Exp - a->Exp;
  bdigits = b->SignificantDigits();

  /* First, make b's exponent smaller --
     This does not cause a loss of precision. */

  multexp = MaxDigits - bdigits - 1;
  if (multexp > expdiff)
    multexp = expdiff;


  if (bdigits == 0)   // Special case when b=0
  {
    b->Exp = a->Exp;
    return;
  }

  if (multexp > 0)
  {
    multiplier = PowerR(multexp);
    b->Mant = b->Mant * multiplier;
    b->Exp = b->Exp - multexp;

    expdiff -= multexp;
  }

  /* Next, make a's exponent larger --
      Note, this causes loss of precision, but its OK since we couldn't
      represent this loss in the sum of the two numbers anyways. */

  if (expdiff)
  {
    multiplier = PowerR(expdiff);
    a->Mant = a->Mant / multiplier;
    a->Exp = a->Exp + expdiff;
  }
}

void bigfp::HalfPrecision()
{
  BIGFP_TEMPORARY bigint divisor;
  int divdigits, digits;

  Normalize();
  digits = SignificantDigits();
  if (digits <= (HalfDigits - 1))
    return;

  divdigits = digits - HalfDigits + 1;

  divisor = PowerR(divdigits);
  Mant = Mant / divisor;
  Exp = Exp + divdigits;
}

void bigfp::MultAdjust(bigfp *p, bigfp *q)
{
  BIGFP_TEMPORARY bigint divisor;
  bigfp *a, *b;
  int adigits, bdigits, totaldigits, divdigits;

  p->Normalize();
  q->Normalize();
  adigits = p->SignificantDigits();
  bdigits = q->SignificantDigits();

  if (adigits > bdigits)
  {
    a = p;
    b = q;
  }
  else
  {
    a = q;
    b = p;
    totaldigits = adigits;
    adigits = bdigits;
    bdigits = totaldigits;
  }

  // A is now the number with more digits

  totaldigits = adigits + bdigits;
  if (totaldigits <= (MaxDigits-1))
    return;


  // Reduce the number of digits in a so it has as many as b OR
  // until totaldigits is acceptable

  divdigits = adigits - bdigits;

  // If we can make the number of total digits acceptable without
  // making a and b have the same number of digits, do so!

  if (divdigits > (totaldigits - MaxDigits + 1))
    divdigits = totaldigits - MaxDigits + 1;

  if (divdigits)
  {
    divisor = PowerR(divdigits);
    a->Mant = a->Mant / divisor;
    a->Exp = a->Exp + divdigits;
    adigits = adigits - divdigits;
  }
  totaldigits = adigits + bdigits;

  if (totaldigits <= (MaxDigits-1))
    return;

  // Reduce a and b so that totaldigits <=(MaxDigits-1)

  divdigits = totaldigits - MaxDigits + 1;
  divdigits = divdigits / 2;

  // SPR #2
  // Special case -- divdigits = 0
  // added 9-25-96 WAR
  // Avoid a divide by zero situtation

  if (divdigits == 0)  // SPR #2
    divdigits++;       // SPR #2

  divisor = PowerR(divdigits);

  a->Mant = a->Mant / divisor;
  a->Exp = a->Exp + divdigits;
  b->Mant = b->Mant / divisor;
  b->Exp = b->Exp + divdigits;
}


bigfp bigfp::operator+(const bigfp& a)
{
  BIGFP_TEMPORARY bigfp result, p, q;
  char invertthis=0, invertq=0;
  BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);

  q = a;
  p = *this;
  Align(&p, &q);

  if (p.Sign < 0)
  {
    invertthis = 1;
    p.Mant = -p.Mant;
  }

  if (q.Sign < 0)
  {
    invertq = 1;
    q.Mant = -q.Mant;
  }

  result.Mant = p.Mant + q.Mant;
  result.Exp = p.Exp;

  if (invertthis)
    p.Mant = -p.Mant;

  if (invertq)
    q.Mant = -q.Mant;

  if (result.Mant.data[BIGINTSIZE-1] & msb)
  {
    result.Mant = -result.Mant;
    result.Sign = -1;
  }
  else
  {
    result.Sign = 1;
  }

  result.Normalize();
  return result;
}

bigfp bigfp::operator-(const bigfp& a)
{
  BIGFP_TEMPORARY bigfp result, p, q;
  BIGINT_BASE msb = BIGINT_BASE_MAX ^ (BIGINT_BASE_MAX >> 1);
  char invertthis=0, invertq=0;

  q = a;
  p = *this;
  Align(&p, &q);

  if (p.Sign < 0)
  {
    invertthis = 1;
    p.Mant = -p.Mant;
  }

  if (q.Sign < 0)
  {
    invertq = 1;
    q.Mant = -q.Mant;
  }

  result.Mant = p.Mant - q.Mant;
  //  SPR #1 -- Was mistakenly using Exp instead of p.Exp
  //  result.Exp = Exp;
  result.Exp = p.Exp;  // SPR #1

  if (invertthis)
    p.Mant = -p.Mant;

  if (invertq)
    q.Mant = -q.Mant;

  if (result.Mant.data[BIGINTSIZE-1] & msb)
  {
    result.Mant = -result.Mant;
    result.Sign = -1;
  }
  else
  {
    result.Sign = 1;
  }

  result.Normalize();
  return result;
}

bigfp bigfp::operator*(const bigfp& a)
{
  BIGFP_TEMPORARY bigfp result, q;

  q = a;

  MultAdjust(this, &q);

  result.Mant = q.Mant * Mant;
  result.Exp = q.Exp + Exp;
  result.Sign = q.Sign * Sign;

  result.Normalize();
  return result;
}

bigfp bigfp::operator/(const bigfp& a)
{
  BIGFP_TEMPORARY bigfp result, q;

  q = a;
  DeNormalize();  // De normalize the dividend
  q.HalfPrecision();  // Make divisor half precision or less.

  result.Mant = Mant / q.Mant;
  result.Exp = Exp - q.Exp;
  result.Sign = q.Sign * Sign;

  result.Normalize();

  return result;
}

int bigfp::operator==(bigfp& q)
{
  Normalize();
  q.Normalize();
  if (Mant == q.Mant && Exp == q.Exp && Sign == q.Sign)
    return 1;
  else
    return 0;
}

int bigfp::operator!=(bigfp& q)
{
  Normalize();
  q.Normalize();
  if (Mant != q.Mant || Exp != q.Exp || Sign != q.Sign)
    return 1;
  else
    return 0;
}

int bigfp::operator>(bigfp& a)
{
  BIGFP_TEMPORARY bigfp q, p;

  q = a;
  p = *this;
  Align(&p, &q);

  if (p.Sign > q.Sign)
    return 1;
  if (p.Sign < q.Sign)
    return 0;
  if (p.Exp > q.Exp)
    return 1;
  if (p.Exp < q.Exp)
    return 0;
  if (p.Mant > q.Mant)
    return 1;

  return 0;
}

int bigfp::operator<(bigfp& a)
{
  BIGFP_TEMPORARY bigfp q, p;

  q = a;
  p = *this;
  Align(&p, &q);

  if (p.Sign < q.Sign)
    return 1;
  if (p.Sign > q.Sign)
    return 0;
  if (p.Exp < q.Exp)
    return 1;
  if (p.Exp > q.Exp)
    return 0;
  if (p.Mant < q.Mant)
    return 1;

  return 0;
}

int bigfp::operator>=(bigfp& a)
{
  BIGFP_TEMPORARY bigfp p, q;

  q = a;
  p = *this;
  Align(&p, &q);

  if (p.Sign > q.Sign)
    return 1;
  if (p.Sign < q.Sign)
    return 0;
  if (p.Exp > q.Exp)
    return 1;
  if (p.Exp < q.Exp)
    return 0;
  if (p.Mant >= q.Mant)
    return 1;

  return 0;
}

int bigfp::operator<=(bigfp& a)
{
  BIGFP_TEMPORARY bigfp p, q;

  q = a;
  p = *this;
  Align(&p, &q);

  if (p.Sign < q.Sign)
    return 1;
  if (p.Sign > q.Sign)
    return 0;
  if (p.Exp < q.Exp)
    return 1;
  if (p.Exp > q.Exp)
    return 0;
  if (p.Mant <= q.Mant)
    return 1;

  return 0;
}


bigfp bigfp::sqrt()    /* returns the square root of this */
{
  BIGFP_TEMPORARY bigint radix;
  BIGFP_TEMPORARY bigfp q, x, dx;

  q.Mant = Mant;
  q.Exp = Exp;
  q.Sign = Sign;

  radix = BIGFP_RADIX;

  q.DeNormalize();
  if (q.Exp % 2)
  {
    q.Mant = q.Mant / radix;
    q.Exp ++;
  }

  x.Mant = q.Mant.sqrt();
  x.Exp = q.Exp/2;

  /* Now that we have the first pass estimiate, compute the rest
     by the formula dx = (y - x*x) / (2x); */

  dx = q - x*x;
  dx = dx / x;
  dx.Mant >>= 1;
  x = x + dx;

  return x;
}


//#include <cstdio>//.h
bigfp bigfp::sine() /* returns the sine of this */
{
  BIGFP_TEMPORARY bigfp factorial, numerator, q, result, temp, end;
  int i;
//  char dec[300];

  result.Mant = (bigint) 0;
  result.Exp = 0;
  result.Sign = 1;

  result = *this;
  q = *this;

  numerator = *this;
  end.Mant = 1;
  end.Exp = -2 * MaxDigits;  // SPR #3 -- not fixed yet
  end.Sign = 1;

  temp = result;

  factorial.Mant = (bigint) 1;
  factorial.Exp = 0;
  factorial.Sign = 1;

  numerator = q;

  for (i=3; temp > end; i+=2)
  {
    numerator = numerator * q;
    numerator = numerator * q;

    temp.Mant = (bigint) (i-1);
    temp.Exp = 0;
    temp.Sign = 1;
    factorial = factorial * temp;
    temp.Mant++;
    factorial = factorial * temp;

    temp = numerator/factorial;
    if (i & 0x2)
      temp.Sign = -temp.Sign;

    result = result + temp;
//    result.bigfp2ascii(dec);
//    printf("%s\n",dec);
//    temp.bigfp2ascii(dec);
//    printf("%s\n",dec);
    temp.Sign = 1;
  }
  return result;
}

bigfp bigfp::cosine() /* returns the cosine of this */
{
  BIGFP_TEMPORARY bigfp factorial, numerator, q, result, temp, end;
  int i;
//  char dec[300];

  result.Mant = (bigint) 1;
  result.Exp = 0;
  result.Sign = 1;

  q = *this;
  numerator = result;

  factorial.Mant = (bigint) 1;
  factorial.Exp = 0;
  factorial.Sign = 1;

  end.Mant = 1;
  end.Exp = -2 * MaxDigits;  // SPR #3 -- not fixed yet
  end.Sign = 1;

  temp = result;

  numerator = result;

  for (i=2; temp > end; i+=2)
  {
    numerator = numerator * q;
    numerator = numerator * q;

    temp.Mant = (bigint) (i-1);
    temp.Exp = 0;
    temp.Sign = 1;
    factorial = factorial * temp;
    temp.Mant++;
    factorial = factorial * temp;

    temp = numerator/factorial;
    if (i & 0x2)
      temp.Sign = -temp.Sign;

    result = result + temp;
//    numerator.bigfp2ascii(dec);
//    printf("%s\n",dec);
//    temp.bigfp2ascii(dec);
//    printf("%s\n",dec);
    temp.Sign = 1;
  }
  return result;
}

bigfp bigfp::tangent() /* returns the cosine of this */
{
  BIGFP_TEMPORARY bigfp s, temp, c, t;

  s = sine();

  // cos = sqrt(1 - sin*sin)

/*  temp = s * s;

  c.Mant = (bigint) 1;
  c.Exp = 0;
  c.Sign = 1;

  c = c - temp;
  c = c.sqrt(); */

  c = cosine();

  // tan = sine / cosine

  t = s / c;

  return t;
}

void bigfp::bigfp2ascii(char *fpdecimal)
{
  char *decimal;
  unsigned long mantdigits;
  int i;
  char *p, *q;
  unsigned long digit;
  int zeros;
  bigint x;
  bigfp y;


  decimal = new char[MaxDigits+1];

  y = *this;
  y.HalfPrecision();
  x = y.Mant;
  p = &decimal[MaxDigits-1];
  p[1] = 0;

  while (x != (bigint) 0)
  {
    digit = (unsigned long) ((x % (bigint)10).data[0]);
    *p =
       ((unsigned char) digit) + '0';
    x = x / (bigint) 10;
    p--;
  }

  /* Now lets figure out where to put the decimal point */

  p++;
  mantdigits = strlen(p);

  /* Put in leading zeros if necessary */
  zeros = -(mantdigits + y.Exp);
  q = fpdecimal;

  if (Sign < 0)
    *q++ = '-';

  if (zeros >= 0)
  {
    *q = '0';
    q++;
    *q = '.';
    q++;
    for (i=0; i<zeros; i++)
    {
      *q = '0';
      q++;
    }
  }

  /* Put in the matissa digits and decimal point */

  zeros = -zeros;
  for (i=0; i<mantdigits; i++)
  {
    *q = p[i];
    q++;
    zeros--;
    if (zeros == 0)
    {
      *q='.';
      q++;
    }
  }

  /* Put in the trailing zeros */

  for (i=0; i<zeros; i++)
  {
    *q = '0';
    q++;
  }

  *q = 0;

  delete decimal;
}


bigfp bigfp::ascii2bigfp(char *fpdecimal)
{
  int leading_zeros;
  int trailing_zeros;
  int significant_digits;
  int decimal;
  char *p, *q;
  char Striped[256];
  bigfp result;
  bigint multiplier;
  int DecimalFound = -1;
  int i;

  result.Mant = (bigint) 0;
  result.Exp = 0;
  result.Sign = 1;

  /* If there is a minus sign in the number then it is negative */

  if (strstr(fpdecimal,"-") != NULL)
    result.Sign = -1;

  /* First off, find all of the leading zeros, trailing zeros, and
     siginificant digits */

  p = fpdecimal;

  /* Move p to first significant digit */

  for(;;)
  {
    if (*p >= '1' && *p <= '9')
      break;
    if (*p == '.')
      break;
    if (*p == 0)
      break;
    p++;
  }

  /* Copy the string onto Stripped */

  q = Striped;
  significant_digits=0;
  for(;;)
  {
    if (*p == 0)
      break;

    if (*p == '.')
    {
      DecimalFound = significant_digits;
      p++;
      continue;
    }
    if (*p < '0' || *p > '9')
    {
      p++;
      continue;
    }

    *q = *p;
    q++;
    p++;
    significant_digits++;
  }
  *q = 0;

  p = strpbrk(Striped, "123456789");
  if (p == NULL)
    p = Striped;

  if (strlen(p) > 18) // Limit sig. digits.
  {
    for (i=strlen(p) -1 ; i>=18; i--)
      p[i] = '0';
  }

  // If the decimal point has been found then get rid of trailing zeros.
  if (DecimalFound != -1)
  {
    for (;;)
    {
      q--;
      if (q == Striped)
        break;
      if (*q == '0')
      {
        *q = 0;
        significant_digits--;
      }
      else
      {
        break;
      }
    }
  }


  if (DecimalFound == -1)
    DecimalFound = strlen(Striped);

  /* Find the number of significant leading zeros */

  q = Striped;
  leading_zeros = 0;
  for(;;)
  {
    if (*q != '0')
      break;
    leading_zeros++;
    q++;
  }

  /* Find the number of significant trailing zeros */

  p = &Striped[strlen(Striped) - 1];

  trailing_zeros = 0;
  while (p>q)
  {
    if (*p != '0')
      break;
    trailing_zeros++;
    p--;
  }

  /* Ok, now we know how many leading and trailing zeros there are, and
     where the least significant digit is. */

  multiplier = (bigint) 1;
  for (i=0; i<(significant_digits - leading_zeros - trailing_zeros); i++)
  {
    result.Mant = result.Mant + multiplier * ((bigint) (unsigned long) (*p - '0'));
    multiplier = multiplier * (bigint) 10;
    p--;
  }

  DecimalFound = DecimalFound - strlen(Striped);
  result.Exp = DecimalFound    + trailing_zeros;
  result.HalfPrecision();

  return result;
}

