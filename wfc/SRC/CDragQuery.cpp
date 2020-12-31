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
** $Workfile: CDragQuery.cpp $
** $Revision: 3 $
** $Modtime: 1/04/00 5:07a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CDragQuery::CDragQuery( HDROP handle )
{
   WFCLTRACEINIT( TEXT( "CDragQuery::CDragQuery()" ) );
   m_Handle = handle;
}

CDragQuery::CDragQuery( const CDragQuery& source )
{
   WFCLTRACEINIT( TEXT( "CDragQuery::CDragQuery( CDragQuery )" ) );
   m_Handle = NULL;
   Copy( source );
}

CDragQuery::~CDragQuery()
{
   WFCLTRACEINIT( TEXT( "CDragQuery::~CDragQuery()" ) );
   Finish();
}

void CDragQuery::Copy( const CDragQuery& source )
{
   WFCLTRACEINIT( TEXT( "CDragQuery::Copy()" ) );

   Finish();
   SetHandle( source.GetHandle() );
}

void CDragQuery::Finish( void )
{
   WFCLTRACEINIT( TEXT( "CDragQuery::Finish()" ) );

   if ( m_Handle != (HDROP) NULL )
   {
      ::DragFinish( m_Handle );
      m_Handle = (HDROP) NULL;
   }
}

void CDragQuery::GetFilenames( CStringArray& filenames ) const
{
   WFCLTRACEINIT( TEXT( "CDragQuery::GetFilenames()" ) );

   filenames.RemoveAll();

   if ( m_Handle == (HDROP) NULL )
   {
      WFCTRACE( TEXT( "SetHandle() has not yet been called." ) );
      return;
   }

   UINT number_of_files = GetNumberOfFiles();
   UINT index           = 0;

   TCHAR filename[ _MAX_PATH ];

   while( index < number_of_files )
   {
      ZeroMemory( filename, sizeof( filename ) );

      if ( ::DragQueryFile( m_Handle, index, filename, DIMENSION_OF( filename ) ) > 0 )
      {
         filenames.Add( filename );
      }

      index++;
   }
}

HDROP CDragQuery::GetHandle( void ) const
{
   WFCLTRACEINIT( TEXT( "CDragQuery::GetHandle()" ) );
   return( m_Handle );
}

UINT CDragQuery::GetNumberOfFiles( void ) const
{
   WFCLTRACEINIT( TEXT( "CDragQuery::GetNumberOfFiles()" ) );

   if ( m_Handle == NULL )
   {
      return( 0 );
   }

   UINT return_value = 0;

   return_value = ::DragQueryFile( m_Handle, 0xFFFFFFFF, NULL, 0 );

   return( return_value );
}

BOOL CDragQuery::GetPoint( POINT& point ) const
{
   WFCLTRACEINIT( TEXT( "CDragQuery::GetPoint()" ) );

   point.x = 0;
   point.y = 0;

   if ( m_Handle == NULL )
   {
      return( FALSE );
   }

   if ( ::DragQueryPoint( m_Handle, &point ) == FALSE )
   {
      WFCTRACE( TEXT( "DragQueryPoint() failed")  );
      WFCTRACEERROR( GetLastError() );
      point.x = 0;
      point.y = 0;
      return( FALSE );
   }

   return( TRUE );
}

void CDragQuery::SetHandle( HDROP handle )
{
   WFCLTRACEINIT( TEXT( "CDragQuery::SetHandle()" ) );
   m_Handle = handle;
}

CDragQuery& CDragQuery::operator=( const CDragQuery& source )
{
   WFCLTRACEINIT( TEXT( "CDragQuery::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
