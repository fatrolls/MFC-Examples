#if ! defined( MFC_TO_STL_HEADER_FILE )

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
** $Workfile: Mfc2Stl.h $
** $Revision: 8 $
** $Modtime: 5/12/00 3:27p $
*/

#define MFC_TO_STL_HEADER_FILE

// Include all of the windows header files that MFC would have included
#include <windows.h>
#include <tchar.h>

// Get rid of a ton of warnings

#pragma warning( disable : 4710 4702 )

#if defined( _DEBUG )
#include <crtdbg.h>

void * __cdecl operator new( size_t number_of_bytes, LPCSTR filename, int line_number );
#define DEBUG_NEW new( THIS_FILE, __LINE__ )
#if _MSC_VER >= 1200
void __cdecl operator delete( void* pointer, LPCSTR filename, int line_number );
#endif
#endif // _DEBUG

#if defined( _DEBUG )
#define ASSERT( x ) _ASSERT( x )
#else
#define ASSERT( x ) ((void)0)
#endif

// Now start picking up the STL stuff

class CString
{
   private:

      void * m_String;

      LPTSTR m_Buffer;

   protected:

      void m_Format( LPCTSTR format_string, va_list argument_list );

   public:

      // Constructors

      // WARNING! The order of the constructors matters!!!!
      CString();
      CString( const CString& source );
      CString( TCHAR character, int number_of_characters = 1 );

      // ANSI Strings
      CString( LPCSTR ansi_string );
      CString( LPCSTR ansi_string, int number_of_characters );

      // UNICODE Strings
      CString( LPCWSTR unicode_string );
      CString( LPCWSTR unicode_string, int number_of_characters );

      // Bytes that happend to be NULL terminated and considered to be an ANSI string
      CString( const unsigned char* ansi_string );

      ~CString();

      // Methods

      void    Append( LPCTSTR string_p );
      void    Append( TCHAR text_character, int number_of_times );
      void    Append( const CString& source );
      int     Collate( LPCTSTR string_pointer ) const;
      int     Compare( LPCTSTR string_p ) const;
      int     CompareNoCase( LPCTSTR string_p ) const;
      void    Copy( LPCSTR string_p, long number_of_characters = (-1), long beginning_at = 0 );
      void    Copy( LPCWSTR string_p, long number_of_characters = (-1), long beginning_at = 0 );
      void    Empty( void );
      int     Find( TCHAR character ) const;
      int     Find( TCHAR character, int start_index ) const;
      int     Find( LPCTSTR string_p ) const;
      int     Find( LPCTSTR string_p, int start_index ) const;
      int     FindOneOf( LPCTSTR string_p ) const;
      TCHAR   GetAt( int character_index ) const;
      LPTSTR  GetBuffer( int minimum_buffer_length );
      int     GetLength( void ) const;
      int     GetSize( void ) const;
      BOOL    IsEmpty( void ) const;
      CString Left( int count ) const;
      void    MakeLower( void );
      void    MakeReverse( void );
      void    MakeUpper( void );
      CString Mid( int first, int count ) const;
      CString Mid( int first ) const;
      void    ReleaseBuffer( int new_length = (-1) );
      int     ReverseFind( TCHAR character ) const;
      CString Right( int count ) const;
      void    SetAt( int character_index, TCHAR character );
      void    SetLength( long new_length );
      CString SpanExcluding( LPCTSTR character_set ) const;
      CString SpanIncluding( LPCTSTR character_set ) const;
      void    TrimLeft( void );
      void    TrimLeft( TCHAR character );
      void    TrimRight( void );
      void    TrimRight( TCHAR character );

      void __cdecl Format( LPCTSTR printf_format_string, ... );

      // Operators

      operator LPCTSTR() const;
      TCHAR operator[]( int array_index ) const;

      const CString& operator = ( const CString& source );
      const CString& operator = ( LPCSTR source );
      const CString& operator = ( LPCWSTR source );
      const CString& operator = ( const unsigned char * source );
      const CString& operator = ( TCHAR character );

      const CString& operator += ( const CString& source );
      const CString& operator += ( TCHAR character );
      friend CString operator + ( const CString& string1, const CString& string2 );
      friend CString operator + ( const CString& string1, TCHAR character );
      friend CString operator + ( TCHAR character, const CString& string2 );
      friend CString operator + ( const CString& string1, LPCTSTR string2 );
      friend CString operator + ( LPCTSTR string1, const CString& string2 );
};

inline bool operator==( const CString& s1, const CString& s2 )
{
   return( ( s1.Compare( s2 ) == 0 ) ? true : false );
};

inline bool operator==( const CString& s1, LPCTSTR s2 )
{
   return( ( s1.Compare( s2 ) == 0 ) ? true : false );
};

inline bool operator==( LPCTSTR s1, const CString& s2 )
{
   return( ( s2.Compare( s1 ) == 0 ) ? true : false );
};

inline bool operator!=( const CString& s1, const CString& s2 )
{
   return( ( s1.Compare( s2 ) == 0 ) ? false : true );
};

inline bool operator!=( const CString& s1, LPCTSTR s2 )
{
   return( ( s1.Compare( s2 ) == 0 ) ? false : true );
};

inline bool operator!=( LPCTSTR s1, const CString& s2 )
{
   return( ( s2.Compare( s1 ) == 0 ) ? false : true );
};

inline bool operator<( const CString& s1, const CString& s2 )
{
   return( ( s1.Compare( s2 ) < 0 ) ? true : false );
};

inline bool operator<( const CString& s1, LPCTSTR s2 )
{
   return( ( s1.Compare( s2 ) < 0 ) ? true : false );
};

inline bool operator<( LPCTSTR s1, const CString& s2 )
{
   return( ( s2.Compare( s1 ) > 0 ) ? true : false );
};

inline bool operator>( const CString& s1, const CString& s2 )
{
   return( ( s1.Compare( s2 ) > 0 ) ? true : false );
};

inline bool operator>( const CString& s1, LPCTSTR s2 )
{
   return( ( s1.Compare( s2 ) > 0 ) ? true : false );
};

inline bool operator>( LPCTSTR s1, const CString& s2 )
{
   return( ( s2.Compare( s1 ) < 0 ) ? true : false );
};

inline bool operator<=( const CString& s1, const CString& s2 )
{
   return( ( s1.Compare( s2 ) <= 0 ) ? true : false );
};

inline bool operator<=( const CString& s1, LPCTSTR s2 )
{
   return( ( s1.Compare( s2 ) <= 0 ) ? true : false );
};

inline bool operator<=( LPCTSTR s1, const CString& s2 )
{
   return( ( s2.Compare( s1 ) >= 0 ) ? true : false );
};

inline bool operator>=( const CString& s1, const CString& s2 )
{
   return( ( s1.Compare( s2 ) >= 0 ) ? true : false );
};

inline bool operator>=( const CString& s1, LPCTSTR s2 )
{
   return( ( s1.Compare( s2 ) >= 0 ) ? true : false );
};

inline bool operator>=( LPCTSTR s1, const CString& s2 )
{
   return( ( s2.Compare( s1 ) <= 0 ) ? true : false );
};

class CByteArray
{
   typedef unsigned char ARRAY_TYPE;

   protected:

      void * m_Array;

   public:

      CByteArray();
     ~CByteArray();

      int         Add( ARRAY_TYPE new_element );
      void        Append( const BYTE * byte_buffer, int number_of_bytes );
      void        Append( const CByteArray& source );
         //      inline void        Copy( const ARRAY_TYPE& source ) { m_Array = vector< ARRAY_TYPE >( source ); }
      void        Copy( const CByteArray& source );
      ARRAY_TYPE& ElementAt( int array_index );
      void        FreeExtra( void );
      ARRAY_TYPE  GetAt( int array_index ) const;
      int         GetSize( void ) const;
      int         GetUpperBound( void ) const;
      void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );
      void        InsertAt( int array_index, CByteArray * array_p );
      void        RemoveAll( void );
      void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );
      void        SetSize( int new_size, int x = 32 );
      void        SetAt( int array_index, ARRAY_TYPE new_element );

      const ARRAY_TYPE * GetData( void ) const;
      ARRAY_TYPE * GetData( void );
      ARRAY_TYPE operator[]( int array_index ) const;
	   ARRAY_TYPE& operator[]( int array_index );
};

class CStringArray
{
   typedef CString ARRAY_TYPE;

   protected:

      void * m_Array;

   public:

      CStringArray();
      CStringArray( const CStringArray& source );
     ~CStringArray();

      int         Add( ARRAY_TYPE new_element );
      void        Append( const CStringArray& source  );
      void        Copy( const CStringArray& source );
      ARRAY_TYPE& ElementAt( int array_index );
      void        FreeExtra( void );
      ARRAY_TYPE  GetAt( int array_index ) const;
      int         GetSize( void ) const;
      int         GetUpperBound( void ) const;
      void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );
      void        InsertAt( int array_index, CStringArray * array_p );
      void        RemoveAll( void );
      void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );
      void        SetSize( int new_size, int x = 32 );
      void        SetAt( int array_index, ARRAY_TYPE new_element );
      ARRAY_TYPE operator[]( int array_index ) const;
	   ARRAY_TYPE& operator[]( int array_index );
};

class CPtrArray
{
   typedef VOID * ARRAY_TYPE;

   protected:

      void * m_Array;

   public:

      CPtrArray();
     ~CPtrArray();

      int         Add( ARRAY_TYPE new_element );
      void        Append( CPtrArray& source  );
//      inline void        Copy( const ARRAY_TYPE& source ) { m_Array = vector< ARRAY_TYPE >( source ); }
      void        Copy( const CPtrArray& source );
      ARRAY_TYPE& ElementAt( int array_index );
      void        FreeExtra( void );
      ARRAY_TYPE  GetAt( int array_index ) const;
      int         GetSize( void ) const;
      int         GetUpperBound( void ) const;
      void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );
      void        InsertAt( int array_index, CPtrArray * array_p );
      void        RemoveAll( void );
      void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );
      void        SetSize( int new_size, int x = 32 );
      void        SetAt( int array_index, ARRAY_TYPE new_element );
      ARRAY_TYPE operator[]( int array_index ) const;
	   ARRAY_TYPE& operator[]( int array_index );
};

class CDWordArray
{
   typedef DWORD ARRAY_TYPE;

   protected:

      void * m_Array;

   public:

      CDWordArray();
     ~CDWordArray();

      int         Add( ARRAY_TYPE new_element );
      void        Append( CDWordArray& source  );
//      inline void        Copy( const ARRAY_TYPE& source ) { m_Array = vector< ARRAY_TYPE >( source ); }
      void        Copy( const CDWordArray& source );
      ARRAY_TYPE& ElementAt( int array_index );
      void        FreeExtra( void );
      ARRAY_TYPE  GetAt( int array_index ) const;
      int         GetSize( void ) const;
      int         GetUpperBound( void ) const;
      void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );
      void        InsertAt( int array_index, CDWordArray * array_p );
      void        RemoveAll( void );
      void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );
      void        SetSize( int new_size, int x = 32 );
      void        SetAt( int array_index, ARRAY_TYPE new_element );
      const ARRAY_TYPE * GetData( void ) const;
      ARRAY_TYPE * GetData( void );
      ARRAY_TYPE operator[]( int array_index ) const;
	   ARRAY_TYPE& operator[]( int array_index );
};

class CWordArray
{
   typedef WORD ARRAY_TYPE;

   protected:

      void * m_Array;

   public:

      CWordArray();
     ~CWordArray();

      int         Add( ARRAY_TYPE new_element );
      void        Append( CWordArray& source  );
//      inline void        Copy( const ARRAY_TYPE& source ) { m_Array = vector< ARRAY_TYPE >( source ); }
      void        Copy( const CWordArray& source );
      ARRAY_TYPE& ElementAt( int array_index );
      void        FreeExtra( void );
      ARRAY_TYPE  GetAt( int array_index ) const;
      int         GetSize( void ) const;
      int         GetUpperBound( void ) const;
      void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );
      void        InsertAt( int array_index, CWordArray * array_p );
      void        RemoveAll( void );
      void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );
      void        SetSize( int new_size, int x = 32 );
      void        SetAt( int array_index, ARRAY_TYPE new_element );
      const ARRAY_TYPE * GetData( void ) const;
      ARRAY_TYPE * GetData( void );
      ARRAY_TYPE operator[]( int array_index ) const;
	   ARRAY_TYPE& operator[]( int array_index );
};

class CUIntArray
{
   typedef unsigned int ARRAY_TYPE;

   protected:

      void * m_Array;

   public:

      CUIntArray();
     ~CUIntArray();

      int         Add( ARRAY_TYPE new_element );
      void        Append( CUIntArray& source  );
//      inline void        Copy( const ARRAY_TYPE& source ) { m_Array = vector< ARRAY_TYPE >( source ); }
      void        Copy( const CUIntArray& source );
      ARRAY_TYPE& ElementAt( int array_index );
      void        FreeExtra( void );
      ARRAY_TYPE  GetAt( int array_index ) const;
      int         GetSize( void ) const;
      int         GetUpperBound( void ) const;
      void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );
      void        InsertAt( int array_index, CUIntArray * array_p );
      void        RemoveAll( void );
      void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );
      void        SetSize( int new_size, int x = 32 );
      void        SetAt( int array_index, ARRAY_TYPE new_element );
      const ARRAY_TYPE * GetData( void ) const;
      ARRAY_TYPE * GetData( void );
      ARRAY_TYPE operator[]( int array_index ) const;
	   ARRAY_TYPE& operator[]( int array_index );
};

#define wfc_append_string_to_CByteArray( string1, bytes_array ) bytes_array.Append( reinterpret_cast< const BYTE * >( string1.operator LPCTSTR() ), string1.GetLength() )

#endif // MFC_TO_STL_HEADER_FILE
