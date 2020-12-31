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
** $Workfile: csmtf.cpp $
** $Revision: 19 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CUINT64
*/

// Construction

CUINT64::CUINT64()
{
   WFCLTRACEINIT( TEXT( "CUINT64::CUINT64()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CUINT64::CUINT64( const CUINT64& source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::CUINT64( CUINT64& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CUINT64::CUINT64( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER * source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::CUINT64( SIXTY_FOUR_BIT_UNSIGNED_INTEGER * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CUINT64::~CUINT64()
{
   WFCLTRACEINIT( TEXT( "CUINT64::~CUINT64()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

// Methods

void CUINT64::Copy( const CUINT64& source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::Copy( CUINT64 )" ) );
   Copy( (const SIXTY_FOUR_BIT_UNSIGNED_INTEGER *) &source );
}

void CUINT64::Copy( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER& source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::Copy( SIXTY_FOUR_BIT_UNSIGNED_INTEGER )" ) );
   Copy( &source );
}

void CUINT64::Copy( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER * source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::Copy( SIXTY_FOUR_BIT_UNSIGNED_INTEGER * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      lsw = source->lsw;
      msw = source->msw;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CUINT64::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CUINT64 at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   lsw = " ) << lsw << TEXT( "\n" );
   dump_context << TEXT( "   msw = " ) << msw << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CUINT64::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CUINT64::Empty()" ) );
   lsw = 0;
   msw = 0;
}

// Operators

CUINT64& CUINT64::operator=( const CUINT64& source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::operator=( CUINT64& )" ) );
   Copy( source );
   return( *this );
}

CUINT64& CUINT64::operator=( const SIXTY_FOUR_BIT_UNSIGNED_INTEGER& source )
{
   WFCLTRACEINIT( TEXT( "CUINT64::operator=( SIXTY_FOUR_BIT_UNSIGNED_INTEGER& )" ) );
   Copy( source );
   return( *this );
}

/*
** CMTFDateTime
*/

// Construction

CMTFDateTime::CMTFDateTime()
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::CMTFDateTime()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CMTFDateTime::CMTFDateTime( const CMTFDateTime& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::CMTFDateTime( CMTFDateTime& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFDateTime::CMTFDateTime( const MTF_DATE_TIME * source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::CMTFDateTime( CMTFDateTime * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFDateTime::CMTFDateTime( const MTF_DATE_TIME& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::CMTFDateTime( MTF_DATE_TIME )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFDateTime::CMTFDateTime( const CTime& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::CMTFDateTime( CTime )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFDateTime::~CMTFDateTime()
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::~CMTFDateTime()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

// Methods

void CMTFDateTime::Convert( CTime& destination ) const
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::Convert()" ) );

   int year    = 0;
   int month   = 0;
   int day     = 0;
   int hours   = 0;
   int minutes = 0;
   int seconds = 0;

   BYTE temp_byte = 0;

   /*
   ** Compressed date structure for storing dates in minimal space on tape
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   */

   /*
   ** Year
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   ** ^^^^^^^^  ^^^^^^
   */

   temp_byte = dt_field[ 1 ];

   bit_clear( temp_byte, 0 );
   bit_clear( temp_byte, 1 );

   year = MAKEWORD( temp_byte, dt_field[ 0 ] );

   year >>= 2;

   WFCTRACEVAL( TEXT( "year is " ), year );

   /*
   ** Month
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                 ^^  ^^
   */

   temp_byte = (BYTE) ( dt_field[ 1 ] % 4 );

   temp_byte <<= 2;

   month = temp_byte + ( dt_field[ 2 ] >> 6 );

   WFCTRACEVAL( TEXT( "month is " ), month );

   /*
   ** Day
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                       ^^^^^
   */

   temp_byte = dt_field[ 2 ];

   bit_clear( temp_byte, 7 );
   bit_clear( temp_byte, 6 );

   day = temp_byte >> 1;

   WFCTRACEVAL( TEXT( "day is " ), day );

   /*
   ** Hours
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                            ^  ^^^^
   */

   temp_byte = dt_field[ 3 ];

   hours = temp_byte >> 4;

   if ( bit_test( dt_field[ 2 ], 0 ) == 1 )
   {
      hours += 16;
   }

   WFCTRACEVAL( TEXT( "hours is " ), hours );

   /*
   ** Minutes
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                                   ^^^^  ^^
   */

   minutes = dt_field[ 4 ] >> 6;

   temp_byte = (BYTE) ( dt_field[ 3 ] % 16 );

   minutes += ( temp_byte << 2 );

   WFCTRACEVAL( TEXT( "minutes is " ), minutes );

   /*
   ** Seconds
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                                           ^^^^^^
   */

   seconds = dt_field[ 4 ];

   bit_clear( seconds, 7 );
   bit_clear( seconds, 6 );

   WFCTRACEVAL( TEXT( "seconds is " ), seconds );

   destination = CTime( year, month, day, hours, minutes, seconds );
}

void CMTFDateTime::Copy( const CTime& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::Copy( CTime )" ) );

   BYTE byte_0 = 0;
   BYTE byte_1 = 0;
   BYTE byte_2 = 0;
   BYTE byte_3 = 0;
   BYTE byte_4 = 0;

   WORD temp_word = 0;

   /*
   ** Compressed date structure for storing dates in minimal space on tape
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   */

   /*
   ** Year
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   ** ^^^^^^^^  ^^^^^^
   */

   temp_word = (WORD) source.GetYear();

   temp_word <<= 2;

   byte_0 = HIBYTE( temp_word );
   byte_1 = LOBYTE( temp_word );

   /*
   ** Month
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                 ^^  ^^
   */

   temp_word = (WORD) source.GetMonth();

   if ( bit_test( temp_word, 3 ) == 1 )
   {
      bit_set( byte_1, 1 );
   }
   else
   {
      bit_clear( byte_1, 1 );
   }

   if ( bit_test( temp_word, 2 ) == 1 )
   {
      bit_set( byte_1, 0 );
   }
   else
   {
      bit_clear( byte_1, 0 );
   }

   bit_clear( temp_word, 3 );
   bit_clear( temp_word, 2 );

   byte_2 = (BYTE) temp_word;

   byte_2 <<= 6;

   /*
   ** Day
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                       ^^^^^
   */

   temp_word = (WORD) source.GetDay();

   temp_word <<= 1;

   byte_2 = (BYTE) ( byte_2 + temp_word );

   /*
   ** Hours
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                            ^  ^^^^
   */

   temp_word = (WORD) source.GetHour();

   if ( bit_test( temp_word, 4 ) == 1 )
   {
      bit_set( byte_2, 0 );
   }
   else
   {
      bit_clear( byte_2, 1 );
   }

   bit_clear( temp_word, 4 );

   byte_3 = (BYTE) temp_word;

   byte_3 <<= 4;

   /*
   ** Minutes
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                                   ^^^^  ^^
   */

   temp_word = (WORD) source.GetMinute();

   if ( bit_test( temp_word, 5 ) == 1 )
   {
      bit_set( byte_3, 3 );
   }
   else
   {
      bit_clear( byte_3, 3 );
   }

   if ( bit_test( temp_word, 4 ) == 1 )
   {
      bit_set( byte_3, 2 );
   }
   else
   {
      bit_clear( byte_3, 2 );
   }

   if ( bit_test( temp_word, 3 ) == 1 )
   {
      bit_set( byte_3, 1 );
   }
   else
   {
      bit_clear( byte_3, 1 );
   }

   if ( bit_test( temp_word, 2 ) == 1 )
   {
      bit_set( byte_3, 0 );
   }
   else
   {
      bit_clear( byte_3, 0 );
   }

   bit_clear( temp_word, 2 );
   bit_clear( temp_word, 3 );
   bit_clear( temp_word, 4 );
   bit_clear( temp_word, 5 );

   byte_4 = (BYTE) temp_word;

   byte_4 <<= 6;

   /*
   ** Seconds
   **  BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
   ** 76543210  76543210  76543210  76543210  76543210
   ** yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss
   **                                           ^^^^^^
   */

   temp_word = (WORD) source.GetSecond();

   byte_4 = (BYTE) ( byte_4 + temp_word );

   // Finally, save the data

   dt_field[ 0 ] = byte_0;
   dt_field[ 1 ] = byte_1;
   dt_field[ 2 ] = byte_2;
   dt_field[ 3 ] = byte_3;
   dt_field[ 4 ] = byte_4;
}

void CMTFDateTime::Copy( const CMTFDateTime& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::Copy( CMTFDateTime& )" ) );
   Copy( (const MTF_DATE_TIME *) &source );
}

void CMTFDateTime::Copy( const MTF_DATE_TIME * source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::Copy( MTF_DATE_TIME * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      int index = 0;

      while( index < sizeof( dt_field ) )
      {
         dt_field[ index ] = source->dt_field[ index ];
         index++;
      }
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMTFDateTime::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CMTFDateTime at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   dt_field[ 0 ] = " ) << dt_field[ 0 ] << TEXT( "\n" );
   dump_context << TEXT( "   dt_field[ 1 ] = " ) << dt_field[ 1 ] << TEXT( "\n" );
   dump_context << TEXT( "   dt_field[ 2 ] = " ) << dt_field[ 2 ] << TEXT( "\n" );
   dump_context << TEXT( "   dt_field[ 3 ] = " ) << dt_field[ 3 ] << TEXT( "\n" );
   dump_context << TEXT( "   dt_field[ 4 ] = " ) << dt_field[ 4 ] << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMTFDateTime::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::Empty()" ) );
   dt_field[ 0 ] = 0;
   dt_field[ 1 ] = 0;
   dt_field[ 2 ] = 0;
   dt_field[ 3 ] = 0;
   dt_field[ 4 ] = 0;
}

// Operators

CMTFDateTime& CMTFDateTime::operator=( const CMTFDateTime& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::operator=( CMTFDateTime& )" ) );
   Copy( source );
   return( *this );
}

CMTFDateTime& CMTFDateTime::operator=( const MTF_DATE_TIME& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::operator=( MTF_DATE_TIME& )" ) );
   Copy( source );
   return( *this );
}

CMTFDateTime& CMTFDateTime::operator=( const CTime& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDateTime::operator=( CTime& )" ) );
   Copy( source );
   return( *this );
}

/*
** CMTFTapeAddress
*/

CMTFTapeAddress::CMTFTapeAddress()
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::CMTFTapeAddress()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CMTFTapeAddress::CMTFTapeAddress( const CMTFTapeAddress& source )
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::CMTFTapeAddress( CMTFTapeAddress )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFTapeAddress::CMTFTapeAddress( const MTF_TAPE_ADDRESS * source )
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::CMTFTapeAddress( MTF_TAPE_ADDRESS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFTapeAddress::~CMTFTapeAddress()
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::~CMTFTapeAddress()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CMTFTapeAddress::Copy( const CMTFTapeAddress& source )
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::Copy( CMTFTapeAddress& )" ) );
   Copy( (const MTF_TAPE_ADDRESS *) &source );
}

void CMTFTapeAddress::Copy( const MTF_TAPE_ADDRESS * source )
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::Copy( MTF_TAPE_ADDRESS * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      elmdata_size = source->elmdata_size;
      data_offset  = source->data_offset;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMTFTapeAddress::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CMTFTapeAddress at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   elmdata_size = " ) << elmdata_size << TEXT( "\n" );
   dump_context << TEXT( "   data_offset  = " ) << data_offset  << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMTFTapeAddress::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMTFTapeAddress::Empty()" ) );
   elmdata_size = 0;
   data_offset  = 0;
}

/*
** CMTFDataBlockHeader
*/

CMTFDataBlockHeader::CMTFDataBlockHeader()
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::CMTFDataBlockHeader()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CMTFDataBlockHeader::CMTFDataBlockHeader( const CMTFDataBlockHeader& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::CMTFDataBlockHeader( CMTFDataBlockHeader )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFDataBlockHeader::CMTFDataBlockHeader( const MTF_DB_HDR * source )
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::CMTFDataBlockHeader( MTF_DB_HDR * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFDataBlockHeader::~CMTFDataBlockHeader()
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::~CMTFDataBlockHeader()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CMTFDataBlockHeader::Copy( const CMTFDataBlockHeader& source )
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::Copy( CMTFDataBlockHeader& )" ) );
   Copy( (const MTF_DB_HDR *) &source );
}

void CMTFDataBlockHeader::Copy( const MTF_DB_HDR * source )
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::Copy( MTF_DB_HDR * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      block_type[ 0 ] = source->block_type[ 0 ];
      block_type[ 1 ] = source->block_type[ 1 ];
      block_type[ 2 ] = source->block_type[ 2 ];
      block_type[ 3 ] = source->block_type[ 3 ];

      block_attribs      = source->block_attribs;
      offset_to_data     = source->offset_to_data;
      machine_os_id      = source->machine_os_id;
      machine_os_version = source->machine_os_version;

      displayable_size.lsw = source->displayable_size.lsw;
      displayable_size.msw = source->displayable_size.msw;

      logical_block_address.lsw = source->logical_block_address.lsw;
      logical_block_address.msw = source->logical_block_address.msw;

      session_id.lsw = source->session_id.lsw;
      session_id.msw = source->session_id.msw;

      control_block_id = source->control_block_id;
   
      string_storage.elmdata_size = source->string_storage.elmdata_size;
      string_storage.data_offset  = source->string_storage.data_offset;

      os_specific_data.elmdata_size = source->os_specific_data.elmdata_size;
      os_specific_data.data_offset  = source->os_specific_data.data_offset;

      string_type = source->string_type;
      reserved    = source->reserved;
      hdr_chksm   = source->hdr_chksm;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMTFDataBlockHeader::Dump( CDumpContext& dump_context ) const
{
   TCHAR block_type_string[ 5 ];
   CMTFTapeAddress tape_address;
   CUINT64 temp_uint;

   block_type_string[ 0 ] = block_type[ 0 ];
   block_type_string[ 1 ] = block_type[ 1 ];
   block_type_string[ 2 ] = block_type[ 2 ];
   block_type_string[ 3 ] = block_type[ 3 ];
   block_type_string[ 4 ] = 0x00;

   dump_context << TEXT( " a CMTFDataBlockHeader at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   block_type[4]      = " ) << block_type_string  << TEXT( "\n" );
   dump_context << TEXT( "   block_attribs      = " ) << block_attribs      << TEXT( "\n" );
   dump_context << TEXT( "   offset_to_data     = " ) << offset_to_data     << TEXT( "\n" );
   dump_context << TEXT( "   machine_os_id      = " ) << machine_os_id      << TEXT( "\n" );
   dump_context << TEXT( "   machine_os_version = " ) << machine_os_version << TEXT( "\n" );

   dump_context << TEXT( "   displayable_size is" );
   temp_uint.Copy( &displayable_size );
   temp_uint.Dump( dump_context );

   dump_context << TEXT( "   logical_block_address is" );
   temp_uint.Copy( &logical_block_address );
   temp_uint.Dump( dump_context );

   dump_context << TEXT( "   session_id is" );
   temp_uint.Copy( &session_id );
   temp_uint.Dump( dump_context );
   dump_context << TEXT( "   control_block_id = " ) << control_block_id << TEXT( "\n" );
   dump_context << TEXT( "   string_storage is" );
   tape_address.Copy( &string_storage );
   tape_address.Dump( dump_context );
   
   dump_context << TEXT( "   os_specific_data is" );
   tape_address.Copy( &string_storage );
   tape_address.Dump( dump_context );

   dump_context << TEXT( "   string_type = " ) << string_type << TEXT( "\n" );
   dump_context << TEXT( "   reserved    = " ) << reserved    << TEXT( "\n" );
   dump_context << TEXT( "   hdr_chksm   = " ) << hdr_chksm   << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMTFDataBlockHeader::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMTFDataBlockHeader::Empty()" ) );

   block_type[ 0 ] = 0;
   block_type[ 1 ] = 0;
   block_type[ 2 ] = 0;
   block_type[ 3 ] = 0;

   block_attribs      = 0;
   offset_to_data     = 0;
   machine_os_id      = 0;
   machine_os_version = 0;

   displayable_size.lsw = 0;
   displayable_size.msw = 0;

   logical_block_address.lsw = 0;
   logical_block_address.msw = 0;

   session_id.lsw = 0;
   session_id.msw = 0;

   control_block_id = 0;
   
   string_storage.elmdata_size = 0;
   string_storage.data_offset  = 0;

   os_specific_data.elmdata_size = 0;
   os_specific_data.data_offset  = 0;

   string_type = 0;
   reserved    = 0;
   hdr_chksm   = 0;
}

/*
** CMTFTape
*/

CMTFTape::CMTFTape()
{
   WFCLTRACEINIT( TEXT( "CMTFTape::CMTFTape()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CMTFTape::CMTFTape( const CMTFTape& source )
{
   WFCLTRACEINIT( TEXT( "CMTFTape::CMTFTape( CMTFTape& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFTape::CMTFTape( const MTF_TAPE * source )
{
   WFCLTRACEINIT( TEXT( "CMTFTape::CMTFTape( MTF_TAPE * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CMTFTape::~CMTFTape()
{
   WFCLTRACEINIT( TEXT( "CMTFTape::~CMTFTape()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CMTFTape::Copy( const CMTFTape& source )
{
   WFCLTRACEINIT( TEXT( "CMTFTape::Copy( CMTFTape& )" ) );
   Copy( (const MTF_TAPE *) &source );
}

void CMTFTape::Copy( const MTF_TAPE * source )
{
   WFCLTRACEINIT( TEXT( "CMTFTape::Copy( MTF_TAPE * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      block_header.block_type[ 0 ] = source->block_header.block_type[ 0 ];
      block_header.block_type[ 1 ] = source->block_header.block_type[ 1 ];
      block_header.block_type[ 2 ] = source->block_header.block_type[ 2 ];
      block_header.block_type[ 3 ] = source->block_header.block_type[ 3 ];

      block_header.block_attribs      = source->block_header.block_attribs;
      block_header.offset_to_data     = source->block_header.offset_to_data;
      block_header.machine_os_id      = source->block_header.machine_os_id;
      block_header.machine_os_version = source->block_header.machine_os_version;

      block_header.displayable_size.lsw = source->block_header.displayable_size.lsw;
      block_header.displayable_size.msw = source->block_header.displayable_size.msw;

      block_header.logical_block_address.lsw = source->block_header.logical_block_address.lsw;
      block_header.logical_block_address.msw = source->block_header.logical_block_address.msw;

      block_header.session_id.lsw = source->block_header.session_id.lsw;
      block_header.session_id.msw = source->block_header.session_id.msw;

      block_header.control_block_id = source->block_header.control_block_id;
   
      block_header.string_storage.elmdata_size = source->block_header.string_storage.elmdata_size;
      block_header.string_storage.data_offset  = source->block_header.string_storage.data_offset;

      block_header.os_specific_data.elmdata_size = source->block_header.os_specific_data.elmdata_size;
      block_header.os_specific_data.data_offset  = source->block_header.os_specific_data.data_offset;

      block_header.string_type = source->block_header.string_type;
      block_header.reserved    = source->block_header.reserved;
      block_header.hdr_chksm   = source->block_header.hdr_chksm;

      tape_id_number            = source->tape_id_number;
      tape_attributes           = source->tape_attributes;
      tape_seq_number           = source->tape_seq_number;
      password_encryption_algor = source->password_encryption_algor;
      ecc_alg                   = source->ecc_alg;
      otc_type                  = source->otc_type;

      tape_name.elmdata_size = source->tape_name.elmdata_size;
      tape_name.data_offset  = source->tape_name.data_offset;

      tape_description.elmdata_size = source->tape_description.elmdata_size;
      tape_description.data_offset  = source->tape_description.data_offset;

      tape_password.elmdata_size = source->tape_password.elmdata_size;
      tape_password.data_offset  = source->tape_password.data_offset;

      software_name.elmdata_size = source->software_name.elmdata_size;
      software_name.data_offset  = source->software_name.data_offset;

      logical_block_size = source->logical_block_size;
      software_vendor_id = source->software_vendor_id;
   
      tape_date.dt_field[ 0 ] = source->tape_date.dt_field[ 0 ];
      tape_date.dt_field[ 1 ] = source->tape_date.dt_field[ 1 ];
      tape_date.dt_field[ 2 ] = source->tape_date.dt_field[ 2 ];
      tape_date.dt_field[ 3 ] = source->tape_date.dt_field[ 3 ];
      tape_date.dt_field[ 4 ] = source->tape_date.dt_field[ 4 ];

      tape_format_version_major = source->tape_format_version_major;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMTFTape::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMTFDataBlockHeader at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   CMTFDataBlockHeader header( &block_header );
   dump_context << TEXT( "   block_header is" );
   header.Dump( dump_context );
   dump_context << TEXT( "   tape_id_number                = " ) << tape_id_number                << TEXT( "\n" );
   dump_context << TEXT( "   tape_attributes               = " ) << tape_attributes               << TEXT( "\n" );
   dump_context << TEXT( "   tape_seq_number               = " ) << tape_seq_number               << TEXT( "\n" );
   dump_context << TEXT( "   password_encryption_algor     = " ) << password_encryption_algor     << TEXT( "\n" );
   dump_context << TEXT( "   ecc_alg                       = " ) << ecc_alg                       << TEXT( "\n" );
   dump_context << TEXT( "   otc_type                      = " ) << otc_type                      << TEXT( "\n" );
   dump_context << TEXT( "   tape_name.elmdata_size        = " ) << tape_name.elmdata_size        << TEXT( "\n" );
   dump_context << TEXT( "   tape_name.data_offset         = " ) << tape_name.data_offset         << TEXT( "\n" );
   dump_context << TEXT( "   tape_description.elmdata_size = " ) << tape_description.elmdata_size << TEXT( "\n" );
   dump_context << TEXT( "   tape_description.data_offset  = " ) << tape_description.data_offset  << TEXT( "\n" );
   dump_context << TEXT( "   tape_password.elmdata_size    = " ) << tape_password.elmdata_size    << TEXT( "\n" );
   dump_context << TEXT( "   tape_password.data_offset     = " ) << tape_password.data_offset     << TEXT( "\n" );
   dump_context << TEXT( "   software_name.elmdata_size    = " ) << software_name.elmdata_size    << TEXT( "\n" );
   dump_context << TEXT( "   software_name.data_offset     = " ) << software_name.data_offset     << TEXT( "\n" );
   dump_context << TEXT( "   logical_block_size            = " ) << logical_block_size            << TEXT( "\n" );
   dump_context << TEXT( "   software_vendor_id            = " ) << software_vendor_id            << TEXT( "\n" );
   dump_context << TEXT( "   tape_date.dt_field[ 0 ]       = " ) << tape_date.dt_field[ 0 ]       << TEXT( "\n" );
   dump_context << TEXT( "   tape_date.dt_field[ 1 ]       = " ) << tape_date.dt_field[ 1 ]       << TEXT( "\n" );
   dump_context << TEXT( "   tape_date.dt_field[ 2 ]       = " ) << tape_date.dt_field[ 2 ]       << TEXT( "\n" );
   dump_context << TEXT( "   tape_date.dt_field[ 3 ]       = " ) << tape_date.dt_field[ 3 ]       << TEXT( "\n" );
   dump_context << TEXT( "   tape_date.dt_field[ 4 ]       = " ) << tape_date.dt_field[ 4 ]       << TEXT( "\n" );
   dump_context << TEXT( "   tape_format_version_major     = " ) << tape_format_version_major     << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMTFTape::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMTFTape::Empty()" ) );

   block_header.block_type[ 0 ] = 0;
   block_header.block_type[ 1 ] = 0;
   block_header.block_type[ 2 ] = 0;
   block_header.block_type[ 3 ] = 0;

   block_header.block_attribs      = 0;
   block_header.offset_to_data     = 0;
   block_header.machine_os_id      = 0;
   block_header.machine_os_version = 0;

   block_header.displayable_size.lsw = 0;
   block_header.displayable_size.msw = 0;

   block_header.logical_block_address.lsw = 0;
   block_header.logical_block_address.msw = 0;

   block_header.session_id.lsw = 0;
   block_header.session_id.msw = 0;

   block_header.control_block_id = 0;
   
   block_header.string_storage.elmdata_size = 0;
   block_header.string_storage.data_offset  = 0;

   block_header.os_specific_data.elmdata_size = 0;
   block_header.os_specific_data.data_offset  = 0;
   block_header.string_type = 0;
   block_header.reserved    = 0;
   block_header.hdr_chksm   = 0;

   tape_id_number            = 0;
   tape_attributes           = 0;
   tape_seq_number           = 0;
   password_encryption_algor = 0;
   ecc_alg                   = 0;
   otc_type                  = 0;

   tape_name.elmdata_size = 0;
   tape_name.data_offset  = 0;

   tape_description.elmdata_size = 0;
   tape_description.data_offset  = 0;

   tape_password.elmdata_size = 0;
   tape_password.data_offset  = 0;

   software_name.elmdata_size = 0;
   software_name.data_offset  = 0;

   logical_block_size = 0;
   software_vendor_id = 0;
   
   tape_date.dt_field[ 0 ] = 0;
   tape_date.dt_field[ 1 ] = 0;
   tape_date.dt_field[ 2 ] = 0;
   tape_date.dt_field[ 3 ] = 0;
   tape_date.dt_field[ 4 ] = 0;

   tape_format_version_major = 0;
}

// End of source
