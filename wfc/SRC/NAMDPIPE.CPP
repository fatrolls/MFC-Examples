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
** $Workfile: namdpipe.cpp $
** $Revision: 23 $
** $Modtime: 3/17/00 4:39p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CNamedPipe::CNamedPipe( DWORD _input_buffer_size, DWORD _output_buffer_size )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::CNamedPipe()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize( _input_buffer_size, _output_buffer_size );
}

CNamedPipe::~CNamedPipe()
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::~CNamedPipe()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_AutomaticallyDelete != FALSE )
   {
      WFCTRACE( TEXT( "Automatically Deleting" ) );

      if ( m_PipeHandle != (HANDLE) NULL )
      {
         Close();
      }
   }

   if ( m_InputBuffer != (LPVOID) NULL )
   {
      WFCTRACE( TEXT( "Freeing input buffer" ) );

      /*
      ** Free our memory
      */

      delete [] m_InputBuffer;

      m_InputBuffer     = (LPVOID) NULL;
      m_InputBufferSize = 0L;
   }

   if ( m_OutputBuffer != (LPVOID) NULL )
   {
      WFCTRACE( TEXT( "Freeing output buffer" ) );

      /*
      ** Free our memory
      */

      delete [] m_OutputBuffer;

      m_OutputBuffer     = (LPVOID) NULL;
      m_OutputBufferSize = 0L;
   }
}

void CNamedPipe::m_Initialize( DWORD _input_buffer_size, DWORD _output_buffer_size )
{
   m_AutomaticallyDelete = TRUE;
   m_ErrorCode           = 0L;
   m_PipeHandle          = (HANDLE) INVALID_HANDLE_VALUE;
   m_Timeout             = NMPWAIT_USE_DEFAULT_WAIT;
   m_PipeName.Empty();

   m_InputBufferSize  = _input_buffer_size;
   m_OutputBufferSize = _output_buffer_size;

   try
   {
      m_InputBuffer = new BYTE[ m_InputBufferSize ];
   }
   catch( ... )
   {
      m_InputBuffer = NULL;
   }

   try
   {
      m_OutputBuffer = new BYTE[ m_OutputBufferSize ];
   }
   catch( ... )
   {
      m_OutputBuffer = NULL;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNamedPipe::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "m_AutomaticallyDelete = "      ) << m_AutomaticallyDelete      << TEXT( "\n" );
   dump_context << TEXT( "m_PipeHandle = "               ) << m_PipeHandle               << TEXT( "\n" );
   dump_context << TEXT( "m_MaximumNumberOfInstances = " ) << m_MaximumNumberOfInstances << TEXT( "\n" );
   dump_context << TEXT( "m_InputBufferSize = "          ) << m_InputBufferSize          << TEXT( "\n" );
   dump_context << TEXT( "m_OutputBufferSize = "         ) << m_OutputBufferSize         << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfBytesToWrite = "     ) << m_NumberOfBytesToWrite     << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfBytesRead = "        ) << m_NumberOfBytesRead        << TEXT( "\n" );
   dump_context << TEXT( "m_Timeout = "                  ) << m_Timeout                  << TEXT( "\n" );
   dump_context << TEXT( "m_PipeName = \""               ) << m_PipeName                 << TEXT( "\"\n" );
   dump_context << TEXT( "m_FullPipeName is " );
   m_FullPipeName.Dump( dump_context );
   dump_context << TEXT( "m_PipeState = "                ) << m_PipeState                << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfInstances = "        ) << m_NumberOfInstances        << TEXT( "\n" );
   dump_context << TEXT( "m_MaximumNumberOfBytesBeforeRemoteTransmission = "           ) << m_MaximumNumberOfBytesBeforeRemoteTransmission << TEXT( "\n" );
   dump_context << TEXT( "m_MaximumNumberOfMillisecondsBeforeRemoteTransmission = "    ) << m_MaximumNumberOfMillisecondsBeforeRemoteTransmission << TEXT( "\n" );
   dump_context << TEXT( "m_UserNameOfClientProcess = \"" ) << m_UserNameOfClientProcess << TEXT( "\"\n" );
}

#endif // _DEBUG

BOOL CNamedPipe::Call( CString& pipe_name, 
                       LPVOID   write_buffer, 
                       DWORD    size_of_write_buffer, 
                       LPVOID   read_buffer, 
                       DWORD    size_of_read_buffer, 
                       DWORD   *address_of_number_of_bytes_read,
                       DWORD    number_of_milliseconds_to_wait )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Call()" ) );

   ASSERT( write_buffer != NULL );
   ASSERT( read_buffer  != NULL );

   if ( write_buffer == NULL || read_buffer == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   /*
   ** Writes to the pipe then reads from it
   */

   BOOL return_value = FALSE;

   return_value = ::CallNamedPipe( pipe_name, 
                                   write_buffer,
                                   size_of_write_buffer,
                                   read_buffer,
                                   size_of_read_buffer,
                                   address_of_number_of_bytes_read,
                                   number_of_milliseconds_to_wait );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

void CNamedPipe::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Close()" ) );

   if ( m_PipeHandle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      ::wfc_close_handle( m_PipeHandle );
      m_PipeHandle = (HANDLE) INVALID_HANDLE_VALUE;
   }
}

BOOL CNamedPipe::Connect( LPOVERLAPPED overlapped_p )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Connect()" ) );

   // overlapped_p can be NULL

   BOOL return_value = FALSE;

   return_value = ::ConnectNamedPipe( m_PipeHandle, overlapped_p );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::Create( LPCTSTR server_name,
                         LPCTSTR pipe_name,
                         DWORD   open_mode,
                         DWORD   type_of_pipe,
                         DWORD   number_of_pipes,
           LPSECURITY_ATTRIBUTES security_attributes_p )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Create()" ) );

   ASSERT( pipe_name != NULL );

   /*
   ** Check parameters for errors
   */

   if ( pipe_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   m_PipeName = TEXT( "\\\\" );

   if ( server_name == NULL )
   {
      m_PipeName += TEXT( "." );
   }
   else
   {
      m_PipeName += server_name;
   }

   m_PipeName += TEXT( "\\PIPE\\" );
   m_PipeName += pipe_name;

   WFCTRACEVAL( TEXT( "pipe_name is " ), CString( pipe_name ) );

   CSecurityAttributes security_attributes;
   SECURITY_DESCRIPTOR security_descriptor;

   if ( security_attributes_p == NULL )
   {
      WFCTRACE( TEXT( "Creating security attributes" ) );

      ::InitializeSecurityDescriptor( &security_descriptor, SECURITY_DESCRIPTOR_REVISION );

      ::SetSecurityDescriptorDacl( &security_descriptor, TRUE, NULL, FALSE );
      security_attributes.bInheritHandle = FALSE;
      security_attributes.lpSecurityDescriptor = &security_descriptor;

      security_attributes_p = (SECURITY_ATTRIBUTES *) &security_attributes;
   }

   m_PipeHandle = ::CreateNamedPipe( m_PipeName,
                                     open_mode,
                                     type_of_pipe, 
                                     number_of_pipes,
                                     m_OutputBufferSize,
                                     m_InputBufferSize,
                                     m_Timeout,
                                     security_attributes_p );

   if ( m_PipeHandle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::Disconnect( void )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Disconnect()" ) );

   BOOL return_value = FALSE;

   return_value = ::DisconnectNamedPipe( m_PipeHandle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::GetInformation( void )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::GetInformation()" ) );

   BOOL return_value = FALSE;

   DWORD type_of_pipe                = 0;
   DWORD size_of_output_buffer       = 0;
   DWORD size_of_input_buffer        = 0;
   DWORD maximum_number_of_instances = 0;

   return_value = ::GetNamedPipeInfo( m_PipeHandle,
                                     &type_of_pipe,
                                     &size_of_output_buffer,
                                     &size_of_input_buffer,
                                     &maximum_number_of_instances );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::GetState( void )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::GetState()" ) );

   BOOL return_value = FALSE;

   TCHAR temp_string[ 513 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );

   return_value = ::GetNamedPipeHandleState( m_PipeHandle,
                                            &m_PipeState,
                                            &m_NumberOfInstances,
                                            &m_MaximumNumberOfBytesBeforeRemoteTransmission,
                                            &m_MaximumNumberOfMillisecondsBeforeRemoteTransmission,
                                             temp_string,
                                             DIMENSION_OF( temp_string ) );

   m_UserNameOfClientProcess = temp_string;

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

#if ! defined( WFC_STL )
BOOL CNamedPipe::Open( LPCTSTR pipe_name, UINT, CFileException * )
#else // WFC_STL
BOOL CNamedPipe::Open( LPCTSTR pipe_name, UINT )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Open()" ) );

   ASSERT( pipe_name != NULL );

   if ( pipe_name == (LPCTSTR) NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;

      return( FALSE );
   }

   /*
   ** pipe_name can be:
   ** "pipe_name" where the pipe will be openend on the local machine
   ** "\\server_name\pipe_name" where the pipe will be opened on the server
   ** "\\server_name\PIPE\pipe_name" which is a fully qualified pipe name
   */

   CUniversalNamingConvention unc( pipe_name );

   WFCTRACEVAL( TEXT( "unc is " ), CString( unc ) );

   if ( unc.ServerName.IsEmpty() != FALSE )
   {
      unc.ServerName = TEXT( "." );
   }

   if ( unc.ShareName.CompareNoCase( TEXT( "PIPE" ) ) != 0 )
   {
      CString temp_string = unc.ShareName;

      unc.ShareName = TEXT( "PIPE" );

      if ( temp_string.GetLength() > 0 )
      {
         unc.PathName = temp_string + TEXT( "\\" ) + unc.PathName;
      }
   }

   unc.Make();

   m_FullPipeName = unc;

   WFCTRACEVAL( TEXT( "Full Pipe Name is " ), CString( unc ) );

   return( Create( unc.ServerName, unc.PathName ) );
}

BOOL CNamedPipe::Peek( LPVOID buffer_address, 
                       DWORD  size_of_buffer,
                       DWORD& number_of_bytes_read,
                       DWORD& number_of_bytes_available,
                       DWORD& number_of_bytes_remaining_in_message )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Peek()" ) );

   /*
   ** buffer_address can be NULL
   */

   BOOL return_value = FALSE;

   return_value = ::PeekNamedPipe( m_PipeHandle, 
                                   buffer_address, 
                                   size_of_buffer, 
                                  &number_of_bytes_read,
                                  &number_of_bytes_available,
                                  &number_of_bytes_remaining_in_message );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::SetState( DWORD new_pipe_mode, 
                           DWORD maximum_number_of_bytes_before_transmission, 
                           DWORD maximum_number_of_milliseconds_before_transmission )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::SetState()" ) );

   BOOL return_value = FALSE;

   return_value = ::SetNamedPipeHandleState( m_PipeHandle,
                                            &new_pipe_mode,
                                            &maximum_number_of_bytes_before_transmission,
                                            &maximum_number_of_milliseconds_before_transmission );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::Transact( LPOVERLAPPED overlapped_p )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Transact()" ) );

   // overlapped_p can be NULL

   BOOL return_value = FALSE;

   return_value = ::TransactNamedPipe( m_PipeHandle,
                                       m_OutputBuffer,
                                       m_NumberOfBytesToWrite,
                                       m_InputBuffer,
                                       m_InputBufferSize,
                                      &m_NumberOfBytesRead,
                                       overlapped_p );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

BOOL CNamedPipe::Wait( LPCTSTR name_of_server, LPCTSTR name_of_pipe, DWORD number_of_milliseconds )
{
   WFCLTRACEINIT( TEXT( "CNamedPipe::Wait()" ) );

   ASSERT( name_of_pipe != NULL );

   /*
   ** Check parameters for errors
   */

   if ( name_of_pipe == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   BOOL return_value = FALSE;

   CString full_pipe_name( TEXT( "\\\\" ) ); // like \\servername\pipe\pipename

   if ( name_of_server == NULL )
   {
      full_pipe_name += TEXT( "." );
   }
   else
   {
      full_pipe_name += name_of_server;
   }

   full_pipe_name += TEXT( "\\pipe\\" );
   full_pipe_name += name_of_pipe;

   return_value = ::WaitNamedPipe( full_pipe_name, number_of_milliseconds );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "FAILED!" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }
   else
   {
      return( TRUE );
   }
}

// End of source
