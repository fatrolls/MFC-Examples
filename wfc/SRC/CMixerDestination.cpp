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
** $Workfile: CMixerDestination.cpp $
** $Revision: 15 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Construction

CMixerDestination::CMixerDestination()
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::CMixerDestination()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_SourceSelector_p = NULL;
}

CMixerDestination::CMixerDestination( const CMixerDestination& source )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::CMixerDestination( CMixerDestination )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_SourceSelector_p = NULL;
   Copy( source );
}

CMixerDestination::~CMixerDestination()
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::~CMixerDestination()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_SourceSelector_p != NULL )
   {
      try
      {
         delete m_SourceSelector_p;
      }
      catch( ... )
      {
         ;
      }
   }

   m_SourceSelector_p = NULL;
}

// Methods

void CMixerDestination::Copy( const CMixerDestination& source )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   if ( m_SourceSelector_p != NULL )
   {
      try
      {
         delete m_SourceSelector_p;
      }
      catch( ... )
      {
      }

      m_SourceSelector_p = NULL;
   }

   CMixerControlInstance::Copy( source );
}

// Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerDestination::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerDestination at " ) << (VOID *) this << TEXT( "\n{\n" );

   if ( m_SourceSelector_p == NULL )
   {
      dump_context << TEXT( "   m_SourceSelector_p is NULL\n" );
   }
   else
   {
      dump_context << TEXT( "   m_SourceSelector_p is " );
      m_SourceSelector_p->Dump( dump_context );
   }

   CMixerControlInstance::Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CMixerDestination::GetSource( const DWORD type_of_source, CMixerSource& source )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::GetSource()" ) );

   BOOL return_value = FALSE;

   DWORD source_number = 0;

   CMixerLine line;

   while( source_number < m_MixerLine.NumberOfConnections )
   {
      if ( m_Mixer.GetByConnection( m_MixerLine.DestinationNumber, source_number, line ) != FALSE )
      {
         if ( line.Component == type_of_source )
         {
            WFCTRACE( TEXT( "type of source found" ) );
            source.SetLine( line );
            source.Open( m_Mixer.GetDeviceID(), m_WhatToNotify, m_WhoToNotify, m_NotifyData );
            return( TRUE );
         }
      }

      source_number++;
   }

   return( return_value );
}

BOOL CMixerDestination::IsSourceSelected( const DWORD source )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::IsSourceSelected()" ) );
   ASSERT( m_SourceSelector_p != NULL );

   BOOL return_value = FALSE;

   if ( m_SourceSelector_p != NULL )
   {
      return_value = m_SourceSelector_p->IsSelected( source );
   }
   else
   {
      WFCTRACE( TEXT( "m_SourceSelector_p is NULL" ) );
   }

   return( return_value );
}

BOOL CMixerDestination::Open( UINT device_number, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::Open()" ) );

   BOOL return_value = FALSE;

   m_WhatToNotify = what_to_notify;
   m_WhoToNotify  = who_to_notify;
   m_NotifyData   = notify_data;

   return_value = CMixerControlInstance::Open( device_number, what_to_notify, who_to_notify, notify_data );

   if ( return_value == FALSE )
   {
      return( FALSE );
   }

   return( return_value );
}

BOOL CMixerDestination::SelectSource( const DWORD source, BOOL selection )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::SelectSource()" ) );
   ASSERT( m_SourceSelector_p != NULL );

   BOOL return_value = FALSE;

   if ( m_SourceSelector_p != NULL )
   {
      return_value = m_SourceSelector_p->Select( source, selection );
   }

   return( return_value );
}

BOOL CMixerDestination::UnselectSource( const DWORD source )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::UnselectSource()" ) );
   ASSERT( m_SourceSelector_p != NULL );

   BOOL return_value = FALSE;

   if ( m_SourceSelector_p != NULL )
   {
      return_value = m_SourceSelector_p->Unselect( source );
   }

   return( return_value );
}

CMixerDestination& CMixerDestination::operator = ( const CMixerDestination& source )
{
   WFCLTRACEINIT( TEXT( "CMixerDestination::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
