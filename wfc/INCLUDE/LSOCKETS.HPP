#if ! defined( LISTENING_SOCKET_CLASS_HEADER )

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
** $Workfile: lsockets.hpp $
** $Revision: 14 $
** $Modtime: 2/14/00 4:45a $
*/

#define LISTENING_SOCKET_CLASS_HEADER

class CListeningSocket : public CSimpleSocket
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CListeningSocket( const CListeningSocket& ) {};
      CListeningSocket& operator=( const CListeningSocket& ) { return( *this ); };

   private:

      int m_NumberOfSimultaneousSocketsToAllow;

      unsigned long m_BindToAddress;

      void m_Initialize( void );

   public:

      CListeningSocket();
      CListeningSocket( SOCKET client_id );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CListeningSocket();

      virtual void OnNewConnection( SOCKET socket_id, LPCTSTR host_name, LPCTSTR dotted_ip_address_string ) = 0; // Called by WaitForConnection
      virtual BOOL Open( void );

#if ! defined( WFC_STL )
      virtual BOOL Open( LPCTSTR channel_name, UINT port_number = 23, CFileException * perror = NULL );
#else // WFC_STL
      virtual BOOL Open( LPCTSTR channel_name, UINT port_number = 23 );
#endif // WFC_STL

      virtual BOOL WaitForConnection( LPCTSTR p_name );
      virtual BOOL WaitForConnection( const int p_number );
      virtual BOOL WaitForConnection( void );

      // 2000-02-13
      // Good additiion suggested by Scott Kolek (scott@skm-software.com)

      virtual void SetBindToAddress( unsigned long address = INADDR_ANY );
      virtual unsigned long GetBindToAddress( void ) const;

      virtual void SetConnectionBacklog( int backlog );
      virtual int  GetConnectionBacklog( void ) const;

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // LISTENING_SOCKET_CLASS_HEADER
