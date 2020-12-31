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
** $Workfile: serial.cpp $
** $Revision: 56 $
** $Modtime: 3/17/00 4:46p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined( WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CSerialFile, CDummyFile, 1 )
#endif // WFC_NO_SERIALIZATION 

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CSerialFile::CSerialFile()
{
   WFCLTRACEINIT( TEXT( "CSerialFile::CSerialFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   FileHandle = (HANDLE) INVALID_HANDLE_VALUE;
   ::ZeroMemory( &m_CommunicationsStatus, sizeof( m_CommunicationsStatus ) );
   m_IsOpen             = FALSE;
   m_PurgeBufferOnError = FALSE;
   Name.Empty();
   m_InputBufferSize  = 4096;
   m_OutputBufferSize = 4096;
}

CSerialFile::~CSerialFile()
{
   WFCLTRACEINIT( TEXT( "CSerialFile::~CSerialFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
}

BOOL CSerialFile::Attach( HANDLE new_handle, HANDLE * old_handle_p )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Attach()" ) );

   // A new method as suggested by Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
   // 1998-07-14

   ASSERT( new_handle != (HANDLE) INVALID_HANDLE_VALUE );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( new_handle == (HANDLE) INVALID_HANDLE_VALUE ||
        m_hFile    == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      return( FALSE );
   }

   if ( old_handle_p != NULL )
   {
      try
      {
         // We were sent a pointer, don't trust it
         *old_handle_p = reinterpret_cast< HANDLE >( m_hFile );
      }
      catch( ... )
      {
         // Do Nothing
      }
   }

   m_IsOpen   = TRUE;
   m_hFile    = reinterpret_cast< UINT >( new_handle );
   FileHandle = new_handle;

   return( TRUE );
}

BOOL CSerialFile::CancelWaitFor( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::CancelWaitFor()" ) );

   BOOL return_value = FALSE;

   return_value = ::SetCommMask( reinterpret_cast< HANDLE >( m_hFile ), 0 );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't set comm mask" ) );
      WFCTRACEERROR( m_ErrorCode );
   }

   return( return_value );
}

BOOL CSerialFile::ClearBreak( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::ClearBreak()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::ClearCommBreak( reinterpret_cast< HANDLE >( m_hFile ) );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

void CSerialFile::Close( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Close()" ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      WFCTRACE( TEXT( "already closed" ) );
      m_IsOpen = FALSE;
      return;
   }

   WFCTRACEVAL( TEXT( "Closing " ), Name );

   m_ClearError( __LINE__ );

   Purge( purgeAll );

   ::EscapeCommFunction( reinterpret_cast< HANDLE >( m_hFile ), CLRDTR );

   if ( m_hFile != static_cast< UINT >( CFile::hFileNull ) )
   {
      CDummyFile::Close();
   }

   FileHandle = (HANDLE) INVALID_HANDLE_VALUE;
   m_IsOpen   = FALSE;
}

BOOL CSerialFile::ConfigurationDialog( CCommunicationsConfiguration& configuration, BOOL save_changes, HWND parent_window_handle )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::ConfigurationDialog()" ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      WFCTRACE( TEXT( "Serial port is not open" ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   // First, find out how large a buffer we need for the configuration data...

   CCommunicationProperties properties;

   return_value = GetProperties( properties );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Can't get properties" ) );
      return( FALSE );
   }

   return_value = GetConfiguration( configuration );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "Can't get configuration" ) );
      return( FALSE );
   }

   int colon_location = 0;

   colon_location = Name.Find( TEXT( ':' ) );

   if ( colon_location == (-1) )
   {
      WFCTRACE( TEXT( "This is really bad, can't find my colon." ) );
      return( FALSE );
   }

   CString device_name;

   device_name = Name.Left( colon_location );

   BYTE * buffer = reinterpret_cast< BYTE * >( NULL );
   
   try
   {
      buffer = new BYTE[ 8192 ]; // insanely large buffer
   }
   catch( ... )
   {
      buffer = reinterpret_cast< BYTE * >( NULL );
   }

   if ( buffer == NULL )
   {
      return( FALSE );
   }

   // Always, always always zeroize the buffer
   ZeroMemory( buffer, 8192 );

   LPCOMMCONFIG communications_configuration_p = reinterpret_cast< LPCOMMCONFIG >( buffer );

   communications_configuration_p->dwSize        = 8192;
   communications_configuration_p->dcb.DCBlength = sizeof( DCB );

   return_value = ::CommConfigDialog( device_name, parent_window_handle, reinterpret_cast< LPCOMMCONFIG >( buffer ) );

   // Alexander Kiesl [Alexander.Kiesl@mch.sni.de] found a bug here.
   // Apparently someone at Microsoft left the door to the day care
   // center and a child got into the source code again. CommConfigDialog()
   // is defined and documented as a BOOL function but it returns
   // something other than TRUE and FALSE. The grown ups at Microsoft
   // should be more careful... This caused me to edit this entire
   // class. Children should learn the meaning of BOOL.

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      delete [] buffer;
      buffer = reinterpret_cast< BYTE * >( NULL );
      return( FALSE );
   }

   configuration.Copy( *( reinterpret_cast< LPCOMMCONFIG >( buffer ) ) );

   if ( save_changes != FALSE )
   {
      communications_configuration_p->dcb.DCBlength = sizeof( DCB );

      CDeviceControlBlock device_control_block;

      device_control_block.Copy( communications_configuration_p->dcb );

      // I don't know why this doesn't work. It keeps returning ERROR_INVALID_PARAMETER but
      // there's no way to tell *WHICH* parameter was invalid.

      return_value = ::SetCommConfig( reinterpret_cast< HANDLE >( m_hFile ), communications_configuration_p, 8192 );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );

         // Heck, let's give SetState() a try.

         WFCTRACEVAL( TEXT( "Trying SetState() because SetCommConfig failed with " ), m_ErrorCode );

         if ( SetState( device_control_block ) == FALSE )
         {
            m_ErrorCode = ::GetLastError();
            WFCTRACEERROR( m_ErrorCode );

            WFCTRACEVAL( TEXT( "SetState() also failed, reason " ), m_ErrorCode );

            delete [] buffer;
            buffer = reinterpret_cast< BYTE * >( NULL );

            return( FALSE );
         }

         delete [] buffer;
         buffer = reinterpret_cast< BYTE * >( NULL );

         return( TRUE );
      }
   }

   delete [] buffer;
   buffer = reinterpret_cast< BYTE * >( NULL );

   return( TRUE );
}

HANDLE CSerialFile::Detach( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Detach()" ) );

   // A new method as suggested by Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
   // 1998-07-14

   HANDLE return_value = reinterpret_cast< HANDLE >( m_hFile );

   m_IsOpen   = FALSE;
   m_hFile    = reinterpret_cast< UINT >( INVALID_HANDLE_VALUE );
   FileHandle = (HANDLE) INVALID_HANDLE_VALUE;

   return( return_value );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CSerialFile::Dump( CDumpContext& dump_context ) const
{
   CDummyFile::Dump( dump_context );

   dump_context << TEXT( "m_IsOpen                  = " );
   
   if ( m_IsOpen == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "m_PurgeBufferOnError      = " );
   
   if ( m_PurgeBufferOnError == FALSE )
   {
      dump_context << TEXT( "FALSE\n" );
   }
   else
   {
      dump_context << TEXT( "TRUE\n" );
   }

   dump_context << TEXT( "m_CommunicationErrorCodes = " ) << m_CommunicationErrorCodes;

   if ( m_CommunicationErrorCodes != 0 )
   {
      dump_context << TEXT( " ( " );

      if ( m_CommunicationErrorCodes & CE_BREAK )
      {
         dump_context << TEXT( "CE_BREAK " );
      }

      if ( m_CommunicationErrorCodes & CE_FRAME )
      {
         dump_context << TEXT( "CE_FRAME " );
      }

      if ( m_CommunicationErrorCodes & CE_IOE )
      {
         dump_context << TEXT( "CE_IOE " );
      }

      if ( m_CommunicationErrorCodes & CE_MODE )
      {
         dump_context << TEXT( "CE_MODE " );
      }

      if ( m_CommunicationErrorCodes & CE_OVERRUN )
      {
         dump_context << TEXT( "CE_OVERRUN " );
      }

      if ( m_CommunicationErrorCodes & CE_RXOVER )
      {
         dump_context << TEXT( "CE_RXOVER " );
      }

      if ( m_CommunicationErrorCodes & CE_RXPARITY )
      {
         dump_context << TEXT( "CE_RXPARITY " );
      }

      if ( m_CommunicationErrorCodes & CE_TXFULL )
      {
         dump_context << TEXT( "CE_TXFULL " );
      }

      if ( m_CommunicationErrorCodes & CE_DNS )
      {
         dump_context << TEXT( "CE_DNS " );
      }

      if ( m_CommunicationErrorCodes & CE_PTO )
      {
         dump_context << TEXT( "CE_PTO " );
      }

      if ( m_CommunicationErrorCodes & CE_OOP )
      {
         dump_context << TEXT( "CE_OOP " );
      }

      dump_context << TEXT( ")\n" );
   }
   else
   {
      dump_context << TEXT( "\n" );
   }

   dump_context << TEXT( "m_CommunicationsStatus is a COMSTAT:\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   fCtsHold  = " ) << m_CommunicationsStatus.fCtsHold  << TEXT( "\n" );
   dump_context << TEXT( "   fDsrHold  = " ) << m_CommunicationsStatus.fDsrHold  << TEXT( "\n" );
   dump_context << TEXT( "   fRlsdHold = " ) << m_CommunicationsStatus.fRlsdHold << TEXT( "\n" );
   dump_context << TEXT( "   fXoffHold = " ) << m_CommunicationsStatus.fXoffHold << TEXT( "\n" );
   dump_context << TEXT( "   fXoffSent = " ) << m_CommunicationsStatus.fXoffSent << TEXT( "\n" );
   dump_context << TEXT( "   fEof      = " ) << m_CommunicationsStatus.fEof      << TEXT( "\n" );
   dump_context << TEXT( "   fTxim     = " ) << m_CommunicationsStatus.fTxim     << TEXT( "\n" );
   dump_context << TEXT( "   fReserved = " ) << m_CommunicationsStatus.fReserved << TEXT( "\n" );
   dump_context << TEXT( "   cbInQue   = " ) << m_CommunicationsStatus.cbInQue   << TEXT( "\n" );
   dump_context << TEXT( "   cbOutQue  = " ) << m_CommunicationsStatus.cbOutQue  << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
   dump_context << TEXT( "m_InputBufferSize  = " ) << m_InputBufferSize  << TEXT( "\n" );
   dump_context << TEXT( "m_OutputBufferSize = " ) << m_OutputBufferSize << TEXT( "\n" );
}

#endif // _DEBUG

DWORD CSerialFile::GetBaudRate( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetBaudRate()" ) );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( 0 );
   }

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      ASSERT( FALSE );
      return( 0 );
   }

   return( device_control_block.BaudRate );
}

BOOL CSerialFile::GetConfiguration( CCommunicationsConfiguration& configuration )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetConfiguration()" ) );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   configuration.Empty();

   BOOL return_value = FALSE;

   DWORD buffer_size = 8 * 1024;

   BYTE * buffer_p = reinterpret_cast< BYTE * >( NULL );
   
   try
   {
      buffer_p = new BYTE[ buffer_size ]; // 8K buffer, insanely large
   }
   catch( ... )
   {
      buffer_p = reinterpret_cast< BYTE * >( NULL );
   }

   if ( buffer_p == NULL )
   {
      return( FALSE );
   }

   // Always, always always zeroize the buffer
   ZeroMemory( buffer_p, buffer_size );

   LPCOMMCONFIG communications_configuration_p = reinterpret_cast< LPCOMMCONFIG >( buffer_p );

   communications_configuration_p->dwSize        = buffer_size;
   communications_configuration_p->dcb.DCBlength = sizeof( DCB );

   return_value = ::GetCommConfig( reinterpret_cast< HANDLE >( m_hFile ), communications_configuration_p, &buffer_size );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      delete [] buffer_p;
      buffer_p = reinterpret_cast< BYTE * >( NULL );
      return( FALSE );
   }

   configuration.Copy( *( reinterpret_cast< LPCOMMCONFIG >( buffer_p ) ) );

   delete [] buffer_p;
   buffer_p = reinterpret_cast< BYTE * >( NULL );

   return( TRUE );
}

DWORD CSerialFile::GetFlowControl( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetFlowControl()" ) );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( 0 );
   }

   DWORD flow_control = 0;

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      ASSERT( FALSE );
      return( 0 );
   }

   if ( device_control_block.fOutxDsrFlow != FALSE &&
        device_control_block.fOutxCtsFlow != FALSE )
   {
      flow_control = flowHardware;
   }

   if ( device_control_block.fInX  != FALSE &&
        device_control_block.fOutX != FALSE )
   {
      flow_control |= flowSoftware;
   }

   return( flow_control );
}

DWORD CSerialFile::GetInputBufferSize( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetInputBufferSize()" ) );

   // A better solution supplied by Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
   // 1998-07-14

   CCommunicationProperties properties;

   if ( GetProperties( properties ) != FALSE )
   {
      return( properties.dwCurrentRxQueue );
   }
   else
   {
      return( 0 );
   }
}

DWORD CSerialFile::GetModemStatus( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetModemStatus()" ) );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( 0 );
   }

   BOOL return_value = FALSE;

   DWORD modem_status = 0;

   return_value = ::GetCommModemStatus( reinterpret_cast< HANDLE >( m_hFile ), &modem_status );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return( modem_status );
   }

   return( 0 );
}

DWORD CSerialFile::GetOutputBufferSize( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetOutputBufferSize()" ) );

   // A better solution supplied by Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
   // 1998-07-14

   CCommunicationProperties properties;

   if ( GetProperties( properties ) != FALSE )
   {
      return( properties.dwCurrentTxQueue );
   }
   else
   {
      return( 0 );
   }
}

BOOL CSerialFile::GetProperties( CCommunicationProperties& properties )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetProperties()" ) );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   // Choose to live

   if ( m_hFile == reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) )
   {
      properties.Empty();
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::GetCommProperties( reinterpret_cast< HANDLE >( m_hFile ), &properties );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      properties.Empty();
      return( FALSE );
   }

   return( TRUE );
}

BOOL CSerialFile::GetState( CDeviceControlBlock& device_control_block )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetState()" ) );
   ASSERT( m_hFile != reinterpret_cast< UINT >( INVALID_HANDLE_VALUE ) );

   if ( ::GetCommState( reinterpret_cast< HANDLE >( m_hFile ), &device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CSerialFile::GetTimeouts( COMMTIMEOUTS& timeouts )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::GetTimeouts()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   // Choose to live

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      ::ZeroMemory( &timeouts, sizeof( COMMTIMEOUTS ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::GetCommTimeouts( (HANDLE) m_hFile, &timeouts );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

#if defined( _DEBUG )
void CSerialFile::m_ClearError( int line_number )
#else
void CSerialFile::m_ClearError( int )
#endif // _DEBUG
{
   WFCLTRACEINIT( TEXT( "CSerialFile::m_ClearError()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return;
   }

   if ( ::ClearCommError( (HANDLE) m_hFile, &m_CommunicationErrorCodes, &m_CommunicationsStatus ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );

      if ( m_ErrorCode == ERROR_INVALID_HANDLE )
      {
         m_hFile    = (UINT) INVALID_HANDLE_VALUE;
         FileHandle = (HANDLE) INVALID_HANDLE_VALUE;
      }

      return;
   }

   if ( m_CommunicationErrorCodes != 0 )
   {
#if defined( _DEBUG )
      TCHAR error_message[ 2048 ];

      ::ZeroMemory( error_message, sizeof( error_message ) );

      if ( m_CommunicationErrorCodes & CE_BREAK )
      {
         _tcscat( error_message, TEXT( "\r\nThe hardware detected a break condition. (CE_BREAK);" ) );
      }

#endif // _DEBUG

      if ( m_CommunicationErrorCodes & CE_FRAME )
      {
#if defined( _DEBUG )
         _tcscat( error_message, TEXT( "\r\nThe hardware detected a framing error. (CE_FRAME);" ) );
#endif // _DEBUG

         if ( m_PurgeBufferOnError != FALSE )
         {
            Purge( purgeClearInputBuffer );

            // Thanks go to Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
            // for suggesting this change
            // 1998-07-14

            m_CommunicationsStatus.cbInQue = 0;
         }
      }

#if defined( _DEBUG )

      if ( m_CommunicationErrorCodes & CE_IOE )
      {
         _tcscat( error_message, TEXT( "\r\nAn I/O error occurred during communications with the device. (CE_IOE);" ) );
      }

      if ( m_CommunicationErrorCodes & CE_MODE )
      {
         _tcscat( error_message, TEXT( "\r\nThe requested mode is not supported or the hCommDev parameter is invalid. (CE_MODE);" ) );
      }

      if ( m_CommunicationErrorCodes & CE_OVERRUN )
      {
         _tcscat( error_message, TEXT( "\r\nA character-buffer overrun has occurred. The next character is lost. (CE_OVERRUN);" ) );
      }

#endif // _DEBUG

      if ( m_CommunicationErrorCodes & CE_RXOVER )
      {
         m_ErrorCode = CE_RXOVER;
#if defined( _DEBUG )
         _tcscat( error_message, TEXT( "\r\nAn input buffer overflow has occurred. There is either no room in the input buffer, or a character was received after the end-of-file (EOF) character. (CE_RXOVER);" ) );
#endif // _DEBUG
      }

#if defined( _DEBUG )

      if ( m_CommunicationErrorCodes & CE_RXPARITY )
      {
         _tcscat( error_message, TEXT( "\r\n.The hardware detected a parity error. (CE_RXPARITY);" ) );
      }

      if ( m_CommunicationErrorCodes & CE_TXFULL )
      {
         _tcscat( error_message, TEXT( "\r\nThe application tried to transmit a character, but the output buffer was full. (CE_TXFULL);" ) );
      }

      if ( m_CommunicationErrorCodes & CE_DNS )
      {
         _tcscat( error_message, TEXT( "\r\nThe parallel device is not selected. (CE_DNS);" ) );
      }

      if ( m_CommunicationErrorCodes & CE_PTO )
      {
         _tcscat( error_message, TEXT( "\r\nA time-out occurred on the parallel device. (CE_PTO);" ) );
      }

      if ( m_CommunicationErrorCodes & CE_OOP )
      {
         _tcscat( error_message, TEXT( "\r\nThe parallel device signaled that it is out of paper. (CE_OOP);" ) );
      }

      TCHAR temp_string[ 100 ];

      _stprintf( temp_string, TEXT( "%d (%d in input_queue)" ), line_number, m_CommunicationsStatus.cbInQue );

      WFCTRACE( error_message );
      WFCTRACE( temp_string   );

#endif // _DEBUG

   }
}

BOOL CSerialFile::IsDataWaiting( void )
{
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   m_ClearError( __LINE__ );

   if ( m_CommunicationsStatus.cbInQue > 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

DWORD CSerialFile::NumberOfBytesWaitingToBeRead( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::NumberOfBytesWaitingToBeRead()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( 0 );
   }

   m_ClearError( __LINE__ );

   return( m_CommunicationsStatus.cbInQue );
}

DWORD CSerialFile::NumberOfBytesWaitingToBeWritten( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::NumberOfBytesWaitingToBeWritten()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( 0 );
   }

   m_ClearError( __LINE__ );

   return( m_CommunicationsStatus.cbOutQue );
}

#pragma warning( disable : 4100 )

#if ! defined( WFC_STL )
BOOL CSerialFile::Open( LPCTSTR channel_name, UINT open_flags, CFileException * exception_p )
#else // WFC_STL
BOOL CSerialFile::Open( LPCTSTR channel_name, UINT open_flags )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Open()" ) );

   ASSERT( channel_name != NULL );

   // Choose to live

   if ( channel_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   if ( m_IsOpen != FALSE )
   {
      Close();
   }

   // We were passed a pointer, do not trust it

   try
   {
      Name = channel_name;

      return( Open() );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

#pragma warning( default : 4100 )

BOOL CSerialFile::Open( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Open()" ) );

   if ( m_IsOpen != FALSE )
   {
      Close();
   }

   // Gawl dang children... They coded CreateFile to accept COM1: through COM9:
   // the only problem is NT can have up to 255 com ports. Let's see... that
   // means CreateFile will fail 246 out of 255 times. To get around this, we
   // have to call the com port by a different name, "COM1:" becomes "\\.\COM1"
   // Why? I dunno, it was probably coded to originally take names of "\\.\COMx"
   // but someone cried until it was hacked to take "COMx:". It sure looks like
   // a compromise to me.

   CString com_port_name( TEXT( "\\\\.\\" ) );

   int index = 0;
   int string_length = Name.GetLength();

   while( index < string_length && Name[ index ] != TEXT( ':' ) )
   {
      com_port_name += Name[ index ];
      index++;
   }

   com_port_name.MakeUpper();

   CString settings_string( TEXT( "" ) );

   settings_string = Name.Right( ( string_length - index ) - 1 );

   // Win95 doesn't seem to like \\.\ so let's trim it if we can.
   // 0123456
   // \\.\COMxxx

   index = 7;

   CString number_string( TEXT( "" ) );

   int com_port_name_string_length = com_port_name.GetLength();

   while( index < com_port_name_string_length )
   {
      if ( com_port_name.GetAt( index ) >= TEXT( '0' ) &&
           com_port_name.GetAt( index ) <= TEXT( '9' ) )
      {
         number_string += com_port_name.GetAt( index );
         index++;
      }
      else
      {
         index = com_port_name_string_length;
      }
   }

   WFCTRACEVAL( TEXT( "number string is " ), number_string );

   int port_number = _ttoi( number_string );

   WFCTRACEVAL( TEXT( "port_number is " ), port_number );

   if ( port_number > 0 && port_number < 10 )
   {
      // Yep, we've got a COM1 through COM9 so strip our \\.\ prefix

      // com_port_name = com_port_name.Right( com_port_name_string_length - 4 );
      com_port_name.Format( TEXT( "COM%d:" ), port_number );
   }

   // Thanks go to Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
   // for suggesting the functions instead of contants.
   // 1998-07-14

   FileHandle = ::CreateFile( (LPCTSTR) com_port_name,
                              m_CreateDesiredAccess(),
                              m_CreateShareMode(),
                              m_CreateSecurityAttributes(),
                              m_CreateCreationDistribution(),
                              m_CreateFlagsAndAttributes(),
                              m_CreateTemplateHandle() );

   if ( FileHandle == INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ::GetLastError();
      m_hFile = reinterpret_cast< UINT >( INVALID_HANDLE_VALUE );
      WFCTRACEVAL( TEXT( "CreateFile() failed on " ), com_port_name );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   m_hFile = reinterpret_cast< HFILE >( FileHandle );

   if ( SetTimeouts() == FALSE )
   {
      WFCTRACE( TEXT( "SetTimeouts failed." ) );
   }

   if ( Purge( purgeAll ) == FALSE )
   {
      WFCTRACE( TEXT( "Purge failed." ) );
   }

   CString baud_string( TEXT( "" ) );

   index = 0;
   string_length = settings_string.GetLength();

   while( index < string_length && settings_string[ index ] != TEXT( ',' ) )
   {
      baud_string += settings_string[ index ];
      index++;
   }

   index++; // Skip over the comma

   CString parity_string( TEXT( "" ) );

   while( index < string_length && settings_string[ index ] != TEXT( ',' ) )
   {
      parity_string += settings_string[ index ];
      index++;
   }

   index++; // skip the comma

   CString data_bits_string( TEXT( "" ) );

   while( index < string_length && settings_string[ index ] != TEXT( ',' ) )
   {
      data_bits_string += settings_string[ index ];
      index++;
   }

   index++; // another dang comma

   CString stop_bits_string( TEXT( "" ) );

   while( index < string_length )
   {
      stop_bits_string += settings_string[ index ];
      index++;
   }

   // Need to add idiot proofing here...
   // check each setting for validity...

   CString dcb_string( TEXT( "" ) );

   dcb_string = TEXT( "baud=" );
   dcb_string += baud_string;
   dcb_string += TEXT( " parity=" );
   dcb_string += parity_string;
   dcb_string += TEXT( " data=" );
   dcb_string += data_bits_string;
   dcb_string += TEXT( " stop=" );
   dcb_string += stop_bits_string;

   WFCTRACEVAL( TEXT( "dcb_string is " ), dcb_string );

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "GetState() failed at line " ), __LINE__ );
      WFCTRACEERROR( m_ErrorCode );
      Close();
      return( FALSE );
   }

   if ( ::BuildCommDCB( dcb_string, &device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "BuildCommDCB failed at line " ), __LINE__ );
      WFCTRACEERROR( m_ErrorCode );
      Close();
      return( FALSE );
   }

   device_control_block.fAbortOnError = FALSE; // Terminate Reads & Writes if there's an error
   device_control_block.fErrorChar    = TRUE;  // Replace any garbled bytes with ErrorChar
   device_control_block.ErrorChar     = (char) ' '; // Garbage bytes are spaces
   device_control_block.fBinary       = TRUE;  // Ignore EOF

   if ( SetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "SetState() failed with error " ), m_ErrorCode );
      WFCTRACEERROR( m_ErrorCode );
      Close();
      return( FALSE );
   }

   if ( ::SetupComm( (HANDLE) m_hFile, m_InputBufferSize, m_OutputBufferSize ) == FALSE )
   {
      WFCTRACE( TEXT( "SetupComm failed." ) );
   }

   // assert DTR

   SetDataTerminalReady( TRUE );

   m_IsOpen      = TRUE;

#if ! defined( WFC_STL )
   m_strFileName = Name;
#else // WFC_STL
   m_FileName = Name;
#endif // WFC_STL

   return( TRUE );
}

UINT CSerialFile::Read( void *buffer, UINT length )
{
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );
   ASSERT( buffer != NULL );

   if ( buffer == NULL || m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( 0 );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ClearError( __LINE__ );

      return( CDummyFile::Read( buffer, length ) );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( 0 );
   }
}

BOOL CSerialFile::Purge( DWORD what_to_purge )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Purge()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::PurgeComm( (HANDLE) m_hFile, what_to_purge );

   if ( return_value == FALSE )
   {
      // 1998-09-15 Thanks go to Jim Peng (jimp@datalink.net) for
      // finding a type here. I was setting return_value to the
      // value returned by GetLastError(). I should have been
      // setting m_ErrorCode. DOH!

      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

void CSerialFile::ReplaceGarbledCharacter( BOOL yes_or_no, BYTE character_to_replace_the_garbled_one_with )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::ReplaceGarbledCharacter()" ) );

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "Can't GetState() at line " ), __LINE__ );
      WFCTRACEERROR( m_ErrorCode );
      return;
   }

   device_control_block.fErrorChar = yes_or_no;  // Replace any garbled bytes with ErrorChar
   device_control_block.ErrorChar  = character_to_replace_the_garbled_one_with;

   if ( SetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "Can't SetState() at line " ), __LINE__ );
      WFCTRACEERROR( m_ErrorCode );
      return;
   }
}

#if ! defined( WFC_NO_SERIALIZATION )

void CSerialFile::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Serialize()" ) );

   CDummyFile::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << (DWORD) m_IsOpen;
      archive << Name;
      archive << m_InputBufferSize;
      archive << m_OutputBufferSize;
   }
   else
   {
      DWORD temp_dword = 0;

      archive >> temp_dword;
      archive >> Name;
      archive >> m_InputBufferSize;
      archive >> m_OutputBufferSize;

      m_IsOpen = temp_dword;

      if ( m_IsOpen != FALSE )
      {
         Open();
      }
   }
}

#endif // WFC_NO_SERIALIZATION

BOOL CSerialFile::SetBaudRate( DWORD baud_rate )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetBaudRate()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   device_control_block.BaudRate = baud_rate;

   if ( SetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CSerialFile::SetBreak( void )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetBreak()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::SetCommBreak( (HANDLE) m_hFile );

   if ( return_value == FALSE )
   {
      WFCTRACE( TEXT( "FAILED!" ) );
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CSerialFile::SetCharacterToWaitFor( BYTE character_to_wait_for )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetCharacterToWaitFor()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   device_control_block.EvtChar = character_to_wait_for;

   if ( SetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CSerialFile::SetDataTerminalReady( BOOL set_DTR_on )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetDataTerminalReady()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   if ( set_DTR_on != FALSE )
   {
      WFCTRACE( TEXT( "Setting DTR on" ) );
      return_value = ::EscapeCommFunction( (HANDLE) m_hFile, SETDTR );
   }
   else
   {
      WFCTRACE( TEXT( "Setting DTR off" ) );
      return_value = ::EscapeCommFunction( (HANDLE) m_hFile, CLRDTR );
   }

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   WFCTRACEVAL( TEXT( "returning " ), return_value );

   return( return_value );
}

void CSerialFile::SetFlowControl( DWORD flow_control )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetFlowControl()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return;
   }

   CDeviceControlBlock device_control_block;

   if ( GetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      ASSERT( FALSE );
      return;
   }

   // Changes by Fabio Angelini (fabioang@iol.it or nico.sw@ibm.net)
   // to get hardware flow control work properly
   // 1998-07-14

   if ( flow_control & flowRtsCts )
   {
      device_control_block.fRtsControl  = RTS_CONTROL_HANDSHAKE;
      device_control_block.fOutxCtsFlow = TRUE;
   }
   else
   {
      device_control_block.fRtsControl  = RTS_CONTROL_DISABLE;
      device_control_block.fOutxCtsFlow = FALSE;
   }

   if ( flow_control & flowDtrDsr )
   {
      device_control_block.fDtrControl  = DTR_CONTROL_HANDSHAKE;
      device_control_block.fOutxDsrFlow = TRUE;
   }
   else
   {
      device_control_block.fDtrControl  = DTR_CONTROL_DISABLE;
      device_control_block.fOutxDsrFlow = FALSE;
   }

   if ( flow_control & flowSoftware )
   {
      device_control_block.fInX     = TRUE;
      device_control_block.fOutX    = TRUE;
      device_control_block.XonChar  = 0x11;
      device_control_block.XoffChar = 0x13;
      device_control_block.XonLim   = 100;
      device_control_block.XoffLim  = 100;
   }
   else
   {
      device_control_block.fInX     = FALSE;
      device_control_block.fOutX    = FALSE;
      device_control_block.XonChar  = 0;
      device_control_block.XoffChar = 0;
      device_control_block.XonLim   = 0;
      device_control_block.XoffLim  = 0;
   }

   if ( SetState( device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      ASSERT( FALSE );
      return;
   }
}

void CSerialFile::SetInputBufferSize( DWORD buffer_size )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetInputBufferSize()" ) );

   m_InputBufferSize = buffer_size;
}

void CSerialFile::SetOutputBufferSize( DWORD buffer_size )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetOutputBufferSize()" ) );

   m_OutputBufferSize = buffer_size;
}

BOOL CSerialFile::SetPurgeBufferOnError( BOOL purge_buffer )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetPurgeBufferOnError()" ) );

   BOOL return_value = m_PurgeBufferOnError;

   m_PurgeBufferOnError = ( purge_buffer == FALSE ) ? FALSE : TRUE;

   return( return_value );
}

BOOL CSerialFile::SetRequestToSend( BOOL set_RTS_on )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetRequestToSend()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   if ( set_RTS_on != FALSE )
   {
      WFCTRACE( TEXT( "Setting RTS on" ) );
      return_value = ::EscapeCommFunction( (HANDLE) m_hFile, SETRTS );
   }
   else
   {
      WFCTRACE( TEXT( "Setting RTS off" ) );
      return_value = ::EscapeCommFunction( (HANDLE) m_hFile, CLRRTS );
   }

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   WFCTRACEVAL( TEXT( "returning " ), return_value );

   return( return_value );
}

BOOL CSerialFile::SetState( CDeviceControlBlock& device_control_block )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetState()" ) );

   if ( ::SetCommState( (HANDLE) m_hFile, &device_control_block ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CSerialFile::SetTimeouts( COMMTIMEOUTS * timeouts_p )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::SetTimeouts()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   // Choose to live

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   COMMTIMEOUTS communications_timeouts;

   ::ZeroMemory( &communications_timeouts, sizeof( communications_timeouts ) );

   if ( timeouts_p != NULL )
   {
      // We were passed a pointer, do not trust it

      try
      {
         communications_timeouts.ReadIntervalTimeout         = timeouts_p->ReadIntervalTimeout;
         communications_timeouts.ReadTotalTimeoutMultiplier  = timeouts_p->ReadTotalTimeoutMultiplier;
         communications_timeouts.ReadTotalTimeoutConstant    = timeouts_p->ReadTotalTimeoutConstant;
         communications_timeouts.WriteTotalTimeoutMultiplier = timeouts_p->WriteTotalTimeoutMultiplier;
         communications_timeouts.WriteTotalTimeoutConstant   = timeouts_p->WriteTotalTimeoutConstant;
      }
      catch( ... )
      {
         communications_timeouts.ReadIntervalTimeout         = MAXDWORD;
         communications_timeouts.ReadTotalTimeoutMultiplier  = 0;
         communications_timeouts.ReadTotalTimeoutConstant    = 0;
         communications_timeouts.WriteTotalTimeoutMultiplier = 0;
         communications_timeouts.WriteTotalTimeoutConstant   = 0;
      }
   }
   else
   {
      // Use our defaults
      communications_timeouts.ReadIntervalTimeout         = MAXDWORD;
      communications_timeouts.ReadTotalTimeoutMultiplier  = 0;
      communications_timeouts.ReadTotalTimeoutConstant    = 0;
      communications_timeouts.WriteTotalTimeoutMultiplier = 0;
      communications_timeouts.WriteTotalTimeoutConstant   = 0;
   }

   return_value = ::SetCommTimeouts( (HANDLE) m_hFile, &communications_timeouts );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CSerialFile::TransmitCharacter( char character_to_transmit )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::TransmitCharacter()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   // Choose to live

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::TransmitCommChar( (HANDLE) m_hFile, character_to_transmit );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't TransmitCommChar()" ) );
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CSerialFile::WaitFor( DWORD& what_to_wait_for )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::WaitFor()" ) );
   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   // Choose to live

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   return_value = ::SetCommMask( reinterpret_cast< HANDLE >( m_hFile ), what_to_wait_for );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't set comm mask" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( return_value );
   }

   return_value = ::WaitCommEvent( reinterpret_cast< HANDLE >( m_hFile ), &what_to_wait_for, NULL );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't wait comm event" ) );
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CSerialFile::WaitForString( const CString& string_to_wait_for, DWORD seconds_to_wait, CString * string_p )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::WaitForString()" ) );

#if defined( _DEBUG )

   CString debug_string( TEXT( "\"" ) );

   debug_string += string_to_wait_for;
   debug_string += TEXT( "\"" );

   WFCTRACEVAL( TEXT( "Waiting for " ), debug_string );

#endif // _DEBUG

   CString response( TEXT( "" ) );

   BYTE buffer[ 1 ];

   BOOL time_expired = FALSE;

   int length_of_string_to_wait_for = string_to_wait_for.GetLength();

   CTime current_time = CTime::GetCurrentTime();

   CTime expiration_time = current_time;

   expiration_time += CTimeSpan( 0, 0, 0, seconds_to_wait + 1 );

   while( time_expired == FALSE )
   {
      if ( IsDataWaiting() != FALSE )
      {
         Read( buffer, 1 );

         response += (TCHAR) buffer[ 0 ];

         // Only compare the last x characters of what came in

         if ( response.GetLength() >= length_of_string_to_wait_for )
         {
            if ( string_to_wait_for.Compare( response.Right( length_of_string_to_wait_for ) ) == 0 )
            {
               WFCTRACE( TEXT( "Returning TRUE" ) );

               if ( string_p != (CString *) NULL )
               {
                  // We were passed a pointer, do not trust it

                  try
                  {
                     *string_p = response;
                  }
                  catch( ... )
                  {
                     ;
                  }
               }

               return( TRUE );
            }
         }
      }
      else
      {
         // This is a cheat. The right way to do it would be to use overlapped
         // I/O but MFC doesn't support overlapped I/O because only NT
         // supports it.

         ::Sleep( 500 );
      }

      current_time = CTime::GetCurrentTime();

      if ( current_time > expiration_time )
      {
         WFCTRACE( TEXT( "timing out..." ) );
         time_expired = TRUE;
      }
   }

   if ( string_p != (CString *) NULL )
   {
      // We were passed a pointer, do not trust it

      try
      {
         *string_p = response;
      }
      catch( ... )
      {
         ;
      }
   }

   WFCTRACE( TEXT( "Returning FALSE" ) );

   return( FALSE );
}

void CSerialFile::Write( BYTE byte_to_write )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Write( BYTE )" ) );

   Write( &byte_to_write, 1 );
}

void CSerialFile::Write( const void *buffer, UINT length )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Write()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );
   ASSERT( buffer != NULL );

   if ( buffer == NULL || m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ClearError( __LINE__ );

      if ( length == 0 )
      {
         return;
      }

      // Windows 95 sucks!

      DWORD number_of_bytes_written       = 0;
      DWORD total_number_of_bytes_written = 0;
      DWORD number_of_bytes_to_write      = length;

      BYTE * temp_buffer = (BYTE *) buffer;

      while( total_number_of_bytes_written < length )
      {
         if ( ::WriteFile( (HANDLE) m_hFile,
                          &temp_buffer[ total_number_of_bytes_written ],
                           number_of_bytes_to_write,
                          &number_of_bytes_written,
                           NULL ) == FALSE &&
              ::GetLastError() != 0 )
         {
            // Something bad happened...
            return;
         }

         number_of_bytes_to_write      -= number_of_bytes_written;
         total_number_of_bytes_written += number_of_bytes_written;

         // 1998-09-10
         // Thanks go to Glenn Brude (d40480@algonet.se) for finding
         // a serious bug here. I was setting number_of_bytes_to_write
         // to zero which meant if everything didn't go in the first
         // call to WriteFile() nothing else would get sent.

         number_of_bytes_written = 0;
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
   }
}

void CSerialFile::Write( CString& string_to_write )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Write()" ) );

   ASSERT( m_hFile != (UINT) INVALID_HANDLE_VALUE );

   if ( m_hFile == (UINT) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return;
   }

   LPTSTR buffer_p = string_to_write.GetBuffer( 1 );

   UINT number_of_bytes = string_to_write.GetLength();

   Write( buffer_p, number_of_bytes );

   string_to_write.ReleaseBuffer();
}

void CSerialFile::Write( const CByteArray& bytes )
{
   WFCLTRACEINIT( TEXT( "CSerialFile::Write()" ) );
   CDummyFile::Write( bytes );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CSerialFile</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles non-overlapped serial communications.">
</HEAD>

<BODY>

<H1>CSerialFile : <A HREF="DumyFile.htm">CDummyFile</A></H1>
$Revision: 56 $<BR>

<HR>

<H2>Description</H2>

This class makes it easy to play with serial ports in NT. The serial
ports in Windows 95 are screwed up so this class may not work the same
way under 95 as it does in NT. I haven't had time to play with the Win95
stuff yet.

<H2>Data Members</H2>

<B>FileHandle</B> - A handle that you can use to call the native Win32
API yourself. You can modify this value but <B>CSerialFile</B> will
ignore the change. In other words, you can't break the class by
modifying this variable.

<P>

<B>Name</B> - The name passed in to the <B>Open</B>() function.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="CancelWaitFor">CancelWaitFor</A></B>( void )</PRE><DD>
<B>WaitFor</B>() is a blocking call. The thread from which
you call <B><A HREF="#WaitFor">WaitFor</A></B>() will stop running until whatever
you're waiting for happens. Sometimes you will never get what
you wait for. This means your thread will never wake up. To
get out of this problem, you can call <B>CancelWaitFor</B>()
from another thread (usually the parent thread).

<DT><PRE>BOOL <B><A NAME="ClearBreak">ClearBreak</A></B>( void )</PRE><DD>
Resumes transmission of data.

<DT><PRE>BOOL <B><A NAME="Close">Close</A></B>( void )</PRE><DD>
Closes the serial port.

<DT><PRE>BOOL <B><A NAME="ConfigurationDialog">ConfigurationDialog</A></B>( CCommunicationsConfiguration&amp; configuration, BOOL save_changes = TRUE, HWND parent_window_handle = NULL )</PRE><DD>
It pops up a dialogbox letting you change the parameters of the serial port.

<DT><PRE>DWORD <B><A NAME="GetBaudRate">GetBaudRate</A></B>( void )</PRE><DD>
Returns the current baud rate.

<DT><PRE>BOOL <B><A NAME="GetConfiguration">GetConfiguration</A></B>( CCommunicationsConfiguration&amp; configuration )</PRE><DD>
Retrieves the configuration of the serial port.

<DT><PRE>DWORD <B><A NAME="GetFlowControl">GetFlowControl</A></B>( void )</PRE><DD>
Retrieves the type of flow control being used.

<DT><PRE>DWORD <B><A NAME="GetInputBufferSize">GetInputBufferSize</A></B>( void ) const</PRE><DD>
Retrieves the input buffer size set via <A HREF="#SetInputBufferSize">SetInputBufferSize()</A>.

<DT><PRE>DWORD <B><A NAME="GetModemStatus">GetModemStatus</A></B>( void )</PRE><DD>
Retrieves the status of the modem if there is one. The return value is
a 32-bit wide bit field. You must and the return value with one of these
flags (defined in <CODE>WINBASE.H</CODE> to see if that status is true:
<UL>
<LI><CODE>MS_CTS_ON</CODE> - To see if the Clear to Send (CTS) pin is high
<LI><CODE>MS_DSR_ON</CODE> - To see if the Data Set Ready (DSR) pin is high
<LI><CODE>MS_RING_ON</CODE> - To see if the modem has detected a ring
<LI><CODE>MS_RLSD_ON</CODE> - To see if the Receive Line Signal Detect (RLSD) signal is on
</UL>

<DT><PRE>DWORD <B><A NAME="GetOutputBufferSize">GetOutputBufferSize</A></B>( void ) const</PRE><DD>
Retrieves the output buffer size set via SetOutputBufferSize().

<DT><PRE>BOOL <B><A NAME="GetProperties">GetProperties</A></B>( CCommunicationProperties&amp; properties )</PRE><DD>
Gets properties about the provider
of the serial port. Returns the data in a CCommunicationProperties object.

<DT><PRE>BOOL <B><A NAME="GetState">GetState</A></B>( CDeviceControlBlock&amp; device_control_block )</PRE><DD>
Gets the state of the port.

<DT><PRE>BOOL <B><A NAME="GetTimeouts">GetTimeouts</A></B>( COMMTIMEOUTS&amp; timeouts )</PRE><DD>
Retrieves the timeouts (COMMTIMEOUTS).

<DT><PRE>BOOL <B><A NAME="IsDataWaiting">IsDataWaiting</A></B>( void )</PRE><DD>
Returns TRUE if there is data
waiting to be read. If the number of bytes in the input queue is zero
then it will return FALSE.

<DT><PRE>DWORD <B><A NAME="NumberOfBytesWaitingToBeRead">NumberOfBytesWaitingToBeRead</A></B>( void )</PRE><DD>Hhhhmmm, Gee I wonder...

<DT><PRE>DWORD <B><A NAME="NumberOfBytesWaitingToBeWritten">NumberOfBytesWaitingToBeWritten</A></B>( void )</PRE><DD>
Hhhhmmm, Gee I wonder...

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( void )
BOOL <B>Open</B>( LPCTSTR channel_name, UINT flags = 0, CFileException * exception_p = NULL )</PRE><DD>
Opens the serial port. You pass the name of the
serial port in the &quot;COM1:9600,n,8,1&quot; format.

<DT><PRE>BOOL <B><A NAME="Purge">Purge</A></B>( DWORD what_to_purge = purgeAll )</PRE><DD>
Purges data in the system buffers. <CODE>what_to_purge</CODE> can be
one or a combination of the following:

<UL>
<LI>purgeTerminateWriteOperation
<LI>purgeTerminateReadOperation
<LI>purgeClearInputBuffer
<LI>purgeClearOutputBuffer
<LI>purgeAll
</UL>

<DT><PRE>UINT <B><A NAME="Read">Read</A></B>( void *buffer, UINT length )</PRE><DD>
Reads data from the serial port.

<DT><PRE>BOOL <B><A NAME="ReplaceGarbledCharacter">ReplaceGarbledCharacter</A></B>( yes_or_no = TRUE, BYTE replacement_character = ' ' )</PRE><DD>
You can tell the serial driver
to automagically replace garbled characters with a known character. The <B>Open</B>()
function sets this mode on replacing garbles with spaces (' ').

<DT><B><A NAME="Serialize">Serialize</A></B><DD>Saves/restores the object.

<DT><PRE>BOOL <B><A NAME="SetBaudRate">SetBaudRate</A></B>( DWORD baud_rate )</PRE><DD>
Changes the current baud rate to <CODE>baud_rate</CODE>.

<DT><PRE>BOOL <B><A NAME="SetBreak">SetBreak</A></B>( void )</PRE><DD>
Halts transmission of data. You must call
<B>ClearBreak</B>() to resume data IO. These are handy functions to use if you
have a lot of processing you need to perform on the data received from the
serial port.

<DT><PRE>BOOL <B><A NAME="SetCharacterToWaitFor">SetCharacterToWaitFor</A></B>( BYTE character_to_wait_for )</PRE><DD>
Sets the character to wait for when you <B>WaitFor</B>() with
<CODE>waitParticularCharacterReceived</CODE> flag.

<DT><PRE>BOOL <B><A NAME="SetDataTerminalReady">SetDataTerminalReady</A></B>( BOOL set_DTR_on = TRUE )</PRE><DD>
Sets the DTR pin high (TRUE) or low (FALSE).

<DT><PRE>void <B><A NAME="SetFlowControl">SetFlowControl</A></B>( DWORD flow_control )</PRE><DD>
Sets the serial port to use the type of flow control you specify.

<DT><PRE>void <B><A NAME="SetInputBufferSize">SetInputBufferSize</A></B>( DWORD buffer_size )</PRE><DD>
Sets the size of the system input
buffer for the serial port. Make this call before you <B>Open</B>() the port. The default
is 4096.

<DT><PRE>void <B><A NAME="SetOutputBufferSize">SetOutputBufferSize</A></B>( DWORD buffer_size )</PRE><DD>
Sets the size of the system output
buffer for the serial port. Make this call before you <B>Open</B>() the port. The default
is 4096.

<DT><PRE>BOOL <B><A NAME="SetPurgeBufferOnError">SetPurgeBufferOnError</A></B>( BOOL purge_buffer = TRUE )</PRE><DD>
This method lets you specify whether or not the buffer will be
purged when an error occurs. This usually happened when the hardware
detected a framing error. The default is to NOT purge the buffer. The return
value is the previous state of the setting.

<DT><PRE>BOOL <B><A NAME="SetRequestToSend">SetRequestToSend</A></B>( BOOL set_RTS_on = TRUE )</PRE><DD>
Sets the RTS pin high (TRUE) or low (FALSE).

<DT><PRE>BOOL <B><A NAME="SetState">SetState</A></B>( CDeviceControlBlock&amp; device_control_block )</PRE><DD>
Sets the state of the port.

<DT><PRE>BOOL <B><A NAME="SetTimeouts">SetTimeouts</A></B>( COMMTIMEOUTS * timeouts_p = NULL )</PRE><DD>
Sets the timeouts (COMMTIMEOUTS).

<DT><PRE>BOOL <B><A NAME="TransmitCharacter">TransmitCharacter</A></B>( char character_to_transmit )</PRE><DD>
Will interrupt the transmission of any buffered data and send
<CODE>character_to_transmit</CODE> immediately. This is kind of dangerous
to do.

<DT><PRE>BOOL <B><A NAME="WaitFor">WaitFor</A></B>( DWORD&amp; stuff_you_can_wait_for )</PRE><DD>
Stops execution of your thread until one of the events has occured. The 
<CODE>stuff_you_can_wait_for</CODE> parameter can be one of the following:

<UL>
<LI>waitBreakDetected
<LI>waitClearToSendChangedState
<LI>waitDataSetReadyChangedState
<LI>waitLineStatusError
<LI>waitRing
<LI>waitReceiveLineSignalDetectChangedState
<LI>waitAnyCharacterReceived
<LI>waitParticularCharacterReceived
<LI>waitTransmitBufferEmpty
</UL>

<DT><PRE>BOOL <B><A NAME="WaitForString">WaitForString</A></B>( const CString&amp; string_to_wait_for, DWORD timeout_seconds = 5, CString * what_was_read )</PRE><DD>
This handy dandy routine will wait
for a specified time for a specified string to come into the serial port.
It is good for dealing with text devices.

<DT><PRE>void <B><A NAME="Write">Write</A></B>( BYTE byte_to_write )
void <B>Write</B>( const CByteArray&amp; array_of_bytes )
void <B>Write</B>( CString&amp; string_to_write )
void <B>Write</B>( const void * buffer, UINT number_of_bytes )</PRE><DD>
Sends data to the serial port. You can send
data using a CString, CByteArray or plain old void pointer. Writing a single
BYTE differs from <B>TransmitCharacter</B>() in that writing the BYTE queues
the byte to be transmitted.
</DL>

<H2>Example</H2><PRE><CODE>void wait_for_ring( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;wait_for_ring()&quot; ) );

   <B>CSerialFile</B> serial;

   while( 1 )
   {
      _tprintf( TEXT( &quot;Opening serial port\n&quot; ) );

      if ( serial.Open( TEXT( &quot;COM1:57600,n,8,1&quot; ) ) != FALSE )
      {
         CString response;

         response = TEXT( &quot;ATM0\r\n&quot; );

         serial.Write( response );

         // See if the phone rang

         while ( serial.WaitForString( TEXT( &quot;RING&quot; ), 2, &amp;response ) == FALSE )
         {
            if ( response.GetLength() &gt; 0 )
            {
               _tprintf( TEXT( &quot;Didn't get RING, going to sleep \&quot;%s\&quot;\n&quot; ), (LPCTSTR) response );
            }

            Sleep( 10000 );
         }

         _tprintf( TEXT( &quot;Received a RING, waiting for them to end\n&quot; ) );

         while( serial.WaitForString( TEXT( &quot;RING&quot; ), 7 ) != FALSE )
         {
            // Do Nothing
         }

         _tprintf( TEXT( &quot;Closing serial port\n&quot; ) );

         serial.Close();

         CTime time_now( CTime::GetCurrentTime() );

         Sleep( 1000 );

         CString message;

         message.Format( TEXT( &quot;The phone rang at %s&quot; ), (LPCTSTR) time_now.Format( &quot;%H:%M:%S %d %b %y&quot; ) );

         CSprintSpectrum pager;

         pager.SetAccount( TEXT( &quot;4101234567&quot; ) );
         pager.SetMessage( message );

         _tprintf( TEXT( &quot;Calling pager.Send()\n&quot; ) );
         pager.Send();
      }
      else
      {
         _tprintf( TEXT( &quot;Can't open serial port\n&quot; ) );
      }

      Sleep( 1000 );
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CSerialFile</B> encapsulates the following API's:

<UL>
<LI>BuildCommDCB
<LI>ClearCommBreak
<LI>ClearCommError
<LI>CommConfigDialog
<LI>CreateFile
<LI>EscapeCommFunction
<LI>GetCommConfig
<LI>GetCommModemStatus
<LI>GetCommProperties
<LI>GetCommState
<LI>GetCommTimeouts
<LI>PurgeComm
<LI>SetCommBreak
<LI>SetCommConfig
<LI>SetCommMask
<LI>SetCommState
<LI>SetCommTimeouts
<LI>SetupComm
<LI>TransmitCommChar
<LI>WaitCommEvent
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: serial.cpp $<BR>
$Modtime: 3/17/00 4:46p $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CSerialFile=hFile=<m_hFile> name=<m_strFileName.m_pchData,s>
#endif
