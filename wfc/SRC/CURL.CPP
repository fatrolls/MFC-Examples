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
** $Workfile: curl.cpp $
** $Revision: 14 $
** $Modtime: 1/04/00 5:24a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CUniformResourceLocator, CObject, 1 );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CUniformResourceLocator::CUniformResourceLocator()
{
   Empty();
}

CUniformResourceLocator::CUniformResourceLocator( const CUniformResourceLocator& source )
{
   Copy( source );
}

CUniformResourceLocator::CUniformResourceLocator( const CUniversalNamingConvention& source )
{
   Copy( source );
}

CUniformResourceLocator::CUniformResourceLocator( LPCTSTR source )
{
   Copy( source );
}

CUniformResourceLocator::~CUniformResourceLocator()
{
   Empty();
}

int CUniformResourceLocator::Compare( const CUniformResourceLocator& source ) const
{
   return( URL.CompareNoCase( source.URL ) );
}

void CUniformResourceLocator::Copy( const CUniformResourceLocator& source )
{
   ProtocolName = source.ProtocolName;
   MachineName  = source.MachineName;
   PathName     = source.PathName;
   PortName     = source.PortName;
   URL          = source.URL;
}

void CUniformResourceLocator::Copy( const CUniversalNamingConvention& source )
{
   Empty();

   ProtocolName = TEXT( "file" );
   MachineName  = source.ServerName;
   PathName     = source.ShareName;
   PathName    += TEXT( "/" );
   PathName    += source.PathName;

   /*
   ** Now go through PathName to make sure it has /'s instead of \'s
   */

   int location_of_slash = 0;

   while( location_of_slash < PathName.GetLength() )
   {
      if ( PathName[ location_of_slash ] == TEXT( '\\' ) )
      {
         PathName.SetAt( location_of_slash, TEXT( '/' ) );
      }

      location_of_slash++;
   }

   Make();
}

void CUniformResourceLocator::Copy( LPCTSTR source )
{
   ASSERT( source != NULL );

   Empty();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      CString temp_string = source;

      int location = temp_string.Find( TEXT( ':' ) );

      if ( location == (-1) )
      {
         return;
      }

      ProtocolName = temp_string.Left( location );

      temp_string = temp_string.Right( ( temp_string.GetLength() - location ) - 1 );

      while( temp_string[ 0 ] == TEXT( '/' ) )
      {
         temp_string = temp_string.Right( temp_string.GetLength() - 1 );
      }

      location = temp_string.Find( TEXT( '/' ) );

      if ( location == (-1) )
      {
         MachineName = temp_string;
      }
      else
      {
         MachineName = temp_string.Left( location );
         PathName    = temp_string.Right( ( temp_string.GetLength() - location ) - 1 );
      }

      /*
      ** Now see if MachineName has a PortName in it
      */

      location = MachineName.Find( TEXT( ':' ) );

      if ( location != (-1) )
      {
         PortName    = MachineName.Right( ( MachineName.GetLength() - location ) - 1 );
         MachineName = MachineName.Left( location );
      }

      Make();
   }
   catch( ... )
   {
      Empty();
   }
}

void CUniformResourceLocator::Empty( void )
{
   ProtocolName.Empty();
   MachineName.Empty();
   PathName.Empty();
   PortName.Empty();
   URL.Empty();
}

void CUniformResourceLocator::Make( void )
{
   URL  = ProtocolName;
   URL += TEXT( "://" );
   URL += MachineName;

   if ( PortName != TEXT( "" ) )
   {
      URL += TEXT( ":" );
      URL += PortName;
   }

   URL += TEXT( "/" );
   URL += PathName;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CUniformResourceLocator::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << ProtocolName;
      archive << MachineName;
      archive << PathName;
      archive << PortName;
      archive << URL;
   }
   else
   {
      archive >> ProtocolName;
      archive >> MachineName;
      archive >> PathName;
      archive >> PortName;
      archive >> URL;
   }
}

#endif // WFC_NO_SERIALIZATION

CUniformResourceLocator& CUniformResourceLocator::operator = ( const CUniformResourceLocator& source )
{
   Copy( source );
   return( *this );
}

CUniformResourceLocator& CUniformResourceLocator::operator = ( const CUniversalNamingConvention& source )
{
   Copy( source );
   return( *this );
}

CUniformResourceLocator& CUniformResourceLocator::operator = ( LPCTSTR source )
{
   Copy( source );
   return( *this );
}

BOOL CUniformResourceLocator::operator == ( const CUniformResourceLocator& right_url ) const
{
   if ( Compare( right_url ) == 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CUniformResourceLocator::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "ProtocolName = \"" ) << ProtocolName << TEXT( "\"\n" );
   dump_context << TEXT( "MachineName  = \"" ) << MachineName  << TEXT( "\"\n" );
   dump_context << TEXT( "PathName     = \"" ) << PathName     << TEXT( "\"\n" );
   dump_context << TEXT( "PortName     = \"" ) << PortName     << TEXT( "\"\n" );
   dump_context << TEXT( "URL          = \"" ) << URL          << TEXT( "\"\n" );
}

#endif // _DEBUG

// End of source
