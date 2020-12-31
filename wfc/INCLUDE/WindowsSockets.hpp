#if ! defined( WINDOWS_SOCKETS_WRAPPER_CLASS_HEADER )

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
** Copyright, 1999, Samuel R. Blackburn
**
** $Workfile: WindowsSockets.hpp $
** $Revision: 4 $
** $Modtime: 9/11/99 5:34a $
*/

#define WINDOWS_SOCKETS_WRAPPER_CLASS_HEADER

class CWindowsSockets
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CWindowsSockets( const CWindowsSockets& ) {};
      CWindowsSockets& operator=( const CWindowsSockets& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      CString m_PortName;

      short m_PortNumberInNetworkByteOrder;

      SOCKET m_SocketID;

      TCHAR m_StringReadTerminatorCharacter;

      static long m_ReferenceCount;

   public:

      CWindowsSockets();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CWindowsSockets();

      // These are here to isolate the differences between all the different
      // implementations of WinSock.

      int bind( SOCKET s, const struct sockaddr FAR *addr, int namelen );
      int closesocket( SOCKET s );
      struct hostent * gethostbyaddr( const char * addr, int len, int type );
      struct hostent * gethostbyname( const char FAR * name );

      FD_ISSET();
      gethostname();
      getservbyname();
      getservbyport();
      htons();
      inet_addr();
      inet_ntoa();
      ntohs();
      recv();
      select();
      send();
      shutdown();
      TransmitFile();

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dc ) const;

#endif // _DEBUG
};

#endif // WINDOWS_SOCKETS_WRAPPER_CLASS_HEADER
