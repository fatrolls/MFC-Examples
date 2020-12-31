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
** $Workfile: CSuperRandomNumberGenerator.cpp $
** $Revision: 10 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CSuperRandomNumberGenerator::CSuperRandomNumberGenerator( DWORD seed )
{
   SetSeed( seed );
}

CSuperRandomNumberGenerator::~CSuperRandomNumberGenerator()
{
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CSuperRandomNumberGenerator::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CSuperRandomNumberGenerator at " ) << (VOID *) this << TEXT( "\n{\n" );

   int index = 0;

   while( index < 25 )
   {
      dump_context << TEXT( "   m_IntegerSeeds[ " ) << index << TEXT( " ] is " ) << m_IntegerSeeds[ index ] << TEXT( "\n" );
      index++;
   }

   index = 0;

   while( index < 25 )
   {
      dump_context << TEXT( "   m_NextValue[ " ) << index << TEXT( " ] is " ) << m_NextValue[ index ] << TEXT( "\n" );
      index++;
   }

   index = 0;

   while( index < 25 )
   {
      dump_context << TEXT( "   m_Seeds[ " ) << index << TEXT( " ] is " ) << m_Seeds[ index ] << TEXT( "\n" );
      index++;
   }

   dump_context << TEXT( "   m_Carry is     " ) << m_Carry     << TEXT( "\n" );
   dump_context << TEXT( "   m_TwoM12 is    " ) << m_TwoM12    << TEXT( "\n" );
   dump_context << TEXT( "   m_TwoM24 is    " ) << m_TwoM24    << TEXT( "\n" );
   dump_context << TEXT( "   m_Index_I24 is " ) << m_Index_I24 << TEXT( "\n" );
   dump_context << TEXT( "   m_Index_J24 is " ) << m_Index_J24 << TEXT( "\n" );
   dump_context << TEXT( "   m_Index24 is   " ) << m_Index24   << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

DWORD CSuperRandomNumberGenerator::GetInteger( void )
{
   double value = GetValue();

   value *= static_cast< double >( 0xFFFFFFFF );

   // Now, the last 8 bits are probably going to be 1
   // To get rid of this flaw in the stream we will
   // do a quick and dirty hash of the bytes that make 
   // up the double value

   const BYTE * buffer = reinterpret_cast< const BYTE *>( &value );

   DWORD hash_value = static_cast< DWORD >( value );
   DWORD temp_value = 0;

   int index = 0;

   while( index < sizeof( value ) )
   {
      hash_value = ( hash_value << 4 ) + buffer[ index ];

      index++;

      temp_value = hash_value & 0xF0000000L;

      if ( temp_value )
      {
         hash_value ^= temp_value >> 24;
      }

      hash_value &= ~temp_value;
   }

   DWORD return_value = static_cast< DWORD >( value );

   return_value += ( ( hash_value >> 5 ) % 256 );

   return( return_value );
}

double CSuperRandomNumberGenerator::GetValue( void )
{
   double temporary_value = 0.0;
   double return_value    = 0.0;

   temporary_value = m_Seeds[ m_Index_J24 ] - m_Seeds[ m_Index_I24 ] - m_Carry;

   if ( temporary_value < (double) 0.0 )
   {
      temporary_value += 1.0;
      m_Carry = m_TwoM24; 
   }
   else
   {
      m_Carry = (double) 0.0;
   }

   m_Seeds[ m_Index_I24 ] = temporary_value;

   m_Index_I24 = m_NextValue[ m_Index_I24 ];
   m_Index_J24 = m_NextValue[ m_Index_J24 ];

   return_value = temporary_value;

   if ( temporary_value < m_TwoM12 )
   {
      return_value += m_TwoM24 * m_Seeds[ m_Index_J24 ];
   }

/* zero is forbidden in case user wants logarithms */

   if ( return_value == 0.0 )
   {
      return_value = m_TwoM24 * m_TwoM24;
   }

   m_Index24++;

   if ( m_Index24 == 24 )
   {
      int i = 0;

      m_Index24 = 0;

      for( i = 1; i <= NUMBER_OF_VALUES_TO_SKIP; i++ )
      {
         temporary_value = m_Seeds[ m_Index_J24 ] - m_Seeds[ m_Index_I24 ] - m_Carry;

         if ( temporary_value < (float) 0.0 )
         {
            temporary_value += 1.0;
            m_Carry = m_TwoM24; 
         }
         else
         {
            m_Carry = (float) 0.0;
         }

         m_Seeds[ m_Index_I24 ] = temporary_value;

         m_Index_I24 = m_NextValue[ m_Index_I24 ];
         m_Index_J24 = m_NextValue[ m_Index_J24 ];
      }
   }

   return( return_value );
}

void CSuperRandomNumberGenerator::m_Initialize( void )
{
   m_Index_I24               = 24;
   m_Index_J24               = 10;
   m_Index24                 = 0;
}

void CSuperRandomNumberGenerator::SetSeed( DWORD jseed )
{
   if ( jseed == 0 )
   {
      CRandomNumberGenerator random;

      jseed = random;
   }

   int lp = 0;
   int i  = 0;
   int k  = 0;

   lp = NUMBER_OF_VALUES_TO_SKIP + 24;
   m_TwoM24 = (double) 1.0;

   for( i = 1; i <= 24; i++ )
   {
      m_TwoM24 *= (double) 0.5;
      k = jseed / 53668;
      jseed = 40014 * ( jseed - ( k * 53668 ) ) - ( k * 12211 );

      if ( jseed < 0 )
      {
         jseed += ICONS;
      }

      m_IntegerSeeds[ i ] = jseed % TWENTY_FOUR_BIT_VALUE;
   }

   m_TwoM12 = m_TwoM24 * (double) 4096.0;

   for( i = 1; i <= 24; i++ )
   {
      m_Seeds[ i ] = static_cast< double >( m_IntegerSeeds[ i ] * m_TwoM24 );
      m_NextValue[ i ] = i - 1;
   }

   m_NextValue[ 1 ] = 24;
   m_Index_I24 = 24;
   m_Index_J24 = 10;
   m_Carry = (double) 0.0;

   if ( m_Seeds[ 24 ] == 0.0 )
   {
      m_Carry = m_TwoM24;
   }
}

// End of source
