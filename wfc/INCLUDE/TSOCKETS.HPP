#if ! defined( TALKING_SOCKET_CLASS_HEADER )

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
** $Workfile: tsockets.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 5:01a $
*/

#define TALKING_SOCKET_CLASS_HEADER

class CTalkingSocket : public CSimpleSocket
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CTalkingSocket( const CTalkingSocket& ) {};
      CTalkingSocket& operator=( const CTalkingSocket& ) { return( *this ); };

   private:

      void m_Initialize( void );

   public:

      CTalkingSocket();
      CTalkingSocket( const CString& address, const short p );
      CTalkingSocket( const CString& host, const CString& p );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CTalkingSocket();

      virtual BOOL Open( void );
      virtual BOOL Open( const CString& address, const CString& port_name );
      virtual BOOL Open( const CString& address, const short p_number );

#if ! defined( WFC_STL )
      virtual BOOL Open( LPCTSTR name, UINT port_number = 23, CFileException* perror = NULL );
#else // WFC_STL
      virtual BOOL Open( LPCTSTR name, UINT port_number = 23 );
#endif // WFC_STL

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dc ) const;

#endif // _DEBUG
};

#endif // TALKING_SOCKET_CLASS_HEADER
