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
** $Workfile: CXMLArchive.cpp $
** $Revision: 18 $
** $Modtime: 1/17/00 9:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// 1998-04-25 - Thanks go to Alexander Sokolsky (sokolsky@who.net)
// for pointing out my flawed assumption that all times are
// UTC time.

static inline void _append_time_zone_offset( CString& time_string )
{
   TIME_ZONE_INFORMATION time_zone_information;

   ZeroMemory( &time_zone_information, sizeof( time_zone_information ) );

   DWORD zone_identifier = GetTimeZoneInformation( &time_zone_information );

   if ( zone_identifier == 0xFFFFFFFF )
   {
      return;
   }

   int offset_hours   = time_zone_information.Bias / 60;
   int offset_minutes = time_zone_information.Bias % 60;

   offset_hours   *= (-1);
   offset_minutes *= (-1);

   TCHAR offset_character = TEXT( '+' );

   if ( offset_hours < 0 || offset_minutes < 0 )
   {
      if ( offset_hours < 0 )
      {
         offset_hours *= (-1);
      }

      if ( offset_minutes < 0 )
      {
         offset_minutes *= (-1);
      }

      offset_character = TEXT( '-' );
   }

   if ( offset_hours == 0 && offset_minutes == 0 )
   {
      time_string += TEXT( "Z" );
   }
   else
   {
      CString zone_string;

      zone_string.Format( TEXT( "X%02d:%02d" ), offset_hours, offset_minutes );
      zone_string.SetAt( 0, offset_character );

      time_string += zone_string;
   }
}

CXMLArchive::CXMLArchive()
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::CXMLArchive()" ) );

   m_AddNewLineAfterEachElement = FALSE;
   m_AmIWriting = FALSE;
   m_Element_p  = NULL;
   _append_time_zone_offset( m_TimeZone );
}

CXMLArchive::~CXMLArchive()
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::~CXMLArchive()" ) );

   m_AddNewLineAfterEachElement = FALSE;
   m_AmIWriting = FALSE;
   m_Element_p  = NULL;
}

BOOL CXMLArchive::GetAddNewLineAfterEachElement( void ) const
{
   return( ( m_AddNewLineAfterEachElement == FALSE ) ? FALSE : TRUE );
}

CExtensibleMarkupLanguageElement * CXMLArchive::GetElement( void ) const
{
   return( m_Element_p );
}

BOOL CXMLArchive::IsLoading( void ) const
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::IsLoading()" ) );

   if ( m_AmIWriting == FALSE )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CXMLArchive::IsStoring( void ) const
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::IsStoring()" ) );

   if ( m_AmIWriting != FALSE )
   {
      return( TRUE );
   }

   return( FALSE );
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, BOOL& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( BOOL )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      DWORD boolean_value = 0;

      // We save them as a DWORD

      sub_element_p = Read( tag, boolean_value );

      if ( sub_element_p != NULL )
      {
         if ( boolean_value == 0 )
         {
            value = FALSE;
         }
         else
         {
            value = TRUE;
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CByteArray& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CByteArray )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      // Always start from a known state
      value.RemoveAll();

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CBase64Coding coder;

         CString contents;
         
         sub_element_p->GetText( contents );

         coder.Decode( contents, value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CDWordArray& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CDWordArray )" ) );

   value.RemoveAll();

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      CString element_name;
      CString data;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         // Cool! We have the top level element. Now we
         // need to cycle through the sub-elements.

         DWORD index = 0;

         BOOL exit_loop = FALSE;

         CExtensibleMarkupLanguageElement * entry_p = NULL;

         while( exit_loop == FALSE )
         {
            element_name.Format( TEXT( "ENTRY(%lu)" ), index );

            entry_p = sub_element_p->GetChild( element_name );

            if ( entry_p == NULL )
            {
               WFCTRACE( TEXT( "Exitting" ) );
               // We've reached the last entry
               exit_loop = TRUE;
            }
            else
            {
               entry_p->GetText( data );

               value.Add( _ttol( data ) );

               index++;
            }
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CString& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CString )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         sub_element_p->GetText( value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CStringArray& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CStringArray )" ) );

   value.RemoveAll();

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      CString element_name;
      CString data;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         // Cool! We have the top level element. Now we
         // need to cycle through the sub-elements.

         DWORD index = 0;

         BOOL exit_loop = FALSE;

         CExtensibleMarkupLanguageElement * entry_p = NULL;

         while( exit_loop == FALSE )
         {
            element_name.Format( TEXT( "ENTRY(%lu)" ), index );

            entry_p = sub_element_p->GetChild( element_name );

            if ( entry_p == NULL )
            {
               WFCTRACE( TEXT( "Exitting" ) );
               // We've reached the last entry
               exit_loop = TRUE;
            }
            else
            {
               entry_p->GetText( data );

               value.Add( data );

               index++;
            }
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, double& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( double )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // Always start from a known state
   value = 0.0;

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         value = ::_ttof( string_value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, DWORD& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( DWORD )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         value = ::_ttol( string_value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, LONGLONG& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( LONGLONG )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         value = ::_ttoi64( string_value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, ULONGLONG& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( ULONGLONG )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         value = (ULONGLONG) ::_ttoi64( string_value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CFileTime& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CFileTime )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         ::wfc_parse_iso_8601_string( string_value, value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

#if ! defined( WFC_STL )

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, COleDateTime& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( COleDateTime )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         ::wfc_parse_iso_8601_string( string_value, value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, COleDateTimeSpan& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( COleDateTimeSpan )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         value = COleDateTimeSpan( 0, 0, 0, ::_ttol( string_value ) );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

#endif // WFC_STL

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CSystemTime& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CSystemTime )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         wfc_parse_iso_8601_string( string_value, value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CTime& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CTime )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         ::wfc_parse_iso_8601_string( string_value, value );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Read( const CString& tag, CTimeSpan& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Read( CTimeSpan )" ) );

   if ( m_AmIWriting == TRUE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = NULL;

      sub_element_p = m_Element_p->GetChild( tag );

      if ( sub_element_p != NULL )
      {
         CString string_value;

         sub_element_p->GetText( string_value );

         value = CTimeSpan( 0, 0, 0, ::_ttol( string_value ) );
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

void CXMLArchive::ReadFrom( CExtensibleMarkupLanguageElement * element_p )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::ReadFrom()" ) );

   m_AmIWriting = FALSE;
   m_Element_p  = element_p;
}

BOOL CXMLArchive::SerializeObject( const CString& tag, void * object_p, XML_ARCHIVE_SERIALIZE_OBJECT serialize_function )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::SerializeObject()" ) );

   if ( object_p == NULL )
   {
      WFCTRACE( TEXT( "Object parameter is NULL!" ) );
      return( FALSE );
   }

   if ( serialize_function == NULL )
   {
      WFCTRACE( TEXT( "Callback is NULL!" ) );
      return( FALSE );
   }

   if ( tag.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "Tag is empty!" ) );
      return( FALSE );
   }

   BOOL return_value = FALSE;

   // We were passed pointers, don't trust them

   try
   {
      return_value = serialize_function( this, tag, object_p );
   }
   catch( ... )
   {
      return_value = FALSE;
   }

   return( return_value == FALSE ? FALSE : TRUE );
}

void CXMLArchive::SetAddNewLineAfterEachElement( BOOL add_new_line )
{
   m_AddNewLineAfterEachElement = ( add_new_line == FALSE ) ? FALSE : TRUE;
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, BOOL value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( BOOL )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         sub_element_p->SetTag( tag );

         if ( value == FALSE )
         {
            sub_element_p->AddText( "0" );
         }
         else
         {
            sub_element_p->AddText( "1" );
         }

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CByteArray& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CByteArray )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         CString contents;

         CBase64Coding encoder;

         encoder.Encode( value, contents );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CDWordArray& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CDWordArray )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         sub_element_p->SetTag( tag );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }

         CXMLArchive entry_archiver;

         entry_archiver.SetAddNewLineAfterEachElement( m_AddNewLineAfterEachElement );

         entry_archiver.WriteTo( sub_element_p );

         DWORD index             = 0;
         DWORD number_of_entries = value.GetSize();

         while( index < number_of_entries )
         {
            entry_archiver.Write( TEXT( "ENTRY" ), value.GetAt( index ) );
            index++;
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CFileTime& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CFileTime )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         CTime the_time;

         value.CopyTo( the_time );

         contents = the_time.Format( TEXT( "%Y-%m-%dT%H:%M:%S" ) );

         // 1998-04-25 - Thanks go to Alexander Sokolsky (sokolsky@who.net)
         // for finding a bug here. I wasn't including the time zone
         // offset information.

         contents += m_TimeZone;

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

#if ! defined( WFC_STL )

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const COleDateTime& value, BOOL value_is_UTC_time )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( COleDateTime )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents = value.Format( TEXT( "%Y-%m-%dT%H:%M:%S" ) );

         // 1998-04-25 - Thanks go to Alexander Sokolsky (sokolsky@who.net)
         // for finding a bug here. I wasn't including the time zone
         // offset information.

         if ( value_is_UTC_time == FALSE )
         {
            // Convert to UTC
            contents += m_TimeZone;
         }
         else
         {
            // Time value is UTC
            contents += TEXT( "Z" );
         }

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const COleDateTimeSpan& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( COleDateTimeSpan )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents.Format( TEXT( "%lu" ), value.GetTotalSeconds() );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

#endif // WFC_STL

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CString& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CString )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         sub_element_p->SetTag( tag );
         sub_element_p->AddText( value );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CStringArray& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CStringArray )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   try
   {
      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         sub_element_p->SetTag( tag );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }

         CXMLArchive entry_archiver;

         entry_archiver.SetAddNewLineAfterEachElement( m_AddNewLineAfterEachElement );

         entry_archiver.WriteTo( sub_element_p );

         DWORD index = 0;
         DWORD number_of_entries = value.GetSize();

         while( index < number_of_entries )
         {
            entry_archiver.Write( TEXT( "ENTRY" ), value.GetAt( index ) );
            index++;
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CSystemTime& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CSystemTime )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         CTime the_time;

         value.CopyTo( the_time );

         // System Time is always UTC

         contents = the_time.Format( TEXT( "%Y-%m-%dT%H:%M:%SZ" ) );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CTime& value, BOOL value_is_UTC_time )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CTime )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents = value.Format( TEXT( "%Y-%m-%dT%H:%M:%S" ) );

         // 1998-04-25 - Thanks go to Alexander Sokolsky (sokolsky@who.net)
         // for finding a bug here. I wasn't including the time zone
         // offset information.

         if ( value_is_UTC_time == FALSE )
         {
            // Time value needs to be converted to UTC
            contents += m_TimeZone;
         }
         else
         {
            // Time value is already UTC
            contents += TEXT( "Z" );
         }

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, const CTimeSpan& value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( CTimeSpan )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents.Format( TEXT( "%lu" ), value.GetTotalSeconds() );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, double value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( double )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents.Format( TEXT( "%.15lf" ), value );

         // We'll be friendly here and strip off trailing zeroes

         BOOL exit_loop = FALSE;

         while( exit_loop == FALSE )
         {
            if ( contents.GetLength() > 0 )
            {
               if ( contents.GetAt( contents.GetLength() - 1 ) == TEXT( '0' ) )
               {
                  contents = contents.Left( contents.GetLength() - 1 );
               }
               else
               {
                  exit_loop = TRUE;
               }
            }
            else
            {
               exit_loop = TRUE;
            }
         }

         if ( contents.GetLength() == 0 )
         {
            contents = TEXT( "0.0" );
         }

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, DWORD value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( DWORD )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents.Format( TEXT( "%lu" ), value );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, LONGLONG value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( LONGLONG )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents.Format( TEXT( "%I64d" ), value );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

CExtensibleMarkupLanguageElement * CXMLArchive::Write( const CString& tag, ULONGLONG value )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::Write( ULONGLONG )" ) );

   if ( m_AmIWriting == FALSE || m_Element_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return( NULL );
   }

   // We were passed a pointer, don't trust it

   try
   {
      // In a perfect object world, we would simply convert the value parameter
      // to a string and call the Write() method that takes two strings and let
      // that method create the new sub element. However, that would make memory
      // leak detection harder since everything allocated would be from that
      // one location. This way, we get a better chance of tracking down the
      // offending leaker.

      CExtensibleMarkupLanguageElement * sub_element_p = CExtensibleMarkupLanguageElement::NewElement( m_Element_p );

      if ( sub_element_p != NULL )
      {
         // Since we're XML, we must convert everything to a string

         CString contents;

         contents.Format( TEXT( "%I64u" ), value );

         sub_element_p->SetTag( tag );
         sub_element_p->AddText( contents );

         if ( m_AddNewLineAfterEachElement != FALSE )
         {
            m_Element_p->AddText( TEXT( "\n" ) );
         }
      }

      return( sub_element_p );
   }
   catch( ... )
   {
      return( NULL );
   }
}

void CXMLArchive::WriteTo( CExtensibleMarkupLanguageElement * element_p )
{
   WFCLTRACEINIT( TEXT( "CXMLArchive::WriteTo()" ) );

   m_AmIWriting = TRUE;
   m_Element_p  = element_p;
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CXMLArchive</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, XML, source code">
<META name="description" content="The C++ class that handles serializing (writing and reading) objects in XML documents.">
</HEAD>

<BODY>

<H1>CXMLArchive</H1>
$Revision: 18 $<BR><HR>

<H2>Description</H2>
This class handles serializing data (aka object persistence) to and
from XML documents. It is patterned after the MFC CArchive class.

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="GetAddNewLineAfterEachElement">GetAddNewLineAfterEachElement</A></B>( void ) const</PRE><DD>
Returns TRUE if the class will add a new line after writing an
element to the document. This makes the resulting document easier to
read by humans.

<DT><PRE>BOOL <B><A NAME="IsLoading">IsLoading</A></B>( void ) const</PRE><DD>
Returns TRUE if this object is being used to load
data from an XML document. This is set by calling <B>ReadFrom</B>().

<DT><PRE>BOOL <B><A NAME="IsStoring">IsStoring</A></B>( void ) const</PRE><DD>
Returns TRUE if this object is being used to write
data to an XML document. This is set by calling <B>WriteTo</B>().

<DT><PRE><A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B><A NAME="Read">Read</A></B>( const CString&amp; tag, BOOL&amp;             value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, CString&amp;          value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, CStringArray&amp;     value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, CByteArray&amp;       value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, CDWordArray&amp;      value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, <A HREF="CFileTime.htm">CFileTime</A>&amp;        value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, COleDateTime&amp;     value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, COleDateTimeSpan&amp; value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, <A HREF="CSystemTime.htm">CSystemTime</A>&amp;      value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, CTime&amp;            value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, CTimeSpan&amp;        value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, double&amp;           value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, DWORD&amp;            value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, LONGLONG&amp;         value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Read</B>( const CString&amp; tag, ULONGLONG&amp;        value )</PRE><DD>
This method reads <CODE>value</CODE> from the XML document with the tag of <CODE>tag</CODE>.
The data is read from children of the element passed in <B>ReadFrom</B>().
CByteArray values are automatically encoded using Base64. 
<A HREF="CFileTime.htm">CFileTime</A>, <A HREF="CSystemTime.htm">CSystemTime</A>,
and CTime values
are written in ISO8601 format. CTimeSpan values are written in seconds.
<B>Read</B>() will return a pointer to the
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A>
object upon success or NULL on failure. If <B>Read</B>() fails,
<CODE>value</CODE> will be set to an initial state.

<DT><PRE>void <B><A NAME="ReadFrom">ReadFrom</A></B>( <A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * element_p )</PRE><DD>
Tells the object where to get its data from. Subsequent calls to <B>Read</B>()
will cause data to be read from the children of <CODE>element_p</CODE>.

<DT><PRE>void <B><A NAME="SetAddNewLineAfterEachElement">SetAddNewLineAfterEachElement</A></B>( BOOL add_new_line = TRUE )</PRE><DD>
When you set this to TRUE, the object will add a line break after
writing an element. This results in an XML document that is slightly
larger but much easier to read by humans.

<DT><PRE><A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B><A NAME="Write">Write</A></B>( const CString&amp; tag, BOOL                    value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const CByteArray&amp;       value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const CDWordArray&amp;      value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const <A HREF="CFileTime.htm">CFileTime</A>&amp;        value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const COleDateTime&amp;     value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const COleDateTimeSpan&amp; value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const CString&amp;          value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const CStringArray&amp;     value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const <A HREF="CSystemTime.htm">CSystemTime</A>&amp;      value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const CTime&amp;            value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, const CTimeSpan&amp;        value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, double                  value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, DWORD                   value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, LONGLONG                value )
<A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * <B>Write</B>( const CString&amp; tag, ULONGLONG               value )</PRE><DD>
This method writes <CODE>value</CODE> to the XML document.
A new element is created with a tag name of <CODE>tag</CODE>. The data
is written to this new element and the element is then made a child of
the element passed to <B><A HREF="#WriteTo">WriteTo()</A></B>.
CByteArray will be Base64 encoded before being written to the document.
<A HREF="CFileTime.htm">CFileTime</A>,
<A HREF="CSystemTime.htm">CSystemTime</A>,
COleDateTime, and CTime will be written in ISO8601 format. Only
<A HREF="CSystemTime.htm">CSystemTime</A> will be written with a time
zone of Z. The other representations of time will have the time zone
offset information written.
CTimeSpan and COleDateTimeSpan will be written as total number of seconds.

<DT><PRE>void <B><A NAME="WriteTo">WriteTo</A></B>( <A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * element_p )</PRE><DD>
This tells the object where to write data. When data is written to <CODE>element_p</CODE>,
new elements are created and made children of <CODE>element_p</CODE>.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

class CSimpleClass
{
   protected:

      CTime   m_Birthday;
      CString m_Name;
      double  m_PriceLimit;

   public:

      void Serialize( <B>CXMLArchive</B>&amp; archive );
};

void CSimpleClass::Serialize( <B>CXMLArchive</B>&amp; archive )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;CSimpleClass::Serialize()&quot; ) );

   <A HREF="CExtensibleMarkupLanguageElement.htm">CExtensibleMarkupLanguageElement</A> * element_for_this_class = NULL;

   <B>CXMLArchive</B> sub_archive;

   if ( archive.<A HREF="#IsStoring">IsStoring</A>() )
   {
      element_for_this_class = archive.<A HREF="#Write">Write</A>( TEXT( &quot;CSIMPLECLASS&quot; ), TEXT( &quot;&quot; ) );

      sub_archive.<A HREF="#WriteTo">WriteTo</A>( element_for_this_class );

      sub_archive.Write( TEXT( &quot;BIRTHDAY&quot;    ), m_Birthday   );
      sub_archive.Write( TEXT( &quot;NAME&quot;        ), m_Name       );
      sub_archive.Write( TEXT( &quot;PRICE_LIMIT&quot; ), m_PriceLimit );
   }
   else
   {
      element_for_this_class = archive.<A HREF="#Read">Read</A>( TEXT( &quot;CSIMPLECLASS&quot; ), TEXT( &quot;&quot; ) );

      sub_archive.<A HREF="#ReadFrom">ReadFrom</A>( element_for_this_class );

      sub_archive.Read( TEXT( &quot;BIRTHDAY&quot;    ), m_Birthday   );
      sub_archive.Read( TEXT( &quot;NAME&quot;        ), m_Name       );
      sub_archive.Read( TEXT( &quot;PRICE_LIMIT&quot; ), m_PriceLimit );
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CXMLArchive.cpp $<BR>
$Modtime: 1/17/00 9:24a $
</BODY>

</HTML>
#endif
