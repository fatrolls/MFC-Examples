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
** $Workfile: sockfile.cpp $
** $Revision: 13 $
** $Modtime: 1/08/00 9:36a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CSimpleSocketFile::CSimpleSocketFile( SOCKET client_id, LPCTSTR name, LPCTSTR dotted_ip_address )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocketFile::CSimpleSocketFile()" ) );

   m_SocketID = client_id;
   m_hFile    = client_id;

   if ( name == NULL )
   {
      Name.Empty();
   }
   else
   {
      Name = name;
   }

   if ( dotted_ip_address == NULL )
   {
      Address.Empty();
   }
   else
   {
      Address = dotted_ip_address;
   }

   // The filename should be the host name followed by IP address then port number.
   // Example: "Sammy (195.99.72.1)"

#if ! defined( WFC_STL )
   m_strFileName.Format( TEXT( "%s (%s)" ), (LPCTSTR) Name, (LPCTSTR) Address );
#else // WFC_STL
   m_FileName.Format( TEXT( "%s (%s)" ), (LPCTSTR) Name, (LPCTSTR) Address );
#endif // WFC_STL
}

CSimpleSocketFile::~CSimpleSocketFile()
{
   WFCLTRACEINIT( TEXT( "CSimpleSocketFile::~CSimpleSocketFile()" ) );
   Close();
}

BOOL CSimpleSocketFile::Open( void )
{
   WFCLTRACEINIT( TEXT( "CSimpleSocketFile::Open( void )" ) );
   return( TRUE );
}

#pragma warning( disable : 4100 )

#if ! defined( WFC_STL )
BOOL CSimpleSocketFile::Open( LPCTSTR name, UINT port, CFileException *perror )
#else // WFC_STL
BOOL CSimpleSocketFile::Open( LPCTSTR name, UINT port )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CSimpleSocketFile::Open()" ) );
   return( TRUE );
}

#pragma warning( default : 4100 )

// End of source
