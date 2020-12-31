#if ! defined ( DATA_PARSER_CLASS_HEADER )

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
** $Workfile: CDataParser.hpp $
** $Revision: 20 $
** $Modtime: 2/20/00 7:59a $
*/

#define DATA_PARSER_CLASS_HEADER

/*
** Sorry this is so huge but I had to get performance up...
*/

class CDataParser
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      inline CDataParser( const CDataParser& ) {};
      inline CDataParser& operator=( const CDataParser& ) { return( *this ); };

   protected:

#if defined( _DEBUG )

      DWORD m_LastIndex;
      DWORD m_NumberOfTimesWeHaveBeenAskedForTheSameIndex;

#endif // _DEBUG

      BOOL         m_AutomaticallyDelete;
      CByteArray * m_Data;
      BOOL         m_IsASCII;
      BOOL         m_IsBigEndian;
      BOOL         m_IsUCS4;
      DWORD        m_UCS4Order;
      BYTE         m_UnicodeToASCIIErrorCharacter;

   public:

      inline CDataParser()
      {
         WFCLTRACEINIT( TEXT( "CDataParser::CDataParser()" ) );

         m_AutomaticallyDelete          = FALSE;
         m_Data                         = NULL;
         m_IsASCII                      = TRUE;
         m_IsBigEndian                  = FALSE;
         m_IsUCS4                       = FALSE;
         m_UCS4Order                    = 4321;
         m_UnicodeToASCIIErrorCharacter = 'q';

#if defined( _DEBUG )
         m_LastIndex                                   = 0;
         m_NumberOfTimesWeHaveBeenAskedForTheSameIndex = 0;
#endif // _DEBUG
      }

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      inline ~CDataParser()
      {
         WFCLTRACEINIT( TEXT( "CDataParser::~CDataParser()" ) );
         Empty();
      }

      inline void AdvanceByOneCharacter( CParsePoint& parse_point, DWORD character_parameter = 0 ) const
      {
         try
         {
            if ( m_Data == NULL )
            {
               ::SetLastError( ERROR_INVALID_ADDRESS );
               return;
            }

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return;
            }

            DWORD number_of_bytes_per_character = 1;

            if ( IsTextUCS4() )
            {
               number_of_bytes_per_character = 4;
            }
            else if ( IsTextASCII() == FALSE )
            {
               number_of_bytes_per_character = 2;
            }

            DWORD last_index = ( parse_point.GetIndex() + number_of_bytes_per_character );

            if ( last_index >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               parse_point.SetIndex( last_index );
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return;
            }

            DWORD character = 0;

            BYTE little_end = m_Data->GetAt( parse_point.GetIndex() );

            if ( IsTextASCII() != TRUE )
            {
               if ( IsTextUCS4() == FALSE )
               {
                  // We are UNICODE, let's decipher that Endian thing

                  if ( ( parse_point.GetIndex() + 1 ) >= static_cast< DWORD >( m_Data->GetSize() ) )
                  {
                     ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
                     return;
                  }

                  BYTE big_end = m_Data->GetAt( parse_point.GetIndex() + 1 );

                  character = IsTextBigEndian() ? MAKEWORD( big_end, little_end ) : MAKEWORD( little_end, big_end );

                  /*
                  ** The above line of code is the same as saying:

                  if ( IsTextBigEndian() != TRUE )
                  {
                     // Intel Format
                     character = MAKEWORD( little_end, big_end );
                  }
                  else
                  {
                     // Sun (stupid) Format
                     character = MAKEWORD( big_end, little_end );
                  }

                  */

                  ::SetLastError( NO_ERROR );

                  if ( character_parameter == 0 )
                  {
                     parse_point.AutoIncrement( static_cast< BYTE >( character ) );
                  }
                  else
                  {
                     parse_point.AutoIncrement( static_cast< BYTE >( character_parameter ) );
                  }

                  // We are UNICODE so advance the byte index by 2
                  // The AutoIncrement() call above will advance the index
                  // by only one byte.

                  parse_point.SetIndex( parse_point.GetIndex() + 1 );
                  return;
               }
               else
               {
                  // The most complicated... UCS4!

                  if ( ( parse_point.GetIndex() + 3 ) >= static_cast< DWORD >( m_Data->GetSize() ) )
                  {
                     ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
                     return;
                  }

                  BYTE byte_2 = m_Data->GetAt( parse_point.GetIndex() + 1 );
                  BYTE byte_3 = m_Data->GetAt( parse_point.GetIndex() + 2 );
                  BYTE byte_4 = m_Data->GetAt( parse_point.GetIndex() + 3 );

                  // Now figure out the order

                  switch( GetUCS4Order() )
                  {
                     case 4321:

                        character = ( byte_4 << 24 ) + ( byte_3 << 16 ) + ( byte_2 << 8 ) + little_end;
                        break;

                     case 1234:

                        character = ( little_end << 24 ) + ( byte_2 << 16 ) + ( byte_3 << 8 ) + byte_4;
                        break;

                     case 2143:

                        character = ( byte_2 << 24 ) + ( little_end << 16 ) + ( byte_4 << 8 ) + byte_3;
                        break;

                     case 3412:

                        character = ( byte_3 << 24 ) + ( byte_4 << 16 ) + ( little_end << 8 ) + byte_2;
                        break;

                     default:

                        ::SetLastError( ERROR_MAPPED_ALIGNMENT );
                        return;
                  }

                  ::SetLastError( NO_ERROR );

                  if ( character_parameter == 0 )
                  {
                     parse_point.AutoIncrement( static_cast< BYTE >( character ) );
                  }
                  else
                  {
                     parse_point.AutoIncrement( static_cast< BYTE >( character_parameter ) );
                  }

                  // We are UCS4 so advance the byte index by 2
                  // The AutoIncrement() call above will advance the index
                  // by only one byte.

                  parse_point.SetIndex( parse_point.GetIndex() + 3 );
                  return;
               }
            }

            ::SetLastError( NO_ERROR );

            if ( character_parameter == 0 )
            {
               parse_point.AutoIncrement( little_end );
            }
            else
            {
               parse_point.AutoIncrement( static_cast< BYTE >( character_parameter ) );
            }
         }
         catch( ... )
         {
            return;
         }
      }

      inline void Empty( void )
      {
         WFCLTRACEINIT( TEXT( "CDataParser::Empty()" ) );

         try
         {
            if ( m_AutomaticallyDelete != FALSE )
            {
               if ( m_Data != NULL )
               {
                  delete m_Data;
                  m_Data = NULL;
               }
            }

            m_AutomaticallyDelete          = FALSE;
            m_Data                         = NULL;
            m_IsASCII                      = TRUE;
            m_IsBigEndian                  = FALSE;
            m_IsUCS4                       = FALSE;
            m_UCS4Order                    = 4321;
            m_UnicodeToASCIIErrorCharacter = 'q';

#if defined( _DEBUG )
            m_LastIndex                                   = 0;
            m_NumberOfTimesWeHaveBeenAskedForTheSameIndex = 0;
#endif // _DEBUG
         }
         catch( ... )
         {
            // We can't do anything in here because this may be NULL!
            return;
         }
      }

inline BOOL Find( const CParsePoint& parse_point, BYTE byte_to_find, CParsePoint& found_at ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Find( BYTE )" ) );

   try
   {
      found_at.Copy( parse_point );

      if ( m_Data == NULL )
      {
         found_at.Empty();
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      DWORD number_of_data_bytes = m_Data->GetSize();

      if ( found_at.GetIndex() >= number_of_data_bytes )
      {
         found_at.Empty();
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      const BYTE * buffer = m_Data->GetData();

      while( found_at.GetIndex() < number_of_data_bytes )
      {
         if ( buffer[ found_at.GetIndex() ] == byte_to_find )
         {
            return( TRUE );
         }

         found_at.AutoIncrement( buffer[ found_at.GetIndex() ] );
      }

      found_at.Empty();

      ::SetLastError( NO_ERROR );
      return( FALSE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL Find( const CParsePoint& parse_point, const CString& string_to_find, CParsePoint& found_at ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Find( CString )" ) );

   try
   {
      found_at.Copy( parse_point );

      if ( m_Data == NULL )
      {
         found_at.Empty();
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      DWORD number_of_data_bytes = m_Data->GetSize();

      if ( found_at.GetIndex() >= number_of_data_bytes )
      {
         found_at.Empty();
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      size_t string_length = string_to_find.GetLength();

      if ( string_length == 0 )
      {
         found_at.Empty();
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      DWORD character_to_test = 0;

      while( ( found_at.GetIndex() + string_length ) <= number_of_data_bytes )
      {
         if ( PeekAtCharacter( found_at, character_to_test, 0 ) == TRUE )
         {
            if ( character_to_test == static_cast< DWORD >( string_to_find.GetAt( 0 ) ) )
            {
               size_t loop_index = 1;

               BOOL string_was_found = TRUE;

               DWORD other_character = 0;

               while( loop_index < string_length )
               {
                  // We peek at string_length - 1 because the GetNextCharacter() call above
                  // advances the character index

                  if ( PeekAtCharacter( found_at, character_to_test, loop_index ) != TRUE )
                  {
                     found_at.Empty();
                     return( FALSE );
                  }

                  other_character = string_to_find.GetAt( loop_index );

                  if ( character_to_test != other_character )
                  {
                     loop_index = string_length;
                     string_was_found = FALSE;
                  }

                  loop_index++;
               }

               if ( string_was_found == TRUE )
               {
                  return( TRUE );
               }
            }

            GetNextCharacter( found_at, character_to_test );
         }
      }

      found_at.Empty();

      ::SetLastError( NO_ERROR );
      return( FALSE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL Find( const CParsePoint& parse_point, const CByteArray& bytes_to_find, CParsePoint& found_at ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Find( CByteArray )" ) );

   try
   {
      found_at.Copy( parse_point );

      if ( m_Data == NULL )
      {
         found_at.Empty();
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      DWORD number_of_data_bytes = m_Data->GetSize();

      if ( found_at.GetIndex() >= number_of_data_bytes )
      {
         found_at.Empty();
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      size_t pattern_length = bytes_to_find.GetSize();

      const BYTE * buffer         = m_Data->GetData();
      const BYTE * pattern_buffer = bytes_to_find.GetData();

      // 2000-02-19
      // Thanks go to Arek Kotas (arekk@metrosoft-us.com) for finding a bug
      // here. I was using < when it should have been <=

      while( ( found_at.GetIndex() + pattern_length ) <= number_of_data_bytes )
      {
         if ( ::memcmp( &buffer[ found_at.GetIndex() ], pattern_buffer, pattern_length ) == 0 )
         {
            return( TRUE );
         }

         found_at.AutoIncrement( buffer[ found_at.GetIndex() ] );
      }

      found_at.Empty();

      ::SetLastError( NO_ERROR );
      return( FALSE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL FindNoCase( const CParsePoint& parse_point, const CString& string_to_find, CParsePoint& found_at ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Find( CString )" ) );

   try
   {
      if ( IsTextASCII() == TRUE )
      {
         found_at.Copy( parse_point );

         if ( m_Data == NULL )
         {
            found_at.Empty();
            ::SetLastError( ERROR_INVALID_ADDRESS );
            return( FALSE );
         }

         DWORD number_of_data_bytes = m_Data->GetSize();

         if ( found_at.GetIndex() >= number_of_data_bytes )
         {
            found_at.Empty();
            ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
            return( FALSE );
         }

         // Don't forget to take into account that we may be a UNICODE build so we
         // need to multiply the number of characters by the number of bytes per
         // character to get the memcmp() to work properly.

         size_t number_of_bytes_in_string = string_to_find.GetLength() * sizeof( TCHAR );

         const BYTE * buffer = m_Data->GetData();

         while( ( found_at.GetIndex() + number_of_bytes_in_string ) <= number_of_data_bytes )
         {
            if ( ::_memicmp( &buffer[ found_at.GetIndex() ], static_cast< LPCTSTR >( string_to_find ), number_of_bytes_in_string ) == 0 )
            {
               return( TRUE );
            }

            found_at.AutoIncrement( buffer[ found_at.GetIndex() ] );
         }

         found_at.Empty();

         ::SetLastError( NO_ERROR );
         return( FALSE );
      }
      else
      {
         if ( IsTextUCS4() == FALSE )
         {
            // The array of bytes we are searching is UNICODE text

            CByteArray characters_to_search_for;

            BYTE little_end = 0;
            BYTE big_end    = 0;

            int loop_index = 0;

            WCHAR character_to_convert = 0;

            while( loop_index < string_to_find.GetLength() )
            {
               character_to_convert = string_to_find.GetAt( loop_index );

               if ( character_to_convert > 255 )
               {
                  little_end = LOBYTE( character_to_convert );
                  big_end    = HIBYTE( character_to_convert );
               }
               else
               {
                  little_end = static_cast< BYTE >( character_to_convert );
                  big_end    = 0;
               }

               if ( IsTextBigEndian() == TRUE )
               {
                  // Big Endian (Sun) format
                  characters_to_search_for.Add( big_end );
                  characters_to_search_for.Add( little_end );
               }
               else
               {
                  characters_to_search_for.Add( little_end );
                  characters_to_search_for.Add( big_end );
               }

               loop_index++;
            }

            return( FindNoCase( parse_point, characters_to_search_for, found_at ) );
         }
         else
         {
            // Text is UCS4, we've got work to do
            return( FALSE );
         }
      }
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL FindNoCase( const CParsePoint& parse_point, const CByteArray& bytes_to_find, CParsePoint& found_at ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Find( CByteArray )" ) );

   try
   {
      found_at.Copy( parse_point );

      if ( m_Data == NULL )
      {
         found_at.Empty();
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      DWORD number_of_data_bytes = m_Data->GetSize();

      if ( found_at.GetIndex() >= number_of_data_bytes )
      {
         found_at.Empty();
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      size_t pattern_length = bytes_to_find.GetSize();

      const BYTE * buffer         = m_Data->GetData();
      const BYTE * pattern_buffer = bytes_to_find.GetData();

      while( ( found_at.GetIndex() + pattern_length ) <= number_of_data_bytes )
      {
         if ( ::_memicmp( &buffer[ found_at.GetIndex() ], pattern_buffer, pattern_length ) == 0 )
         {
            return( TRUE );
         }

         found_at.AutoIncrement( buffer[ found_at.GetIndex() ] );
      }

      found_at.Empty();

      ::SetLastError( NO_ERROR );
      return( FALSE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL Get( CParsePoint& parse_point, DWORD length, CByteArray& bytes_to_get ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Get( CByteArray )" ) );

   try
   {
      bytes_to_get.RemoveAll();

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      // 1999-01-30 - Josh Mayfield (mayfielj@squared.com) found an off-by-one error here

      if ( ( parse_point.GetIndex() + length ) > static_cast< DWORD > ( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      DWORD index = 0;

      while( index < length )
      {
         bytes_to_get.Add( m_Data->GetAt( parse_point.GetIndex() ) );
         parse_point.AutoIncrement( m_Data->GetAt( parse_point.GetIndex() ) );
         index++;
      }

      ::SetLastError( NO_ERROR );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL Get( CParsePoint& parse_point, DWORD length, CString& string_to_get ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::Get( CString )" ) );

   try
   {
      string_to_get.Empty();

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      // 1999-01-30 - Josh Mayfield (mayfielj@squared.com) found an off-by-one error here

      if ( ( parse_point.GetIndex() + length ) > static_cast< DWORD > ( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      DWORD loop_index = 0;

      while( loop_index < length )
      {
         string_to_get += static_cast< TCHAR > ( m_Data->GetAt( parse_point.GetIndex() ) );
         parse_point.AutoIncrement( m_Data->GetAt( parse_point.GetIndex() ) );
         loop_index++;
      }

      ::SetLastError( NO_ERROR );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BYTE GetAt( DWORD byte_index ) const
{
   try
   {

#if defined( _DEBUG )

      if ( byte_index == m_LastIndex )
      {
         const_cast< DWORD& > ( m_NumberOfTimesWeHaveBeenAskedForTheSameIndex )++;

         if ( m_NumberOfTimesWeHaveBeenAskedForTheSameIndex > 25 )
         {
            // We've asked for this same stinking character 25 times already!
            // Looks like our caller is stuck in an endless loop

            ASSERT( FALSE );
         }
      }
      else
      {
         const_cast< DWORD& > ( m_LastIndex                                   ) = byte_index;
         const_cast< DWORD& > ( m_NumberOfTimesWeHaveBeenAskedForTheSameIndex ) = 0;
      }

#endif // _DEBUG

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( 0 );
      }

      if ( byte_index >= static_cast< DWORD > ( m_Data->GetSize() ) )
      {
         return( 0 );
      }

      return( m_Data->GetAt( byte_index ) );
   }
   catch( ... )
   {
      return( 0 );
   }
}

inline DWORD GetCharacter( const CParsePoint& const_parse_point, const DWORD number_of_characters_ahead = 0 ) const
{
   try
   {
      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( 0 );
      }

      CParsePoint parse_point( const_parse_point );

      if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( 0 );
      }

      DWORD number_of_bytes_per_character = 1;

      if ( IsTextUCS4() )
      {
         number_of_bytes_per_character = 4;
      }
      else if ( IsTextASCII() == FALSE )
      {
         number_of_bytes_per_character = 2;
      }

      DWORD number_of_bytes_to_skip_ahead = number_of_bytes_per_character * number_of_characters_ahead;

      // We must now skip the rest of the bytes that make up one character

      number_of_bytes_to_skip_ahead += ( number_of_bytes_per_character - 1 );

      DWORD last_index = ( parse_point.GetIndex() + number_of_bytes_to_skip_ahead );

      if ( last_index >= static_cast< DWORD >( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( 0 );
      }

      number_of_bytes_per_character = 0;

      BYTE little_end = 0;

      do
      {
         little_end = m_Data->GetAt( parse_point.GetIndex() );
         parse_point.AutoIncrement( little_end );
         number_of_bytes_per_character++;
      }
      while( number_of_bytes_per_character < number_of_bytes_to_skip_ahead );

      DWORD character = 0;

      if ( IsTextASCII() != TRUE )
      {
         if ( IsTextUCS4() == FALSE )
         {
            // We are UNICODE, let's decipher that Endian thing

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( 0 );
            }

            BYTE big_end = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( big_end );

            character = IsTextBigEndian() ? MAKEWORD( big_end, little_end ) : MAKEWORD( little_end, big_end );
            /*
            if ( IsTextBigEndian() != TRUE )
            {
               // Intel Format
               character = MAKEWORD( little_end, big_end );
            }
            else
            {
               // Sun Format
               character = MAKEWORD( big_end, little_end );
            }
            */

            ::SetLastError( NO_ERROR );

#if ! defined( UNICODE )
         // ASCII build, check for UNICODE translation problem

         if ( character > 255 )
         {
            character = GetUnicodeToASCIITranslationFailureCharacter();
         }
#endif // UNICODE

            return( character );
         }
         else
         {
            // The most complicated... UCS4!

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( 0 );
            }

            BYTE byte_2 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_2 );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( 0 );
            }

            BYTE byte_3 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_3 );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( 0 );
            }

            BYTE byte_4 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_4 );

            // Now figure out the order

            switch( GetUCS4Order() )
            {
               case 4321:

                  character = ( byte_4 << 24 ) + ( byte_3 << 16 ) + ( byte_2 << 8 ) + little_end;
                  break;

               case 1234:

                  character = ( little_end << 24 ) + ( byte_2 << 16 ) + ( byte_3 << 8 ) + byte_4;
                  break;

               case 2143:

                  character = ( byte_2 << 24 ) + ( little_end << 16 ) + ( byte_4 << 8 ) + byte_3;
                  break;

               case 3412:

                  character = ( byte_3 << 24 ) + ( byte_4 << 16 ) + ( little_end << 8 ) + byte_2;
                  break;

               default:

                  ::SetLastError( ERROR_MAPPED_ALIGNMENT );
                  return( 0 );
            }

            ::SetLastError( NO_ERROR );

#if ! defined( UNICODE )
         // ASCII build, check for UNICODE translation problem

         if ( character > 255 )
         {
            character = GetUnicodeToASCIITranslationFailureCharacter();
         }
#endif // UNICODE
            return( character );
         }
      }

      ::SetLastError( NO_ERROR );
      return( little_end );
   }
   catch( ... )
   {
      return( 0 );
   }
}

inline BOOL GetNextCharacter( CParsePoint& parse_point, DWORD& character ) const
{
   try
   {
      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      BYTE little_end = m_Data->GetAt( parse_point.GetIndex() );
      parse_point.AutoIncrement( little_end );

      if ( IsTextASCII() != TRUE )
      {
         if ( IsTextUCS4() == FALSE )
         {
            // We are UNICODE, let's decipher that Endian thing

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE big_end = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( big_end );

            character = IsTextBigEndian() ? MAKEWORD( big_end, little_end ) : MAKEWORD( little_end, big_end );

            /*
            if ( IsTextBigEndian() != TRUE )
            {
               // Intel Format

               character = MAKEWORD( little_end, big_end );
            }
            else
            {
               character = MAKEWORD( big_end, little_end );
            }
            */

            ::SetLastError( NO_ERROR );

#if ! defined( UNICODE )
         // ASCII build, check for UNICODE translation problem

         if ( character > 255 )
         {
            character = GetUnicodeToASCIITranslationFailureCharacter();
         }
#endif // UNICODE

            return( TRUE );
         }
         else
         {
            // The most complicated... UCS4!

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE byte_2 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_2 );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE byte_3 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_3 );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE byte_4 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_4 );

            // Now figure out the order

            switch( GetUCS4Order() )
            {
               case 4321:

                  character = ( byte_4 << 24 ) + ( byte_3 << 16 ) + ( byte_2 << 8 ) + little_end;
                  break;

               case 1234:

                  character = ( little_end << 24 ) + ( byte_2 << 16 ) + ( byte_3 << 8 ) + byte_4;
                  break;

               case 2143:

                  character = ( byte_2 << 24 ) + ( little_end << 16 ) + ( byte_4 << 8 ) + byte_3;
                  break;

               case 3412:

                  character = ( byte_3 << 24 ) + ( byte_4 << 16 ) + ( little_end << 8 ) + byte_2;
                  break;

               default:

                  ::SetLastError( ERROR_MAPPED_ALIGNMENT );
                  character = 0;
                  return( FALSE );
            }

            ::SetLastError( NO_ERROR );

#if ! defined( UNICODE )
         // ASCII build, check for UNICODE translation problem

         if ( character > 255 )
         {
            character = GetUnicodeToASCIITranslationFailureCharacter();
         }
#endif // UNICODE

            return( TRUE );
         }
      }

      character = little_end;
      ::SetLastError( NO_ERROR );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline DWORD GetUCS4Order( void ) const
{
   return( m_UCS4Order );
}

inline BYTE GetUnicodeToASCIITranslationFailureCharacter( void ) const
{
   return( m_UnicodeToASCIIErrorCharacter );
}

inline DWORD GetSize( void ) const
{
   try
   {
      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( 0 );
      }

      int the_size = m_Data->GetSize();

      return( ( the_size < 0 ) ? 0 : the_size );
   }
   catch( ... )
   {
      return( 0 );
   }
}

inline BOOL GetUntilAndIncluding( CParsePoint& parse_point, BYTE termination_byte, CByteArray& bytes_to_get ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::GetUntilAndIncluding( CByteArray )" ) );

   try
   {
      bytes_to_get.SetSize( 0, 8192 ); // For speed

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      if ( parse_point.GetIndex() >= static_cast< DWORD > ( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      BYTE byte_to_test = 0;

      do
      {
         if ( parse_point.GetIndex() < static_cast< DWORD > ( m_Data->GetSize() ) )
         {
            byte_to_test = m_Data->GetAt( parse_point.GetIndex() );
            bytes_to_get.Add( byte_to_test );
            parse_point.AutoIncrement( byte_to_test );
         }
         else
         {
            ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
            return( FALSE );
         }
      }
      while( byte_to_test != termination_byte );

      ::SetLastError( NO_ERROR );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL GetUntilAndIncluding( CParsePoint& parse_point, BYTE termination_byte, CString& string_to_get ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::GetUntilAndIncluding( CString )" ) );

   // 1999-07-01 - Optimized this routine

   try
   {
      // Start out with an empty string
      string_to_get.Empty();

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      DWORD number_of_bytes_in_data = static_cast< DWORD > ( m_Data->GetSize() );

      if ( parse_point.GetIndex() >= number_of_bytes_in_data )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      BYTE byte_to_test = 0;

      const BYTE * buffer_pointer = m_Data->GetData();

      TCHAR temp_buffer[ 257 ];
      temp_buffer[ 256 ] = 0x00; // NULL Terminate

      int temp_buffer_index = 0;

      do
      {
         if ( parse_point.GetIndex() < static_cast< DWORD > ( m_Data->GetSize() ) )
         {
            byte_to_test = buffer_pointer[ parse_point.GetIndex() ];

            temp_buffer[ temp_buffer_index ] = byte_to_test;
            temp_buffer_index++;

            if ( temp_buffer_index == 256 )
            {
               // Our buffer is full, let CString have it
               // This optimization greatly reduces the number of memory allocations
               // that CString must make.

               string_to_get += temp_buffer;
               temp_buffer_index = 0;
            }

            parse_point.AutoIncrement( byte_to_test );
         }
         else
         {
            string_to_get.Empty();
            ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
            return( FALSE );
         }
      }
      while( byte_to_test != termination_byte );

      if ( temp_buffer_index < 256 && temp_buffer_index > 0 )
      {
         temp_buffer[ temp_buffer_index ] = 0x00; // NULL Terminate
         string_to_get += temp_buffer;
      }

      ::SetLastError( NO_ERROR );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

// 1998-11-21, New for Release 38
// The following method was added by Jeff Barczewski (jb@snowflight.com)
// He added to fix a bug in the parsing of comment sections in XML
inline BOOL GetUntilAndIncluding( CParsePoint& parse_point, const CString& termination_characters, CString& string_to_get ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::GetUntilAndIncluding( CString )" ) );

   try
   {
      string_to_get.Empty();

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      if ( parse_point.GetIndex() >= static_cast< DWORD > ( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      CByteArray bytes;
      bytes.SetSize( 0, 8192 );

      DWORD character = 0;

      int termination_characters_length = termination_characters.GetLength();

#if defined( CSTRING_APPENDING_IS_FAST )

      while( GetNextCharacter( parse_point, character ) == TRUE )
      {
#if ! defined( UNICODE )
         // ASCII build, check for UNICODE translation problem

         if ( character > 255 )
         {
            character = GetUnicodeToASCIITranslationFailureCharacter();
         }
#endif // UNICODE

         string_to_get += static_cast< TCHAR >( character );

         if ( string_to_get.GetLength() >= termination_characters_length )
         {
            if ( string_to_get.Right( termination_characters_length ).Compare( termination_characters ) == 0 )
            {
               return( TRUE );
            }
         }
      }

#else // CSTRING_APPENDING_IS_FAST

      CByteArray byte_array;
      byte_array.SetSize( 0, 8192 );

      while( GetNextCharacter( parse_point, character ) == TRUE )
      {
#if ! defined( UNICODE )
         // ASCII build, check for UNICODE translation problem

         if ( character > 255 )
         {
            character = GetUnicodeToASCIITranslationFailureCharacter();
         }

         byte_array.Add( static_cast< BYTE >( character ) );
#else // UNICODE

         byte_array.Add( LOBYTE( character ) );
         byte_array.Add( HIBYTE( character ) );

#endif // UNICODE

         if ( byte_array.GetSize() >= termination_characters_length )
         {
            const BYTE * address = byte_array.GetData();
            const BYTE * address_to_compare = &address[ byte_array.GetSize() - ( termination_characters_length * sizeof( TCHAR ) ) ];

            // Don't forget to take into account that we may be a UNICODE build so we
            // need to multiply the number of characters by the number of bytes per
            // character to get the memcmp() to work properly.

            if ( ::memcmp( address_to_compare, termination_characters, termination_characters_length * sizeof( TCHAR ) ) == 0 )
            {
#if defined( UNICODE )
               byte_array.Add( 0 );
#endif // UNICODE
               byte_array.Add( 0 );
               string_to_get = (LPCTSTR) byte_array.GetData();
               return( TRUE );
            }
         }
      }

#endif // CSTRING_APPENDING_IS_FAST

      ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
      return( FALSE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL GetUntilAndIncluding( CParsePoint& parse_point, const CByteArray& termination_bytes, CString& string_to_get ) const
{
   WFCLTRACEINIT( TEXT( "CDataParser::GetUntilAndIncluding( CByteArray )" ) );

   try
   {
      string_to_get.Empty();

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      if ( parse_point.GetIndex() >= static_cast< DWORD > ( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      TCHAR character_to_test = 0;

      const BYTE * data_p = m_Data->GetData();
      const BYTE * termination_bytes_p = termination_bytes.GetData();

      DWORD termination_bytes_length = termination_bytes.GetSize();

      do
      {
         if ( parse_point.GetIndex() + termination_bytes_length - 1 < static_cast< DWORD > ( m_Data->GetSize() ) )
         {
            character_to_test = m_Data->GetAt( parse_point.GetIndex() );
            string_to_get += character_to_test;
            parse_point.AutoIncrement( static_cast< BYTE >( character_to_test ) );
         }
         else
         {
            ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
            return( FALSE );
         }
      }
      while( 0 != ::memcmp( data_p + parse_point.GetIndex(), termination_bytes_p, termination_bytes_length ) );

      for( DWORD loop_index = 0; loop_index < termination_bytes_length; loop_index++ )
      {
         //move to the end of the string
         character_to_test = m_Data->GetAt( parse_point.GetIndex() );
         string_to_get += static_cast< TCHAR > ( character_to_test );
         parse_point.AutoIncrement( static_cast< BYTE >( character_to_test ) );
      }

      ::SetLastError( NO_ERROR );

      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL Initialize( CByteArray * data, BOOL automatically_delete = FALSE )
{
   WFCLTRACEINIT( TEXT( "CDataParser::Initialize( CByteArray )" ) );

   try
   {
      Empty();

      m_AutomaticallyDelete = automatically_delete;
      m_Data                = data;

      ::SetLastError( NO_ERROR );

      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

inline BOOL Initialize( const CStringArray& strings )
{
   WFCLTRACEINIT( TEXT( "CDataParser::Initialize( CStringArray )" ) );

   try
   {
      // Let's create our own CByteArray

      CByteArray * bytes_p = NULL;

      try
      {
         bytes_p = new CByteArray;
      }
      catch( ... )
      {
         bytes_p = NULL;
      }

      if ( bytes_p == NULL )
      {
         WFCTRACE( TEXT( "Can't allocate memory for a new CByteArray" ) );
         return( FALSE );
      }

      CString a_string;

      DWORD index             = 0;
      DWORD number_of_strings = strings.GetSize();
      DWORD string_index      = 0;
      DWORD string_length     = 0;

      while( index < number_of_strings )
      {
         a_string = strings.GetAt( index );

         // CByteArray doesn't have a method where you can append a lot bytes at once
         // so we have to hack around it

         string_index = 0;
         string_length = a_string.GetLength();

         while( string_index < string_length )
         {
            bytes_p->Add( static_cast< BYTE > ( a_string.GetAt( string_index ) ) );
            string_index++;
         }

         index++;
      }

      Initialize( bytes_p, TRUE );

      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}
      inline BOOL IsTextASCII( void ) const     { return( ( m_IsASCII     == FALSE ) ? FALSE : ( m_IsUCS4 == TRUE ) ? FALSE : TRUE ); }
      inline BOOL IsTextBigEndian( void ) const { return( ( m_IsBigEndian == FALSE ) ? FALSE : TRUE ); }
      inline BOOL IsTextUCS4( void ) const      { return( ( m_IsUCS4      == FALSE ) ? FALSE : TRUE ); }

inline BOOL PeekAtCharacter( const CParsePoint& const_parse_point, DWORD& character, const DWORD number_of_characters_ahead = 1 ) const
{
   try
   {
      if ( m_Data == NULL )
      {
         ::SetLastError( ERROR_INVALID_ADDRESS );
         return( FALSE );
      }

      CParsePoint parse_point( const_parse_point );

      if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      DWORD number_of_bytes_per_character = 1;

      if ( IsTextUCS4() )
      {
         number_of_bytes_per_character = 4;
      }
      else if ( IsTextASCII() == FALSE )
      {
         number_of_bytes_per_character = 2;
      }

      // We must calculate the number of bytes to skip until we reach
      // the first byte of the desired character

      DWORD number_of_bytes_to_skip_ahead = number_of_bytes_per_character * number_of_characters_ahead;

      DWORD last_index = ( parse_point.GetIndex() + number_of_bytes_to_skip_ahead );

      if ( last_index >= static_cast< DWORD >( m_Data->GetSize() ) )
      {
         ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
         return( FALSE );
      }

      // Reuse the variable since we no longer need it
      number_of_bytes_per_character = 0;

      BYTE little_end = 0;

      while( number_of_bytes_per_character < number_of_bytes_to_skip_ahead )
      {
         little_end = m_Data->GetAt( parse_point.GetIndex() );
         parse_point.AutoIncrement( little_end );
         number_of_bytes_per_character++;
      }

      // Get the first byte of the character
      little_end = m_Data->GetAt( parse_point.GetIndex() );

      if ( IsTextASCII() != TRUE )
      {
         if ( IsTextUCS4() == FALSE )
         {
            // Advance over the byte we just read, we do it here so if we are
            // parsing an ASCII document, we won't incur the performance hit
            parse_point.AutoIncrement( little_end );

            // We are UNICODE, let's decipher that Endian thing

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE big_end = m_Data->GetAt( parse_point.GetIndex() );

            character = IsTextBigEndian() ? MAKEWORD( big_end, little_end ) : MAKEWORD( little_end, big_end );

            ::SetLastError( NO_ERROR );
            return( TRUE );
         }
         else
         {
            // The most complicated... UCS4!

            // Advance over the byte we just read, we do it here so if we are
            // parsing an ASCII document, we won't incur the performance hit
            parse_point.AutoIncrement( little_end );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE byte_2 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_2 );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE byte_3 = m_Data->GetAt( parse_point.GetIndex() );
            parse_point.AutoIncrement( byte_3 );

            if ( parse_point.GetIndex() >= static_cast< DWORD >( m_Data->GetSize() ) )
            {
               ::SetLastError( ERROR_ALLOTTED_SPACE_EXCEEDED );
               return( FALSE );
            }

            BYTE byte_4 = m_Data->GetAt( parse_point.GetIndex() );

            // Now figure out the order

            switch( GetUCS4Order() )
            {
               case 4321:

                  character = ( byte_4 << 24 ) + ( byte_3 << 16 ) + ( byte_2 << 8 ) + little_end;
                  break;

               case 1234:

                  character = ( little_end << 24 ) + ( byte_2 << 16 ) + ( byte_3 << 8 ) + byte_4;
                  break;

               case 2143:

                  character = ( byte_2 << 24 ) + ( little_end << 16 ) + ( byte_4 << 8 ) + byte_3;
                  break;

               case 3412:

                  character = ( byte_3 << 24 ) + ( byte_4 << 16 ) + ( little_end << 8 ) + byte_2;
                  break;

               default:

                  ::SetLastError( ERROR_MAPPED_ALIGNMENT );
                  character = 0;
                  return( FALSE );
            }

            ::SetLastError( NO_ERROR );
            return( TRUE );
         }
      }

      character = little_end;
      ::SetLastError( NO_ERROR );
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

      inline DWORD PeekCharacter( const CParsePoint& parse_point, const LONG number_of_characters_ahead ) const
      {
         DWORD return_value = 0;
         (void) PeekAtCharacter( parse_point, return_value, number_of_characters_ahead );
         return( return_value );
      }

inline BOOL SetTextToASCII( BOOL text_is_ascii = TRUE )
{
   m_IsASCII = ( text_is_ascii == FALSE ) ? FALSE : TRUE;
   m_IsUCS4 = FALSE;
   return( TRUE );
}

inline BOOL SetTextToBigEndian( BOOL unicode_is_big_endian = TRUE )
{
   m_IsBigEndian = ( unicode_is_big_endian == FALSE ) ? FALSE : TRUE;
   return( TRUE );
}

inline BOOL SetTextToUCS4( BOOL text_is_ucs4 = TRUE )
{
   if ( text_is_ucs4 == FALSE )
   {
      m_IsUCS4 = FALSE;
   }
   else
   {
      m_IsASCII = FALSE;
      m_IsUCS4  = TRUE;
   }

   return( TRUE );
}

inline BOOL SetUCS4Order( DWORD order = 4321 )
{
   switch( order )
   {
      case 4321:
      case 1234:
      case 2143:
      case 3412:

         m_UCS4Order = order;
         return( TRUE );

      default:

         m_UCS4Order = 4321;
         return( FALSE );
   }
}

inline void SetUnicodeToASCIITranslationFailureCharacter( BYTE asci_character )
{
   m_UnicodeToASCIIErrorCharacter = asci_character;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void  Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // DATA_PARSER_CLASS_HEADER
