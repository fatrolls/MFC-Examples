#if ! defined( SOCKET_CLASS_HEADER )

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
** $Workfile: sockets.hpp $
** $Revision: 18 $
** $Modtime: 1/04/00 5:00a $
*/

#define SOCKET_CLASS_HEADER

typedef struct _wfc_socket_thunk
{
   HINSTANCE dll_instance_handle;
   TCHAR     dll_name[ MAX_PATH ];
   SOCKET                 (PASCAL FAR * accept)(SOCKET , struct sockaddr FAR *, int FAR *);
   int                    (PASCAL FAR * bind)(SOCKET , const struct sockaddr FAR *, int );
   int                    (PASCAL FAR * closesocket)(SOCKET );
   int                    (PASCAL FAR * connect)(SOCKET , const struct sockaddr FAR *, int );
   int                    (PASCAL FAR * ioctlsocket)( SOCKET, long , u_long FAR * );
   int                    (PASCAL FAR * getpeername)( SOCKET, struct sockaddr FAR *, int FAR * );
   int                    (PASCAL FAR * getsockname)( SOCKET, struct sockaddr FAR *, int FAR * );
   int                    (PASCAL FAR * getsockopt)( SOCKET, int, int, char FAR *, int FAR * );
   u_long                 (PASCAL FAR * htonl)( u_long );
   u_short                (PASCAL FAR * htons)( u_short );
   unsigned long          (PASCAL FAR * inet_addr)( const char FAR * );
   char FAR *             (PASCAL FAR * inet_ntoa)( struct in_addr );
   int                    (PASCAL FAR * listen)( SOCKET, int );
   u_long                 (PASCAL FAR * ntohl)( u_long );
   u_short                (PASCAL FAR * ntohs)( u_short );
   int                    (PASCAL FAR * recv)( SOCKET, char FAR *, int, int );
   int                    (PASCAL FAR * recvfrom)( SOCKET, char FAR *, int, int, struct sockaddr FAR *, int FAR * );
   int                    (PASCAL FAR * select)( int , fd_set FAR *, fd_set FAR *, struct fd_set FAR *, const struct timeval FAR * );
   int                    (PASCAL FAR * send)( SOCKET, const char FAR *, int, int );
   int                    (PASCAL FAR * sendto)( SOCKET, const char FAR *, int, int, const struct  FAR *, int );
   int                    (PASCAL FAR * setsockopt)( SOCKET, int, int, const char FAR *, int );
   int                    (PASCAL FAR * shutdown)( SOCKET, int );
   SOCKET                 (PASCAL FAR * socket)( int, int, int );
   struct hostent FAR *   (PASCAL FAR * gethostbyaddr)( const char FAR *, int, int );
   struct hostent FAR *   (PASCAL FAR * gethostbyname)( const char FAR * );
   int                    (PASCAL FAR * gethostname)( char FAR *, int );
   struct servent FAR *   (PASCAL FAR * getservbyport)( int port, const char FAR * );
   struct servent FAR *   (PASCAL FAR * getservbyname)( const char FAR *, const char FAR * );
   struct protoent FAR *  (PASCAL FAR * getprotobynumber)( int );
   struct protoent FAR *  (PASCAL FAR * getprotobyname)( const char FAR * );
   int                    (PASCAL FAR * WSAStartup)( WORD, LPWSADATA );
   int                    (PASCAL FAR * WSACleanup)( void );
   void                   (PASCAL FAR * WSASetLastError)( int );
   int                    (PASCAL FAR * WSAGetLastError)( void );
   BOOL                   (PASCAL FAR * WSAIsBlocking)( void );
   int                    (PASCAL FAR * WSAUnhookBlockingHook)( void );
   FARPROC                (PASCAL FAR * WSASetBlockingHook)( FARPROC );
   int                    (PASCAL FAR * WSACancelBlockingCall)( void );
   HANDLE                 (PASCAL FAR * WSAAsyncGetServByName)( HWND, u_int , const char FAR *, const char FAR *, char FAR *, int );
   HANDLE                 (PASCAL FAR * WSAAsyncGetServByPort)( HWND, u_int , int port, const char FAR *, char FAR *, int );
   HANDLE                 (PASCAL FAR * WSAAsyncGetProtoByName)( HWND, u_int, const char FAR *, char FAR *, int );
   HANDLE                 (PASCAL FAR * WSAAsyncGetProtoByNumber)( HWND, u_int, int number, char FAR *, int );
   HANDLE                 (PASCAL FAR * WSAAsyncGetHostByName)( HWND, u_int, const char FAR *, char FAR *, int );
   HANDLE                 (PASCAL FAR * WSAAsyncGetHostByAddr)( HWND, u_int, const char FAR *, int, int, char FAR *, int );
   int                    (PASCAL FAR * WSACancelAsyncRequest)( HANDLE );
   int                    (PASCAL FAR * WSAAsyncSelect)(SOCKET, HWND, u_int, long );
   int                    (PASCAL FAR * WSARecvEx)(SOCKET, char FAR *, int, int FAR * );
   BOOL                   (PASCAL FAR * TransmitFile)( SOCKET, HANDLE, DWORD,  DWORD, LPOVERLAPPED, LPTRANSMIT_FILE_BUFFERS, DWORD );
   BOOL                   (PASCAL FAR * AcceptEx)( SOCKET, SOCKET, PVOID, DWORD, DWORD, DWORD, LPDWORD, LPOVERLAPPED );
   VOID                   (PASCAL FAR * GetAcceptExSockaddrs)( PVOID, DWORD, DWORD, DWORD, struct sockaddr **, LPINT, struct sockaddr **, LPINT );
   int                    (PASCAL FAR * __WSAFDIsSet)(SOCKET, fd_set FAR * );
}
WFC_SOCKET_THUNK, *WFC_SOCKET_THUNK_P;

class CSimpleSocket : public CDummyFile
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CSimpleSocket( const CSimpleSocket& ) {};
      CSimpleSocket& operator=( const CSimpleSocket& ) { return( *this ); };

   private:

      void m_Initialize( void );
      static void m_InitializeThunk( void );

   protected:

      CString m_PortName;

      short m_PortNumberInNetworkByteOrder;

      SOCKET m_SocketID;

      TCHAR m_StringReadTerminatorCharacter;

      DWORD m_Options;

      static long m_ReferenceCount;

      static WFC_SOCKET_THUNK_P m_Thunk_p;

   public:

      enum _Options
      {
         optionsDefault             = 0x00000000,
         optionsDontResolveHostName = 0x00000001
      };

      /*
      ** Construction
      */

      CSimpleSocket();
      CSimpleSocket( SOCKET client_id );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CSimpleSocket();

      CString      Address; 
      CString      Name;
      CStringArray AliasList; // Pointers to CString's

      static void __stdcall GetMyAddress( CString& dotted_ip_address );
      static void __stdcall GetMyName( CString& machine_name );
      static void __stdcall StartWindowsSockets( void );
      static void __stdcall StopWindowsSockets( void );
      static void __stdcall TranslateErrorCode( DWORD error_code, LPTSTR destination_string, DWORD size_of_destination_string );

      /*
      ** Getting data from the object
      */

      virtual void   GetAddress( CString& a ) const;
      virtual SOCKET GetID( void ) const;
      virtual void   GetName( CString& a ) const;
      virtual void   GetPort( short& p ) const;
      virtual void   GetPort( CString& p ) const;
      virtual TCHAR  GetStringReadTerminatorCharacter( void ) const;

      /*
      ** Putting data into the object
      */

      virtual void SetAddress( LPCTSTR a ); // Fills in Address, Name and AliasList
      virtual void SetID( const SOCKET id );
      virtual void SetName( LPCTSTR a );
      virtual void SetPort( LPCTSTR p );
      virtual void SetPort( const short p );
      virtual void SetStringReadTerminatorCharacter( TCHAR terminator );

      /*
      ** Misc Functions
      */

      virtual BOOL Open( void ) = 0;

#if ! defined( WFC_STL )
      virtual BOOL Open( LPCTSTR channel_name, UINT port_number = 23, CFileException* pError = NULL ) = 0;
#else // WFC_STL
      virtual BOOL Open( LPCTSTR channel_name, UINT port_number = 23 ) = 0;
#endif // WFC_STL

      virtual void Close( void );
      virtual DWORD GetOptions( void ) const;
      virtual BOOL IsBroken( void ) const;
      virtual BOOL IsDataWaiting( void );
      virtual void SetOptions( DWORD new_options );
      virtual BOOL SetSocketOption( int level, int option_name, const char * option_value, int option_length );

      // Not all versions of Visual C++ have TF_DISCONNECT defined

#if defined( TF_DISCONNECT )

      virtual BOOL Transmit( CFile& file_to_send, DWORD flags = TF_DISCONNECT, CByteArray* send_before = NULL, CByteArray* send_after = NULL );

#endif // TF_DISCONNECT

      virtual void Write( const CString& data_to_write );
      virtual void Write( const VOID *buffer, const long number_of_bytes_to_write );

      virtual UINT Read( VOID *buffer, const int max_bytes );
      virtual void Read( CString& line_to_read );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dc ) const;

#endif // _DEBUG
};

#endif // SOCKET_CLASS_HEADER
