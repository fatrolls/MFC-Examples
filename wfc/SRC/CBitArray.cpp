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
** $Workfile: CBitArray.cpp $
** $Revision: 19 $
** $Modtime: 1/17/00 8:57a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CBitArray, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif // _DEBUG

const int CBitArray::m_SizeOfBitRepresentation    = 32;
const int CBitArray::m_MostSignificantBitLocation = 31;

#define AN_ELEMENT_THAT_IS_ALL_ONES (0xFFFFFFFF)

// Construction

CBitArray::CBitArray()
{
#if defined( _DEBUG )
   m_NumberOfBitsPerGroup  = 8;
   m_NumberOfGroupsPerLine = 5;
#endif // _DEBUG

   m_IndexOfFirstBit   = 0;
   m_TotalNumberOfBits = 0;

   RemoveAll();
}

CBitArray::CBitArray( DWORD initial_size )
{
#if defined( _DEBUG )
   m_NumberOfBitsPerGroup  = 8;
   m_NumberOfGroupsPerLine = 5;
#endif // _DEBUG

   m_IndexOfFirstBit   = 0;
   m_TotalNumberOfBits = 0;

   RemoveAll();
   SetSize( initial_size );
}

CBitArray::CBitArray( const CBitArray& source )
{
#if defined( _DEBUG )
   m_NumberOfBitsPerGroup  = 8;
   m_NumberOfGroupsPerLine = 5;
#endif // _DEBUG

   m_IndexOfFirstBit   = 0;
   m_TotalNumberOfBits = 0;

   Copy( source );   
}

CBitArray::CBitArray( const CByteArray& source )
{
#if defined( _DEBUG )
   m_NumberOfBitsPerGroup  = 8;
   m_NumberOfGroupsPerLine = 5;
#endif // _DEBUG

   m_IndexOfFirstBit   = 0;
   m_TotalNumberOfBits = 0;

   Copy( source );   
}

CBitArray::~CBitArray()
{
   RemoveAll();

#if defined( _DEBUG )
   m_NumberOfBitsPerGroup  = 0;
   m_NumberOfGroupsPerLine = 0;
#endif // _DEBUG

   m_IndexOfFirstBit   = 0;
   m_TotalNumberOfBits = 0;
}

// Methods

void CBitArray::Add( DWORD value, DWORD count )
{
   DWORD loop_counter = 0;
   DWORD bit_location = 0;
   DWORD index        = 0;

   while( loop_counter < count )
   {
      bit_location = GetSize();

      if ( m_GetElementIndexOfBitLocation( bit_location, index ) != FALSE )
      {
         if ( index >= static_cast< DWORD >( m_Bits.GetSize() ) )
         {
            // We need to grow the array

            if ( ( count - loop_counter ) > m_SizeOfBitRepresentation )
            {
               if ( value != 0 )
               {
                  m_Bits.Add( AN_ELEMENT_THAT_IS_ALL_ONES );
               }
               else
               {
                  m_Bits.Add( 0 );
               }

               loop_counter        += m_SizeOfBitRepresentation;
               m_TotalNumberOfBits += m_SizeOfBitRepresentation;

               continue;
            }
            else
            {
               // Add a zero bit (an element that is all zeroes)
               m_Bits.Add( 0 );
            }
         }

         m_TotalNumberOfBits++;

         // 1998-12-09 Peter Ekberg (peda@sectra.se) found a really nasty bug here.
         // I had assumed that only zero bits would be added to the array. While
         // this is true, those zero-bits could get stomped on by SetAll() and
         // Complement(). Because of this, we have to set the bit value every time.

         SetAt( bit_location, value );
      }
      else
      {
         ASSERT( FALSE );
      }

      loop_counter++;
   }
}

void CBitArray::AddByte( BYTE value )
{
   Add( bit_test( value, 7 ) );
   Add( bit_test( value, 6 ) );
   Add( bit_test( value, 5 ) );
   Add( bit_test( value, 4 ) );
   Add( bit_test( value, 3 ) );
   Add( bit_test( value, 2 ) );
   Add( bit_test( value, 1 ) );
   Add( bit_test( value, 0 ) );
}

void CBitArray::AddValue( DWORD value, DWORD number_of_bits )
{
   ASSERT( number_of_bits < 33 );

   if ( number_of_bits > 32 )
   {
      return;
   }

   DWORD index = 0;

   while( index < number_of_bits )
   {
      Add( 0 );
      index++;
   }

   DWORD offset = number_of_bits - 1;

   index = 0;

   DWORD starting_bit_location = GetSize() - number_of_bits;

   while( index < number_of_bits )
   {
      if ( bit_test( value, offset ) == 1 )
      {
         // Remember, we added only zeroes above, so we only
         // need to worry about setting one-values.

         SetAt( starting_bit_location + index, 1 );
      }

      index++;
      offset--;
   }
}

void CBitArray::Append( const CBitArray& source )
{
   // This method is a cheap and cheesy way of appending.
   // I should probably re-write it to take advantage
   // of m_SizeOfBitRepresentation and append things
   // an element at a time

   DWORD index          = 0;
   DWORD number_of_bits = source.GetSize();

   while( index < number_of_bits )
   {
      Add( source.GetAt( index ) );
      index++;
   }
}

void CBitArray::Append( const BYTE * data, DWORD number_of_bytes )
{
   // We were passed a pointer, don't trust it

   try
   {
      DWORD index = 0;

      while( index < number_of_bytes )
      {
         AddByte( data[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CBitArray::Complement( void )
{
   // Set all 1's to 0's and all 0's to 1's

   DWORD index              = m_IndexOfFirstBit / m_SizeOfBitRepresentation;
   DWORD number_of_elements = m_Bits.GetSize();

   // We set index to the first element that contains good bits.
   // We are skipping any elements at the beginning of m_Bits
   // that contain LeftTrim()'d bits. In other words, don't
   // complement unused bits.

   while( index < number_of_elements )
   {
      m_Bits.ElementAt( index ) ^= AN_ELEMENT_THAT_IS_ALL_ONES;
      index++;
   }
}

void CBitArray::Copy( const CBitArray& source )
{
   m_Bits.Copy( source.m_Bits );
   m_TotalNumberOfBits = source.m_TotalNumberOfBits;
   m_IndexOfFirstBit   = source.m_IndexOfFirstBit;
}

void CBitArray::Copy( const CByteArray& source )
{
   RemoveAll();

   DWORD index           = 0;
   DWORD number_of_bytes = source.GetSize();

   if ( number_of_bytes > sizeof( DWORD ) )
   {
      // We can add things 32 bits at a time

      DWORD value_to_add = 0;

      while( index < (int) ( number_of_bytes - sizeof( DWORD ) ) )
      {
         value_to_add = MAKELONG( MAKEWORD( source.GetAt( index + 3 ), source.GetAt( index + 2 ) ), MAKEWORD( source.GetAt( index + 1 ), source.GetAt( index ) ) );
         m_Bits.Add( value_to_add );
         index += sizeof( DWORD );
      }
   }

   while( index < number_of_bytes )
   {
      AddByte( source.GetAt( index ) );
      index++;
   }
}

void CBitArray::CopyTo( CByteArray& destination )
{
   if ( GetSize() == 0 )
   {
      destination.RemoveAll();
      return;
   }

   FreeExtra();

   DWORD bits               = 0;
   DWORD number_of_elements = m_Bits.GetSize();
   DWORD index              = 0;

   WORD word = 0;

   // 1998-12-09 Optimization suggested by Peter Ekberg (peda@sectra.se)

   destination.SetSize( number_of_elements * sizeof( DWORD ) );

   // Get a raw pointer. This is the fastest way to access memory

   BYTE * buffer_pointer = destination.GetData();

   DWORD buffer_index = 0;

   while( index < number_of_elements )
   {
      bits = m_Bits.GetAt( index );

      word = HIWORD( bits );

      buffer_pointer[ buffer_index ] = HIBYTE( word );
      buffer_index++;

      buffer_pointer[ buffer_index ] = LOBYTE( word );
      buffer_index++;

      word = LOWORD( bits );

      buffer_pointer[ buffer_index ] = HIBYTE( word );
      buffer_index++;

      buffer_pointer[ buffer_index ] = LOBYTE( word );
      buffer_index++;

      index++;
   }

   // We have added a number of bytes that is divisible by four
   // We may not have needed to do such a thing. Let's see if
   // we can get rid of a couple of bytes.

   DWORD number_of_bytes = ( GetSize() + 7 ) / 8;

   destination.SetSize( number_of_bytes );
}

void CBitArray::CopyTo( CDWordArray& destination )
{
   FreeExtra();
   destination.Copy( m_Bits );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CBitArray::SetDumpOptions( int number_of_bits_per_group, int number_of_groups_per_line )
{
   m_NumberOfBitsPerGroup  = number_of_bits_per_group;
   m_NumberOfGroupsPerLine = number_of_groups_per_line;
}

void CBitArray::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_TotalNumberOfBits is " ) << m_TotalNumberOfBits << TEXT( "\n" );
   dump_context << TEXT( "   m_IndexOfFirstBit   is " ) << m_IndexOfFirstBit   << TEXT( "\n" );

   CString debug_string;
   CString line_number_string;

   DWORD index                = 0;
   DWORD line_index           = 0;
   DWORD line_number          = 0;
   DWORD total_number_of_bits = GetSize();

   int digits_in_group = 0;

   while( index < total_number_of_bits )
   {
      if ( GetAt( index ) == 1 )
      {
         debug_string += TEXT( '1' );
      }
      else
      {
         debug_string += TEXT( '0' );
      }

      digits_in_group++;

      if ( digits_in_group >= (int) m_NumberOfBitsPerGroup )
      {
         debug_string += TEXT( ' ' );
         digits_in_group = 0;

         line_index++;

         if ( line_index == static_cast< DWORD >( m_NumberOfGroupsPerLine ) )
         {
            line_number_string.Format( TEXT( "%05lu : " ), line_number );
            debug_string += TEXT( '\n' );
            line_number_string += debug_string;
            dump_context << line_number_string;
            debug_string.Empty();
            line_number_string.Empty();
            line_index = 0;
            line_number = index + 1;
         }
      }

      index++;
   }

   if ( debug_string.GetLength() > 0 )
   {
      debug_string += TEXT( '\n' );
      line_number_string.Format( TEXT( "%05lu : " ), line_number );
      line_number_string += debug_string;
      dump_context << line_number_string;
   }

   if ( dump_context.GetDepth() > 0 )
   {
      m_Bits.Dump( dump_context );
   }

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CBitArray::Find( const CBitArray& value, DWORD& found_at, DWORD starting_at ) const
{
   DWORD value_to_search_for = 0;

   if ( value.GetSize() <= m_SizeOfBitRepresentation )
   {
      // We can fit the bit array into a single DWORD value, let's
      // use the fast version of this function

      value_to_search_for = value.GetValue( 0, value.GetSize() );

      return( Find( value_to_search_for, value.GetSize(), found_at, starting_at ) );
   }

   // OK, we're bigger than a DWORD, that means we have to do things the hard way

   value_to_search_for = value.GetValue( 0, m_SizeOfBitRepresentation );

   BOOL exit_loop       = FALSE;
   BOOL value_was_found = FALSE;

   DWORD starting_index = starting_at;
   DWORD ending_index   = GetSize();
   DWORD size_of_value  = value.GetSize();
   DWORD found_index    = 0;
   DWORD loop_index     = 0;
   DWORD this_bit       = 0;
   DWORD that_bit       = 0;

   while( exit_loop == FALSE )
   {
      if ( ( starting_index + size_of_value ) > ending_index )
      {
         // We ran out of room looking for the pattern
         return( FALSE );
      }

      if ( Find( value_to_search_for, m_SizeOfBitRepresentation, found_index, starting_index ) == TRUE )
      {
         // We found the first 32 (sizeof(DWORD)) bits, let's look for the
         // rest for them

         starting_index = found_index;

         loop_index = 0;

         value_was_found = TRUE;

         this_bit = 0;
         that_bit = 0;

         while( loop_index < ( size_of_value - m_SizeOfBitRepresentation ) )
         {
            this_bit = value.GetAt( m_SizeOfBitRepresentation + loop_index );
            that_bit = GetAt( m_SizeOfBitRepresentation + loop_index + found_index );

            if ( this_bit == that_bit )
            {
               loop_index++;
            }
            else
            {
               value_was_found = FALSE;
               starting_index++;
               loop_index = size_of_value; // Exit this loop
            }
         }

         if ( value_was_found == TRUE )
         {
            found_at = found_index;
            return( TRUE );
         }
      }
      else
      {
         // Can't find the bit-pattern
         return( FALSE );
      }
   }

   return( FALSE );
}

BOOL CBitArray::Find( DWORD value, DWORD number_of_bits_in_value, DWORD& found_at, DWORD starting_at ) const
{
   // Always start at a known state
   found_at = 0;

   ASSERT( number_of_bits_in_value <= GetSize() );

   if ( number_of_bits_in_value > GetSize() )
   {
      // There aren't enough bits in the array to possibly match the pattern.
      // There are more bits in the pattern than in the array.
      return( FALSE );
   }

   DWORD upper_bound = GetUpperBound();

   // Let's do a Boyer-Moore'ish kind of search

   DWORD desired_number_of_ones   = 0;
   DWORD desired_number_of_zeroes = 0;
   DWORD index                    = 0;

   // Let's count the number of ones and zeroes in the pattern we're searching for

   while( index < number_of_bits_in_value )
   {
      if ( bit_test( value, index ) == 1 )
      {
         desired_number_of_ones++;
      }
      else
      {
         desired_number_of_zeroes++;
      }

      index++;
   }

   // We reduce upper_bound because we can't possibly match
   // the pattern when there are fewer number of bits remaining
   // in the array than are in the pattern.

   upper_bound -= number_of_bits_in_value;

   DWORD value_to_test          = 0;
   DWORD number_of_bits_to_skip = 0;
   DWORD number_of_ones         = 0;
   DWORD number_of_zeroes       = 0;

   // Finally! We're ready to start searching the array

   while( starting_at <= upper_bound )
   {
      value_to_test = GetValue( starting_at, number_of_bits_in_value );

      if ( value_to_test == value )
      {
         found_at = starting_at;
         return( TRUE );
      }

      // OK, we haven't found the desired value (i.e. bit-pattern)
      // Let's use the Boyer-Moore'ish trick of jumping ahead a few
      // bits instead of incrementing by only one. The first step in
      // determining how many bits we can skip is to count the number
      // of ones and zeroes in the value we just pulled from the array.

      index                  = 0;
      number_of_ones         = 0;
      number_of_zeroes       = 0;
      number_of_bits_to_skip = 1; // We can always skip one bit

      while( index < number_of_bits_in_value )
      {
         if ( bit_test( value_to_test, index ) == 1 )
         {
            number_of_ones++;
         }
         else
         {
            number_of_zeroes++;
         }

         index++;
      }

      // Now we know how many ones and zeroes are in the value we
      // know isn't the right one, and we know how many ones and
      // zeroes are in the value we're searching for. Here's where
      // Boyer-Moore comes in. We know the number of ones in the
      // pattern we're searching for and the number of ones in the
      // portion of the array we get from the array must be equal.
      // Likewise, the number of zeroes must be equal. Given this
      // fact, we can calculate the difference between what we
      // need and what we found and skip ahead those number of bits.
      // For example, if the pattern we're searching for has 31 zeroes
      // and the number of zeroes in what we just pulled from the array
      // contained only 15 zeroes, we can safely skip the next 16 bits.
      // Kinda neato.

      if ( number_of_ones < desired_number_of_ones )
      {
         number_of_bits_to_skip = desired_number_of_ones - number_of_ones;
      }

      if ( number_of_zeroes < desired_number_of_zeroes )
      {
         // Let's see if this difference is greater than the current number of bits to skip

         if ( ( desired_number_of_zeroes - number_of_zeroes ) > number_of_bits_to_skip )
         {
            number_of_bits_to_skip = desired_number_of_zeroes - number_of_zeroes;
         }
      }

      starting_at += number_of_bits_to_skip;
   }

   return( FALSE );
}

void CBitArray::FreeExtra( void )
{
   DWORD number_of_bits = m_IndexOfFirstBit;

   if ( number_of_bits >= m_TotalNumberOfBits )
   {
      RemoveAll();
      return;
   }

   while( number_of_bits >= m_SizeOfBitRepresentation )
   {
      m_Bits.RemoveAt( 0 );
      number_of_bits      -= m_SizeOfBitRepresentation;
      m_TotalNumberOfBits -= m_SizeOfBitRepresentation;
   }

   DWORD this_set_of_bits = 0;
   DWORD that_set_of_bits = 0;
   DWORD index            = 0;
   DWORD bit_number       = 0;

   while( number_of_bits > 0 )
   {
      this_set_of_bits = 0;
      that_set_of_bits = 0;
      index            = 0;
      bit_number       = m_MostSignificantBitLocation;

      // Always start at the beginning of the array

      this_set_of_bits = m_Bits.GetAt( index );

      if ( bit_number > 0 )
      {
         // Only kill the bit if it ain't the LSB

         DWORD bit_index = bit_number - 1;

         while( ( bit_index + 1 ) > 0 )
         {
            // Why can't I do a left shift here?

            if ( bit_test( this_set_of_bits, bit_index ) != 0 )
            {
               bit_set( this_set_of_bits, bit_index + 1 );
            }
            else
            {
               bit_clear( this_set_of_bits, bit_index + 1 );
            }

            bit_index--;
         }

         m_Bits.SetAt( index, this_set_of_bits );
      }

      DWORD loop_index = m_Bits.GetUpperBound();

      while( index < loop_index )
      {
         this_set_of_bits = m_Bits.GetAt( index );
         that_set_of_bits = m_Bits.GetAt( index + 1 );

         if ( bit_test( that_set_of_bits, m_MostSignificantBitLocation ) == 1 )
         {
            bit_set( this_set_of_bits, 0 );
         }
         else
         {
            bit_clear( this_set_of_bits, 0 );
         }

         that_set_of_bits <<= 1;

         m_Bits.SetAt( index,     this_set_of_bits );
         m_Bits.SetAt( index + 1, that_set_of_bits );

         index++;
      }

      number_of_bits--;
      m_TotalNumberOfBits--;
   }

   m_IndexOfFirstBit = 0;
}

DWORD CBitArray::GetAt( DWORD bit_location ) const
{
   DWORD size = GetSize();

   ASSERT( bit_location < size );

   if ( bit_location >= size )
   {
      return( 0 );
   }

   DWORD index      = 0;
   DWORD bit_number = 0;

   if ( m_GetElementIndexOfBitLocation( bit_location, index, &bit_number ) == FALSE )
   {
      ASSERT( FALSE );
      return( 0 );
   }

   if ( index >= static_cast< DWORD >( m_Bits.GetSize() ) )
   {
      ASSERT( FALSE );
      return( 0 );
   }

   DWORD temp_bits = m_Bits.GetAt( index );

   if ( bit_test( temp_bits, bit_number ) == 1 )
   {
      return( 1 );
   }

   return( 0 );
}

DWORD CBitArray::GetNumberOfOnes( void ) const
{
   DWORD index          = 0;
   DWORD number_of_ones = 0;
   DWORD number_of_bits = GetSize();

   while( index < number_of_bits )
   {
      if ( GetAt( index ) == 1 )
      {
         number_of_ones++;
      }

      index++;
   }

   return( number_of_ones );
}

DWORD CBitArray::GetNumberOfZeroes( void ) const
{
   return( GetSize() - GetNumberOfOnes() );
}

DWORD CBitArray::GetSize( void ) const
{
   return( m_TotalNumberOfBits - m_IndexOfFirstBit );
}

DWORD CBitArray::GetUpperBound( void ) const
{
   if ( GetSize() > 0 )
   {
      return( GetSize() - 1 );
   }

   return( 0 );
}

DWORD CBitArray::GetValue( DWORD starting_bit_location, DWORD number_of_bits ) const
{
   ASSERT( number_of_bits < 33 );

   if ( number_of_bits > m_SizeOfBitRepresentation )
   {
      return( 0 );
   }

   if ( ( starting_bit_location + number_of_bits ) > GetSize() )
   {
      return( 0 );
   }

   DWORD return_value = 0;
   DWORD index        = 0;
   DWORD bit_value    = 0;

   while( index < number_of_bits )
   {
      return_value <<= 1;

      bit_value = GetAt( starting_bit_location + index );

      return_value += bit_value;
      index++;
   }

   return( return_value );
}

void CBitArray::InsertAt( DWORD bit_location, DWORD value )
{
   if ( bit_location == 0 )
   {
      if ( m_IndexOfFirstBit > 0 )
      {
         m_IndexOfFirstBit--;
         SetAt( 0, value );
         return;
      }
   }

   if ( bit_location > GetUpperBound() )
   {
      // Attempting to insert passed the end of the array
      // we call this kind of thing Append().

      Add( value );
   }

   Add( 0 );

   DWORD this_set_of_bits = 0;
   DWORD that_set_of_bits = 0;
   DWORD index            = 0;
   DWORD bit_number       = 0;

   if ( m_GetElementIndexOfBitLocation( bit_location, index, &bit_number ) == FALSE )
   {
      ASSERT( FALSE );
      return;
   }

   DWORD loop_index = m_Bits.GetUpperBound();

   if ( loop_index >= 1 )
   {
      this_set_of_bits = m_Bits.GetAt( loop_index );
      this_set_of_bits >>= 1;

      m_Bits.SetAt( loop_index, this_set_of_bits );

      loop_index--;

      while( loop_index > index )
      {
         that_set_of_bits = m_Bits.GetAt( loop_index + 1 );
         this_set_of_bits = m_Bits.GetAt( loop_index );

         // The most significant bit of that set of bit should be equal to
         // the least significant bit of this set of bits.

         if ( bit_test( this_set_of_bits, 0 ) == 1 )
         {
            bit_set( that_set_of_bits, m_MostSignificantBitLocation );
         }
         else
         {
            bit_clear( that_set_of_bits, m_MostSignificantBitLocation );
         }

         this_set_of_bits >>= 1;

         m_Bits.SetAt( loop_index + 1, that_set_of_bits );
         m_Bits.SetAt( loop_index,     this_set_of_bits );

         loop_index--;
      }

      this_set_of_bits = m_Bits.GetAt( index );

      DWORD upper_bound = m_Bits.GetUpperBound();

      if ( bit_number != 0 && index < upper_bound )
      {
         that_set_of_bits = m_Bits.GetAt( index + 1 );

         if ( bit_test( this_set_of_bits, 0 ) == 1 )
         {
            bit_set( that_set_of_bits, m_MostSignificantBitLocation );
         }
         else
         {
            bit_clear( that_set_of_bits, m_MostSignificantBitLocation );
         }

         m_Bits.SetAt( index + 1, that_set_of_bits );
         m_Bits.SetAt( index,     this_set_of_bits );
      }
   }

   // Now the least significant bit is safe

   this_set_of_bits = m_Bits.GetAt( index );

   DWORD bit_index = 0;

   while( bit_index < bit_number )
   {
      if ( bit_test( this_set_of_bits, bit_index + 1 ) == 1 )
      {
         bit_set( this_set_of_bits, bit_index );
      }
      else
      {
         bit_clear( this_set_of_bits, bit_index );
      }

      bit_index++;
   }

   if ( value != 0 )
   {
      bit_set( this_set_of_bits, bit_number );
   }
   else
   {
      bit_clear( this_set_of_bits, bit_number );
   }

   m_Bits.SetAt( index, this_set_of_bits );
}

CBitArray CBitArray::Left( DWORD number_of_bits ) const
{
   CBitArray return_value;

   if ( number_of_bits >= GetSize() )
   {
      return_value.Copy( *this );
   }
   else
   {
      DWORD index = 0;

      while( index < number_of_bits )
      {
         return_value.Add( GetAt( index ) );
         index++;
      }
   }

   return( return_value );
}

void CBitArray::LeftTrim( DWORD number_of_bits )
{
   if ( number_of_bits >= GetSize() )
   {
      RemoveAll();
      return;
   }

   m_IndexOfFirstBit += number_of_bits;
}

#if defined( _DEBUG )

// 1998-12-05
// New calcuation provided by Peter Ekberg (peda@sectra.se) to get rid of floating point calculations

BOOL CBitArray::m_GetElementIndexOfBitLocation( const DWORD bit_location, DWORD& index, DWORD * bit_number_p ) const
{
   index = ( bit_location + m_IndexOfFirstBit ) / m_SizeOfBitRepresentation;

   if ( bit_number_p != NULL )
   {
      *bit_number_p = m_MostSignificantBitLocation - ( ( bit_location + m_IndexOfFirstBit ) % m_SizeOfBitRepresentation );
   }

   return( TRUE );
}

#endif // _DEBUG

CBitArray CBitArray::Mid( DWORD starting_at, DWORD number_of_bits ) const
{
   CBitArray return_value;

   if ( starting_at > GetUpperBound() )
   {
      // There's nothing to return
      return( return_value );
   }

   if ( ( starting_at + number_of_bits ) > GetUpperBound() )
   {
      return( return_value );
   }

   DWORD index = 0;

   while( index < number_of_bits )
   {
      return_value.Add( GetAt( index + starting_at ) );
      index++;
   }

   return( return_value );
}

void CBitArray::RemoveAll( void )
{
   m_Bits.RemoveAll();
   m_TotalNumberOfBits = 0;
   m_IndexOfFirstBit   = 0;
}

void CBitArray::RemoveAt( DWORD bit_location )
{
   ASSERT( GetSize() > 0 );

   if ( GetSize() < 1 )
   {
      return;
   }

   // There one simple optimization we can perform, if the user
   // wants to remove the bit at the beginning, it is the same
   // as LeftTrim()'ing

   if ( bit_location == 0 )
   {
      LeftTrim( 1 );
      return;
   }

   if ( bit_location > GetUpperBound() )
   {
      return;
   }

   DWORD this_set_of_bits = 0;
   DWORD that_set_of_bits = 0;
   DWORD index            = 0;
   DWORD bit_number       = 0;

   if ( m_GetElementIndexOfBitLocation( bit_location, index, &bit_number ) == FALSE )
   {
      ASSERT( FALSE );
      return;
   }

   this_set_of_bits = m_Bits.GetAt( index );

   if ( bit_number > 0 )
   {
      DWORD bit_index = bit_number - 1;

      while( ( bit_index + 1 ) > 0 )
      {
         if ( bit_test( this_set_of_bits, bit_index ) == 1 )
         {
            bit_set( this_set_of_bits, bit_index + 1 );
         }
         else
         {
            bit_clear( this_set_of_bits, bit_index + 1 );
         }

         bit_index--;
      }

      m_Bits.SetAt( index, this_set_of_bits );
   }

   DWORD loop_index = m_Bits.GetUpperBound();

   while( index < loop_index )
   {
      this_set_of_bits = m_Bits.GetAt( index );
      that_set_of_bits = m_Bits.GetAt( index + 1 );

      if ( bit_test( that_set_of_bits, m_MostSignificantBitLocation ) == 1 )
      {
         bit_set( this_set_of_bits, 0 );
      }
      else
      {
         bit_clear( this_set_of_bits, 0 );
      }

      that_set_of_bits <<= 1;

      m_Bits.SetAt( index,     this_set_of_bits );
      m_Bits.SetAt( index + 1, that_set_of_bits );

      index++;
   }

   m_TotalNumberOfBits--;
}

CBitArray CBitArray::Right( DWORD number_of_bits ) const
{
   CBitArray return_value;

   if ( number_of_bits >= GetSize() )
   {
      return_value.Copy( *this );
   }
   else
   {
      DWORD index        = 0;
      DWORD get_at_index = GetSize() - number_of_bits;

      while( index < number_of_bits )
      {
         return_value.Add( GetAt( get_at_index + index ) );
         index++;
      }
   }

   return( return_value );
}

void CBitArray::RightTrim( DWORD number_of_bits )
{
   if ( number_of_bits >= GetSize() )
   {
      RemoveAll();
      return;
   }

   m_TotalNumberOfBits -= number_of_bits;

   // 1998-12-09 Peter Ekberg (peda@sectra.se) found a bug here. I was
   // having a bit of a rounding error (no, I couldn't resist the pun).

   DWORD number_of_elements = GetSize();

   number_of_elements += ( m_SizeOfBitRepresentation - 1 );
   number_of_elements /= m_SizeOfBitRepresentation;

   m_Bits.SetSize( number_of_elements );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CBitArray::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   m_Bits.Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << m_TotalNumberOfBits;
   }
   else
   {
      archive >> m_TotalNumberOfBits;
   }
}

#endif // WFC_NO_SERIALIZATION

void CBitArray::SetAll( DWORD value )
{
   if ( value != 0 )
   {
      memset( m_Bits.GetData(), 0xFF, ( m_Bits.GetSize() * sizeof( DWORD ) ) );
   }
   else
   {
      memset( m_Bits.GetData(), 0x00, ( m_Bits.GetSize() * sizeof( DWORD ) ) );
   }
}

void CBitArray::SetAt( DWORD bit_location, DWORD value )
{
   ASSERT( bit_location < GetSize() );

   if ( bit_location > GetUpperBound() )
   {
      return;
   }

   DWORD index      = 0;
   DWORD bit_number = 0;

   if ( m_GetElementIndexOfBitLocation( bit_location, index, &bit_number ) == FALSE )
   {
      ASSERT( FALSE );
      return;
   }

   // Thanks go to Anne Davidson (davidsoa@nichols.com) for finding
   // a bug here. I should have been testing for greater than or
   // equal to, not just greater than. DOH!
   // 1998-07-21

   if ( index >= static_cast< DWORD >( m_Bits.GetSize() ) )
   {
      return;
   }

   DWORD this_set_of_bits = m_Bits.GetAt( index );

   if ( value != 0 )
   {
      bit_set( this_set_of_bits, bit_number );
   }
   else
   {
      bit_clear( this_set_of_bits, bit_number );
   }

   m_Bits.SetAt( index, this_set_of_bits );
}

void CBitArray::SetSize( DWORD number_of_bits )
{
   if ( number_of_bits == 0 )
   {
      RemoveAll();
      return;
   }

   // Thanks go to Jeff Winkler (winkler1@sprynet.com)
   // for finding a bug here where number_of_bits is
   // less than m_SizeOfBitRepresentation and GetSize()
   // is zero. It would not add. DOH!

   DWORD number_of_elements = static_cast< DWORD >( m_Bits.GetSize() );

   if ( number_of_bits > ( number_of_elements * m_SizeOfBitRepresentation ) )
   {
      DWORD number_of_elements_to_add = number_of_bits - GetSize();

      // Thanks go to Anne Davidson (davidsoa@nichols.com) for finding
      // a bug here in that caused a rounding error.
      // 1998-07-21

      number_of_elements_to_add += ( m_SizeOfBitRepresentation - 1 );

      number_of_elements_to_add /= m_SizeOfBitRepresentation;

      if ( number_of_elements == 0 && number_of_elements_to_add == 0 )
      {
         // Dang math problem...
         number_of_elements_to_add++;
      }

      m_Bits.SetSize( number_of_elements + number_of_elements_to_add );
   }

   // 1998-12-09 Peter Ekberg (peda@sectra.se) found a bug here. I was
   // not adding m_IndexOfFirstBit to number_of_bits. This was stupid of me. :-(
   m_TotalNumberOfBits = number_of_bits + m_IndexOfFirstBit;
}

void CBitArray::SetValue( DWORD starting_bit_location, DWORD value, DWORD number_of_bits )
{
   ASSERT( number_of_bits <= m_SizeOfBitRepresentation );

   if ( number_of_bits > m_SizeOfBitRepresentation || number_of_bits < 1 )
   {
      return;
   }

   DWORD index  = 0;
   DWORD offset = number_of_bits - 1;

   while( index < number_of_bits )
   {
      // 1998-12-08 Thanks to Peter Ekberg (peda@sectra.se) for finding
      // a bug here. I had the arguments to bit_test() reversed.

      SetAt( starting_bit_location + index, bit_test( value, offset ) );
      index++;
      offset--;
   }
}

CBitArray& CBitArray::operator=( const CBitArray& source )
{
   Copy( source );
   return( *this );
}

CBitArray& CBitArray::operator=( const CByteArray& source )
{
   Copy( source );
   return( *this );
}

CBitArray& CBitArray::operator+=( const CBitArray& source )
{
   Append( source );
   return( *this );
}

CBitArray& CBitArray::operator+=( const CByteArray& source )
{
   Append( source );
   return( *this );
}

DWORD CBitArray::operator[]( int index ) const
{
   return( GetAt( index ) );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CBitArray</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, bits, bit array, array of bits, source code">
<META name="description" content="This C++ class let's you manipulate a set of bits like it was an array.">
</HEAD>


<BODY>

<H1>CBitArray</H1>
$Revision: 19 $<BR><HR>

<H2>Description</H2>

This class treats bits like they were an integral type.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CBitArray</B>()
<B>CBitArray</B>( DWORD initial_size )
<B>CBitArray</B>( const CBitArray&amp; source )
<B>CBitArray</B>( const CByteArray&amp; source )<DD>
Constructs this object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B><A NAME="Add">Add</A></B>( DWORD bit_to_add, DWORD count = 1 )</PRE><DD>
Appends a new bit to the array. If <CODE>bit_to_add</CODE>
is not zero, a 1-bit is added.

<DT><PRE>void <B><A NAME="AddByte">AddByte</A></B>( BYTE byte_to_add )</PRE><DD>
Appends byte (8 bits) to the array.

<DT><PRE>void <B><A NAME="AddValue">AddValue</A></B>( DWORD value_to_add, DWORD number_of_bits_in_value )</PRE><DD>
Appends a a value to the array. You specify how many bits are in <CODE>value_to_add</CODE>
(up to 32).

<DT><PRE>void <B><A NAME="Append">Append</A></B>( const CBitArray&amp; source  )
void <B>Append</B>( const BYTE * data, DWORD number_of_bytes )</PRE><DD>
Appends a whole bunch of bits to the array.

<DT><PRE>void <B><A NAME="Complement">Complement</A></B>( void )</PRE><DD>
Turns every zero into a one and every one into a zero in the array.

<DT><PRE>void <B><A NAME="Copy">Copy</A></B>( const CBitArray&amp; source )
void <B>Copy</B>( const CByteArray&amp; source )</PRE><DD>
Copies bits from the specified <CODE>source</CODE>.

<DT><PRE>void <B><A NAME="CopyTo">CopyTo</A></B>( CByteArray&amp; destination )
void <B>CopyTo</B>( CDWordArray&amp; destination )</PRE><DD>
Exports the bits to the <CODE>destination</CODE> supplied.

<DT><PRE>BOOL <B><A NAME="Find">Find</A></B>( const CBitArray&amp; value, DWORD&amp; found_at, DWORD starting_at = 0 ) const
BOOL <B>Find</B>( DWORD value, DWORD number_of_bits_in_value, DWORD&amp; found_at, DWORD starting_at = 0 ) const</PRE><DD>
Searches for a bit pattern in the array. If it returns TRUE, <CODE>found_at</CODE>
will be filled with the index where the pattern begins.

<DT><PRE>void <B><A NAME="FreeExtra">FreeExtra</A></B>( void )</PRE><DD>
Compresses the memory used to store the bits.

<DT><PRE>DWORD <B><A NAME="GetAt">GetAt</A></B>( DWORD index ) const</PRE><DD>
Returns a 1 if the bit at that <CODE>index</CODE> is not zero.
It will return 0 if that bit is a zero. If <CODE>index</CODE>
is something wacky (i.e. passed the end of the array), it will
return 0.

<DT><PRE>DWORD <B><A NAME="GetNumberOfOnes">GetNumberOfOnes</A></B>( void ) const</PRE><DD>
Returns the number of bits that are 1.

<DT><PRE>DWORD <B><A NAME="GetNumberOfZeroes">GetNumberOfZeroes</A></B>( void ) const</PRE><DD>
Returns the number of bits that are 0.

<DT><PRE>DWORD <B><A NAME="GetSize">GetSize</A></B>( void ) const</PRE><DD>
Returns the number of bits in the array.

<DT><PRE>DWORD <B><A NAME="GetUpperBound">GetUpperBound</A></B>( void ) const</PRE><DD>
Returns the current upper bound of this array. Because array indexes are zero-based, this function returns a value 1 less than GetSize().

<DT><PRE>DWORD <B><A NAME="GetValue">GetValue</A></B>( DWORD index, DWORD length ) const</PRE><DD>
Returns the value at the given location.

<DT><PRE>void <B><A NAME="InsertAt">InsertAt</A></B>( DWORD index, DWORD value )</PRE><DD>
Inserts a single bit at the given <CODE>index</CODE>.

<DT><PRE>CBitArray <B><A NAME="Left">Left</A></B>( DWORD number_of_bits ) const</PRE><DD>
Returns the left-most <CODE>number_of_bits</CODE>.

<DT><PRE>void <B><A NAME="LeftTrim">LeftTrim</A></B>( DWORD number_of_bits )</PRE><DD>
Trims the <CODE>number_of_bits</CODE> from the beginning
of the array.

<DT><PRE>CBitArray <B><A NAME="Mid">Mid</A></B>( DWORD starting_at_index, DWORD number_of_bits ) const</PRE><DD>
Returns <CODE>number_of_bits</CODE> beginning at <CODE>starting_at_index</CODE>.

<DT><PRE>void <B><A NAME="RemoveAll">RemoveAll</A></B>( void )</PRE><DD>
Clears the array. It removes all bits.

<DT><PRE>void <B><A NAME="RemoveAt">RemoveAt</A></B>( DWORD index )</PRE><DD>
Removes a single bit at the given <CODE>index</CODE>.

<DT><PRE>CBitArray <B><A NAME="Right">Right</A></B>( DWORD number_of_bits )</PRE><DD>
Returns the last <CODE>number_of_bits</CODE> in the array.

<DT><PRE>void <B><A NAME="RightTrim">RightTrim</A></B>( DWORD number_of_bits )</PRE><DD>
Removes the last <CODE>number_of_bits</CODE> from the array.

<DT><PRE>void <B><A NAME="Serialize">Serialize</A></B>( CArchive&amp; archive )</PRE><DD>
After all, we are a CObject...

<DT><PRE>void <B><A NAME="SetAll">SetAll</A></B>( DWORD value )</PRE><DD>
Sets all of the bits in the array to <CODE>value</CODE>.

<DT><PRE>void <B><A NAME="SetAt">SetAt</A></B>( DWORD index, DWORD value )</PRE><DD>
Sets the bits at the given <CODE>index</CODE> to <CODE>value</CODE>.

<DT><PRE>void <B><A NAME="SetSize">SetSize</A></B>( DWORD size )</PRE><DD>
Allocates enough memory to hold <CODE>size</CODE> bits.

<DT><PRE>void <B><A NAME="SetValue">SetValue</A></B>( DWORD index, DWORD value, DWORD length )</PRE><DD>
Beginning at <CODE>index</CODE>, the bits in <CODE>value</CODE> will
replace the bits in the array for <CODE>length</CODE> number of bits.

</DL>

<H2>Operators</H2>

<DL COMPACT>

<DT><PRE>CBitArray&amp; operator <B>=</B> ( const CBitArray&amp; source )
CBitArray&amp; operator <B>=</B> ( const CByteArray& source )</PRE><DD>
Basically calls <B>Copy</B>().

<DT><PRE>CBitArray&amp; operator <B>+=</B> ( const CBitArray&amp; source )
CBitArray&amp; operator <B>+=</B> ( const CByteArray&amp; source )</PRE><DD>
Basically calls <B>Append</B>().

<DT><PRE>DWORD operator <B>[]</B> ( int index ) const</PRE><DD>
Calls <B>GetAt</B>().

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>CBitArray</B> bits;

   bits.Add( 0x55 );

   _tprintf( TEXT( &quot;Bit number 7 is %d\n&quot;, (int) bits.GetAt( 7 ) );

   bits.SetAt( 7, 0 ); // Turn bit 7 off
}</CODE></PRE>
<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CBitArray.cpp $<BR>
$Modtime: 1/17/00 8:57a $
</BODY>

</HTML>
#endif
