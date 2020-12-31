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
** $Workfile: CMixer.cpp $
** $Revision: 21 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined( _WFC_DEBUG_MIXER_GET_CONTROL_DETAILS )

static void dump_mixer_control_details( LPCTSTR file, UINT line, LPCTSTR get_or_set, HMIXEROBJ mixer_object, MIXERCONTROLDETAILS * details_p, DWORD option )
{
   TCHAR debug_string[ 513 ];

   if ( details_p == NULL )
   {
      OutputDebugString( TEXT( "details_p is NULL!\n" ) );
   }

   _stprintf( debug_string, TEXT( "in %s at line %d, %s( %lu, %p, %lX )\n" ), file, line, get_or_set, (DWORD) mixer_object, details_p, option );
   OutputDebugString( debug_string );
   _stprintf( debug_string, TEXT( "at address %p\n" ), (VOID *) details_p );
   OutputDebugString( debug_string );

   if ( details_p == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      _stprintf( debug_string, TEXT( "MIXERCONTROLDETAILS.cbStruct       = %lu\n" ), details_p->cbStruct );
      OutputDebugString( debug_string );
      _stprintf( debug_string, TEXT( "MIXERCONTROLDETAILS.dwControlID    = %lu\n" ), details_p->dwControlID );
      OutputDebugString( debug_string );
      _stprintf( debug_string, TEXT( "MIXERCONTROLDETAILS.cChannels      = %lu\n" ), details_p->cChannels );
      OutputDebugString( debug_string );
      _stprintf( debug_string, TEXT( "MIXERCONTROLDETAILS.cMultipleItems = %lu\n" ), details_p->cMultipleItems );
      OutputDebugString( debug_string );
      _stprintf( debug_string, TEXT( "MIXERCONTROLDETAILS.cbDetails      = %lu\n" ), details_p->cbDetails );
      OutputDebugString( debug_string );
   }
   catch( ... )
   {
   }
}

#endif // _WFC_DEBUG_MIXER_GET_CONTROL_DETAILS

// Construction

CMixer::CMixer()
{
   WFCLTRACEINIT( TEXT( "CMixer::CMixer()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Handle = NULL;
}

CMixer::~CMixer()
{
   WFCLTRACEINIT( TEXT( "CMixer::CMixer()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Handle = NULL;
}

// Methods

void CMixer::Close( void )
{
   WFCLTRACEINIT( TEXT( "CMixer::Close()" ) );

   m_ErrorCode = ::mixerClose( m_Handle );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      WFCTRACE( TEXT( "Close Failed" ) );
   }

   m_Handle = NULL;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMixer::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CMixer at " ) << (VOID *) this << TEXT( "\n" );
}

#endif // _DEBUG

BOOL CMixer::Get( CMixerCapabilities& capabilities )
{
   WFCLTRACEINIT( TEXT( "CMixer::Get()" ) );

   MIXERCAPS mixer_capabilities;

   ::ZeroMemory( &mixer_capabilities, sizeof( mixer_capabilities ) );

   m_ErrorCode = ::mixerGetDevCaps( m_DeviceID, &mixer_capabilities, sizeof( mixer_capabilities ) );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      capabilities.Empty();
      return( FALSE );
   }

   capabilities.Copy( mixer_capabilities );

   return( TRUE );
}

BOOL CMixer::GetAllControls( const CMixerLine& line, CPtrArray& array )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetAllControls()" ) );

   array.RemoveAll();

   MIXERLINECONTROLS line_controls;

   ::ZeroMemory( &line_controls, sizeof( line_controls ) );

   line_controls.cbStruct = sizeof( line_controls );

   MIXERCONTROL *control_array = NULL;

   DWORD size_of_buffer = 0;

   size_of_buffer = line.NumberOfControls * sizeof( MIXERCONTROL );

   try
   {
      control_array = new MIXERCONTROL[ line.NumberOfControls ];
   }
   catch( ... )
   {
      control_array = NULL;
   }

   ASSERT( control_array != NULL );

   // Choose to live
   if ( control_array == NULL )
   {
      m_ErrorCode = MMSYSERR_NOMEM;
      return( FALSE );
   }

   ::ZeroMemory( control_array, size_of_buffer );

   // Initialize the structures

   DWORD loop_index = 0;

   while( loop_index < line.NumberOfControls )
   {
      control_array[ loop_index ].cbStruct = sizeof( MIXERCONTROL );
      loop_index++;
   }

   line_controls.dwLineID  = line.ID;
   line_controls.cControls = line.NumberOfControls;
   line_controls.cbmxctrl  = sizeof( MIXERCONTROL );
   line_controls.pamxctrl  = control_array;

   DWORD flags = 0;

   flags = notifyMixerNumber | MIXER_GETLINECONTROLSF_ALL;

   BOOL return_value = TRUE;

   m_ErrorCode = ::mixerGetLineControls( (HMIXEROBJ) m_DeviceID, &line_controls, flags );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return_value = FALSE;
   }
   else
   {
      loop_index = 0;

      CMixerControl * control_p = NULL;

      while( loop_index < line.NumberOfControls )
      {
         try
         {
            control_p = new CMixerControl;
         }
         catch( ... )
         {
            control_p = NULL;
         }

         ASSERT( control_p != NULL );

         // Choose to live
         if ( control_p != NULL )
         {
            control_p->Copy( control_array[ loop_index ] );
            array.Add( control_p );
         }
         else
         {
            m_ErrorCode = MMSYSERR_NOMEM;
         }

         loop_index++;
      }

      return_value = TRUE;
   }

   ::ZeroMemory( control_array, size_of_buffer );

   delete [] control_array;

   return( return_value );
}

BOOL CMixer::GetByComponent( const DWORD component, CMixerLine& line )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetByComponent()" ) );

   MIXERLINE mixer_line;

   ::ZeroMemory( &mixer_line, sizeof( mixer_line ) );

   mixer_line.cbStruct        = sizeof( mixer_line );
   mixer_line.dwComponentType = component;

   DWORD flags = 0;

   flags = notifyMixerNumber | MIXER_GETLINEINFOF_COMPONENTTYPE;

   m_ErrorCode = ::mixerGetLineInfo( (HMIXEROBJ) m_DeviceID, &mixer_line, flags );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return( FALSE );
   }

   line.Copy( mixer_line );

   return( TRUE );
}

BOOL CMixer::GetByDestination( const DWORD destination, CMixerLine& line )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetByDestination()" ) );

   MIXERLINE mixer_line;

   ::ZeroMemory( &mixer_line, sizeof( mixer_line ) );

   mixer_line.cbStruct      = sizeof( mixer_line );
   mixer_line.dwDestination = destination;

   DWORD flags = 0;

   flags = notifyMixerNumber | MIXER_GETLINEINFOF_DESTINATION;

   m_ErrorCode = ::mixerGetLineInfo( (HMIXEROBJ) m_DeviceID, &mixer_line, flags );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return( FALSE );
   }

   line.Copy( mixer_line );

   return( TRUE );
}

BOOL CMixer::GetByID( const DWORD id, CMixerLine& line )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetByID()" ) );

   MIXERLINE mixer_line;

   ::ZeroMemory( &mixer_line, sizeof( mixer_line ) );

   mixer_line.cbStruct = sizeof( mixer_line );
   mixer_line.dwLineID = id;

   DWORD flags = 0;

   flags = notifyMixerNumber | MIXER_GETLINEINFOF_LINEID;

   m_ErrorCode = ::mixerGetLineInfo( (HMIXEROBJ) m_DeviceID, &mixer_line, flags );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return( FALSE );
   }

   line.Copy( mixer_line );

   return( TRUE );
}

BOOL CMixer::GetByConnection( const DWORD destination, const DWORD source, CMixerLine& line )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetByConnection()" ) );

   MIXERLINE mixer_line;

   ::ZeroMemory( &mixer_line, sizeof( mixer_line ) );

   mixer_line.cbStruct      = sizeof( mixer_line );
   mixer_line.dwDestination = destination;
   mixer_line.dwSource      = source;

   DWORD flags = 0;

   flags = notifyMixerNumber | MIXER_GETLINEINFOF_SOURCE;

   m_ErrorCode = ::mixerGetLineInfo( (HMIXEROBJ) m_DeviceID, &mixer_line, flags );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return( FALSE );
   }

   line.Copy( mixer_line );

   return( TRUE );
}

BOOL CMixer::GetControlDetails( const CMixerLine& line, const CMixerControl& control, CPtrArray& array )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetControlDetails()" ) );

   array.RemoveAll();

   MIXERCONTROLDETAILS control_details;

   ::ZeroMemory( &control_details, sizeof( control_details ) );

   DWORD type_of_details = 0;

   type_of_details = control.GetUnits();

   DWORD size_of_element = 0;

   if ( type_of_details == CMixerControl::unitsBoolean )
   {
      size_of_element = sizeof( MIXERCONTROLDETAILS_BOOLEAN );
   }
   else if ( type_of_details == CMixerControl::unitsSigned   ||
             type_of_details == CMixerControl::unitsDecibels )
   {
      size_of_element = sizeof( MIXERCONTROLDETAILS_SIGNED );
   }
   else if ( type_of_details == CMixerControl::unitsUnsigned ||
             type_of_details == CMixerControl::unitsPercent  )
   {
      size_of_element = sizeof( MIXERCONTROLDETAILS_UNSIGNED );
   }
   else
   {
      WFCTRACEVAL( TEXT( "Unknown type of details to get " ), type_of_details );
      ASSERT( FALSE );
      return( FALSE );
   }

   DWORD number_of_items_per_channel = 0;
   DWORD number_of_channels          = line.NumberOfChannels;

   if ( control.IsUniform() )
   {
      number_of_items_per_channel = 1;
      number_of_channels          = 1;

      if ( type_of_details == CMixerControl::unitsBoolean )
      {
         number_of_items_per_channel = 0;
      }
   }
   else
   {
      number_of_items_per_channel = control.NumberOfItemsPerChannel;
   }

   if ( control.IsMultiple() )
   {
      number_of_items_per_channel = control.NumberOfItemsPerChannel;
   }

   DWORD number_of_elements = 0;

   number_of_elements = number_of_channels * ( ( number_of_items_per_channel == 0 ) ? 1 : number_of_items_per_channel );

   WFCTRACEVAL( TEXT( "Number of elements is " ), number_of_elements );

   DWORD buffer_size = 0;

   buffer_size = number_of_elements * size_of_element;

   BYTE * memory_buffer = NULL;

   try
   {
      memory_buffer = new BYTE[ buffer_size ];
   }
   catch( ... )
   {
      memory_buffer = NULL;
   }

   ASSERT( memory_buffer != NULL );

   // Choose to live

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = MMSYSERR_NOMEM;
      return( FALSE );
   }

   control_details.cbStruct       = sizeof( control_details );
   control_details.dwControlID    = control.ID;
   control_details.cChannels      = number_of_channels;
   control_details.cMultipleItems = number_of_items_per_channel;
   control_details.cbDetails      = size_of_element;
   control_details.paDetails      = memory_buffer;

   DWORD flags = 0;

   flags = MIXER_GETCONTROLDETAILSF_VALUE;

#if defined( _WFC_DEBUG_MIXER_GET_CONTROL_DETAILS )

   dump_mixer_control_details( THIS_FILE, __LINE__, TEXT( "mixerGetControlDetails" ), (HMIXEROBJ) m_Handle, &control_details, flags );

#endif // _WFC_DEBUG_MIXER_GET_CONTROL_DETAILS

   m_ErrorCode = ::mixerGetControlDetails( (HMIXEROBJ) m_Handle, &control_details, flags );

   BOOL return_value = FALSE;

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      WFCTRACE( TEXT( "mixerGetControlDetails() failed" ) );
      return_value = FALSE;
   }
   else
   {
      CMixerControlDetailsData * data_p = NULL;

      DWORD index = 0;

      while( index < number_of_elements )
      {
         try
         {
            data_p = new CMixerControlDetailsData;
         }
         catch( ... )
         {
            data_p = NULL;
         }

         ASSERT( data_p != NULL );

         // Choose to live
         if ( data_p != NULL )
         {
            if ( type_of_details == CMixerControl::unitsBoolean )
            {
               MIXERCONTROLDETAILS_BOOLEAN *array = NULL;

               array = (MIXERCONTROLDETAILS_BOOLEAN *) memory_buffer;

               ASSERT( (DWORD) array == (DWORD) memory_buffer );

               data_p->Copy( array[ index ] );
            }
            else if ( type_of_details == CMixerControl::unitsSigned   ||
                      type_of_details == CMixerControl::unitsDecibels )
            {
               MIXERCONTROLDETAILS_SIGNED *array = NULL;

               array = (MIXERCONTROLDETAILS_SIGNED *) memory_buffer;

               ASSERT( (DWORD) array == (DWORD) memory_buffer );

               data_p->Copy( array[ index ] );
            }
            else if ( type_of_details == CMixerControl::unitsUnsigned ||
                      type_of_details == CMixerControl::unitsPercent  )
            {
               MIXERCONTROLDETAILS_UNSIGNED *array = NULL;

               array = (MIXERCONTROLDETAILS_UNSIGNED *) memory_buffer;

               ASSERT( (DWORD) array == (DWORD) memory_buffer );

               data_p->Copy( array[ index ] );
            }
            else
            {
               // We should never get here
               ASSERT( FALSE );
               delete data_p; // prevent a memory leak
               delete [] memory_buffer;
               return( FALSE );
            }

            array.Add( data_p );
         }

         index++;
      }

      return_value = TRUE;
   }

   ::ZeroMemory( memory_buffer, buffer_size );
   delete [] memory_buffer;

   return( return_value );
}

BOOL CMixer::GetControlListText( const CMixerLine& line, const CMixerControl& control, CPtrArray& array )
{
   WFCLTRACEINIT( TEXT( "CMixer::GetControlListText()" ) );

   array.RemoveAll();

   if ( control.IsList() == FALSE )
   {
      WFCTRACE( TEXT( "This ain't no list" ) );
      return( FALSE );
   }

   MIXERCONTROLDETAILS control_details;

   ::ZeroMemory( &control_details, sizeof( control_details ) );

   MIXERCONTROLDETAILS_LISTTEXT * details_array = NULL;

   DWORD size_of_element = 0;

   size_of_element = sizeof( MIXERCONTROLDETAILS_LISTTEXT );

   DWORD number_of_items_per_channel = 0;

   if ( control.IsUniform() != FALSE )
   {
      number_of_items_per_channel = 1;
   }
   else
   {
      number_of_items_per_channel = control.NumberOfItemsPerChannel;
   }

   if ( control.IsMultiple() != FALSE )
   {
      number_of_items_per_channel = control.NumberOfItemsPerChannel;
   }

   DWORD number_of_elements  = 0;
   DWORD number_of_channels = line.NumberOfChannels;

   // This may be right for Lists but wrong with others...

   if ( control.IsUniform() != FALSE )
   {
      number_of_channels = 1;
   }

   number_of_elements = number_of_channels * number_of_items_per_channel;

   WFCTRACEVAL( TEXT( "Number of elements is " ), number_of_elements );

   try
   {
      details_array = new MIXERCONTROLDETAILS_LISTTEXT[ number_of_elements ];
   }
   catch( ... )
   {
      details_array = NULL;
   }

   ASSERT( details_array != NULL );

   // Choose to live

   if ( details_array == NULL )
   {
      m_ErrorCode = MMSYSERR_NOMEM;
      return( FALSE );
   }

   control_details.cbStruct       = sizeof( control_details );
   control_details.dwControlID    = control.ID;
   control_details.cChannels      = number_of_channels;
   control_details.cMultipleItems = number_of_items_per_channel;
   control_details.cbDetails      = size_of_element;
   control_details.paDetails      = details_array;

   DWORD flags = 0;

   flags = notifyMixerNumber | MIXER_GETCONTROLDETAILSF_LISTTEXT;

#if defined( _WFC_DEBUG_MIXER_GET_CONTROL_DETAILS )

   dump_mixer_control_details( THIS_FILE, __LINE__, TEXT( "mixerGetControlDetails" ), (HMIXEROBJ) m_Handle, &control_details, flags );

#endif // _WFC_DEBUG_MIXER_GET_CONTROL_DETAILS

   m_ErrorCode = ::mixerGetControlDetails( (HMIXEROBJ) m_DeviceID, &control_details, flags );

   BOOL return_value = FALSE;

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return_value = FALSE;
   }
   else
   {
      CMixerControlDetailsData * data_p = NULL;

      DWORD index = 0;

      while( index < number_of_elements )
      {
         try
         {
            data_p = new CMixerControlDetailsData;
         }
         catch( ... )
         {
            data_p = NULL;
         }

         ASSERT( data_p != NULL );

         // Choose to live
         if ( data_p != NULL )
         {
            data_p->Copy( details_array[ index ] );
            array.Add( data_p );
         }

         index++;
      }

      return_value = TRUE;
   }

   ::ZeroMemory( details_array, number_of_elements * size_of_element );
   delete [] details_array;

   return( return_value );
}

UINT CMixer::GetDeviceID( void ) const
{
   return( m_DeviceID );
}

DWORD CMixer::GetErrorCode( void ) const
{
   return( m_ErrorCode );
}

void CMixer::GetErrorString( CString& error_string ) const
{
   WFCLTRACEINIT( TEXT( "CMixer::GetErrorString()" ) );

   switch( m_ErrorCode )
   {
      case MMSYSERR_NOERROR:

         error_string = TEXT( "No Error" );
         break;

      case MMSYSERR_ERROR:

         error_string = TEXT( "Unspecified Error" );
         break;

      case MMSYSERR_BADDEVICEID:

         error_string = TEXT( "Device ID out of range" );
         break;

      case MMSYSERR_NOTENABLED:

         error_string = TEXT( "Driver failed enable" );
         break;

      case MMSYSERR_ALLOCATED:

         error_string = TEXT( "Device already allocated" );
         break;

      case MMSYSERR_INVALHANDLE:

         error_string = TEXT( "Device handle is invalid" );
         break;

      case MMSYSERR_NODRIVER:

         error_string = TEXT( "No device driver present" );
         break;

      case MMSYSERR_NOMEM:

         error_string = TEXT( "Memory allocation error" );
         break;

      case MMSYSERR_NOTSUPPORTED:

         error_string = TEXT( "Function is not supported" );
         break;

      case MMSYSERR_BADERRNUM:

         error_string = TEXT( "Error value out of range" );
         break;

      case MMSYSERR_INVALFLAG:

         error_string = TEXT( "Invalid flag passed" );
         break;

      case MMSYSERR_INVALPARAM:

         error_string = TEXT( "Invalid parameter passed" );
         break;

      case MMSYSERR_HANDLEBUSY:

         error_string = TEXT( "Handle being used simultaneously on another thread (or callback)" );
         break;

      case MMSYSERR_INVALIDALIAS:

         error_string = TEXT( "Specified alias not found" );
         break;

      case MMSYSERR_BADDB:

         error_string = TEXT( "Bad registry database" );
         break;

      case MMSYSERR_KEYNOTFOUND:

         error_string = TEXT( "Registry key not found" );
         break;

      case MMSYSERR_READERROR:

         error_string = TEXT( "Registry read error" );
         break;

      case MMSYSERR_WRITEERROR:

         error_string = TEXT( "Registry write error" );
         break;

      case MMSYSERR_DELETEERROR:

         error_string = TEXT( "Registry delete error" );
         break;

      case MMSYSERR_VALNOTFOUND:

         error_string = TEXT( "Registry value not found" );
         break;

      case MMSYSERR_NODRIVERCB:

         error_string = TEXT( "Driver does not call DriverCallback" );
         break;

      case WAVERR_BADFORMAT:

         error_string = TEXT( "Unsupported Wave format" );
         break;

      case WAVERR_STILLPLAYING:

         error_string = TEXT( "Wave is still playing" );
         break;

      case WAVERR_UNPREPARED:

         error_string = TEXT( "Wave header not prepared" );
         break;

      case WAVERR_SYNC:

         error_string = TEXT( "Wave device is synchronous" );
         break;

      case MIDIERR_UNPREPARED:

         error_string = TEXT( "MIDI header not prepared" );
         break;

      case MIDIERR_STILLPLAYING:

         error_string = TEXT( "MIDI is still playing" );
         break;

      case MIDIERR_NOMAP:

         error_string = TEXT( "MIDI has no configured instruments" );
         break;

      case MIDIERR_NOTREADY:

         error_string = TEXT( "MIDI hardware is still busy" );
         break;

      case MIDIERR_NODEVICE:

         error_string = TEXT( "MIDI port no longer connected" );
         break;

      case MIDIERR_INVALIDSETUP:

         error_string = TEXT( "MIDI invalid MIF" );
         break;

      case MIDIERR_BADOPENMODE:

         error_string = TEXT( "MIDI operation unsupported with open mode" );
         break;

      case MIDIERR_DONT_CONTINUE:

         error_string = TEXT( "MIDI through device is eating a message" );
         break;

      case TIMERR_NOCANDO:

         error_string = TEXT( "Timer request not completed" );
         break;

      case TIMERR_STRUCT:

         error_string = TEXT( "Timer structure size error" );
         break;

      case JOYERR_PARMS:

         error_string = TEXT( "Joystick bad parameters" );
         break;

      case JOYERR_NOCANDO:

         error_string = TEXT( "Joystick request not completed" );
         break;

      case JOYERR_UNPLUGGED:

         error_string = TEXT( "Joystick is unplugged" );
         break;

      case MIXERR_INVALLINE:

         error_string = TEXT( "Mixer invalid line" );
         break;

      case MIXERR_INVALCONTROL:

         error_string = TEXT( "Mixer invalid control" );
         break;

      case MIXERR_INVALVALUE:

         error_string = TEXT( "Mixer invalid value" );
         break;

      default:

         error_string.Format( TEXT( "Unknown (%lu)" ), m_ErrorCode );

#if defined( _DEBUG )

         if ( m_ErrorCode > MMSYSERR_BASE )
         {
            CString debug_string;

            debug_string.Format( TEXT( "Unknown (MMSYSERR_BASE + %d)" ), m_ErrorCode - MMSYSERR_BASE );
            WFCTRACE( debug_string );
         }
         else
         {
            WFCTRACE( TEXT( "I'm really confused now..." ) );
         }

#endif

         break;
   }
}

HMIXEROBJ CMixer::GetHandle( void ) const
{
   return( (HMIXEROBJ) m_Handle );
}

UINT CMixer::GetNumberOfDevices( void ) const
{
   WFCLTRACEINIT( TEXT( "CMixer::GetNumberOfDevices()" ) );

   UINT return_value = 0;

   return_value = ::mixerGetNumDevs();

   return( return_value );
}

BOOL CMixer::Open( UINT device_id, DWORD what_to_notify, DWORD who_to_notify, DWORD notify_data )
{
   WFCLTRACEINIT( TEXT( "CMixer::Open()" ) );

   m_ErrorCode = ::mixerOpen( &m_Handle, device_id, who_to_notify, notify_data, what_to_notify );

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      return( FALSE );
   }

   m_DeviceID = device_id;

   return( TRUE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CMixer::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CMixer::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << m_DeviceID;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> m_DeviceID;
      Open( m_DeviceID );
   }
}

#endif // WFC_NO_SERIALIZATION

BOOL CMixer::SetControlDetails( const CMixerLine& line, const CMixerControl& control, const CPtrArray& settings_array )
{
   WFCLTRACEINIT( TEXT( "CMixer::SetControlDetails()" ) );

   DWORD type_of_details = 0;

   type_of_details = control.GetUnits();

   DWORD size_of_element = 0;

   if ( type_of_details == CMixerControl::unitsBoolean )
   {
      size_of_element = sizeof( MIXERCONTROLDETAILS_BOOLEAN );
   }
   else if ( type_of_details == CMixerControl::unitsSigned   ||
             type_of_details == CMixerControl::unitsDecibels )
   {
      size_of_element = sizeof( MIXERCONTROLDETAILS_SIGNED );
   }
   else if ( type_of_details == CMixerControl::unitsUnsigned ||
             type_of_details == CMixerControl::unitsPercent  )
   {
      size_of_element = sizeof( MIXERCONTROLDETAILS_UNSIGNED );
   }
   else
   {
      WFCTRACE( TEXT( "Unknown type of details to get" ) );
      return( FALSE );
   }

   DWORD number_of_items_per_channel = 0;
   DWORD number_of_channels          = line.NumberOfChannels;

   if ( control.IsUniform() )
   {
      number_of_items_per_channel = 1;
      number_of_channels          = 1;

      if ( type_of_details == CMixerControl::unitsBoolean )
      {
         number_of_items_per_channel = 0;
      }
   }
   else
   {
      number_of_items_per_channel = control.NumberOfItemsPerChannel;
   }

   if ( control.IsMultiple() )
   {
      number_of_items_per_channel = control.NumberOfItemsPerChannel;
   }

   int number_of_elements = 0;

   number_of_elements = number_of_channels * ( ( number_of_items_per_channel == 0 ) ? 1 : number_of_items_per_channel );

   WFCTRACEVAL( TEXT( "Number of elements is " ), number_of_elements );

   DWORD buffer_size = 0;

   buffer_size = number_of_elements * size_of_element;

   BYTE * memory_buffer = NULL;

   try
   {
      memory_buffer = new BYTE[ buffer_size ];
   }
   catch( ... )
   {
      memory_buffer = NULL;
   }

   ASSERT( memory_buffer != NULL );

   // Choose to live

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = MMSYSERR_NOMEM;
      return( FALSE );
   }

   CMixerControlDetailsData * data_p = NULL;

   int loop_index = 0;

   while( loop_index < number_of_elements )
   {
      if ( loop_index < settings_array.GetSize() )
      {
         data_p = (CMixerControlDetailsData *) settings_array.GetAt( loop_index );
      }
      else
      {
         ASSERT( FALSE );
         data_p = NULL;
      }

      if ( data_p != NULL )
      {
         if ( type_of_details == CMixerControl::unitsBoolean )
         {
            MIXERCONTROLDETAILS_BOOLEAN *array = NULL;

            array = (MIXERCONTROLDETAILS_BOOLEAN *) memory_buffer;

            ASSERT( (DWORD) array == (DWORD) memory_buffer );
            array[ loop_index ].fValue = ( ( data_p->Parameter1 == 0 ) ? FALSE : TRUE );
         }
         else if ( type_of_details == CMixerControl::unitsSigned   ||
                   type_of_details == CMixerControl::unitsDecibels )
         {
            MIXERCONTROLDETAILS_SIGNED *array = NULL;

            array = (MIXERCONTROLDETAILS_SIGNED *) memory_buffer;

            ASSERT( (DWORD) array == (DWORD) memory_buffer );

            array[ loop_index ].lValue = data_p->Parameter1;
         }
         else if ( type_of_details == CMixerControl::unitsUnsigned ||
                   type_of_details == CMixerControl::unitsPercent  )
         {
            MIXERCONTROLDETAILS_UNSIGNED *array = NULL;

            array = (MIXERCONTROLDETAILS_UNSIGNED *) memory_buffer;

            ASSERT( (DWORD) array == (DWORD) memory_buffer );

            array[ loop_index ].dwValue = data_p->Parameter1;
         }
         else
         {
            // We should never get here
            ASSERT( FALSE );
            delete [] memory_buffer;
            return( FALSE );
         }
      }

      loop_index++;
   }

   MIXERCONTROLDETAILS control_details;

   ::ZeroMemory( &control_details, sizeof( control_details ) );

   control_details.cbStruct       = sizeof( control_details );
   control_details.dwControlID    = control.ID;
   control_details.cChannels      = number_of_channels;
   control_details.cMultipleItems = number_of_items_per_channel;
   control_details.cbDetails      = size_of_element;
   control_details.paDetails      = memory_buffer;

   DWORD flags = 0;

   flags = MIXER_GETCONTROLDETAILSF_VALUE;

#if defined( _WFC_DEBUG_MIXER_SET_CONTROL_DETAILS )

   dump_mixer_control_details( THIS_FILE, __LINE__, TEXT( "mixerSetControlDetails" ), (HMIXEROBJ) m_Handle, &control_details, flags );

#endif // _WFC_DEBUG_MIXER_SET_CONTROL_DETAILS

   m_ErrorCode = ::mixerSetControlDetails( (HMIXEROBJ) m_Handle, &control_details, flags );

   BOOL return_value = FALSE;

   if ( m_ErrorCode != MMSYSERR_NOERROR )
   {
      WFCTRACE( TEXT( "mixerSetControlDetails() failed" ) );
      WFCTRACEVAL( TEXT( "Error code is " ), m_ErrorCode );
      return_value = FALSE;
   }
   else
   {
      return_value = TRUE;
   }

   ::ZeroMemory( memory_buffer, buffer_size );
   delete [] memory_buffer;

   return( return_value );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CMixer</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles the Mixer API.">
</HEAD>

<BODY>

<H1>CMixer : CObject</H1>
$Revision: 21 $<BR><HR>

<H2>Description</H2>
This is the class handles general mixer stuff. It retrieves things
like mixer capabilities, opening and closing.

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Close</B><DD>Closes the connection to the mixer device.
<DT><B>Get</B><DD>Retrieves the mixer's capabilities via CMixerCapabilities.
<DT><B>GetAllControls</B><DD>
<DT><B>GetByComponent</B><DD>
<DT><B>GetByConnection</B><DD>
<DT><B>GetByDestination</B><DD>
<DT><B>GetByID</B><DD>
<DT><B>GetControlDetails</B><DD>
<DT><B>GetControlListText</B><DD>
<DT><B>GetDeviceID</B><DD>
<DT><B>GetErrorCode</B><DD>
<DT><B>GetErrorString</B><DD>
<DT><B>GetHandle</B><DD>
<DT><B>GetNumberOfDevices</B><DD>
<DT><B>Open</B><DD>
<DT><B>Serialize</B><DD>
<DT><B>SetControlDetails</B><DD>
</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>

<UL>
<LI>mixerClose
<LI>mixerGetControlDetails
<LI>mixerGetDevCaps
<LI>mixerGetLineControls
<LI>mixerGetLineInfo
<LI>mixerGetNumDevs
<LI>mixerOpen
<LI>mixerSetControlDetails
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CMixer.cpp $<BR>
$Modtime: 1/04/00 5:15a $
</BODY>

</HTML>
#endif
