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
** $Workfile: CMixerSwitchControl.cpp $
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

CMixerSwitchControl::CMixerSwitchControl()
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::CMixerSwitchControl()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Array.Add( &m_Switch );
}

CMixerSwitchControl::CMixerSwitchControl( const CMixerSwitchControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::CMixerSwitchControl( CMixerSwitchControl )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Array.Add( &m_Switch );
   Copy( source );
}

CMixerSwitchControl::~CMixerSwitchControl()
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::~CMixerSwitchControl()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Array.RemoveAll();
}

// Methods

void CMixerSwitchControl::Copy( const CMixerSwitchControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::Copy( CMixerSwitchControl )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Open( source.m_Mixer.GetDeviceID(), source.m_WhatToNotify, source.m_WhoToNotify, source.m_NotifyData );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerSwitchControl::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerSwitchControl at " ) << (VOID *) this << TEXT( "\n{\n" );
   CMixerControlInstance::Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CMixerSwitchControl::GetState( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::GetState()" ) );

   BOOL return_value = FALSE;

   return_value = m_GetAll();

   if ( return_value != FALSE )
   {
      return( ( ( m_Switch.Parameter1 == 0 ) ? FALSE : TRUE ) );
   }

   return( return_value );
}

BOOL CMixerSwitchControl::m_GetAll( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::m_GetAll()" ) );

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

            m_Switch.Copy( *data_p );
         }

         delete data_p;

         array.SetAt( loop_index, NULL );
      }

      loop_index++;
   }

   array.RemoveAll();

   return( return_value );
}

BOOL CMixerSwitchControl::SetState( const BOOL turn_on )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::SetState()" ) );

   BOOL return_value = FALSE;

   // Set left channel level

   m_Switch.Parameter1 = turn_on;

   return_value = m_Mixer.SetControlDetails( m_MixerLine, m_MixerControl, m_Array );

   if ( return_value != FALSE )
   {
      m_GetAll();
   }

   return( return_value );
}

BOOL CMixerSwitchControl::TurnOff( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::TurnOff()" ) );

   BOOL return_value = FALSE;

   return_value = SetState( FALSE );

   return( return_value );
}

BOOL CMixerSwitchControl::TurnOn( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::TurnOn()" ) );

   BOOL return_value = FALSE;

   return_value = SetState( TRUE );

   return( return_value );
}

CMixerSwitchControl& CMixerSwitchControl::operator=( const CMixerSwitchControl& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSwitchControl::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
