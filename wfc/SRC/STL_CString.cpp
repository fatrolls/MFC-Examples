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
** $Workfile: STL_CString.cpp $
** $Revision: 5 $
** $Modtime: 5/13/00 10:53a $
*/

#if defined( WFC_STL )

// Get rid of a ton of warnings

#pragma warning( disable : 4710 4702 )

// Now start picking up the STL stuff

#include <string>
#include <locale>

using namespace std;

#if defined( UNICODE )

// UNICODE build
typedef wstring text_string;

#else // UNICODE

// ASCII build
typedef string text_string;

#endif // UNICODE

void CString::m_Format( LPCTSTR format_string, va_list argument_list )
{
   try
   {
      va_list saved_argument_list;

      long buffer_size = _tcslen( format_string ) * 2;

      CString format_object( format_string );

      int string_index = 0;

      while( ( string_index = format_object.Find( TEXT( '%' ), string_index ) ) != (-1) )
      {
         string_index++;
         // Add 128 bytes for every % in the string
         buffer_size += 128;
      }

      TCHAR * buffer_to_write_to = NULL;
      
      try
      {
         buffer_to_write_to = (TCHAR *) malloc( ( buffer_size + 1 ) * sizeof( TCHAR ) );

          if ( buffer_to_write_to == NULL )
          {
            va_end( saved_argument_list );
            return;
          }

         bool exit_loop = false;

         while( exit_loop != true )
         {
            saved_argument_list = argument_list;

            if ( _vsntprintf( buffer_to_write_to, buffer_size, format_string, saved_argument_list ) == (-1) )
            {
               buffer_size *= 2;

               free( buffer_to_write_to );
               buffer_to_write_to = NULL;

               buffer_to_write_to = (TCHAR *) malloc( ( buffer_size + 1 ) * sizeof( TCHAR ) );

               if ( buffer_to_write_to == NULL )
               {
                  va_end( saved_argument_list );
                  return;
               }
            } 
            else
            {
               exit_loop = true;
            }
         }

         va_end( saved_argument_list );

         // Now copy the string into our buffer

         reinterpret_cast< text_string * >( m_String )->assign( buffer_to_write_to );
         free( buffer_to_write_to );
         buffer_to_write_to = NULL;
      }
      catch( ... )
      {
         try
         {
            if ( buffer_to_write_to != NULL )
            {
               free( buffer_to_write_to );
               buffer_to_write_to = NULL;
            }
         }
         catch( ... )
         {
         }
      }
   }
   catch( ... )
   {
   }
}

// Constructors

// WARNING! The order of the constructors matters!!!!
CString::CString()
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( LPCSTR source )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      Copy( source );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( LPCWSTR source )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      Copy( source );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( const CString& source )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      Copy( source );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( TCHAR character, int number_of_characters )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      reinterpret_cast< text_string * >( m_String )->append( number_of_characters, character );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( LPCSTR string_p, int length )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      Copy( string_p, length );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( const unsigned char * string_p )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      Copy( (LPCSTR) string_p );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::CString( LPCWSTR string_p, int length )
{
   m_String = NULL;
   m_Buffer = NULL;

   try
   {
      m_String = new text_string;
      Copy( string_p, length );
   }
   catch( ... )
   {
      m_String = NULL;
   }
}

CString::~CString()
{
   try
   {
      if ( m_String != NULL )
      {
         text_string * temp = (text_string *) m_String;
         delete temp;
         m_String = NULL;
      }
      if ( m_Buffer != NULL )
      {
         delete m_Buffer;
         m_Buffer = NULL;
      }
   }
   catch( ... )
   {
   }
}

// Methods

void CString::Append( LPCTSTR string_p )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->append( string_p );
   }
   catch( ... )
   {
   }
}

void CString::Append( TCHAR text_character, int number_of_times )
{
   try
   {
      int loop_index = 0;

      TCHAR temp_string[ 2 ];

      temp_string[ 0 ] = text_character;
      temp_string[ 1 ] = 0;

      while( loop_index < number_of_times )
      {
         reinterpret_cast< text_string * >( m_String )->append( temp_string );
         loop_index++;
      }
   }
   catch( ... )
   {
   }
}

void CString::Append( const CString& source )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->append( (LPCTSTR) reinterpret_cast< text_string * >( source.m_String )->c_str() );
   }
   catch( ... )
   {
   }
}

int CString::Collate( LPCTSTR string_pointer ) const
{
   try
   {
      return( ( string_pointer == NULL ) ? 1 : _tcscoll( reinterpret_cast< text_string * >( m_String )->c_str(), string_pointer ) );
   }
   catch( ... )
   {
      return( 0 );
   }
};

int CString::Compare( LPCTSTR string_p ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->compare( string_p ) );
   }
   catch( ... )
   {
      return( 0 );
   }
}

int CString::CompareNoCase( LPCTSTR string_p ) const
{
   try
   {
      return( _tcsicmp( reinterpret_cast< text_string * >( m_String )->c_str(), string_p ) );
   }
   catch( ... )
   {
      return( 0 );
   }
}

#if defined( UNICODE )

// We are a UNICODE build trying to copy an ASCII string, this is easy...

void CString::Copy( LPCSTR string_p, long number_of_characters, long beginning_at )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->resize( 0 );

      if ( string_p == NULL )
      {
         return;
      }

      if ( number_of_characters == (-1) )
      {
         long loop_index = beginning_at;

         while( string_p[ loop_index ] != 0 )
         {
            reinterpret_cast< text_string * >( m_String )->append( 1, string_p[ beginning_at ] );
            loop_index++;
         }
      }
      else
      {
         // Only append a finite number of characters...

         long loop_index = 0;

         while( loop_index < number_of_characters )
         {
            Append( string_p[ beginning_at + loop_index ] );
            loop_index++;
         }
      }
   }
   catch( ... )
   {
   }
}

#else // UNICODE

// We are an ASCII build copying an ascii string, we don't need to do anything special

void CString::Copy( LPCSTR string_p, long number_of_characters, long beginning_at )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->resize( 0 );

      if ( string_p == NULL )
      {
         return;
      }

      if ( number_of_characters == (-1) )
      {
         reinterpret_cast< text_string * >( m_String )->append( &string_p[ beginning_at ] );
      }
      else
      {
         // Only append a finite number of characters...

         long loop_index = 0;

         while( loop_index < number_of_characters )
         {
            Append( string_p[ beginning_at + loop_index ] );
            loop_index++;
         }
      }
   }
   catch( ... )
   {
   }
}

#endif // UNICODE

#if defined( UNICODE )

// We're already UNICODE so we don't need to do anything special

void CString::Copy( LPCWSTR string_p, long number_of_characters, long beginning_at )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->resize( 0 );

      if ( string_p == NULL )
      {
         return;
      }

      if ( number_of_characters == (-1) )
      {
         reinterpret_cast< text_string * >( m_String )->append( &string_p[ beginning_at ] );
      }
      else
      {
         // Only append a finite number of characters...

         long loop_index = 0;

         while( loop_index < number_of_characters )
         {
            Append( string_p[ beginning_at + loop_index ] );
            loop_index++;
         }
      }
   }
   catch( ... )
   {
   }
}

#else // UNICODE

// We are ASCII build, we need to convert ASCII to UNICODE

void CString::Copy( LPCWSTR string_p, long number_of_characters, long beginning_at )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->resize( 0 );

      if ( string_p == NULL )
      {
         return;
      }

      long number_of_characters_to_copy = 0;

      if ( number_of_characters == (-1) )
      {
         number_of_characters_to_copy = wcslen( string_p );
      }
      else
      {
         number_of_characters_to_copy = number_of_characters;
      }

      number_of_characters_to_copy -= beginning_at;

      char  * ascii_string = NULL;

      if ( number_of_characters_to_copy <= 0 )
      {
         return;
      }

      try
      {
         ascii_string = new char[ ( number_of_characters_to_copy + 1 ) * sizeof( WCHAR ) ];
      }
      catch( ... )
      {
         ascii_string = NULL;
      }

      if ( ascii_string == NULL )
      {
         Empty();
         return;
      }

      ::UNICODE_to_ASCII( &string_p[ beginning_at ], ascii_string, number_of_characters_to_copy );
      ascii_string[ number_of_characters_to_copy ] = 0x00;

      reinterpret_cast< text_string * >( m_String )->append( ascii_string );

      delete ascii_string;
   }
   catch( ... )
   {
   }
}

#endif // UNICODE

void CString::Empty( void )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->resize( 0 );
   }
   catch( ... )
   {
   }
}

int CString::Find( TCHAR character ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->find( character ) );
   }
   catch( ... )
   {
      return( -1 );
   }
}

int CString::Find( TCHAR character, int start_index ) const
{
   try
   {
      if ( start_index >= reinterpret_cast< text_string * >( m_String )->length() || start_index < 0 )
      {
         return( -1 );
      }

      if ( start_index == 0 )
      {
         return( reinterpret_cast< text_string * >( m_String )->find( character ) );
      }

      // STL's find is whacko. Put some sense back into it.
      // This is a hack until I can decipher what STL is attempting to do

      CString temp_string( Mid( start_index ) );

      int found_at = temp_string.Find( character );

      if ( found_at >= 0 )
      {
         return( start_index + found_at );
      }
   }
   catch( ... )
   {
   }

   return( -1 );
}

int CString::Find( LPCTSTR string_p ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->find( string_p ) );
   }
   catch( ... )
   {
      return( -1 );
   }
}

int CString::Find( LPCTSTR string_p, int start_index ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->find( string_p, start_index ) );
   }
   catch( ... )
   {
      return( -1 );
   }
}

int CString::FindOneOf( LPCTSTR string_p ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->find_first_of( string_p ) );
   }
   catch( ... )
   {
      return( -1 );
   }
}

void __cdecl CString::Format( LPCTSTR printf_format_string, ... )
{
   try
   {
      va_list argument_list;

      va_start( argument_list, printf_format_string );
      m_Format( printf_format_string, argument_list );
      va_end( argument_list );
   }
   catch( ... )
   {
   }
}

TCHAR CString::GetAt( int character_index ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->at( character_index ) );
   }
   catch( ... )
   {
      return( 0 );
   }
}

LPTSTR CString::GetBuffer( int minimum_buffer_length )
{
   try
   {
      if ( m_Buffer != NULL )
      {
         delete m_Buffer;
         m_Buffer = NULL;
      }

      try
      {
         m_Buffer = new TCHAR[ minimum_buffer_length + 1 ];
      }
      catch( ... )
      {
         m_Buffer = NULL;
      }

      if ( m_Buffer == NULL )
      {
         return( NULL );
      }

      m_Buffer[ minimum_buffer_length ] = 0; // NULL terminate the string

      // Copy the contents of our current string into the new buffer

      if ( minimum_buffer_length < reinterpret_cast< text_string * >( m_String )->length() )
      {
         // The currently held string is longer than the minimum buffer length
         memcpy( m_Buffer, reinterpret_cast< text_string * >( m_String )->data(), minimum_buffer_length * sizeof( TCHAR ) );
      }
      else
      {
         memcpy( m_Buffer, reinterpret_cast< text_string * >( m_String )->data(), reinterpret_cast< text_string * >( m_String )->length() * sizeof( TCHAR ) );
      }

      return( m_Buffer );
   }
   catch( ... )
   {
      return( NULL );
   }
}

int CString::GetLength( void ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->length() );
   }
   catch( ... )
   {
      return( 0 );
   }
}

int CString::GetSize( void ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->length() );
   }
   catch( ... )
   {
      return( 0 );
   }
}

BOOL CString::IsEmpty( void ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->empty() ? true : false );
   }
   catch( ... )
   {
      return( TRUE );
   }
}

void CString::MakeLower( void )
{
   try
   {
      // 2000-05-01
      // Thanks go to Kevin Godden (k.godden@mvt.ie) for sending me a more terse implementation
      std::ctype<TCHAR>().tolower( reinterpret_cast< text_string * >( m_String )->begin(), reinterpret_cast< text_string * >( m_String )->end() );
   }
   catch( ... )
   {
   }
}

void CString::MakeReverse( void )
{
   try
   {
      long last_character_index = reinterpret_cast< text_string * >( m_String )->length() - 1;
      long loop_index           = 0;

      TCHAR character_to_move = 0;

      while( loop_index < last_character_index )
      {
         character_to_move = reinterpret_cast< text_string * >( m_String )->at( loop_index );
         reinterpret_cast< text_string * >( m_String )->at( loop_index ) = reinterpret_cast< text_string * >( m_String )->at( last_character_index );
         reinterpret_cast< text_string * >( m_String )->at( last_character_index ) = character_to_move;
         loop_index++;
         last_character_index--;
      }
   }
   catch( ... )
   {
   }
}

void CString::MakeUpper( void )
{
   try
   {
      // 2000-05-01
      // Thanks go to Kevin Godden (k.godden@mvt.ie) for sending me a more terse implementation
      std::ctype<TCHAR>().toupper( reinterpret_cast< text_string * >( m_String )->begin(), reinterpret_cast< text_string * >( m_String )->end() );
   }
   catch( ... )
   {
   }
}

void CString::ReleaseBuffer( int new_length )
{
   try
   {
      if ( m_Buffer == NULL )
      {
         return;
      }

      if ( new_length < 0 )
      {
         // NULL terminated string buffer

         Copy( CString( m_Buffer ) );
      }
      else
      {
         reinterpret_cast< text_string * >( m_String )->resize( 0 ); // Empty the string
         reinterpret_cast< text_string * >( m_String )->assign( m_Buffer, new_length );
      }

      delete m_Buffer;
      m_Buffer = NULL;
   }
   catch( ... )
   {
   }
}

int CString::ReverseFind( TCHAR character ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->rfind( character ) );
   }
   catch( ... )
   {
      return( -1 );
   }
}

void CString::SetAt( int character_index, TCHAR character )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->at( character_index ) = character;
   }
   catch( ... )
   {
   }
}

void CString::SetLength( long new_length )
{
   try
   {
      if ( new_length < reinterpret_cast< text_string * >( m_String )->length() )
      {
         Copy( Left( new_length ) );
      }
      else if ( new_length > reinterpret_cast< text_string * >( m_String )->length() )
      {
         while( new_length > reinterpret_cast< text_string * >( m_String )->length() )
         {
            Append( (TCHAR) ' ' );
         }
      }
   }
   catch( ... )
   {
   }
}

CString CString::Mid( int first, int count ) const
{
   CString return_value;

   try
   {
      reinterpret_cast< text_string * >( return_value.m_String )->operator = ( reinterpret_cast< text_string * >( m_String )->substr( first, count ) );
   }
   catch( ... )
   {
   }

   return( return_value );
}

CString CString::Mid( int first ) const
{
   if ( first <= 0 )
   {
      return( CString( *this ) );
   }

   // "ABCD1234" Mid( 2 ) should return "CD1234"
   CString return_value;

   try
   {
      reinterpret_cast< text_string * >( return_value.m_String )->operator = ( reinterpret_cast< text_string * >( m_String )->substr( first, reinterpret_cast< text_string * >( m_String )->length() - first ) );
   }
   catch( ... )
   {
   }

   return( return_value );
}

CString CString::Right( int count ) const
{
   CString return_value;

   try
   {
      if ( reinterpret_cast< text_string * >( m_String )->length() > count )
      {
         reinterpret_cast< text_string * >( return_value.m_String )->operator = ( reinterpret_cast< text_string * >( m_String )->substr( reinterpret_cast< text_string * >( m_String )->length() - count ) );
      }
   }
   catch( ... )
   {
   }

   return( return_value );
}

CString CString::Left( int count ) const
{
   CString return_value;

   try
   {
      reinterpret_cast< text_string * >( return_value.m_String )->operator = ( reinterpret_cast< text_string * >( m_String )->substr( 0, count ) );
   }
   catch( ... )
   {
   }

   return( return_value );
}

CString CString::SpanExcluding( LPCTSTR character_set ) const
{
   try
   {
      return( Left( ::_tcscspn( reinterpret_cast< text_string * >( m_String )->c_str(), character_set ) ) );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

CString CString::SpanIncluding( LPCTSTR character_set ) const
{
   try
   {
      return( Left( ::_tcsspn( reinterpret_cast< text_string * >( m_String )->c_str(), character_set ) ) );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

void CString::TrimRight( void )
{
   try
   {
      while( isspace( reinterpret_cast< text_string * >( m_String )->at( reinterpret_cast< text_string * >( m_String )->length() - 1 ) ) )
      {
         reinterpret_cast< text_string * >( m_String )->resize( reinterpret_cast< text_string * >( m_String )->length() - 1 );
      }
   }
   catch( ... )
   {
   }
}

void CString::TrimLeft( void )
{
   try
   {
      if ( reinterpret_cast< text_string * >( m_String )->length() > 0 )
      {
         int number_of_element_to_erase = 0;

         while( isspace( reinterpret_cast< text_string * >( m_String )->at( number_of_element_to_erase ) ) )
         {
            number_of_element_to_erase++;
         }

         reinterpret_cast< text_string * >( m_String )->erase( 0, number_of_element_to_erase );
      }
   }
   catch( ... )
   {
   }
}

void CString::TrimLeft( TCHAR character )
{
   try
   {
      if ( reinterpret_cast< text_string * >( m_String )->length() > 0 )
      {
         int number_of_element_to_erase = 0;

         while( character == reinterpret_cast< text_string * >( m_String )->at( number_of_element_to_erase ) )
         {
            number_of_element_to_erase++;
         }

         reinterpret_cast< text_string * >( m_String )->erase( 0, number_of_element_to_erase );
      }
   }
   catch( ... )
   {
   }
}

void CString::TrimRight( TCHAR character )
{
   try
   {
      while( character == reinterpret_cast< text_string * >( m_String )->at( reinterpret_cast< text_string * >( m_String )->length() - 1 ) )
      {
         reinterpret_cast< text_string * >( m_String )->erase( reinterpret_cast< text_string * >( m_String )->length() - 1, 1 );
      }
   }
   catch( ... )
   {
   }
}

//void TrimRight( LPCTSTR string1 )

// Operators

CString::operator LPCTSTR() const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->c_str() );
   }
   catch( ... )
   {
      return( NULL );
   }
}

TCHAR CString::operator[]( int array_index ) const
{
   try
   {
      return( reinterpret_cast< text_string * >( m_String )->at( array_index ) );
   }
   catch( ... )
   {
      return( 0 );
   }
}

const CString& CString::operator=( const CString& source )
{
   try
   {
      Copy( source );
   }
   catch( ... )
   {
   }

   return( *this );
}

const CString& CString::operator=( LPCSTR source )
{
   try
   {
      Copy( source );
   }
   catch( ... )
   {
   }

   return( *this );
}

const CString& CString::operator=( LPCWSTR source )
{
   try
   {
      Copy( source );
   }
   catch( ... )
   {
   }

   return( *this );
}

const CString& CString::operator=( const unsigned char * source )
{
   try
   {
      Copy( (LPCSTR) source );
   }
   catch( ... )
   {
   }

   return( *this );
}

const CString& CString::operator=( TCHAR character )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->resize( 0 );
      reinterpret_cast< text_string * >( m_String )->append( 1, character );
   }
   catch( ... )
   {
   }

   return( *this );
}

const CString& CString::operator += ( const CString& source )
{
   try
   {
      Append( source );
   }
   catch( ... )
   {
   }

   return( *this );
}

const CString& CString::operator += ( TCHAR character )
{
   try
   {
      reinterpret_cast< text_string * >( m_String )->append( 1, character );
   }
   catch( ... )
   {
   }

   return( *this );
}

CString operator + ( const CString& string1, const CString& string2 )
{
   try
   {
      CString return_value( string1 );
      return_value.Append( string2 );
      return( return_value );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

CString operator + ( const CString& string1, TCHAR character )
{
   try
   {
      CString return_value( string1 );
      return_value.Append( character, 1 );
      return( return_value );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

CString operator + ( TCHAR character, const CString& string2 )
{
   try
   {
      CString return_value;
      return_value.Append( character, 1 );
      return_value.Append( string2 );
      return( return_value );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

CString operator + ( const CString& string1, LPCTSTR string2 )
{
   try
   {
      CString return_value( string1 );
      return_value.Append( string2 );
      return( return_value );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

CString operator + ( LPCTSTR string1, const CString& string2 )
{
   try
   {
      CString return_value( string1 );
      return_value.Append( string2 );
      return( return_value );
   }
   catch( ... )
   {
      CString return_value;
      return( return_value );
   }
}

#endif // WFC_STL
