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
** $Workfile: sockets.cpp $
** $Revision: 51 $
** $Modtime: 1/17/00 9:31a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

long CSimpleSocket::m_ReferenceCount = 0;
WFC_SOCKET_THUNK_P CSimpleSocket::m_Thunk_p = NULL;

static HANDLE inline _create_socket_thunk_mutex( void )
{
   WFCLTRACEINIT( TEXT( "_create_socket_thunk_mutex()" ) );

   // We need to create a mutex that *ANY* process on the system can
   // get a handle to regardless of security. To do this, we need to
   // create the mutex with a NULL DACL. Please read Knowledge Base
   // article Q106387

   LPCTSTR mutex_name = TEXT( "CSimpleSocketWinsockThunkInitializationMutex" );

   SECURITY_DESCRIPTOR * security_descriptor_p = (SECURITY_DESCRIPTOR *) NULL;

   security_descriptor_p = (SECURITY_DESCRIPTOR *) LocalAlloc( LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH );

   if ( security_descriptor_p == NULL )
   {
      // Oh well, hope for the best...
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Can't allocate memory for security descriptor." ) );
      return( CreateMutex( NULL, FALSE, mutex_name ) );
   }

   if ( InitializeSecurityDescriptor( security_descriptor_p,
                                      SECURITY_DESCRIPTOR_REVISION ) == FALSE )
   {
      // Oh well, hope for the best...
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Can't initialize security descriptor." ) );
      LocalFree( (HLOCAL) security_descriptor_p );
      return( CreateMutex( NULL, FALSE, mutex_name ) );
   }

   ASSERT( IsValidSecurityDescriptor( security_descriptor_p ) != FALSE );

   if ( IsValidSecurityDescriptor( security_descriptor_p ) == FALSE )
   {
      // Oh well, hope for the best...
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Invalid security descriptor just after creating it." ) );
      LocalFree( (HLOCAL) security_descriptor_p );
      return( CreateMutex( NULL, FALSE, mutex_name ) );
   }

   if ( SetSecurityDescriptorDacl( security_descriptor_p,
                                   TRUE,
                           (ACL *) NULL, // This is the "NULL DACL"
                                   FALSE ) == FALSE )
   {
      // Oh well, hope for the best...
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Can't set security descriptor DACL." ) );
      LocalFree( (HLOCAL) security_descriptor_p );
      return( CreateMutex( NULL, FALSE, mutex_name ) );
   }

   ASSERT( IsValidSecurityDescriptor( security_descriptor_p ) != FALSE );

   if ( IsValidSecurityDescriptor( security_descriptor_p ) == FALSE )
   {
      // Oh well, hope for the best...
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Invalid security descriptor just after setting NULL DACL." ) );
      LocalFree( (HLOCAL) security_descriptor_p );
      return( CreateMutex( NULL, FALSE, mutex_name ) );
   }

   SECURITY_ATTRIBUTES security_attributes;

   security_attributes.nLength              = sizeof( security_attributes );
   security_attributes.lpSecurityDescriptor = security_descriptor_p;
   security_attributes.bInheritHandle       = TRUE;

   HANDLE mutex_handle = NULL;
   
   mutex_handle = CreateMutex( &security_attributes, FALSE, mutex_name );

   if ( mutex_handle == NULL )
   {
      // Oh well, hope for the best...
      WFCTRACEERROR( GetLastError() );
      WFCTRACE( TEXT( "Can't create mutex with NULL DACL." ) );
      LocalFree( (HLOCAL) security_descriptor_p );
      return( CreateMutex( NULL, FALSE, mutex_name ) );
   }

   LocalFree( (HLOCAL) security_descriptor_p );

   return( mutex_handle );
}

CSimpleSocket::CSimpleSocket()
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::CSimpleSocket()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Initialize();

   if ( m_ReferenceCount == 0 )
   {
      HANDLE mutex_handle = _create_socket_thunk_mutex();

      if ( mutex_handle != NULL )
      {
         WFCTRACE( TEXT( "Mutex created." ) );

         // Try to take ownership of the mutex.
         // If you're wondering why I didn't use a critical section, it is
         // because of the olde chicken-or-the-egg problem. I can't create
         // a critical section because it must be created via InitializeCriticalSection().
         // There's no way (without changing the interface and breaking everyone's code)
         // to intialize one critical section by two threads executing simultaneously
         // (a feat not possible on single-CPU machines). With a mutex, when you "create"
         // one, you will get a handle to an existing mutex if it is already created.
         // This solves that problem but presents another. Since the mutex is named, it is
         // a system-wide mutex. That means another application using WFC's socket class
         // can block this application. What we really need is some serialization 
         // mechanism that is process-wide and named (something a little more than a
         // critical sectiona and a little less than a named mutex).

         if ( ::WaitForSingleObject( mutex_handle, INFINITE ) == WAIT_OBJECT_0 )
         {
            WFCTRACE( TEXT( "Protected code entered" ) );

            // We are now the only thread executing this section of the code

            if ( m_ReferenceCount == 0 )
            {
               // Yup. The thunk still needs to be initialized
               WFCTRACE( TEXT( "Starting sockets." ) );
               StartWindowsSockets();
            }
            else
            {
               WFCTRACE( TEXT( "Mutex acquired but not needed." ) );
            }

            m_ReferenceCount++;
            ::ReleaseMutex( mutex_handle );
            wfc_close_handle( mutex_handle );
            return;
         }
         else
         {
            WFCTRACE( TEXT( "Couldn't wait for single object." ) );
         }
         
         // We couldn't acquire the mutex

         wfc_close_handle( mutex_handle );
      }
      else
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Couldn't create mutex. This is very bad and should not happen." ) );

         StartWindowsSockets();
         m_ReferenceCount++;
         return;
      }
   }
   else
   {
      WFCTRACEVAL( TEXT( "Thunk initialization skipped because reference count is " ), m_ReferenceCount );
   }

   m_ReferenceCount++;
}

CSimpleSocket::CSimpleSocket( SOCKET socket_id )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::CSimpleSocket( SOCKET )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Initialize();

   if ( m_ReferenceCount == 0 )
   {
      HANDLE mutex_handle = _create_socket_thunk_mutex();

      if ( mutex_handle != NULL )
      {
         WFCTRACE( TEXT( "Mutex created." ) );

         // Try to take ownership of the mutex.
         // If you're wondering why I didn't use a critical section, it is
         // because of the olde chicken-or-the-egg problem. I can't create
         // a critical section because it must be created via InitializeCriticalSection().
         // There's no way (without changing the interface and breaking everyone's code)
         // to intialize one critical section by two threads executing simultaneously
         // (a feat not possible on single-CPU machines). With a mutex, when you "create"
         // one, you will get a handle to an existing mutex if it is already created.
         // This solves that problem but presents another. Since the mutex is named, it is
         // a system-wide mutex. That means another application using WFC's socket class
         // can block this application. What we really need is some serialization 
         // mechanism that is process-wide and named (something a little more than a
         // critical sectiona and a little less than a named mutex).

         if ( ::WaitForSingleObject( mutex_handle, INFINITE ) == WAIT_OBJECT_0 )
         {
            WFCTRACE( TEXT( "Protected code entered" ) );

            // We are now the only thread executing this section of the code

            if ( m_ReferenceCount == 0 )
            {
               // Yup. The thunk still needs to be initialized
               WFCTRACE( TEXT( "Starting sockets." ) );
               StartWindowsSockets();
            }
            else
            {
               WFCTRACE( TEXT( "Mutex acquired but not needed." ) );
            }

            m_ReferenceCount++;
            ::ReleaseMutex( mutex_handle );
            wfc_close_handle( mutex_handle );
            SetID( socket_id );
            return;
         }
         else
         {
            WFCTRACE( TEXT( "Couldn't wait for single object." ) );
         }
         
         // We couldn't acquire the mutex

         ::ReleaseMutex( mutex_handle );
         wfc_close_handle( mutex_handle );
      }
      else
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Couldn't create mutex. This is very bad and should not happen." ) );

         StartWindowsSockets();
         m_ReferenceCount++;
         SetID( socket_id );
         return;
      }
   }
   else
   {
      WFCTRACEVAL( TEXT( "Thunk initialization skipped because reference count is " ), m_ReferenceCount );
   }

   m_ReferenceCount++;

   SetID( socket_id );
}

CSimpleSocket::~CSimpleSocket()
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::~CSimpleSocket()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();

   m_ReferenceCount--;

   if ( m_ReferenceCount == 0 )
   {
      HANDLE mutex_handle = _create_socket_thunk_mutex();

      if ( mutex_handle != NULL )
      {
         if ( ::WaitForSingleObject( mutex_handle, INFINITE ) == WAIT_OBJECT_0 )
         {
            // We are now the only thread executing this section of the code

            if ( m_ReferenceCount == 0 )
            {
               // Yup. The thunk still needs to be initialized
               WFCTRACE( TEXT( "Stopping sockets." ) );
               StopWindowsSockets();
            }
            else
            {
               WFCTRACE( TEXT( "Mutex acquired but not needed." ) );
            }
         }

         ::ReleaseMutex( mutex_handle );
         wfc_close_handle( mutex_handle );
      }
      else
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Couldn't create mutex. This is very bad and should not happen." ) );

         StopWindowsSockets();
      }
   }
}

void CSimpleSocket::Close( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::Close()" ) );
   ASSERT( m_Thunk_p != NULL );

   if ( m_SocketID != INVALID_SOCKET )
   {
      WFCTRACE( TEXT( "Calling closesocket()" ) );

      // Darin Greaham (greaham@cyberramp.com) had a problem with a client
      // not reading data before closing the socket.
      // 1998-08-18

      m_Thunk_p->shutdown( m_SocketID, 1 ); // SD_SEND, don't allow any more sends

      // This should be a BYTE buffer but recv is mis-prototyped.
      char buffer[ 4096 ];

      int number_of_bytes_read = 1;

#if defined( _DEBUG )

      DWORD total_number_of_bytes_read = 0;

#endif // _DEBUG

      while( number_of_bytes_read > 0 && ( number_of_bytes_read != SOCKET_ERROR ) )
      {
         // Read the buffer 4Kb at a time.
         number_of_bytes_read = m_Thunk_p->recv( m_SocketID, buffer, sizeof( buffer ), 0 );

#if defined( _DEBUG )

         if ( number_of_bytes_read > 0 )
         {
            total_number_of_bytes_read += number_of_bytes_read;
         }

#endif // _DEBUG
      }

      WFCTRACEVAL( TEXT( "Read this many bytes before closing " ), total_number_of_bytes_read );

      m_Thunk_p->closesocket( m_SocketID );
      m_SocketID = INVALID_SOCKET;
      SetHandle( (HANDLE) CFile::hFileNull );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CSimpleSocket::Dump( CDumpContext &dump_context ) const
{
   CDummyFile::Dump( dump_context );

   dump_context << TEXT( "Address                        = \"" ) << Address    << TEXT( "\"\n" );
   dump_context << TEXT( "Name                           = \"" ) << Name       << TEXT( "\"\n" );
   dump_context << TEXT( "m_PortName                     = \"" ) << m_PortName << TEXT( "\"\n" );
   dump_context << TEXT( "m_PortNumberInNetworkByteOrder = "   ) << m_Thunk_p->ntohs( m_PortNumberInNetworkByteOrder ) << TEXT( "\n" );
   dump_context << TEXT( "m_SocketID                     = "   ) << m_SocketID       << TEXT( "\n" );
   dump_context << TEXT( "m_ReferenceCount               = "   ) << m_ReferenceCount << TEXT( "\n" );

   int loop_index        = 0;
   int number_of_aliases = AliasList.GetSize();

   dump_context << TEXT( "AliasList conains " ) << number_of_aliases << TEXT( " aliases.\n" );

   CString string;

   while( loop_index < number_of_aliases )
   {
      string = AliasList.GetAt( loop_index );
      dump_context << loop_index << TEXT( ". \"" ) << string << TEXT( "\"\n" );

      loop_index++;
   }
}

#endif // _DEBUG

void CSimpleSocket::GetAddress( CString& _address ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetAddress()" ) );

   _address = Address;
}

SOCKET CSimpleSocket::GetID( void ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetID()" ) );

   return( m_SocketID );
}

void CSimpleSocket::GetMyAddress( CString& ip_address )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetMyAddress()" ) );
   ip_address.Empty();

   BOOL i_started_winsock = FALSE;

   char my_name[ 4096 ];

   ZeroMemory( my_name, sizeof( my_name ) );

   int return_value = 0;

   DWORD error_code = 0;

   if ( m_Thunk_p == NULL )
   {
      m_InitializeThunk();
   }

   return_value = m_Thunk_p->gethostname( my_name, DIMENSION_OF( my_name ) );

   if ( return_value != 0 )
   {
      error_code = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( error_code );

      if ( error_code != WSANOTINITIALISED )
      {
         return;
      }

      // Let's start sockets

      StartWindowsSockets();

      i_started_winsock = TRUE;

      // Now let's retry the gethostname

      return_value = m_Thunk_p->gethostname( my_name, DIMENSION_OF( my_name ) );

      if ( return_value != 0 )
      {
         // Give up
         StopWindowsSockets();
         return;
      }
   }

   // We now have our name

   LPHOSTENT host_entry_p = (LPHOSTENT) NULL;

   host_entry_p = m_Thunk_p->gethostbyname( my_name );

   if ( host_entry_p == NULL )
   {
      if ( i_started_winsock != FALSE )
      {
         StopWindowsSockets();
      }

      // Give up

      return;
   }

   LPSTR dotted_ip_address = (LPSTR) NULL;

   /*
   ** You just gotta love the way Unix people thought . . . NOT!
   */

   struct in_addr internet_address;

   internet_address.S_un.S_un_b.s_b1 = host_entry_p->h_addr_list[ 0 ][ 0 ];
   internet_address.S_un.S_un_b.s_b2 = host_entry_p->h_addr_list[ 0 ][ 1 ];
   internet_address.S_un.S_un_b.s_b3 = host_entry_p->h_addr_list[ 0 ][ 2 ];
   internet_address.S_un.S_un_b.s_b4 = host_entry_p->h_addr_list[ 0 ][ 3 ];

   dotted_ip_address = m_Thunk_p->inet_ntoa( internet_address );

   if ( dotted_ip_address == (LPSTR) NULL )
   {
      if ( i_started_winsock != FALSE )
      {
         StopWindowsSockets();
      }

      return;
   }

#if defined( UNICODE )
   ::ASCII_to_UNICODE( dotted_ip_address, (LPWSTR) my_name );
   ip_address = (LPCWSTR) my_name;
#else
   ip_address = dotted_ip_address;
#endif // UNICODE

   if ( i_started_winsock != FALSE )
   {
      StopWindowsSockets();
   }
}

void CSimpleSocket::GetMyName( CString& host_name )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetMyName()" ) );

   host_name.Empty();

   BOOL i_started_winsock = FALSE;

   char my_name[ 4096 ];

   ZeroMemory( my_name, sizeof( my_name ) );

   int return_value = 0;

   DWORD error_code = 0;

   if ( m_Thunk_p == NULL )
   {
      m_InitializeThunk();
   }

   return_value = m_Thunk_p->gethostname( my_name, DIMENSION_OF( my_name ) );

   if ( return_value != 0 )
   {
      error_code = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( error_code );

      if ( error_code != WSANOTINITIALISED )
      {
         return;
      }

      // Let's start sockets

      StartWindowsSockets();

      i_started_winsock = TRUE;

      // Now let's retry the gethostname

      return_value = m_Thunk_p->gethostname( my_name, DIMENSION_OF( my_name ) );

      if ( return_value != 0 )
      {
         // Give up
         StopWindowsSockets();
         return;
      }
   }

   // We now have our name

#if defined( UNICODE )

   WCHAR temp_name[ 4096 ];
   ::ASCII_to_UNICODE( my_name, temp_name );
   host_name = temp_name;
#else
   host_name = my_name;
#endif // UNICODE

   if ( i_started_winsock != FALSE )
   {
      StopWindowsSockets();
   }
}

void CSimpleSocket::GetName( CString& _host_name ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetName()" ) );

   _host_name = Name;
}

DWORD CSimpleSocket::GetOptions( void ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetOptions()" ) );
   return( m_Options );
}

void CSimpleSocket::GetPort( short& _port_number ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetPort()" ) );

   _port_number = m_Thunk_p->ntohs( m_PortNumberInNetworkByteOrder );
}

void CSimpleSocket::GetPort( CString& _port_name ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetPort()" ) );

   _port_name = m_PortName;
}

TCHAR CSimpleSocket::GetStringReadTerminatorCharacter( void ) const
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::GetStringReadTerminatorCharacter()" ) );

   return( m_StringReadTerminatorCharacter );
}

BOOL CSimpleSocket::IsBroken( void ) const
{
   if ( m_SocketID == INVALID_SOCKET )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CSimpleSocket::IsDataWaiting( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::IsDataWaiting()" ) );
   ASSERT( m_Thunk_p != NULL );

   if ( m_SocketID == INVALID_SOCKET )
   {
      return( FALSE );
   }

   int bytes_for_this_socket = 0;
   int socket_status         = 0;

   FD_SET socket_in;

   TIMEVAL time_out;

   /*
   ** Initialize the data structures
   */

   FD_ZERO( (LPFD_SET) &socket_in );

   time_out.tv_sec  = 0;
   time_out.tv_usec = 0;

   /*
   ** Set socket_in to specify that we are looking for data on socket port_id
   */

   FD_SET( m_SocketID, (LPFD_SET) &socket_in );

   /*
   ** See if data is waiting
   */

   socket_status = m_Thunk_p->select( 0, &socket_in, NULL, NULL, &time_out );

   if ( socket_status == SOCKET_ERROR )
   {
      WFCTRACEVAL( TEXT( "Can't select() at line " ), __LINE__ );

      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   if ( socket_status == 0 )
   {
      /*
      ** No Data is waiting on any socket in the OS
      */

      return( FALSE );
   }

   /*
   ** Welp, data is waiting for *A* socket. It may not be *our* socket. A socket in the
   ** operating system has data waiting in it. Let's see if it happens to be *our* socket.
   */

   bytes_for_this_socket = m_Thunk_p->__WSAFDIsSet( m_SocketID, &socket_in );
   
   if ( bytes_for_this_socket == 0 )
   {
      /*
      ** There is data for a socket somewhere in the system but not for our socket
      */

      return( FALSE );
   }

   return( TRUE );
}

void CSimpleSocket::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::m_Initialize()" ) );

   /*
   ** Make sure everything is empty
   */

   m_PortNumberInNetworkByteOrder  = 0;
   m_SocketID                      = INVALID_SOCKET;
   SetHandle( (HANDLE) CFile::hFileNull );
   m_StringReadTerminatorCharacter = LINE_FEED;
   m_Options                       = optionsDefault;

   Address.Empty();
   Name.Empty();
   m_PortName.Empty();
   AliasList.RemoveAll();
}

#define WFC_LOAD_SOCKET_THUNK( dll_instance_handle, structure_pointer, function_name, thunk_function ) \
{\
   *( (FARPROC *) &structure_pointer->function_name ) = GetProcAddress( dll_instance_handle, #function_name );\
   if ( structure_pointer->function_name == NULL ) \
{\
   WFCTRACEVAL( TEXT( "Loading not-implemented thunk for " ), CString( #function_name ) ); \
   *( (FARPROC *) &structure_pointer->function_name ) = (FARPROC) thunk_function;\
}\
}

static SOCKET PASCAL FAR accept_thunk( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( INVALID_SOCKET );
}

static int PASCAL FAR generic_thunk( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( SOCKET_ERROR );
}

static u_long PASCAL FAR return_u_long_zero( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( 0 );
}

static u_short PASCAL FAR return_u_short_zero( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( 0 );
}

static void * PASCAL FAR return_NULL( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( NULL );
}

static unsigned long PASCAL FAR return_addr_none( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( INADDR_NONE );
}

static int PASCAL FAR return_not_implemented( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return( ERROR_CALL_NOT_IMPLEMENTED );
}

static void PASCAL FAR return_nothing( void )
{
   SetLastError( ERROR_CALL_NOT_IMPLEMENTED );
   return;
}

void CSimpleSocket::m_InitializeThunk( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::m_InitializeThunk()" ) );

   if ( m_Thunk_p != NULL )
   {
      WFCTRACE( TEXT( "Thunk layer already initialized." ) );
      return;
   }

   try
   {
      m_Thunk_p = new WFC_SOCKET_THUNK;
   }
   catch( ... )
   {
      m_Thunk_p = NULL;
   }

   if ( m_Thunk_p == NULL )
   {
      WFCTRACE( TEXT( "Can't allocate memory for thunk layer." ) );
      return;
   }

   ZeroMemory( m_Thunk_p, sizeof( WFC_SOCKET_THUNK ) );

   OSVERSIONINFO operating_system_version_information;

   ZeroMemory( &operating_system_version_information, sizeof( operating_system_version_information ) );
   operating_system_version_information.dwOSVersionInfoSize = sizeof( operating_system_version_information );

   if ( ::GetVersionEx( &operating_system_version_information ) != FALSE )
   {
      // Now figure out which Win32 we're running

      if ( operating_system_version_information.dwPlatformId == VER_PLATFORM_WIN32_NT )
      {
         // YIPPEE!! A real operating system!

         if ( operating_system_version_information.dwMajorVersion == 4 )
         {
            _tcsncpy( m_Thunk_p->dll_name, TEXT( "ws2_32.dll" ), DIMENSION_OF( m_Thunk_p->dll_name ) );
         }
         else
         {
            _tcsncpy( m_Thunk_p->dll_name, TEXT( "wsock32.dll" ), DIMENSION_OF( m_Thunk_p->dll_name ) );
         }
      }
      else if ( operating_system_version_information.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
      {
         // Piece of crap Windows95 garbage
         _tcsncpy( m_Thunk_p->dll_name, TEXT( "wsock32.dll" ), DIMENSION_OF( m_Thunk_p->dll_name ) );
      }
   }

   if ( _tcslen( m_Thunk_p->dll_name ) > 0 )
   {
      m_Thunk_p->dll_instance_handle = ::LoadLibrary( m_Thunk_p->dll_name );
   }

   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, accept, accept_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, bind, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, closesocket, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, connect, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, ioctlsocket, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getpeername, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getsockname, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getsockopt, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, htonl, return_u_long_zero );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, htons, return_u_short_zero );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, inet_addr, return_addr_none );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, inet_ntoa, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, listen, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, ntohl, return_u_long_zero );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, ntohs, return_u_short_zero );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, recv, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, recvfrom, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, select, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, send, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, sendto, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, setsockopt, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, shutdown, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, socket, accept_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, gethostbyaddr, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, gethostbyname, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, gethostname, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getservbyport, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getservbyname, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getprotobynumber, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, getprotobyname, return_NULL );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, WSAStartup, return_not_implemented );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, WSACleanup, generic_thunk );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, WSASetLastError, return_nothing );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, WSAGetLastError, return_not_implemented );
   WFC_LOAD_SOCKET_THUNK( m_Thunk_p->dll_instance_handle, m_Thunk_p, __WSAFDIsSet, return_u_long_zero );
}

UINT CSimpleSocket::Read( VOID *buffer, const int size_of_buffer )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::Read()" ) );

   ASSERT( m_Thunk_p != NULL );
   ASSERT( buffer != NULL );
   ASSERT( size_of_buffer > 0 );

   if ( buffer == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( 0 );
   }

   // We were passed a pointer, don't trust it . . .

   try
   {
      if ( m_SocketID != INVALID_SOCKET )
      {
         int number_of_bytes_read = 0;

         ::ZeroMemory( buffer, size_of_buffer );
   
         number_of_bytes_read = m_Thunk_p->recv( m_SocketID, (char *) buffer, size_of_buffer, 0 );
   
         if ( number_of_bytes_read == SOCKET_ERROR )
         {
            WFCTRACEVAL( TEXT( "Error in recv() at line " ), __LINE__ );

            m_ErrorCode = m_Thunk_p->WSAGetLastError();
            WFCTRACEERROR( m_ErrorCode );
            return( 0 );
         }
         else if ( number_of_bytes_read == 0 )
         {
            // Thanks to Angelini Fabio [fabioang@iol.it] for
            // finding a bug here. I was ignoring the ZERO case. OOPS!

            // The connection was gracefully closed.

            Close();
         }
      
         return( number_of_bytes_read );   
      }
      else
      {
         return( 0 );
      }
   }
   catch( ... )
   {
      return( 0 );
   }
}

void CSimpleSocket::Read( CString& line_to_read )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::Read( CString& line_to_read )" ) );
   ASSERT( m_Thunk_p != NULL );

   line_to_read.Empty(); // Always begin from a known state

   if ( m_SocketID != INVALID_SOCKET )
   {
      char character = 0;

      int number_of_bytes_read = 0;

      /*
      ** Thanks go to A. Mackay (eddie@tag.co.uk) for finding
      ** a stupidity point here. I was terminating a read on
      ** a carriage return, line feed or a NULL. This broke existing
      ** code. Now the string read terminator is user settable.
      */

      do
      {
         number_of_bytes_read = m_Thunk_p->recv( m_SocketID, &character, 1, 0 );

         if ( character != 0x00 )
         {
            if ( number_of_bytes_read == SOCKET_ERROR )
            {
               WFCTRACEVAL( TEXT( "Error in recv() at line " ), __LINE__ );

               m_ErrorCode = m_Thunk_p->WSAGetLastError();
               WFCTRACEERROR( m_ErrorCode );
               return;
            }

            line_to_read += (TCHAR) character;
         }
      }
      while( character != m_StringReadTerminatorCharacter &&
             character != 0x00 );
   }
}

void CSimpleSocket::SetAddress( LPCTSTR address_string )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetAddress()" ) );
   ASSERT( m_Thunk_p != NULL );

   /*
   ** Called when a client connects to us. This function also fills in the
   ** client's name for security checking.
   */

   ASSERT( address_string != NULL );

   Name.Empty();
   Address.Empty();
   AliasList.RemoveAll();

   if ( address_string == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      CString address;

      address = address_string;

      /*
      ** Address may contain "131.26.31.92" or "cheetah.sed.pobox.com"
      ** Given either, we must fill in host_name and IP_address
      */

      LPHOSTENT host_entry_p = (LPHOSTENT) NULL;

      /*
      ** See if it is in xxx.xxx.xxx.xxx form
      */

      int index = 0;

      BOOL exit_loop = FALSE;

      while( index < address.GetLength() && exit_loop == FALSE )
      {
         if ( address[ index ] != TEXT( '.' ) && ! _istdigit( address[ index ] ) )
         {
            /*
            ** The character is not a period and not a digit so it cannot meet the requirements
            ** of xxx.xxx.xxx.xxx type address and therefore must be a host name
            */

            exit_loop = TRUE;
         }
         else
         {
            index++;
         }
      }

      char ascii_address_string[ 4096 ];

      ZeroMemory( ascii_address_string, sizeof( ascii_address_string ) );

#if defined( UNICODE )

      UNICODE_to_ASCII( address, ascii_address_string );

#else

      strcpy( ascii_address_string, address );

#endif

      if ( exit_loop != FALSE ) // exit_loop is FALSE when we do not have a dotted IP address
      {
         /*
         ** Tech Note: You must cast the CString object to a const char * when using things like printf()
         */

         if ( ! ( m_Options & optionsDontResolveHostName ) )
         {
            host_entry_p = m_Thunk_p->gethostbyname( ascii_address_string );
         }
         else
         {
            host_entry_p = NULL;
         }
      }
      else
      {
         /*
         ** The string was an IP address in the form of "xxx.xxx.xxx.xxx"
         */

#if ! defined( UNICODE )
         Name    = ascii_address_string;
         Address = ascii_address_string;
#else
         {
            WCHAR unicode_address_string[ 512 ];

            ::ZeroMemory( unicode_address_string, sizeof( unicode_address_string ) );

            ::ASCII_to_UNICODE( ascii_address_string, unicode_address_string );

            Name    = unicode_address_string;
            Address = unicode_address_string;
         }
#endif

         if ( ! ( m_Options & optionsDontResolveHostName ) )
         {
            ULONG internet_address = 0L;

            internet_address = m_Thunk_p->inet_addr( ascii_address_string );
            host_entry_p = m_Thunk_p->gethostbyaddr( (const char *) &internet_address, 4, PF_INET );
         }
      }

      if ( host_entry_p == (LPHOSTENT) NULL )
      {
         WFCTRACEVAL( TEXT( "gethostbyxxx() failed at line " ), __LINE__ );

         m_ErrorCode = m_Thunk_p->WSAGetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return;
      }

      if ( exit_loop == FALSE )
      {
         Address = address;
      }
      else
      {
         LPSTR dotted_ip_address = (LPSTR) NULL;

         /*
         ** You just gotta love the way Unix people thought . . . NOT!
         */

         struct in_addr internet_address;

         internet_address.S_un.S_un_b.s_b1 = host_entry_p->h_addr_list[ 0 ][ 0 ];
         internet_address.S_un.S_un_b.s_b2 = host_entry_p->h_addr_list[ 0 ][ 1 ];
         internet_address.S_un.S_un_b.s_b3 = host_entry_p->h_addr_list[ 0 ][ 2 ];
         internet_address.S_un.S_un_b.s_b4 = host_entry_p->h_addr_list[ 0 ][ 3 ];

         dotted_ip_address = m_Thunk_p->inet_ntoa( internet_address );

         if ( dotted_ip_address == (LPSTR) NULL )
         {
            return;
         }

         Address.Empty();

         index = 0;

         while( dotted_ip_address[ index ] != 0x00 )
         {
            Address += (TCHAR) dotted_ip_address[ index ];
            index++;
         }

         WFCTRACEVAL( TEXT( "ip_address == " ), Address );
      }

      /*
      ** We don't call set_name() because that function will call this function and we'll go into an endless loop
      */

      Name = host_entry_p->h_name;

      /*
      ** Now lets get the aliases for this fella
      */

      AliasList.RemoveAll();

      index = 0;

      CString new_string;

      int index_2 = 0;

      while( host_entry_p->h_aliases[ index ] != (char *) NULL )
      {
         index_2 = 0;
         new_string.Empty();

         while( host_entry_p->h_aliases[ index ][ index_2 ] != 0x00 )
         {
            new_string += (TCHAR) host_entry_p->h_aliases[ index ][ index_2 ];
            index_2++;
         }

         AliasList.Add( new_string );
         index++;
      }
   }
   catch( ... )
   {
      ; // Do Nothing
   }
}

void CSimpleSocket::SetID( const SOCKET id )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetID()" ) );

   if ( m_SocketID != INVALID_SOCKET )
   {
      Close();
   }

   m_SocketID = id;
   SetHandle( (HANDLE) id );
}

void CSimpleSocket::SetName( LPCTSTR host_string )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetName()" ) );
   ASSERT( host_string != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      if ( host_string == NULL )
      {
         Name.Empty();
      }
      else
      {
         Name = host_string;
      }
   }
   catch( ... )
   {
      Name.Empty();
   }
}

void CSimpleSocket::SetOptions( DWORD new_options )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetOptions()" ) );

   m_Options = new_options;
}

void CSimpleSocket::SetPort( LPCTSTR name_string )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetPort( const char *name_string )" ) );

   ASSERT( m_Thunk_p != NULL );
   ASSERT( name_string != NULL );

   if ( name_string == NULL )
   {
      m_PortName.Empty();
      m_PortNumberInNetworkByteOrder = 0;
      return;
   }

   CString name;

   // We were passed a pointer, don't trust it

   try
   {
      // Let's see if the user passed us a number as a string

      int number_value = _ttoi( name_string );

      if ( number_value != 0 )
      {
         // Well whaddya know, they sent us a number disguised as a string

         SetPort( (short) number_value );
         return;
      }

      name = name_string;

      /*
      ** Although not documented anywhere, the name of the protocol must be in lower case
      ** If you look in the data file for getservbyname() [winnt/system32/drivers/etc/services]
      ** you will notice that everything is in lower case. Gotta love Unix . . .
      */

      name.MakeLower();

      /*
      ** This routine sets port_name and m_PortNumberInNetworkByteOrder
      */

      LPSERVENT service_entry_p = (LPSERVENT) NULL;

#if defined( UNICODE )

      char ascii_name_string[ 1024 ];

      ::ZeroMemory( ascii_name_string, sizeof( ascii_name_string ) );

      ::UNICODE_to_ASCII( name, ascii_name_string );

      service_entry_p = m_Thunk_p->getservbyname( ascii_name_string, NULL );

#else

      service_entry_p = m_Thunk_p->getservbyname( name, NULL );

#endif

      if ( service_entry_p == (LPSERVENT) NULL )
      {
         m_ErrorCode = m_Thunk_p->WSAGetLastError();

         WFCTRACEVAL( TEXT( "getservbyname() failed at line " ), __LINE__ );
         WFCTRACEERROR( m_ErrorCode );

         return;
      }

      m_PortName = name;
      m_PortNumberInNetworkByteOrder = service_entry_p->s_port;
   }
   catch( ... )
   {
      return;
   }
}

void CSimpleSocket::SetPort( const short p )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetPort( const short p )" ) );
   ASSERT( m_Thunk_p != NULL );

   /*
   ** This routine sets port_name and m_PortNumberInNetworkByteOrder
   */

   m_PortNumberInNetworkByteOrder = m_Thunk_p->htons( p );

   /*
   ** Now go find a name for this port . . .
   */

   LPSERVENT service_entry_p = (LPSERVENT) NULL;

   service_entry_p = m_Thunk_p->getservbyport( m_PortNumberInNetworkByteOrder, NULL );

   if ( service_entry_p == (LPSERVENT) NULL )
   {
      WFCTRACEVAL( TEXT( "getservbyport() failed at line " ), __LINE__ );

      m_ErrorCode = m_Thunk_p->WSAGetLastError();

#if defined( _DEBUG )

      TCHAR error_message[ MAX_PATH ];

      TranslateErrorCode( m_ErrorCode, error_message, DIMENSION_OF( error_message ) );

      WFCTRACEVAL( TEXT( "Error was " ), CString( error_message ) );

#endif // _DEBUG

      m_PortName.Format( TEXT( "Port #%d" ), (int) p );
      return;
   }

   m_PortName = service_entry_p->s_name;
}

BOOL CSimpleSocket::SetSocketOption( int level, int option_name, const char * option_value, int option_length )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetSocketOption()" ) );
   ASSERT( m_Thunk_p != NULL );

   if ( m_Thunk_p == NULL )
   {
      WFCTRACE( TEXT( "Thunk not yet initialized." ) );
      return( FALSE );
   }

   // One popular mistake with using setsockopt is to use BOOL types like the
   // documentation seems to say. What they really mean is "address of a BOOL"

   ASSERT( option_value != (const char *) 0 );
   ASSERT( option_value != (const char *) 1 );

   // We were passed a pointer, don't trust it

   try
   {
      if ( m_Thunk_p->setsockopt( m_SocketID, level, option_name, option_value, option_length ) == SOCKET_ERROR )
      {
         m_ErrorCode = m_Thunk_p->WSAGetLastError();
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }

   return( TRUE );
}

void CSimpleSocket::SetStringReadTerminatorCharacter( TCHAR terminator )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::SetStringReadTerminator()" ) );

   m_StringReadTerminatorCharacter = terminator;
}

void __stdcall CSimpleSocket::StartWindowsSockets( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::StartWindowsSockets()" ) );

   m_InitializeThunk();

   /*
   ** Start WINSOCK
   */

   WSADATA winsock_data;

   int socket_error = 0;

   WORD desired_winsock_version = 0x0101; // We'd like WINSOCK v1.1 at least

   BYTE major_version_required = 0;
   BYTE minor_version_required = 0;

   ::ZeroMemory( &winsock_data, sizeof( winsock_data ) );

   socket_error = m_Thunk_p->WSAStartup( desired_winsock_version, (LPWSADATA) &winsock_data );

   if ( socket_error != 0 )
   {
      //WFCTRACE( TEXT( "WSAStartup failed with an error code of %d at line %d of %s\n" ), socket_error, __LINE__, __FILE__ );
      return;
   }

   major_version_required = HIBYTE( desired_winsock_version );
   minor_version_required = LOBYTE( desired_winsock_version );

   if ( (   LOBYTE( winsock_data.wVersion ) <  major_version_required ) ||
        (   LOBYTE( winsock_data.wVersion ) == major_version_required ) &&
        ( ( HIBYTE( winsock_data.wVersion ) <  minor_version_required ) ) )
   {
      WFCTRACE( TEXT( "Need a later version of Winsock" ) );
   }
}

void __stdcall CSimpleSocket::StopWindowsSockets( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::StopWindowsSockets()" ) );
   
   if ( m_Thunk_p != NULL )
   {
      m_Thunk_p->WSACleanup();

      if ( m_Thunk_p->dll_instance_handle != NULL )
      {
         ::FreeLibrary( m_Thunk_p->dll_instance_handle );
      }

      ZeroMemory( m_Thunk_p, sizeof( WFC_SOCKET_THUNK ) );
      delete m_Thunk_p;
      m_Thunk_p = NULL;
   }
}

void __stdcall CSimpleSocket::TranslateErrorCode( DWORD error_code, LPTSTR destination_string, DWORD size_of_destination_string )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::TranslateErrorCode()" ) );

   // We were passed a pointer, don't trust it

   try
   {
   switch( error_code )
   {
      /*
      ** Following are Windows Sockets Library errors
      */

      case WSAENOTSOCK:

        _tcsncpy( destination_string, TEXT( "WSAENOTSOCK, Socket operation on non-socket. A socket created in one process is used by another process." ), size_of_destination_string );
        return;

      case WSAEDESTADDRREQ:

        _tcsncpy( destination_string, TEXT( "WSAEDESTADDRREQ, Destination address required." ), size_of_destination_string );
        return;

      case WSAEMSGSIZE:

        _tcsncpy( destination_string, TEXT( "WSAEMSGSIZE, Message too long." ), size_of_destination_string );
        return;

      case WSAEPROTOTYPE:

        _tcsncpy( destination_string, TEXT( "WSAEPROTOTYPE, Protocol wrong type for socket." ), size_of_destination_string );
        return;

      case WSAENOPROTOOPT:

        _tcsncpy( destination_string, TEXT( "WSAENOPROTOOPT, Protocol not available." ), size_of_destination_string );
        return;

      case WSAEPROTONOSUPPORT:

        _tcsncpy( destination_string, TEXT( "WSAEPROTONOSUPPORT, Protocol not supported." ), size_of_destination_string );
        return;

      case WSAESOCKTNOSUPPORT:

        _tcsncpy( destination_string, TEXT( "WSAESOCKTNOSUPPORT, Socket type not supported." ), size_of_destination_string );
        return;

      case WSAEOPNOTSUPP:

        _tcsncpy( destination_string, TEXT( "WSAEOPNOTSUPP, Operation not supported on socket." ), size_of_destination_string );
        return;

      case WSAEPFNOSUPPORT:

        _tcsncpy( destination_string, TEXT( "WSAEPFNOSUPPORT, Protocol family not supported." ), size_of_destination_string );
        return;

      case WSAEAFNOSUPPORT:

        _tcsncpy( destination_string, TEXT( "WSEAFNOSUPPORT, Address family not supported by protocol family." ), size_of_destination_string );
        return;

      case WSAEADDRINUSE:

        _tcsncpy( destination_string, TEXT( "WSAEADDRINUSE, Triggered by bind() because a process went down without closing a socket." ), size_of_destination_string );
        return;

      case WSAEADDRNOTAVAIL:

        _tcsncpy( destination_string, TEXT( "WSAEADDRNOTAVAIL, Can't assign requested address." ), size_of_destination_string );
        return;

      case WSAENETDOWN:

        _tcsncpy( destination_string, TEXT( "WSAENETDOWN, Network is down." ), size_of_destination_string );
        return;

      case WSAENETUNREACH:

        _tcsncpy( destination_string, TEXT( "WSAENETUNREACH, Network is unreachable." ), size_of_destination_string );
        return;

      case WSAENETRESET:

        _tcsncpy( destination_string, TEXT( "WSAENETRESET, Network dropped connection or reset." ), size_of_destination_string );
        return;

      case WSAECONNABORTED:

        _tcsncpy( destination_string, TEXT( "WSAECONNABORTED, Software caused connection abort." ), size_of_destination_string );
        return;

      case WSAECONNRESET:

        _tcsncpy( destination_string, TEXT( "WSAECONNRESET, Connection reset by peer." ), size_of_destination_string );
        return;

      case WSAENOBUFS:

        _tcsncpy( destination_string, TEXT( "WSAENOBUFS, No buffer space available." ), size_of_destination_string );
        return;

      case WSAEISCONN:

        _tcsncpy( destination_string, TEXT( "WSAEISCONN, Socket is already connected." ), size_of_destination_string );
        return;

      case WSAENOTCONN:

        _tcsncpy( destination_string, TEXT( "WSAENOTCONN, Socket is not connected." ), size_of_destination_string );
        return;

      case WSAESHUTDOWN:

        _tcsncpy( destination_string, TEXT( "WSAESHUTDOWN, Can't send after socket shutdown." ), size_of_destination_string );
        return;

      case WSAETIMEDOUT:

        _tcsncpy( destination_string, TEXT( "WSAETIMEDOUT, Connection timed out." ), size_of_destination_string );
        return;

      case WSAECONNREFUSED:

        _tcsncpy( destination_string, TEXT( "WSAECONNREFUSED, Connection refused." ), size_of_destination_string );
        return;

      case WSAEHOSTDOWN:

        _tcsncpy( destination_string, TEXT( "WSAEHOSTDOWN, Networking subsystem not started." ), size_of_destination_string );
        return;

      case WSAEHOSTUNREACH:

        _tcsncpy( destination_string, TEXT( "WSAEHOSTUNREACH, No route to host." ), size_of_destination_string );
        return;

      case WSAEWOULDBLOCK:

        _tcsncpy( destination_string, TEXT( "WSAEWOULDBLOCK, Operation would block." ), size_of_destination_string );
        return;

      case WSAEINPROGRESS:

        _tcsncpy( destination_string, TEXT( "WSAEINPROGRESS, Operation now in progress." ), size_of_destination_string );
        return;

      case WSAEALREADY:

        _tcsncpy( destination_string, TEXT( "WSAEALREADY, Operation already in progress." ), size_of_destination_string );
        return;

      case WSAEINTR:

        _tcsncpy( destination_string, TEXT( "WSAEALREADY, Operation was interrupted." ), size_of_destination_string );
        return;

      case WSAEBADF:

        _tcsncpy( destination_string, TEXT( "WSAEBADF, Bad file number." ), size_of_destination_string );
        return;

      case WSAEACCES:

        _tcsncpy( destination_string, TEXT( "WSAEACCES, Access is denied." ), size_of_destination_string );
        return;

      case WSAEFAULT:

        _tcsncpy( destination_string, TEXT( "WSAEFAULT, Bad memory address." ), size_of_destination_string );
        return;

      case WSAEINVAL:

        _tcsncpy( destination_string, TEXT( "WSAEINVAL, The socket has not been bound with bind() or is already connected." ), size_of_destination_string );
        return;

      case WSAEMFILE:

        _tcsncpy( destination_string, TEXT( "WSAEMFILE, No more file descriptors are available." ), size_of_destination_string );
        return;

      case WSAETOOMANYREFS:

        _tcsncpy( destination_string, TEXT( "WSAETOOMANYREFS, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAENAMETOOLONG:

        _tcsncpy( destination_string, TEXT( "WSAENAMETOOLONG, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAENOTEMPTY:

        _tcsncpy( destination_string, TEXT( "WSAENOTEMPTY, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAEPROCLIM:

        _tcsncpy( destination_string, TEXT( "WSAEPROCLIM, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAEUSERS:

        _tcsncpy( destination_string, TEXT( "WSAEUSERS, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAEDQUOT:

        _tcsncpy( destination_string, TEXT( "WSAEDQUOT, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAESTALE:

        _tcsncpy( destination_string, TEXT( "WSAESTALE, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAEREMOTE:

        _tcsncpy( destination_string, TEXT( "WSAEREMOTE, Undocumented WinSock error." ), size_of_destination_string );
        return;

      case WSAEDISCON:

        _tcsncpy( destination_string, TEXT( "WSAEDISCON, Circuit was gracefully terminated." ), size_of_destination_string );
        return;

      case WSASYSNOTREADY:

        _tcsncpy( destination_string, TEXT( "WSASYSNOTREADY, The underlying network subsystem is not ready for network communication." ), size_of_destination_string );
        return;

      case WSAVERNOTSUPPORTED:

        _tcsncpy( destination_string, TEXT( "WSAVERNOTSUPPORTED, The version of Windows Sockets API support requested is not provided by this particular Windows Sockets implementation." ), size_of_destination_string );
        return;

      case WSANOTINITIALISED:

        _tcsncpy( destination_string, TEXT( "WSANOTINITIALISED, WSAStartup() has not been called." ), size_of_destination_string );
        return;

      case WSAHOST_NOT_FOUND:

        _tcsncpy( destination_string, TEXT( "WSAHOST_NOT_FOUND, Authoritative answer host not found." ), size_of_destination_string );
        return;

      case WSATRY_AGAIN:

        _tcsncpy( destination_string, TEXT( "WSATRY_AGAIN, Non-authoritative answer host not found or SERVERFAIL." ), size_of_destination_string );
        return;

      case WSANO_RECOVERY:

        _tcsncpy( destination_string, TEXT( "WSANO_RECOVERY, Non recoverable errors, FORMERR, REFUSED, NOTIMP." ), size_of_destination_string );
        return;

      case WSANO_DATA:

        _tcsncpy( destination_string, TEXT( "WSANO_DATA or WSANO_ADDRESS, Valid name, no data record of requested type." ), size_of_destination_string );
        return;

      case WSABASEERR + 1005:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_RECEIVERS, at least one Reserve has arrived." ), size_of_destination_string );
        return;

      case WSABASEERR + 1006:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_SENDERS, at least one Path has arrived." ), size_of_destination_string );
        return;

      case WSABASEERR + 1007:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_NO_SENDERS, there are no senders." ), size_of_destination_string );
        return;

      case WSABASEERR + 1008:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_NO_RECEIVERS, there are no receivers." ), size_of_destination_string );
        return;

      case WSABASEERR + 1009:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_REQUEST_CONFIRMED, Reserve has been confirmed." ), size_of_destination_string );
        return;

      case WSABASEERR + 1010:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_ADMISSION_FAILURE, error due to lack of resources." ), size_of_destination_string );
        return;

      case WSABASEERR + 1011:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_POLICY_FAILURE, rejected for administrative reasons - bad credentials." ), size_of_destination_string );
        return;

      case WSABASEERR + 1012:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_BAD_STYLE, unknown or conflicting style." ), size_of_destination_string );
        return;

      case WSABASEERR + 1013:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_BAD_OBJECT, problem with some part of the filterspec or provider specific buffer in general." ), size_of_destination_string );
        return;

      case WSABASEERR + 1014:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_TRAFFIC_CTRL_ERROR, problem with some part of the flowspec." ), size_of_destination_string );
        return;

      case WSABASEERR + 1015:

        _tcsncpy( destination_string, TEXT( "WSA_QOS_GENERIC_ERROR, general error." ), size_of_destination_string );
        return;

      default:

         {
            TCHAR message_string[ 129 ];

            if ( error_code >= WSABASEERR )
            {
               _stprintf( (LPTSTR) message_string, (LPCTSTR) TEXT( "Unknown WinSock Error Number %d (WSABASEERR + %d)" ), error_code, error_code - WSABASEERR );
            }
            else
            {
               _stprintf( (LPTSTR) message_string, (LPCTSTR) TEXT( "Unknown WinSock Error Number %d" ), error_code );
            }

            _tcsncpy( destination_string, message_string, size_of_destination_string );
         }

         return;
   }
   }
   catch( ... )
   {
      return;
   }
}

#if defined( TF_DISCONNECT )

BOOL CSimpleSocket::Transmit( CFile& file_to_send, DWORD flags, CByteArray * send_before, CByteArray * send_after )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::Transmit()" ) );

   // We were passed a pointer, don't trust it

   try
   {
      TRANSMIT_FILE_BUFFERS transmit_file_buffers;

      ::ZeroMemory( &transmit_file_buffers, sizeof( transmit_file_buffers ) );

      TRANSMIT_FILE_BUFFERS *buffers_p = (TRANSMIT_FILE_BUFFERS *) NULL;

      if ( send_before != NULL )
      {
         buffers_p                        = &transmit_file_buffers;
         transmit_file_buffers.Head       = (PVOID) send_before->GetData();
         transmit_file_buffers.HeadLength = send_before->GetSize();
      }

      if ( send_after != NULL )
      {
         buffers_p                        = &transmit_file_buffers;
         transmit_file_buffers.Tail       = (PVOID) send_after->GetData();
         transmit_file_buffers.TailLength = send_after->GetSize();
      }

      BOOL return_value = m_Thunk_p->TransmitFile( m_SocketID, 
                                          (HANDLE) file_to_send.m_hFile,
                                          0,
                                          0,
                                          NULL,
                                          buffers_p,
                                          flags );

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
   catch( ... )
   {
      return( FALSE );
   }
}

#endif // TF_DISCONNECT

void CSimpleSocket::Write( const VOID *buffer, const long number_of_bytes_to_write )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::Write()" ) );

   ASSERT( m_Thunk_p != NULL );
   ASSERT( buffer != NULL );
   ASSERT( number_of_bytes_to_write > 0L );

   // We were passed a pointer, don't trust it

   try
   {
      if ( buffer == NULL )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return;
      }

      if ( m_SocketID == INVALID_SOCKET )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return;
      }

      BYTE *byte_buffer = (BYTE *) NULL;

      byte_buffer = (BYTE *) buffer;

      if ( byte_buffer == (BYTE *) NULL )
      {
         m_ErrorCode = ERROR_INVALID_ADDRESS;
         return;
      }

      /*
      ** Loop until the bytes are sent or until we give up
      */

      BOOL bytes_were_sent = FALSE;

      int number_of_bytes_sent = 0;
      int loop_count           = 0;

      while( bytes_were_sent == FALSE && loop_count < 100 )
      {
         number_of_bytes_sent = m_Thunk_p->send( m_SocketID, (const char *) byte_buffer, number_of_bytes_to_write, 0 );

         if ( number_of_bytes_sent == SOCKET_ERROR )
         {
            m_ErrorCode = m_Thunk_p->WSAGetLastError();
            WFCTRACEERROR( m_ErrorCode );

#if defined( _DEBUG )

            TCHAR temp_string[ 513 ];

            ::ZeroMemory( temp_string, sizeof( temp_string ) );

            TranslateErrorCode( m_ErrorCode, temp_string, DIMENSION_OF( temp_string ) );

            WFCTRACEVAL( TEXT( "Error: " ), CString( temp_string ) );

#endif // _DEBUG

            if ( m_ErrorCode != WSAENOBUFS && m_ErrorCode != WSAEINPROGRESS )
            {
               if ( m_ErrorCode == WSAENOTCONN  ||
                    m_ErrorCode == WSAENETRESET ||
                    m_ErrorCode == WSAESHUTDOWN )
               {
                  /*
                  ** Someone hung up on us or unplugged our lan cable
                  */

                  m_SocketID = INVALID_SOCKET;
                  SetHandle( (HANDLE) CFile::hFileNull );
               }

               return;
            }
            else
            {
               loop_count++;
            }
         }
         else
         {
            bytes_were_sent = TRUE;
         }
      }
   }
   catch( ... )
   {
      return;
   }
}

void CSimpleSocket::Write( const CString& string_to_write )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocket::Write( const CString& string_to_write )" ) );
   ASSERT( m_Thunk_p != NULL );

   CString temp_string;

   temp_string = string_to_write;

   // Thanks go to zschen (zschen@ms.chttl.com.tw) for finding a bug here.
   // I wasn't sending the trailing NULL to the socket. DOH!

   Write( (LPCTSTR) temp_string, temp_string.GetLength() + 1 );
}

#pragma warning( default : 4100 )

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CSimpleSocket</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that encapsulates TCP/IP socket I/O.">
</HEAD>

<BODY>

<H1>CSimpleSocket : <A HREF="DumyFile.htm">CDummyFile</A></H1>
$Revision: 51 $
<HR>

<H2>Description</H2>

This class is inherited from <B><A HREF="DumyFile.htm">CDummyFile</A></B>. When I first saw the socket API, it seemed to be
the fruit of a weird, twisted mind. Then I remembered sockets came from the Unix world. No one ever accused of Unix being 
straightforward. With this in mind I wrote <B>CSimpleSocket</B> to try to bring some sanity to sockets. There are two parts
to a socket. The IP address and a port number.

<H2>Data Members</H2>

<B>Address</B> - The &quotdotted&quot IP address. Example: &quot20.2.1.3&quot<P>
<B>Name</B> - The name of the machine. This will be empty if the address has no name.<P>
<B>AliasList</B> - This contains the alternate names for the IP address. Some machines have
multiple names.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the socket.

<DT><PRE>void <B>GetAddress</B>( CString&amp; dotted_ip_address_string ) const</PRE><DD>
Retrieves the <B>Address</B> data member.

<DT><PRE>SOCKET <B>GetID</B>( void ) const</PRE><DD>
Retrieves the Socket ID so you can call the socket API directly.

<DT><PRE>void <B>GetMyAddress</B>( CString&amp; dotted_ip_address_string )</PRE><DD>
Retrieves your IP address.

<DT><PRE>void <B>GetMyName</B>( CString&amp; machine_name )</PRE><DD>
Retrieves your IP host name.

<DT><PRE>void <B>GetName</B>( CString&amp; host_name ) const</PRE><DD>
Retrieves the <B>Name</B> data member.

<DT><PRE>void <B>GetPort</B>( short&amp; port_number ) const
void <B>GetPort</B>( CString&amp; port_name ) const</PRE><DD>
Retrieves the port number or port name of this socket. For example,
if you have a telnet socket (i.e. port number 23), <B>GetPort</B> will
return 23 in <CODE>port_number</CODE> and &quot;telnet&quot;
in <CODE>port_name</CODE>. If no name can be found for the port number,
<CODE>port_name</CODE> will be filled with a string representation of
the port number.

<DT><PRE>TCHAR <B>GetStringReadTerminatorCharacter</B>( void ) const</PRE><DD>
Returns the character that will cause a <B>Read</B>() to terminate when
reading a <B>CString</B>.

<DT><PRE>BOOL <B>IsDataWaiting</B>( void  )</PRE><DD>
Returns TRUE if there are bytes waiting to be <B>Read</B>().

<DT><PRE>BOOL <B>Open</B>( void ) = 0
BOOL <B>Open</B>( const char * machine_name_or_address, UINT port_number = 23, CFileException * = NULL ) = 0</PRE><DD>
Pure virtual function that opens the socket. You have to implement these functions.

<DT><PRE>void <B>Read</B>( CString&amp; line_to_read )
UINT <B>Read</B>( VOID * buffer, const int maximum_number_of_bytes_to_read )</PRE><DD>
Pulls data out of the socket. If you are reading a string, the character
set by <B>SetStringReadTerminatorCharacter</B>()
will terminate the read. A NULL (character zero) will always terminate
a string read.

<DT><PRE>void <B>SetAddress</B>( const char * address )</PRE><DD>
This sets the <B>Address</B>, <B>Name</B> and <B>AliasList</B>
data members. You use either a &quotdotted&quot IP address or a machine name, <B>SetAddress</B> will
figure out what you mean.

<DT><PRE>void <B>SetID</B>( const SOCKET socket_id )</PRE><DD>
Use this function if you've created a socket using the native socket
API and want to play with it via <B>CSimpleSocket</B>. It does not set 
any of the address/name members. If the class is allready being used to play
with an existing socket, it will be closed before the <CODE>socket_id</CODE>
is attached.

<DT><PRE>void <B>SetName</B>( const char * machine_name )</PRE><DD>
Simply sets the <B>Name</B> member.

<DT><PRE>void <B>SetPort</B>( const short port_number )
void <B>SetPort</B>( const char * port_name )</PRE><DD>
Sets the port number and name.

<DT><PRE>void <B>SetStringReadTerminatorCharacter</B>( TCHAR character )</PRE><DD>
Sets the character that will terminate a string <B>Read</B>().
A NULL (character zero) will always terminate a string read.

<DT><PRE>void <B>StartWindowsSockets</B>( void )</PRE><DD>
Starts sockets.
It is not recommended that you call this function. <B>CSimpleSocket</B>
will call it as needed.

<DT><PRE>void <B>StopWindowsSockets</B>( void )</PRE><DD>
Stops sockets.
It is not recommended that you call this function. <B>CSimpleSocket</B>
will call it as needed.

<DT><PRE>void <B>TranslateErrorCode</B>( DWORD error_code, LPSTR destination_string, DWORD size_of_string )</PRE><DD>
Did you ever wonder what 10014 means? This function translates a socket
error code into something humanly readable.

<DT><PRE>BOOL <B>Transmit</B>( CFile&amp; file_to_send, DWORD flags = TF_DISCONNECT, CByteArray * send_before = NULL, CByteArray * send_after )</PRE><DD>
Will transmit the <CODE>file_to_send</CODE> down the socket. If you want to
send some bytes before the file, set <CODE>send_before</CODE> to the address
of a CByteArray. If you want some bytes sent after the file, set <CODE>send_after</CODE>
to the address of a CByteArray. Read up on the TransmitFile() API for a
discussion of the <CODE>flags</CODE> parameter.

<DT><PRE>void <B>Write</B>( const CString&amp; string_to_write )
void <B>Write</B>( const VOID * buffer, const long number_of_bytes_to_write )</PRE><DD>
Sends data out of the socket.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

int close_the_socket( <B>CSimpleSocket</B>&amp; the_socket )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;close_the_socket()&quot; ) );

   the_socket.Close();

   // OK, this is a really lame sample but the class
   // is pure virtual!
}</CODE></PRE>
<H2>API's Used</H2>

<B>CSimpleSocket</B> uses the following API's:
<UL>
<LI>closesocket
<LI>CreateMutex
<LI>FD_ISSET
<LI>FD_SET
<LI>FD_ZERO
<LI>FreeLibrary
<LI>gethostbyname
<LI>gethostbyaddr
<LI>gethostname
<LI>GetLastError
<LI>GetProcAddress
<LI>getservbyname
<LI>getservbyport
<LI>GetVersionEx
<LI>htons
<LI>inet_ntoa
<LI>InitializeSecurityDescriptor
<LI>IsValidSecurityDescriptor
<LI>LoadLibrary
<LI>LocalAlloc
<LI>LocalFree
<LI>ntohs
<LI>recv
<LI>ReleaseMutex
<LI>select
<LI>send
<LI>SetSecurityDescriptorDacl
<LI>TransmitFile
<LI>WaitForSingleObject
<LI>WSACleanup
<LI>WSAStartup
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: sockets.cpp $<BR>
$Modtime: 1/17/00 9:31a $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CSimpleSocket=hFile=<m_hFile> name=<m_strFileName.m_pchData,s>
#endif
