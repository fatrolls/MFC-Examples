#if ! defined( NET_RESOURCE_CLASS_HEADER )

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
** $Workfile: cnetrsrc.hpp $
** $Revision: 11 $
** $Modtime: 1/04/00 4:51a $
*/

#define NET_RESOURCE_CLASS_HEADER

class CNetworkResourceInformation
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetworkResourceInformation )
#endif // WFC_NO_SERIALIZATION

   private:

      void m_Initialize( void );

   public:

      CNetworkResourceInformation();
      CNetworkResourceInformation( const NETRESOURCE *source );
      CNetworkResourceInformation( const CNetworkResourceInformation& source );

      virtual ~CNetworkResourceInformation();

      /*
      ** Patterned after NETRESOURCE
      */

      CString   LocalName;
      CString   RemoteName;
      CString   Comment;
      CString   Provider;
      DWORD     Scope;
      DWORD     Type;
      DWORD     DisplayType;
      DWORD     Usage;

      virtual void Copy( const NETRESOURCE *source );
      virtual void Copy( const CNetworkResourceInformation& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
};

class CNetworkResources : public CNetwork
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_DYNAMIC( CNetworkResources )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetworkResources( const CNetworkResources& ) {};
      CNetworkResources& operator=( const CNetworkResources& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      HANDLE m_ResumeHandle;

      NETRESOURCE m_NetResource;

   public:

      enum Scope {
                    scopeConnected  = RESOURCE_CONNECTED,
                    scopeAll        = RESOURCE_GLOBALNET,
                    scopePersistent = RESOURCE_REMEMBERED,
                    scopeRecent     = RESOURCE_RECENT,
                    scopeContext    = RESOURCE_CONTEXT
                 };

      enum Type  {
                    typeAny      = RESOURCETYPE_ANY,
                    typeDisk     = RESOURCETYPE_DISK,
                    typePrint    = RESOURCETYPE_PRINT,
                    typeReserved = RESOURCETYPE_RESERVED,
                    typeUnknown  = RESOURCETYPE_UNKNOWN
                 };

      enum Usage {
                    usageAll           = RESOURCEUSAGE_ALL,
                    usageConnectable   = RESOURCEUSAGE_CONNECTABLE,
                    usageContainer     = RESOURCEUSAGE_CONTAINER,
                    usageNoLocalDevice = RESOURCEUSAGE_NOLOCALDEVICE,
                    usageSibling       = RESOURCEUSAGE_SIBLING,
                    usageAttached      = RESOURCEUSAGE_ATTACHED,
                    usageReserved      = RESOURCEUSAGE_RESERVED
                 };

      CNetworkResources();
      CNetworkResources( LPCTSTR machine_name );
      virtual ~CNetworkResources();

      virtual BOOL Enumerate( CNetworkResourceInformation& information );
      virtual BOOL GetNext( CNetworkResourceInformation& information );
};

#endif // NET_RESOURCE_CLASS_HEADER
