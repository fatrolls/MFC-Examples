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
** $Workfile: CMixerWaveIn.cpp $
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

CMixerWaveIn::CMixerWaveIn()
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::CMixerWaveIn()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

CMixerWaveIn::CMixerWaveIn( const CMixerWaveIn& source )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::CMixerWaveIn()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerWaveIn::~CMixerWaveIn()
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::~CMixerWaveIn()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
}

// Methods

void CMixerWaveIn::Copy( const CMixerWaveIn& source )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   m_RecordingGain.Copy( source.m_RecordingGain );
   Open( source.m_Mixer.GetDeviceID(), source.m_WhatToNotify, source.m_WhoToNotify, source.m_NotifyData );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerWaveIn::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerWaveIn at " ) << (VOID *) this << TEXT( "\n{\n" );
   CMixerControlInstance::Dump( dump_context );
   dump_context << TEXT( "   m_RecordingGain is " );
   m_RecordingGain.Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

DWORD CMixerWaveIn::GetMaximumGain( void ) const
{
   return( m_RecordingGain.GetMaximum() ) ;
}

DWORD CMixerWaveIn::GetMinimumGain( void ) const
{
   return( m_RecordingGain.GetMinimum() );
}

DWORD CMixerWaveIn::GetLeftChannelRecordingGain( void )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::GetLeftChannelRecordingGain()" ) );

   DWORD gain = 0;

   gain = m_RecordingGain.GetLeftChannelVolume();

   return( gain );
}

DWORD CMixerWaveIn::GetRecordingGain( void )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::GetRecordingGain()" ) );

   DWORD gain = 0;

   gain = m_RecordingGain.GetVolume();

   return( gain );
}

DWORD CMixerWaveIn::GetRightChannelRecordingGain( void )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::GetRightChannelRecordingGain()" ) );

   DWORD gain = 0;

   gain = m_RecordingGain.GetRightChannelVolume();

   return( gain );
}

BOOL CMixerWaveIn::Open( UINT device_number, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::Open()" ) );

   BOOL return_value = FALSE;

   m_WhatToNotify = what_to_notify;
   m_WhoToNotify  = who_to_notify;
   m_NotifyData   = notify_data;

   return_value = CMixerDestination::Open( device_number, what_to_notify, who_to_notify, notify_data );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Can't open" ) );
      return( FALSE );
   }

   return_value = m_Mixer.GetByComponent( CMixerLine::destinationWaveIn, m_MixerLine );

   if ( return_value == FALSE )
   {
      Close();
      return( FALSE );
   }

   CPtrArray array;

   return_value = m_Mixer.GetAllControls( m_MixerLine, array );

   if ( return_value == FALSE )
   {
      Close();
      return( FALSE );
   }

   BOOL control_was_found = FALSE;

   int loop_index = 0;

   CMixerControl * control_p = NULL;

   while( loop_index < array.GetSize() )
   {
      control_p = (CMixerControl *) array.GetAt( loop_index );

      if ( control_p != NULL )
      {
         if ( control_p->Type == CMixerControl::Mixer )
         {
            WFCTRACE( TEXT( "Creating m_SourceSelector_p" ) );

            try
            {
               m_SourceSelector_p = new CMixerSourceSelector( m_MixerLine, *control_p );
            }
            catch( ... )
            {
               m_SourceSelector_p = NULL;
            }

            ASSERT( m_SourceSelector_p != NULL );

            if ( m_SourceSelector_p != NULL )
            {
               m_SourceSelector_p->Open( device_number, what_to_notify, who_to_notify, notify_data );
            }
         }

         if ( control_p->Type == CMixerControl::Volume )
         {
            if ( control_was_found == FALSE )
            {
               m_RecordingGain.SetLine( m_MixerLine );
               m_RecordingGain.SetControl( *control_p );
               m_RecordingGain.Open( device_number, what_to_notify, who_to_notify, notify_data );
               control_was_found = TRUE;
            }
         }

         delete control_p;

         array.SetAt( loop_index, NULL );
      }

      loop_index++;
   }

   array.RemoveAll();

   if ( control_was_found == FALSE )
   {
      WFCTRACE( TEXT( "Can't find control" ) );
      Close();
      return( FALSE );
   }

   return( return_value );
}

BOOL CMixerWaveIn::SetLeftChannelRecordingGain( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::SetLeftChannelRecordingGain()" ) );

   BOOL return_value = FALSE;

   return_value = m_RecordingGain.SetLeftChannelVolume( desired_level );

   return( return_value );
}

BOOL CMixerWaveIn::SetRecordingGain( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::SetRecordingGain()" ) );

   BOOL return_value = FALSE;

   return_value = m_RecordingGain.SetVolume( desired_level );

   return( return_value );
}

BOOL CMixerWaveIn::SetRightChannelRecordingGain( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::SetRightChannelRecordingGain()" ) );

   BOOL return_value = FALSE;

   return_value = m_RecordingGain.SetRightChannelVolume( desired_level );

   return( return_value );
}

CMixerWaveIn& CMixerWaveIn::operator=( const CMixerWaveIn& source )
{
   WFCLTRACEINIT( TEXT( "CMixerWaveIn::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
