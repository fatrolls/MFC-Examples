#if ! defined( NET_INFORMATION_CLASS_HEADER )

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
** $Workfile: cnetinfo.hpp $
** $Revision: 10 $
** $Modtime: 1/04/00 4:51a $
*/

#define NET_INFORMATION_CLASS_HEADER

class CNetworkInformation : public _NETINFOSTRUCT
{
   public:

      CNetworkInformation();
      CNetworkInformation( const NETINFOSTRUCT *source );
      CNetworkInformation( const CNetworkInformation& source );

      virtual ~CNetworkInformation();

      virtual void Copy( const NETINFOSTRUCT *source );
      virtual void Copy( const CNetworkInformation& source );
      virtual void Empty( void );
      virtual const CNetworkInformation& operator = ( const CNetworkInformation& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // NET_INFORMATION_CLASS_HEADER
