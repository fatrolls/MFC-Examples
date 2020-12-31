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
** $Workfile: CMixerSpeakers.cpp $
** $Revision: 16 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Construction

CMixerSpeakers::CMixerSpeakers()
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::CMixerSpeakers()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

CMixerSpeakers::CMixerSpeakers( const CMixerSpeakers& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::CMixerSpeakers()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerSpeakers::~CMixerSpeakers()
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::~CMixerSpeakers()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

// Methods

void CMixerSpeakers::Copy( const CMixerSpeakers& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   m_Volume.Copy( source.m_Volume );
   m_Mute.Copy( source.m_Mute );
   Open( source.m_Mixer.GetDeviceID(), source.m_WhatToNotify, source.m_WhoToNotify, source.m_NotifyData );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerSpeakers::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerSpeakers at " ) << (VOID *) this << TEXT( "\n{\n" );
   CMixerDestination::Dump( dump_context );

   dump_context << TEXT( "   m_Volume is " );
   m_Volume.Dump( dump_context );

   dump_context << TEXT( "   m_Mute is " );
   m_Mute.Dump( dump_context );

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

DWORD CMixerSpeakers::GetMaximumVolume( void )
{
   return( m_Volume.GetMaximum() );
}

DWORD CMixerSpeakers::GetMinimumVolume( void )
{
   return( m_Volume.GetMinimum() );
}

DWORD CMixerSpeakers::GetLeftChannelVolume( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::GetLeftChannelVolume()" ) );

   DWORD volume = 0;

   volume = m_Volume.GetLeftChannelVolume();

   return( volume );
}

DWORD CMixerSpeakers::GetVolume( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::GetVolume()" ) );

   DWORD volume = 0;

   volume = m_Volume.GetVolume();

   return( volume );
}

DWORD CMixerSpeakers::GetRightChannelVolume( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::GetRightChannelVolume()" ) );

   DWORD volume = 0;

   volume = m_Volume.GetRightChannelVolume();

   return( volume );
}

BOOL CMixerSpeakers::IsMuted( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::IsMuted()" ) );

   if ( m_Mute.GetState() != FALSE )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CMixerSpeakers::Mute( const BOOL mute_on )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::Mute()" ) );

   BOOL return_value = FALSE;

   return_value = m_Mute.SetState( mute_on );

   return( return_value );
}

BOOL CMixerSpeakers::Open( UINT device_number, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::Open()" ) );

   BOOL return_value = FALSE;

   m_WhatToNotify = what_to_notify;
   m_WhoToNotify  = who_to_notify;
   m_NotifyData   = notify_data;

   return_value = CMixerDestination::Open( device_number, what_to_notify, who_to_notify, notify_data );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Open failed" ) );
      return( FALSE );
   }

   return_value = m_Mixer.GetByComponent( CMixerLine::destinationSpeakers, m_MixerLine );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Can't find speakers" ) );
      Close();
      return( FALSE );
   }

   CPtrArray array;

   return_value = m_Mixer.GetAllControls( m_MixerLine, array );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "GetAllControls() failed" ) );
      Close();
      return( FALSE );
   }

   BOOL volume_control_was_found = FALSE;
   BOOL mute_control_was_found   = FALSE;

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
            if ( volume_control_was_found == FALSE )
            {
               m_Volume.SetLine( m_MixerLine );
               m_Volume.SetControl( *control_p );
               m_Volume.Open( device_number, what_to_notify, who_to_notify, notify_data );
               volume_control_was_found = TRUE;
            }
            else
            {
               WFCTRACE( TEXT( "More than one volume control was found" ) );
            }
         }

         if ( control_p->Type == CMixerControl::Mute )
         {
            if ( mute_control_was_found == FALSE )
            {
               m_Mute.SetLine( m_MixerLine );
               m_Mute.SetControl( *control_p );
               m_Mute.Open( device_number, what_to_notify, who_to_notify, notify_data );
               mute_control_was_found = TRUE;
            }
            else
            {
               WFCTRACE( TEXT( "More than one volume control was found" ) );
            }
         }

         delete control_p;
         array.SetAt( loop_index, NULL );
      }

      loop_index++;
   }

   array.RemoveAll();

   if ( volume_control_was_found == FALSE )
   {
      WFCTRACE( TEXT( "Can't find volume control" ) );
      Close();
      return( FALSE );
   }

   if ( mute_control_was_found == FALSE )
   {
      WFCTRACE( TEXT( "Can't find mute control" ) );
      Close();
      return( FALSE );
   }

   WFCTRACE( TEXT( "Found the control" ) );

   return( return_value );
}

BOOL CMixerSpeakers::SetLeftChannelVolume( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::SetLeftChannelVolume()" ) );

   BOOL return_value = FALSE;

   return_value = m_Volume.SetLeftChannelVolume( desired_level );

   return( return_value );
}

BOOL CMixerSpeakers::SetVolume( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::SetlVolume()" ) );

   BOOL return_value = FALSE;

   return_value = m_Volume.SetVolume( desired_level );

   return( return_value );
}

BOOL CMixerSpeakers::SetRightChannelVolume( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::SetRightChannelVolume()" ) );

   BOOL return_value = FALSE;

   return_value = m_Volume.SetRightChannelVolume( desired_level );

   return( return_value );
}

BOOL CMixerSpeakers::UnMute( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakerd::UnMute()" ) );

   BOOL return_value = FALSE;

   return_value = m_Mute.TurnOff();

   return( return_value );
}

CMixerSpeakers& CMixerSpeakers::operator=( const CMixerSpeakers& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSpeakers::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
