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
** $Workfile: CMixerVolumeControl.cpp $
** $Revision: 14 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Construction

CMixerVolumeControl::CMixerVolumeControl()
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::CMixerVolumeControl()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Channels.Add( &m_LeftChannel );
   m_Channels.Add( &m_RightChannel );
}

CMixerVolumeControl::CMixerVolumeControl( const CMixerVolumeControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::CMixerVolumeControl( CMixerVolumeControl )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Channels.Add( &m_LeftChannel );
   m_Channels.Add( &m_RightChannel );
   Copy( source );
}

CMixerVolumeControl::~CMixerVolumeControl()
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::~CMixerVolumeControl()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Channels.RemoveAll();
}

// Methods

void CMixerVolumeControl::Copy( const CMixerVolumeControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Open( source.m_Mixer.GetDeviceID(), source.m_WhatToNotify, source.m_WhoToNotify, source.m_NotifyData );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerVolumeControl::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerVolumeControl at " ) << (VOID *) this << TEXT( "\n{\n" );
   CMixerControlInstance::Dump( dump_context );
   dump_context << TEXT( "   m_LeftChannel is " );
   m_LeftChannel.Dump( dump_context );
   dump_context << TEXT( "   m_RightChannel is " );
   m_RightChannel.Dump( dump_context );
   dump_context << TEXT( "   m_BothChannels is " );
   m_BothChannels.Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

DWORD CMixerVolumeControl::GetMaximum( void ) const
{
   return( m_MixerControl.Maximum );
}

DWORD CMixerVolumeControl::GetMinimum( void ) const
{
   return( m_MixerControl.Minimum );
}

DWORD CMixerVolumeControl::GetLeftChannelVolume( void )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::GetLeftChannelVolume()" ) );

   DWORD gain = 0;

   if ( m_GetAll() != FALSE )
   {
      gain = m_LeftChannel.Parameter1;
   }

   return( gain );
}

DWORD CMixerVolumeControl::GetVolume( void )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::GetVolume()" ) );

   DWORD gain = 0;

   if ( m_GetAll() != FALSE )
   {
      gain = m_BothChannels.Parameter1;
   }

   return( gain );
}

DWORD CMixerVolumeControl::GetRightChannelVolume( void )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::GetRightChannelVolume()" ) );

   DWORD gain = 0;

   if ( m_GetAll() != FALSE )
   {
      gain = m_RightChannel.Parameter1;
   }

   return( gain );
}

BOOL CMixerVolumeControl::m_GetAll( void )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::m_GetAll()" ) );

   BOOL return_value = FALSE;

   CPtrArray array;

   return_value = m_Mixer.GetControlDetails( m_MixerLine, m_MixerControl, array );

   if ( return_value == FALSE )
   {
      Close();
      return( FALSE );
   }

   int loop_index = 0;

   CMixerControlDetailsData * data_p = NULL;

   while( loop_index < array.GetSize() )
   {
      data_p = (CMixerControlDetailsData *) array.GetAt( loop_index );

      if ( data_p != NULL )
      {
         if ( loop_index == 0 )
         {
            // Left channel

            m_LeftChannel.Copy( *data_p );
         }

         if ( loop_index == 1 )
         {
            // Right channel

            m_RightChannel.Copy( *data_p );
         }

         delete data_p;
         array.SetAt( loop_index, NULL );
      }

      loop_index++;
   }

   array.RemoveAll();

   if ( m_LeftChannel.Parameter1 > m_RightChannel.Parameter1 )
   {
      m_BothChannels.Parameter1 = m_LeftChannel.Parameter1;
   }
   else
   {
      m_BothChannels.Parameter1 = m_RightChannel.Parameter1;
   }

   return( return_value );
}

BOOL CMixerVolumeControl::SetLeftChannelVolume( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::SetLeftChannelVolume()" ) );

   BOOL return_value = FALSE;

   DWORD new_level = desired_level;

   if ( new_level < m_MixerControl.Minimum )
   {
      new_level = m_MixerControl.Minimum;
   }

   if ( new_level > m_MixerControl.Maximum )
   {
      new_level = m_MixerControl.Maximum;
   }

   m_GetAll();

   m_LeftChannel.Parameter1 = new_level;

   return_value = m_Mixer.SetControlDetails( m_MixerLine, m_MixerControl, m_Channels );

   if ( return_value != FALSE )
   {
      m_GetAll();
   }

   return( return_value );
}

BOOL CMixerVolumeControl::SetVolume( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::SetVolume()" ) );

   BOOL return_value = FALSE;

   DWORD new_level = desired_level;

   if ( new_level < m_MixerControl.Minimum )
   {
      new_level = m_MixerControl.Minimum;
   }

   if ( new_level > m_MixerControl.Maximum )
   {
      new_level = m_MixerControl.Maximum;
   }

   m_LeftChannel.Parameter1  = new_level;
   m_RightChannel.Parameter1 = new_level;

   return_value = m_Mixer.SetControlDetails( m_MixerLine, m_MixerControl, m_Channels );

   if ( return_value != FALSE )
   {
      m_GetAll();
   }

   return( return_value );
}

BOOL CMixerVolumeControl::SetRightChannelVolume( const DWORD desired_level )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::SetRightChannelVolume()" ) );

   BOOL return_value = FALSE;

   DWORD new_level = desired_level;

   if ( new_level < m_MixerControl.Minimum )
   {
      new_level = m_MixerControl.Minimum;
   }

   if ( new_level > m_MixerControl.Maximum )
   {
      new_level = m_MixerControl.Maximum;
   }

   m_GetAll();

   m_RightChannel.Parameter1 = new_level;

   return_value = m_Mixer.SetControlDetails( m_MixerLine, m_MixerControl, m_Channels );

   if ( return_value != FALSE )
   {
      m_GetAll();
   }

   return( return_value );
}

CMixerVolumeControl& CMixerVolumeControl::operator=( const CMixerVolumeControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerVolumeControl::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
