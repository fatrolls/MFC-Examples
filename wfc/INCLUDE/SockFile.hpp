#if ! defined( SIMPLE_SOCKET_FILE_CLASS_HEADER )

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
** $Workfile: sockfile.hpp $
** $Revision: 10 $
** $Modtime: 1/06/00 4:01p $
*/

#define SIMPLE_SOCKET_FILE_CLASS_HEADER

class CSimpleSocketFile : public CSimpleSocket
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CSimpleSocketFile( const CSimpleSocketFile& ) {};
      CSimpleSocketFile& operator=( const CSimpleSocketFile& ) { return( *this ); };

   public:

      CSimpleSocketFile( SOCKET client_id, LPCTSTR host_name, LPCTSTR dotted_ip_address_string );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CSimpleSocketFile();

      virtual BOOL Open( void );

#if ! defined( WFC_STL )
      virtual BOOL Open( LPCTSTR channel_name, UINT port_number = 23, CFileException* pError = NULL );
#else // WFC_STL
      virtual BOOL Open( LPCTSTR channel_name, UINT port_number = 23 );
#endif // WFC_STL
};

#endif // SIMPLE_SOCKET_FILE_CLASS_HEADER
