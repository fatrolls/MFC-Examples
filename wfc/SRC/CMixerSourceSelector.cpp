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
** $Workfile: CMixerSourceSelector.cpp $
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

CMixerSourceSelector::CMixerSourceSelector( const CMixerSourceSelector& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::CMixerSourceSelector( CMixerSourceSelector )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CMixerSourceSelector::CMixerSourceSelector( const CMixerLine& destination, const CMixerControl& control )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::CMixerSourceSelector( CMixerLine, CMixerControl )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_MixerControl.Type != CMixerControl::Mixer )
   {
      WFCTRACE( TEXT( "m_MixerControl is not a mixer." ) );
      m_MixerLine.Empty();
   }

   SetLine( destination );
   SetControl( control );
}

CMixerSourceSelector::~CMixerSourceSelector()
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::~CMixerSourceSelector()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Close();

   int index = 0;

   while( index < m_Settings.GetSize() )
   {
      delete m_Settings.GetAt( index );
      index++;
   }

   m_Settings.RemoveAll();
}

// Methods

void CMixerSourceSelector::Copy( const CMixerSourceSelector& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::Copy()" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   m_MixerLine.Copy( source.m_MixerLine );
   m_MixerControl.Copy( source.m_MixerControl );

   if ( m_MixerControl.Type != CMixerControl::Mixer )
   {
      WFCTRACE( TEXT( "m_MixerControl is not a mixer" ) );
      m_MixerControl.Empty();
   }

   Open( source.m_Mixer.GetDeviceID(), source.m_WhatToNotify, source.m_WhoToNotify, source.m_NotifyData );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixerSourceSelector::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMixerSourceSelector at " ) << (VOID *) this << TEXT( "\n{\n" );
   CMixerControlInstance::Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

DWORD CMixerSourceSelector::GetSource( void ) const
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::GetSource()" ) );
   return( m_MixerLine.Component );
}

BOOL CMixerSourceSelector::IsSelected( const DWORD source )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::IsSelected()" ) );

   BOOL return_value = FALSE;

   return_value = m_GetSettings();

   int index = 0;

   CMixerControlDetailsData * data_p = NULL;

   while( index < m_Settings.GetSize() )
   {
      data_p = (CMixerControlDetailsData *) m_Settings.GetAt( index );

      if ( data_p != NULL )
      {
         if ( data_p->Parameter2 == source )
         {
            return_value = ( ( data_p->Parameter1 == FALSE ) ? FALSE : TRUE );
         }
      }

      index++;
   }

   return( return_value );
}

BOOL CMixerSourceSelector::m_GetSettings( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::m_GetSettings()" ) );

   BOOL return_value = FALSE;

   CPtrArray array;

   return_value = m_Mixer.GetControlDetails( m_MixerLine, m_MixerControl, array );

   if ( return_value != FALSE )
   {
      int loop_index = 0;

      CMixerControlDetailsData * data_p    = NULL;
      CMixerControlDetailsData * setting_p = NULL;

      while( loop_index < array.GetSize() )
      {
         data_p = (CMixerControlDetailsData *) array.GetAt( loop_index );

         if ( data_p != NULL )
         {
            if ( loop_index < m_Settings.GetSize() )
            {
               setting_p = (CMixerControlDetailsData *) m_Settings.GetAt( loop_index );

               if  ( setting_p != NULL )
               {
                  setting_p->Parameter1 = data_p->Parameter1;
               }
            }

            delete data_p;
            array.SetAt( loop_index, NULL );
         }

         loop_index++;
      }
   }

   return( return_value );
}

BOOL CMixerSourceSelector::m_SetSettings( void )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::m_SetSettings()" ) );

   BOOL return_value = FALSE;

   return_value = m_Mixer.SetControlDetails( m_MixerLine, m_MixerControl, m_Settings );

   return( return_value );
}

BOOL CMixerSourceSelector::Open( UINT device_number, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::Open()" ) );

   BOOL return_value = FALSE;

   m_WhatToNotify = what_to_notify;
   m_WhoToNotify  = who_to_notify;
   m_NotifyData   = notify_data;

   return_value = CMixerControlInstance::Open( device_number, what_to_notify, who_to_notify, notify_data );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Can't open device" ) );
      return( FALSE );
   }

   CPtrArray array;

   return_value = m_Mixer.GetControlListText( m_MixerLine, m_MixerControl, m_Settings );

   if ( return_value == FALSE )
   {
      Close();
      return( FALSE );
   }

   return_value = m_GetSettings();

   return( return_value );
}

BOOL CMixerSourceSelector::Select( const DWORD source, BOOL selected )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::Select()" ) );
   WFCTRACEVAL( TEXT( "source is " ), source );

   BOOL return_value = FALSE;

   return_value = m_GetSettings();

   BOOL source_was_found = FALSE;

   int index = 0;

   CMixerControlDetailsData * data_p = NULL;

   while( index < m_Settings.GetSize() )
   {
      data_p = (CMixerControlDetailsData *) m_Settings.GetAt( index );

      if ( data_p != NULL )
      {
         WFCTRACEVAL( TEXT( "Comparing to " ), data_p->Parameter2 );

         if ( data_p->Parameter2 == source )
         {
            source_was_found = TRUE;
            data_p->Parameter1 = ( selected == FALSE ) ? FALSE : TRUE;
         }
      }

      index++;
   }

   if ( source_was_found != FALSE )
   {
      return_value = m_SetSettings();
   }
   else
   {
      WFCTRACE( TEXT( "Source was not found" ) );
   }

   return( return_value );
}

BOOL CMixerSourceSelector::Unselect( const DWORD source )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::UnSelect()" ) );

   BOOL return_value = FALSE;

   return_value = Select( source, FALSE );

   return( return_value );
}

CMixerSourceSelector& CMixerSourceSelector::operator=( const CMixerSourceSelector& source )
{
   WFCLTRACEINIT( TEXT( "CMixerSourceSelector::operator=()" ) );
   Copy( source );
   return( *this );
}

// End of source
