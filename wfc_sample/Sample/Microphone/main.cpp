#include <wfc.h>
#pragma hdrstop

#pragma comment( lib, "winmm.lib" )

void turn_microphone_off( void )
{
   WFCTRACELEVELON( 31 );
   WFCTRACEINIT( TEXT( "turn_microphone_off()" ) );

   CMixer mixer;

   if ( mixer.Open() == FALSE )
   {
      WFCTRACE( TEXT( "Can't open mixer." ) );
      return;
   }

#if 0

   CMixerControlInstance selector;

   if ( selector.Open() == FALSE )
   {
      WFCTRACE( TEXT( "Can't open instance." ) );
      return;
   }

   selector.Dump( afxDump );

#endif

   CMixerLine microphone;

   if ( mixer.GetByComponent( CMixerLine::destinationSpeakers, microphone ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't get microphone" ) );
      return;
   }

   CPtrArray array;

   if ( mixer.GetAllControls( microphone, array ) == FALSE )
   {
      WFCTRACE( TEXT( "GetAllControls() failed" ) );
      return;
   }

   WFCTRACEVAL( TEXT( "Number of controls is " ), array.GetSize() );

   BOOL volume_control_was_found = FALSE;
   BOOL mute_control_was_found   = FALSE;

   int loop_index = 0;
   
   CMixerControl * control_p = NULL;

   while( loop_index < array.GetSize() )
   {
      control_p = (CMixerControl *) array.GetAt( loop_index );

      if ( control_p != NULL )
      {
         control_p->Dump( afxDump );
#if 0
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
#endif

         delete control_p;
         array.SetAt( loop_index, NULL );
      }

      loop_index++;
   }

   array.RemoveAll();

   Sleep( 500 );
}

void main( void )
{
   turn_microphone_off();
}
