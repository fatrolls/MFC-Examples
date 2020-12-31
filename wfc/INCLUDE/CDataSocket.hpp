#if ! defined( DATA_SOCKET_CLASS_HEADER )

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
** $Workfile: CDataSocket.hpp $
** $Revision: 4 $
** $Modtime: 1/04/00 4:41a $
*/

#define DATA_SOCKET_CLASS_HEADER

class CDataSocket : public CDataFile
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CDataSocket( const CDataSocket& ) {};
      CDataSocket& operator=( const CDataSocket& ) { return( *this ); };

   protected:

      CSimpleSocket * m_Socket_p;

   public:

      CDataSocket();
      CDataSocket( CSimpleSocket * socket_p );
      virtual ~CDataSocket();

      virtual void Attach( CSimpleSocket * socket_p );
      virtual UINT Read( void * buffer, UINT number_of_bytes_to_read );
      virtual long Seek( long offset, UINT from );
      virtual void Write( const void * buffer, UINT number_of_bytes_to_write );
};

#endif // DATA_SOCKET_CLASS_HEADER
