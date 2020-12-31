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
** $Workfile: CMixerSource.cpp $
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

CMixerSource::CMixerSource()
{
   WFCLTRACEINIT( TEXT( "CMixerSource::CMixerSource()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

CMixerSource::CMixerSource( const CMixerSource& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSource::CMixerSource( CMixerSource )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerSource::~CMixerSource()
{
   WFCLTRACEINIT( TEXT( "CMixerSource::~CMixerSource()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

// Methods

void CMixerSource::Copy( const CMixerSource& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSource::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   CMixerControlInstance::Copy( source );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerSource::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerSource at " ) << (VOID *) this << TEXT( "\n{\n" );
   CMixerControlInstance::Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CMixerSource::GetControl( CMixerVolumeControl& control )
{
   WFCLTRACEINIT( TEXT( "CMixerSource::GetControl()" ) );

   BOOL return_value = FALSE;

   CPtrArray controls_array;

   if ( m_Mixer.GetAllControls( m_MixerLine, controls_array ) != FALSE )
   {
      CMixerControl * control_p = NULL;

      int control_index = 0;

      while( control_index < controls_array.GetSize() )
      {
         control_p = (CMixerControl *) controls_array.GetAt( control_index );

         if ( control_p != NULL )
         {
            if ( control_p->IsFader() )
            {
               WFCTRACE( TEXT( "Setting control" ) );
               return_value = TRUE;
               control.SetLine( m_MixerLine );
               control.SetControl( *control_p );
               control.Open( m_Mixer.GetDeviceID(), m_WhatToNotify, m_WhoToNotify, m_NotifyData );
            }

            delete control_p;
         }

         control_index++;
      }

      controls_array.RemoveAll();
   }
#if defined( _DEBUG )
   else
   {
      CString error_string;
      m_Mixer.GetErrorString( error_string );
      WFCTRACEVAL( TEXT( "GetAllControls() failed with " ), error_string );

   }
#endif // _DEBUG

   return( return_value );
}

BOOL CMixerSource::Open( UINT device_number, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixerSource::Open()" ) );

   BOOL return_value = FALSE;

   m_WhatToNotify = what_to_notify;
   m_WhoToNotify  = who_to_notify;
   m_NotifyData   = notify_data;

   return_value = CMixerControlInstance::Open( device_number, what_to_notify, who_to_notify, notify_data );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Open failed." ) );
      return( FALSE );
   }

   return( TRUE );
}

CMixerSource& CMixerSource::operator=( const CMixerSource& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSource::operator=( CMixerSource )" ) );
   Copy( source );
   return( *this );
}

// End of source
