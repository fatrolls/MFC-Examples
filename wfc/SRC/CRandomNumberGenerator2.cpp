#include <wfc.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CRandomNumberGenerator2.cpp $
** $Revision: 6 $
** $Modtime: 2/05/00 8:27a $
** $Reuse Tracing Code: 1 $
*/

// Algorithm provided by Yehuda Hahn (ygh@cfsnet.com)
// Source adapted from http://www.math.keio.ac.jp/matumoto/cokus.c

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// This is the ``Mersenne Twister'' random number generator MT19937, which
// generates pseudorandom integers uniformly distributed in 0..(2^32 - 1)
// starting from any odd seed in 0..(2^32 - 1).  This version is a recode
// by Shawn Cokus (Cokus@math.washington.edu) on March 8, 1998 of a version by
// Takuji Nishimura (who had suggestions from Topher Cooper and Marc Rieffel in
// July-August 1997).
//
// Effectiveness of the recoding (on Goedel2.math.washington.edu, a DEC Alpha
// running OSF/1) using GCC -O3 as a compiler: before recoding: 51.6 sec. to
// generate 300 million random numbers; after recoding: 24.0 sec. for the same
// (i.e., 46.5% of original time), so speed is now about 12.5 million random
// number generations per second on this machine.
//
// According to the URL <http://www.math.keio.ac.jp/~matumoto/emt.html>
// (and paraphrasing a bit in places), the Mersenne Twister is ``designed
// with consideration of the flaws of various existing generators,'' has
// a period of 2^19937 - 1, gives a sequence that is 623-dimensionally
// equidistributed, and ``has passed many stringent tests, including the
// die-hard test of G. Marsaglia and the load test of P. Hellekalek and
// S. Wegenkittl.''  It is efficient in memory usage (typically using 2506
// to 5012 bytes of static data, depending on data type sizes, and the code
// is quite short as well).  It generates random numbers in batches of 624
// at a time, so the caching and pipelining of modern systems is exploited.
// It is also divide- and mod-free.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Library General Public License as published by
// the Free Software Foundation (either version 2 of the License or, at your
// option, any later version).  This library is distributed in the hope that
// it will be useful, but WITHOUT ANY WARRANTY, without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
// the GNU Library General Public License for more details.  You should have
// received a copy of the GNU Library General Public License along with this
// library; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place, Suite 330, Boston, MA 02111-1307, USA.
//
// The code as Shawn received it included the following notice:
//
//   Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.  When
//   you use this, send an e-mail to <matumoto@math.keio.ac.jp> with
//   an appropriate reference to your work.
//
// It would be nice to CC: <Cokus@math.washington.edu> when you write.
//

typedef unsigned long uint32;

#define N              (624)                 // length of state vector
#define M              (397)                 // a period parameter
#define K              (0x9908B0DFU)         // a magic constant
#define hiBit(u)       ((u) & 0x80000000U)   // mask all but highest   bit of u
#define loBit(u)       ((u) & 0x00000001U)   // mask all but lowest    bit of u
#define loBits(u)      ((u) & 0x7FFFFFFFU)   // mask     the highest   bit of u
#define mixBits(u, v)  (hiBit(u)|loBits(v))  // move hi bit of u to hi bit of v

DWORD CRandomNumberGenerator2::m_LoadMersenneTwister( void )
 {
    register DWORD *p0 = m_State;
    register DWORD *p2 = m_State + 2;
    register DWORD *pM = m_State + M;
    register DWORD s0 = 0;
    register DWORD s1 = 0;
    register int    j = 0;

    if ( m_Left < (-1) )
    {
        InitializeSeed();
    }

    m_Left = N - 1;
    m_Next = m_State + 1;

    for( s0 = m_State[ 0 ], s1 = m_State[ 1 ], j = N - M + 1; --j; s0 = s1, s1 = *p2++ )
    {
        *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? K : 0U);
    }

    for( pM = m_State, j = M; --j; s0 = s1, s1 = *p2++ )
    {
        *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? K : 0U);
    }

    s1 = m_State[0], *p0 = *pM ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? K : 0U);
    s1 ^= (s1 >> 11);
    s1 ^= (s1 <<  7) & 0x9D2C5680U;
    s1 ^= (s1 << 15) & 0xEFC60000U;
    return(s1 ^ (s1 >> 18));
 }

CRandomNumberGenerator2::CRandomNumberGenerator2()
{
   ZeroMemory( m_State, sizeof( m_State ) );
   InitializeSeed();
}

CRandomNumberGenerator2::CRandomNumberGenerator2( DWORD new_seed )
{
   ZeroMemory( m_State, sizeof( m_State ) );
   SetSeed( new_seed );
}

CRandomNumberGenerator2::~CRandomNumberGenerator2()
{
}

void CRandomNumberGenerator2::InitializeSeed( void )
{
   WFCLTRACEINIT( TEXT( "CRandomNumberGenerator2::InitializeSeed()" ) );

   // We need to seed our algorithm with something random from the operating system

   WORD high_word = 0;
   WORD low_word  = 0;

   // GetTickCount() returns the number of milliseconds the machine has been turned on

   high_word = LOWORD( ::GetTickCount() );

   DWORD number_of_sectors_per_cluster = 0;
   DWORD number_of_bytes_per_sector    = 0;
   DWORD number_of_free_clusters       = 0;
   DWORD total_number_of_clusters      = 0;

   // Different folks have different amounts of free space on their hard drives

   if ( ::GetDiskFreeSpace( NULL,
                           &number_of_sectors_per_cluster,
                           &number_of_bytes_per_sector,
                           &number_of_free_clusters,
                           &total_number_of_clusters ) != FALSE )
   {
      WFCTRACE( TEXT( "Got drive data OK" ) );

      low_word = LOWORD( number_of_free_clusters );

      // This is a nice number but not nice enough. It won't vary enough
      // from call to call. So, let's scramble it a bit (no pun intented)
      // Anther call to GetTickCount() should do the trick because the
      // GetDiskFreeSpace() will take a varying amount of time.

      low_word  ^= ( (WORD) ::GetTickCount() );
   }
   else
   {
      WFCTRACE( TEXT( "OOPS! In fail safe mode" ) );

      // This is a fail-safe condition. We resort to time because it is kinda
      // random but it is guessable.

      SYSTEMTIME system_time;

      ZeroMemory( &system_time, sizeof( system_time ) );

      ::GetSystemTime( &system_time );

      // The most random part of the system time is the milliseconds then seconds

      BYTE high_byte = 0;
      BYTE low_byte  = 0;

      high_byte = LOBYTE( system_time.wMilliseconds );
      low_byte  = (BYTE) ( ( system_time.wMilliseconds >> 8 ) + system_time.wSecond );

      low_word = MAKEWORD( low_byte, high_byte );
   }

   SetSeed( MAKELONG( low_word, high_word ) );
}

DWORD CRandomNumberGenerator2::GetInteger( void )
{
   DWORD return_value = 0;

   if ( --m_Left < 0 )
   {
      return( m_LoadMersenneTwister() );
   }

   return_value  = *m_Next++;
   return_value ^= (return_value >> 11);
   return_value ^= (return_value <<  7) & 0x9D2C5680U;
   return_value ^= (return_value << 15) & 0xEFC60000U;

   return( return_value ^ (return_value >> 18) );
}

double CRandomNumberGenerator2::GetFloat( void )
{
   union
   {
      double return_value;
      unsigned char bytes[ 8 ];
   }
   x;

   x.return_value = GetInteger();

   DWORD temp_integer = GetInteger();

   // This works for Intel-Endian machines
   x.bytes[ 0 ] ^= HIBYTE( HIWORD( temp_integer ) );
   x.bytes[ 1 ] ^= HIBYTE( LOWORD( temp_integer ) );
   x.bytes[ 2 ] ^= LOBYTE( HIWORD( temp_integer ) );

   // This works for Sun-Endian machines
   //x.bytes[ 7 ] ^= HIBYTE( HIWORD( temp_integer ) );
   //x.bytes[ 6 ] ^= HIBYTE( LOWORD( temp_integer ) );
   //x.bytes[ 5 ] ^= LOBYTE( HIWORD( temp_integer ) );

   return( x.return_value );
}

void CRandomNumberGenerator2::SetSeed( DWORD new_seed )
{
   WFCLTRACEINIT( TEXT( "CRandomNumberGenerator2::SetSeed()" ) );
   WFCTRACEVAL( TEXT( "Seed being set to " ), new_seed );

    //
    // We initialize state[0..(N-1)] via the generator
    //
    //   x_new = (69069 * x_old) mod 2^32
    //
    // from Line 15 of Table 1, p. 106, Sec. 3.3.4 of Knuth's
    // _The Art of Computer Programming_, Volume 2, 3rd ed.
    //
    // Notes (SJC): I do not know what the initial state requirements
    // of the Mersenne Twister are, but it seems this seeding generator
    // could be better.  It achieves the maximum period for its modulus
    // (2^30) iff x_initial is odd (p. 20-21, Sec. 3.2.1.2, Knuth); if
    // x_initial can be even, you have sequences like 0, 0, 0, ...;
    // 2^31, 2^31, 2^31, ...; 2^30, 2^30, 2^30, ...; 2^29, 2^29 + 2^31,
    // 2^29, 2^29 + 2^31, ..., etc. so I force seed to be odd below.
    //
    // Even if x_initial is odd, if x_initial is 1 mod 4 then
    //
    //   the          lowest bit of x is always 1,
    //   the  next-to-lowest bit of x is always 0,
    //   the 2nd-from-lowest bit of x alternates      ... 0 1 0 1 0 1 0 1 ... ,
    //   the 3rd-from-lowest bit of x 4-cycles        ... 0 1 1 0 0 1 1 0 ... ,
    //   the 4th-from-lowest bit of x has the 8-cycle ... 0 0 0 1 1 1 1 0 ... ,
    //    ...
    //
    // and if x_initial is 3 mod 4 then
    //
    //   the          lowest bit of x is always 1,
    //   the  next-to-lowest bit of x is always 1,
    //   the 2nd-from-lowest bit of x alternates      ... 0 1 0 1 0 1 0 1 ... ,
    //   the 3rd-from-lowest bit of x 4-cycles        ... 0 0 1 1 0 0 1 1 ... ,
    //   the 4th-from-lowest bit of x has the 8-cycle ... 0 0 1 1 1 1 0 0 ... ,
    //    ...
    //
    // The generator's potency (min. s>=0 with (69069-1)^s = 0 mod 2^32) is
    // 16, which seems to be alright by p. 25, Sec. 3.2.1.3 of Knuth.  It
    // also does well in the dimension 2..5 spectral tests, but it could be
    // better in dimension 6 (Line 15, Table 1, p. 106, Sec. 3.3.4, Knuth).
    //
    // Note that the random number user does not see the values generated
    // here directly since reloadMT() will always munge them first, so maybe
    // none of all of this matters.  In fact, the seed values made here could
    // even be extra-special desirable if the Mersenne Twister theory says
    // so-- that's why the only change I made is to restrict to odd seeds.
    //

    register DWORD x = (new_seed | 1) & 0xFFFFFFFF;
    register DWORD *s = m_State;
    register int    j = 0;

    for(m_Left=0, *s++=x, j=N; --j;
        *s++ = (x*=69069U) & 0xFFFFFFFF);
}

CRandomNumberGenerator2::operator char()
{
   DWORD random_value = GetInteger();

   char return_value = static_cast< char >( random_value >> 9 );

   return( return_value );
}

CRandomNumberGenerator2::operator unsigned char()
{
   DWORD random_value = GetInteger();
   
   unsigned char return_value = static_cast< unsigned char >( random_value >> 17 );

   return( return_value );
}

CRandomNumberGenerator2::operator int()
{
   return( GetInteger() );
}

CRandomNumberGenerator2::operator unsigned int()
{
   return( GetInteger() );
}

CRandomNumberGenerator2::operator short()
{
   return( static_cast< short >( GetInteger() ) );
}

CRandomNumberGenerator2::operator unsigned short()
{
   return( static_cast< unsigned short >( GetInteger() ) );
}

CRandomNumberGenerator2::operator long()
{
   return( static_cast< long >( GetInteger() ) );
}

CRandomNumberGenerator2::operator unsigned long()
{
   return( GetInteger() );
}

CRandomNumberGenerator2::operator float()
{
   return( static_cast< float >( GetFloat() ) );
}

CRandomNumberGenerator2::operator double()
{
   return( GetFloat() );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRandomNumberGenerator2</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, Random number generator, source code, Mersenne Prime Twister">
<META name="description" content="This C++ class gives you a really good random number generator.">
</HEAD>

<BODY>

<H1>CRandomNumberGenerator2</H1>
$Revision: 6 $
<HR>

<H2>Description</H2>

This class implements a better random number generator than the C runtime
library. It uses the Mersenne Twister algorithm. Yehuda Hahn
(<A HREF="mailto:ygh@cfsnet.com">ygh@cfsnet.com</A>) wrote the C version
adapted from
<A HREF="http://www.math.keio.ac.jp/matumoto/cokus.c">http://www.math.keio.ac.jp/matumoto/cokus.c</A>
All I did was wrap it in a C++ class.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>DWORD <B><A NAME="GetInteger">GetInteger</A></B>( void )</PRE><DD>
Returns a 32-bit random integer.

<DT><PRE>double <B><A NAME="GetFloat">GetFloat</A></B>( void )</PRE><DD>
Returns a random float between 0 and 1.

<DT><PRE>void <B><A NAME="InitializeSeed">InitializeSeed</A></B>( void )</PRE><DD>
Initializes the seed value for the generator. To increase randomness,
it uses a combination of the number of milliseconds the NT machine has
been on and the number of free clusters on the current drive to seed
the generator.

<DT><PRE>void <B><A NAME="SetSeed">SetSeed</A></B>( DWORD new_seed )</PRE><DD>
Sets the seed to this value. You can use this if you don't like my
method of seeding.

</DL>

<H2>Operators</H2>

These are what makes this class cool. You can use the class as a
base type.

<UL>
<LI><PRE><B>char</B></PRE>
<LI><PRE><B>unsigned char</B></PRE>
<LI><PRE><B>int</B></PRE>
<LI><PRE><B>unsigned int</B></PRE>
<LI><PRE><B>short</B></PRE>
<LI><PRE><B>unsigned short</B></PRE>
<LI><PRE><B>long</B></PRE>
<LI><PRE><B>unsigned long</B></PRE>
<LI><PRE><B>float</B></PRE>
<LI><PRE><B>double</B></PRE>
</UL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CRandomNumberGenerator( void )
{
   <B>CRandomNumberGenerator2</B> random_number;

   int index = 0;

   while( index &lt; 20 )
   {
      _tprintf( TEXT( &quot;DWORD  random number is %lu\n&quot; ), (DWORD)  random_number );
      _tprintf( TEXT( &quot;double random number is %lf\n&quot; ), (double) random_number );

      index++;
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CRandomNumberGenerator2</B> uses the following API's:
<UL>
<LI>GetDiskFreeSpace
<LI>GetSystemTime
<LI>GetTickCount
</UL>

<H2>Randomness Test</H2>

I'm no mathematician. If you are, please have mercy on me when you
read the results of my randomness tests on this generator.<P>

I ran this generator through a few tests that I could think of for
randomness. Here's the results for generating 100,000,000 32-bit integers
(that makes 3,200,000,000 bits).

<TABLE BORDER="0">
<TR><TD>Number of 1-bits</TD><TD>1,600,024,395</TD></TR>
<TR><TD>Number of 0-bits</TD><TD>1,599,975,605</TD></TR>
<TR><TD>Longest series of 1-bits</TD><TD>31</TD></TR>
<TR><TD>Longest series of 0-bits</TD><TD>37</TD></TR>
</TABLE>

Here's a breakdown of the bits in each of the 32 slots that
make up a 32-bit integer. The count is the number of times
the bit at that location had a value of 1.

<TABLE>
<TR><TD>Bit Number</TD><TD>Number of 1's</TD></TR>
<TR><TD>0</TD><TD>50,001,806</TD></TR>
<TR><TD>1</TD><TD>49,996,289</TD></TR>
<TR><TD>2</TD><TD>49,998,465</TD></TR>
<TR><TD>3</TD><TD>49,995,963</TD></TR>
<TR><TD>4</TD><TD>50,008,188</TD></TR>
<TR><TD>5</TD><TD>49,991,291</TD></TR>
<TR><TD>6</TD><TD>50,010,640</TD></TR>
<TR><TD>7</TD><TD>50,004,980</TD></TR>
<TR><TD>8</TD><TD>50,002,946</TD></TR>
<TR><TD>9</TD><TD>49,997,908</TD></TR>
<TR><TD>10</TD><TD>49,993,413</TD></TR>
<TR><TD>11</TD><TD>50,004,827</TD></TR>
<TR><TD>12</TD><TD>49,998,652</TD></TR>
<TR><TD>13</TD><TD>49,993,790</TD></TR>
<TR><TD>14</TD><TD>50,000,819</TD></TR>
<TR><TD>15</TD><TD>49,995,340</TD></TR>
<TR><TD>16</TD><TD>50,000,634</TD></TR>
<TR><TD>17</TD><TD>50,004,450</TD></TR>
<TR><TD>18</TD><TD>49,999,081</TD></TR>
<TR><TD>19</TD><TD>50,003,646</TD></TR>
<TR><TD>20</TD><TD>50,001,295</TD></TR>
<TR><TD>21</TD><TD>50,005,936</TD></TR>
<TR><TD>22</TD><TD>50,001,090</TD></TR>
<TR><TD>23</TD><TD>50,003,166</TD></TR>
<TR><TD>24</TD><TD>50,003,137</TD></TR>
<TR><TD>25</TD><TD>49,999,151</TD></TR>
<TR><TD>26</TD><TD>49,998,465</TD></TR>
<TR><TD>27</TD><TD>50,001,554</TD></TR>
<TR><TD>28</TD><TD>50,005,453</TD></TR>
<TR><TD>29</TD><TD>50,010,749</TD></TR>
<TR><TD>30</TD><TD>49,995,459</TD></TR>
<TR><TD>31</TD><TD>49,995,812</TD></TR>
</TABLE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CRandomNumberGenerator2.cpp $<BR>
$Modtime: 2/05/00 8:27a $
</BODY>

</HTML>
#endif
