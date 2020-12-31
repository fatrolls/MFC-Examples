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
** $Workfile: ovrlpd.cpp $
** $Revision: 16 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// Construction

COverlapped::COverlapped()
{
   WFCLTRACEINIT( TEXT( "COverlapped::COverlapped()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Internal     = 0;
   InternalHigh = 0;
   Offset       = 0;
   OffsetHigh   = 0;
   hEvent       = ::CreateEvent( NULL, TRUE, FALSE, NULL );
   m_AutomaticallyDelete = TRUE;
}

COverlapped::COverlapped( const OVERLAPPED * source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::COverlapped( OVERLAPPED * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Internal     = 0;
   InternalHigh = 0;
   Offset       = 0;
   OffsetHigh   = 0;
   hEvent       = NULL;
   m_AutomaticallyDelete = FALSE;

   Copy( source );
}

COverlapped::COverlapped( const OVERLAPPED& source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::COverlapped( OVERLAPPED& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Internal     = 0;
   InternalHigh = 0;
   Offset       = 0;
   OffsetHigh   = 0;
   hEvent       = NULL;
   m_AutomaticallyDelete = FALSE;

   Copy( source );
}

COverlapped::COverlapped( const COverlapped& source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::COverlapped( COverlapped& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Internal     = 0;
   InternalHigh = 0;
   Offset       = 0;
   OffsetHigh   = 0;
   hEvent       = NULL;
   m_AutomaticallyDelete = FALSE;

   Copy( source );
}

COverlapped::~COverlapped()
{
   WFCLTRACEINIT( TEXT( "COverlapped::~COverlapped()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

// Methods

void COverlapped::Copy( const COverlapped& source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::Copy( COverlapped& )" ) );
   Empty();

   Internal     = source.Internal;
   InternalHigh = source.InternalHigh;
   Offset       = source.Offset;
   OffsetHigh   = source.OffsetHigh;
   hEvent       = source.hEvent;
   SetAutomaticallyDelete( FALSE );
}

void COverlapped::Copy( const OVERLAPPED * source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::Copy( OVERLAPPED * )" ) );
   Empty();

   // We were passed a pointer, don't trust it

   try
   {
      Internal     = source->Internal;
      InternalHigh = source->InternalHigh;
      Offset       = source->Offset;
      OffsetHigh   = source->OffsetHigh;
      hEvent       = source->hEvent;
      SetAutomaticallyDelete( FALSE );
   }
   catch( ... )
   {
      Empty();
   }
}

void COverlapped::Copy( const OVERLAPPED& source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::Copy( OVERLAPPED& )" ) );
   Empty();

   Copy( &source );
}

void COverlapped::Empty( void )
{
   WFCLTRACEINIT( TEXT( "COverlapped::Empty()" ) );
   Internal     = 0;
   InternalHigh = 0;
   Offset       = 0;
   OffsetHigh   = 0;

   if ( m_AutomaticallyDelete != FALSE && hEvent != NULL )
   {
      ::wfc_close_handle( hEvent );
   }

   hEvent = NULL;
}

void COverlapped::SetAutomaticallyDelete( BOOL automatically_delete )
{
   WFCLTRACEINIT( TEXT( "COverlapped::SetAutomaticallyDelete()" ) );
   m_AutomaticallyDelete = ( automatically_delete == FALSE ) ? FALSE : TRUE;
}

void COverlapped::SetEvent( HANDLE new_event_handle )
{
   if ( m_AutomaticallyDelete != FALSE && hEvent != NULL )
   {
      ::wfc_close_handle( hEvent );
      hEvent = NULL;
   }

   hEvent = new_event_handle;

   // We didn't create this event so don't automatically delete it
   SetAutomaticallyDelete( FALSE );
}

// Operators

COverlapped& COverlapped::operator=( const COverlapped& source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::operator=( COverlapped& )" ) );
   Copy( source );
   return( *this );
}

COverlapped& COverlapped::operator=( const OVERLAPPED& source )
{
   WFCLTRACEINIT( TEXT( "COverlapped::operator=( OVERLAPPED )" ) );
   Copy( source );
   return( *this );
}

// End of source
