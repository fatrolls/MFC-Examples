#if ! defined( REMOTE_ACCESS_SERVICE_ADMINISTRATION_CLASS_HEADER )

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
** $Workfile: CRASADM.HPP $
** $Revision: 7 $
** $Modtime: 1/04/00 4:54a $
*/

#define REMOTE_ACCESS_SERVICE_ADMINISTRATION_CLASS_HEADER

#if _MSC_VER >= 1020

class CRemoteAccessServiceAdministration
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CRemoteAccessServiceAdministration( const CRemoteAccessServiceAdministration& ) {};
      CRemoteAccessServiceAdministration& operator=( const CRemoteAccessServiceAdministration& ) { return( *this ); };

   protected:

      RAS_PORT_0 *m_PortArray;

      WORD m_TotalNumberOfEntries;
      WORD m_CurrentEntryNumber;

      UINT m_ErrorCode;

      virtual void m_Initialize( void );

   public:

      CRemoteAccessServiceAdministration();

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceAdministration();

      virtual void  GetErrorString( const UINT error_code, CString& error_string ) const;
      virtual DWORD GetErrorCode( void ) const;
      virtual BOOL  GetUserAccountServer( CString& user_account_server_name, LPCTSTR ras_server_name, LPCTSTR ras_server_domain_name = NULL );
      virtual BOOL  ClearPortStatistics( const CString& port_name, LPCTSTR server_name = NULL ); // Default to this machine
      virtual BOOL  DisconnectPort( const CString& port_name, LPCTSTR server_name = NULL ); // RasAdminPortDisconnect
      virtual BOOL  EnumeratePorts( LPCTSTR server_name = NULL ); // RasAdminPortEnum
      virtual BOOL  GetNext( CRemoteAccessServicePort& port );
      //virtual BOOL  GetInformation( CRemoteAccessServicePort& port ); // RasAdminPortGetInfo
      //virtual BOOL  GetInformation(); // RasAdminServerGetInfo
      //virtual BOOL  GetInformation(); // RasAdminUserGetInfo
      //virtual BOOL  SetInformation(); // RasAdminUserSetInfo

      //virtual BOOL  AcceptNewConnection(); // RasAdminAcceptNewConnection
      //virtual BOOL  ConnectionHangupNotification(); // RasAdminConnectionHandgupNotification
      //virtual BOOL  GetIPAddressForUser(); // RasAdminGetIpAddressForUser
      //virtual BOOL  ReleaseIPAddress(); // RasAdminReleaseIpAddress

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // _MSC_VER

#endif // REMOTE_ACCESS_SERVICE_ADMINISTRATION_CLASS_HEADER
