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
** $Workfile: cunc.cpp $
** $Revision: 16 $
** $Modtime: 1/24/00 8:33p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CUniversalNamingConvention, CObject, 1 );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CUniversalNamingConvention::CUniversalNamingConvention()
{
   Empty();
}

CUniversalNamingConvention::CUniversalNamingConvention( const CUniversalNamingConvention& source )
{
   Copy( source );
}

CUniversalNamingConvention::CUniversalNamingConvention( const CUniformResourceLocator& source )
{
   Copy( source );
}

CUniversalNamingConvention::CUniversalNamingConvention( LPCTSTR source )
{
   Copy( source );
}

CUniversalNamingConvention::~CUniversalNamingConvention()
{
   Empty();
}

int CUniversalNamingConvention::Compare( const CUniversalNamingConvention& source ) const
{
   if ( this == &source )
   {
      return( 0 );
   }

   return( UNC.CompareNoCase( source.UNC ) );
}

void CUniversalNamingConvention::Copy( const CUniversalNamingConvention& source )
{
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   ServerName = source.ServerName;
   ShareName  = source.ShareName;
   PathName   = source.PathName;

   /*
   ** Its safer if we construct the UNC
   */

   Make();
}

void CUniversalNamingConvention::Copy( const CUniformResourceLocator& source )
{
   Empty();

   ServerName = source.MachineName;
   PathName   = source.PathName;

   int location_of_slash = PathName.Find( TEXT( '/' ) );

   if ( location_of_slash != (-1) )
   {
      ShareName = PathName.Left( location_of_slash );
      PathName  = PathName.Right( ( PathName.GetLength() - location_of_slash ) - 1 );
   }

   /*
   ** Now go through the Path and convert /'s to \'s
   */

   location_of_slash = 0;

   while( location_of_slash < PathName.GetLength() )
   {
      if ( PathName[ location_of_slash ] == TEXT( '/' ) )
      {
         PathName.SetAt( location_of_slash, TEXT( '\\' ) );
      }

      location_of_slash++;
   }

   Make();
}

void CUniversalNamingConvention::Copy( LPCTSTR source )
{
   ASSERT( source != NULL );

   // We were passed a pointer, do not trust it

   try
   {
      /*
      ** Input should be "\\server_name\share_name\directory\filename.ext"
      */

      /*
      ** Make sure we start out with a virgin object
      */

      Empty();

      if ( source == NULL )
      {
         return;
      }

      CString temp_string( source );

      if ( temp_string.GetLength() < 2 || temp_string.Left( 2 ) != TEXT( "\\\\" ) )
      {
         PathName = temp_string;
         Make();
         return;
      }

      /*
      ** See if the first two characters are back slashes, if so, rip them off
      */

      while( temp_string[ 0 ] == TEXT( '\\' ) )
      {
         temp_string = temp_string.Right( temp_string.GetLength() - 1 );
      }

      int location_of_back_slash = temp_string.Find( TEXT( '\\' ) );

      /*
      ** First field is ServerName
      */

      if ( location_of_back_slash == (-1) )
      {
         /*
         ** The user sent us something like "\\dodah.txt"
         */

         PathName = temp_string;
         Make();
         return;
      }

      /*
      ** First field is server name
      */

      ServerName = temp_string.Left( location_of_back_slash );

      temp_string = temp_string.Right( ( temp_string.GetLength() - location_of_back_slash ) - 1 );

      /*
      ** Second field is ShareName
      */

      location_of_back_slash = temp_string.Find( TEXT( '\\' ) );

      if ( location_of_back_slash == (-1) )
      {
         /*
         ** User sent us something like "\\server_name\"
         */

         Make();
         return;
      }

      ShareName = temp_string.Left( location_of_back_slash );
      PathName  = temp_string.Right( ( temp_string.GetLength() - location_of_back_slash ) - 1 );

      Make();
   }
   catch( ... )
   {
      Empty();
   }
}

void CUniversalNamingConvention::Empty( void )
{
   ServerName.Empty();
   ShareName.Empty();
   PathName.Empty();
   UNC.Empty();
}

void CUniversalNamingConvention::Make( void )
{
#if ! defined( WFC_STL )
   TRACE( TEXT( "CUniversalNamingConvention::Make() : Adding \"\\\\\" + \"%s\" + \"\\\" + \"%s\" + \"\\\" + \"%s\"\n" ),
          (LPCTSTR) ServerName,
          (LPCTSTR) ShareName,
          (LPCTSTR) PathName );
#endif // WFC_STL

   UNC  = TEXT( "\\\\" );
   UNC += ServerName;
   UNC += TEXT( "\\" );
   UNC += ShareName;
   UNC += TEXT( "\\" );
   UNC += PathName;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CUniversalNamingConvention::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << ServerName;
      archive << ShareName;
      archive << PathName;
      archive << UNC;
   }
   else
   {
      archive >> ServerName;
      archive >> ShareName;
      archive >> PathName;
      archive >> UNC;
   }
}

#endif // WFC_NO_SERIALIZATION

CUniversalNamingConvention& CUniversalNamingConvention::operator = ( const CUniversalNamingConvention& source )
{
   Copy( source );
   return( *this );
}

CUniversalNamingConvention& CUniversalNamingConvention::operator = ( const CUniformResourceLocator& source )
{
   Copy( source );
   return( *this );
}

CUniversalNamingConvention& CUniversalNamingConvention::operator = ( LPCTSTR source )
{
   Copy( source );
   return( *this );
}

BOOL CUniversalNamingConvention::operator == ( const CUniversalNamingConvention& right_unc ) const
{
   if ( Compare( right_unc ) == 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CUniversalNamingConvention::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "ServerName = \"" ) << ServerName << TEXT( "\"\n" );
   dump_context << TEXT( "ShareName  = \"" ) << ShareName  << TEXT( "\"\n" );
   dump_context << TEXT( "PathName   = \"" ) << PathName   << TEXT( "\"\n" );
   dump_context << TEXT( "UNC        = \"" ) << UNC        << TEXT( "\"\n" );
}

#endif // _DEBUG

// End of source
