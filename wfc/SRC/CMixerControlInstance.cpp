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
** $Workfile: CMixerControlInstance.cpp $
** $Revision: 17 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CMixerControlInstance::CMixerControlInstance()
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::CMixerControlInstance()" ) );

   m_WhatToNotify = 0;
   m_WhoToNotify  = 0;
   m_NotifyData   = 0;
}

CMixerControlInstance::CMixerControlInstance( const CMixerControlInstance& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::CMixerControlInstance( CMixerControlInstance )" ) );

   m_WhatToNotify = 0;
   m_WhoToNotify  = 0;
   m_NotifyData   = 0;

   Copy( source );
}

CMixerControlInstance::~CMixerControlInstance()
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::~CMixerControlInstance()" ) );

   m_WhatToNotify = 0;
   m_WhoToNotify  = 0;
   m_NotifyData   = 0;
}

void CMixerControlInstance::Copy( const CMixerControlInstance& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   m_Mixer.Open( source.m_Mixer.GetDeviceID(), source.m_WhatToNotify, source.m_WhoToNotify, source.m_NotifyData );
   m_MixerLine.Copy( source.m_MixerLine );
   m_MixerControl.Copy( source.m_MixerControl );
}

void CMixerControlInstance::Close( void )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::Close()" ) );
   m_Mixer.Close();
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerControlInstance::Dump( CDumpContext& dump_context ) const
{
   CString temp_string;

   dump_context << TEXT( "a CMixerControlInstance at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_Mixer is " );
   m_Mixer.Dump( dump_context );
   dump_context << TEXT( "   m_MixerLine is " );
   m_MixerLine.Dump( dump_context );
   dump_context << TEXT( "   m_MixerControl is " );
   m_MixerControl.Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CMixerControlInstance::Open( UINT device_number, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::Open()" ) );

   BOOL return_value = FALSE;

   m_WhatToNotify = what_to_notify;
   m_WhoToNotify  = who_to_notify;
   m_NotifyData   = notify_data;

   return_value = m_Mixer.Open( device_number, what_to_notify, who_to_notify, notify_data );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Failed." ) );
      return( FALSE );
   }

   return( TRUE );
}

void CMixerControlInstance::SetLine( const CMixerLine& line )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::SetLine()" ) );
   m_MixerLine.Copy( line );
}

void CMixerControlInstance::SetControl( const CMixerControl& control )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::SetControl()" ) );
   m_MixerControl.Copy( control );
}

CMixerControlInstance& CMixerControlInstance::operator=( const CMixerControlInstance& source )
{
   WFCLTRACEINIT( TEXT( "CMixerControlInstance::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
