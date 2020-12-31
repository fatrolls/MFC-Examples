#if ! defined( REMOTE_ACCESS_SERVICE_CLASS_HEADER )

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
** $Workfile: cras.hpp $
** $Revision: 17 $
** $Modtime: 1/04/00 4:52a $
*/

#define REMOTE_ACCESS_SERVICE_CLASS_HEADER

typedef struct _WFC_RAS_THUNK
{
   HINSTANCE dll_instance_handle;
   TCHAR     dll_name[ MAX_PATH ];
   DWORD (APIENTRY * RasDialA)( LPRASDIALEXTENSIONS, LPSTR, LPRASDIALPARAMSA, DWORD, LPVOID, LPHRASCONN );
   DWORD (APIENTRY * RasDialW)( LPRASDIALEXTENSIONS, LPWSTR, LPRASDIALPARAMSW, DWORD, LPVOID, LPHRASCONN );
   DWORD (APIENTRY * RasEnumConnectionsA)( LPRASCONNA, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasEnumConnectionsW)( LPRASCONNW, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasEnumEntriesA)( LPSTR, LPSTR, LPRASENTRYNAMEA, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasEnumEntriesW)( LPWSTR, LPWSTR, LPRASENTRYNAMEW, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasGetConnectStatusA)( HRASCONN, LPRASCONNSTATUSA );
   DWORD (APIENTRY * RasGetConnectStatusW)( HRASCONN, LPRASCONNSTATUSW );
   DWORD (APIENTRY * RasGetErrorStringA)( UINT, LPSTR, DWORD );
   DWORD (APIENTRY * RasGetErrorStringW)( UINT, LPWSTR, DWORD );
   DWORD (APIENTRY * RasHangUpA)( HRASCONN );
   DWORD (APIENTRY * RasHangUpW)( HRASCONN );
   DWORD (APIENTRY * RasGetProjectionInfoA)( HRASCONN, RASPROJECTION, LPVOID, LPDWORD );
   DWORD (APIENTRY * RasGetProjectionInfoW)( HRASCONN, RASPROJECTION, LPVOID, LPDWORD );
   DWORD (APIENTRY * RasCreatePhonebookEntryA)( HWND, LPSTR );
   DWORD (APIENTRY * RasCreatePhonebookEntryW)( HWND, LPWSTR );
   DWORD (APIENTRY * RasEditPhonebookEntryA)( HWND, LPSTR, LPSTR );
   DWORD (APIENTRY * RasEditPhonebookEntryW)( HWND, LPWSTR, LPWSTR );
   DWORD (APIENTRY * RasSetEntryDialParamsA)( LPSTR, LPRASDIALPARAMSA, BOOL );
   DWORD (APIENTRY * RasSetEntryDialParamsW)( LPWSTR, LPRASDIALPARAMSW, BOOL );
   DWORD (APIENTRY * RasGetEntryDialParamsA)( LPSTR, LPRASDIALPARAMSA, LPBOOL );
   DWORD (APIENTRY * RasGetEntryDialParamsW)( LPWSTR, LPRASDIALPARAMSW, LPBOOL );
   DWORD (APIENTRY * RasEnumDevicesA)( LPRASDEVINFOA, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasEnumDevicesW)( LPRASDEVINFOW, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasGetCountryInfoA)( LPRASCTRYINFOA, LPDWORD );
   DWORD (APIENTRY * RasGetCountryInfoW)( LPRASCTRYINFOW, LPDWORD );
   DWORD (APIENTRY * RasGetEntryPropertiesA)( LPSTR, LPSTR, LPRASENTRYA, LPDWORD, LPBYTE, LPDWORD );
   DWORD (APIENTRY * RasGetEntryPropertiesW)( LPWSTR, LPWSTR, LPRASENTRYW, LPDWORD, LPBYTE, LPDWORD );
   DWORD (APIENTRY * RasSetEntryPropertiesA)( LPSTR, LPSTR, LPRASENTRYA, DWORD, LPBYTE, DWORD );
   DWORD (APIENTRY * RasSetEntryPropertiesW)( LPWSTR, LPWSTR, LPRASENTRYW, DWORD, LPBYTE, DWORD );
   DWORD (APIENTRY * RasRenameEntryA)( LPSTR, LPSTR, LPSTR );
   DWORD (APIENTRY * RasRenameEntryW)( LPWSTR, LPWSTR, LPWSTR );
   DWORD (APIENTRY * RasDeleteEntryA)( LPSTR, LPSTR );
   DWORD (APIENTRY * RasDeleteEntryW)( LPWSTR, LPWSTR );
   DWORD (APIENTRY * RasValidateEntryNameA)( LPSTR, LPSTR );
   DWORD (APIENTRY * RasValidateEntryNameW)( LPWSTR, LPWSTR );

#if ( WINVER >= 0x401 )

   DWORD (APIENTRY * RasGetSubEntryHandleA)( HRASCONN, DWORD, LPHRASCONN );
   DWORD (APIENTRY * RasGetSubEntryHandleW)( HRASCONN, DWORD, LPHRASCONN );
   DWORD (APIENTRY * RasGetCredentialsA)( LPSTR, LPSTR, LPRASCREDENTIALSA);
   DWORD (APIENTRY * RasGetCredentialsW)( LPWSTR, LPWSTR, LPRASCREDENTIALSW );
   DWORD (APIENTRY * RasSetCredentialsA)( LPSTR, LPSTR, LPRASCREDENTIALSA, BOOL );
   DWORD (APIENTRY * RasSetCredentialsW)( LPWSTR, LPWSTR, LPRASCREDENTIALSW, BOOL );
   DWORD (APIENTRY * RasConnectionNotificationA)( HRASCONN, HANDLE, DWORD );
   DWORD (APIENTRY * RasConnectionNotificationW)( HRASCONN, HANDLE, DWORD );
   DWORD (APIENTRY * RasGetSubEntryPropertiesA)( LPSTR, LPSTR, DWORD, LPRASSUBENTRYA, LPDWORD, LPBYTE, LPDWORD );
   DWORD (APIENTRY * RasGetSubEntryPropertiesW)( LPWSTR, LPWSTR, DWORD, LPRASSUBENTRYW, LPDWORD, LPBYTE, LPDWORD );
   DWORD (APIENTRY * RasSetSubEntryPropertiesA)( LPSTR, LPSTR, DWORD, LPRASSUBENTRYA, DWORD, LPBYTE, DWORD );
   DWORD (APIENTRY * RasSetSubEntryPropertiesW)( LPWSTR, LPWSTR, DWORD, LPRASSUBENTRYW, DWORD, LPBYTE, DWORD );
   DWORD (APIENTRY * RasGetAutodialAddressA)( LPSTR, LPDWORD, LPRASAUTODIALENTRYA, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasGetAutodialAddressW)( LPWSTR, LPDWORD, LPRASAUTODIALENTRYW, LPDWORD, LPDWORD);
   DWORD (APIENTRY * RasSetAutodialAddressA)( LPSTR, DWORD, LPRASAUTODIALENTRYA, DWORD, DWORD );
   DWORD (APIENTRY * RasSetAutodialAddressW)( LPWSTR, DWORD, LPRASAUTODIALENTRYW, DWORD, DWORD );
   DWORD (APIENTRY * RasEnumAutodialAddressesA)( LPSTR *, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasEnumAutodialAddressesW)( LPWSTR *, LPDWORD, LPDWORD );
   DWORD (APIENTRY * RasGetAutodialEnableA)( DWORD, LPBOOL );
   DWORD (APIENTRY * RasGetAutodialEnableW)( DWORD, LPBOOL );
   DWORD (APIENTRY * RasSetAutodialEnableA)( DWORD, BOOL );
   DWORD (APIENTRY * RasSetAutodialEnableW)( DWORD, BOOL );
   DWORD (APIENTRY * RasGetAutodialParamA)( DWORD, LPVOID, LPDWORD );
   DWORD (APIENTRY * RasGetAutodialParamW)( DWORD, LPVOID, LPDWORD );
   DWORD (APIENTRY * RasSetAutodialParamA)( DWORD, LPVOID, DWORD );
   DWORD (APIENTRY * RasSetAutodialParamW)( DWORD, LPVOID, DWORD );

#endif // ( WINVER >= 0x401 )

}
WFC_RAS_THUNK, *WFC_RAS_THUNK_P;

#pragma warning ( disable : 4097 )

/*
** We have to declare a typedef because of the funcky way Microsoft declared RASAMB in RAS.H
*/

typedef RASAMB _rasamb;

class CRemoteAccessServiceAuthenticationMessageBlock : public _rasamb
{
   private:

      void m_Initialize( void );

   public:

      CRemoteAccessServiceAuthenticationMessageBlock();
      CRemoteAccessServiceAuthenticationMessageBlock( const RASAMB *source );
      CRemoteAccessServiceAuthenticationMessageBlock( const CRemoteAccessServiceAuthenticationMessageBlock& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceAuthenticationMessageBlock();

      void  Copy( const RASAMB *source );
      void  Copy( const CRemoteAccessServiceAuthenticationMessageBlock& source );
      BYTE  GetLana( void ) const;
      DWORD GetErrorCode( void ) const;
      void  GetErrorString( CString& return_string ) const;
      CRemoteAccessServiceAuthenticationMessageBlock& operator=( const CRemoteAccessServiceAuthenticationMessageBlock& source );
};

/*
** We have to declare a typedef because of the funcky way Microsoft declared RASAMB in RAS.H
*/

typedef RASPPPNBF _raspppnbf;

class CRemoteAccessServiceNetBEUIFramer : public _raspppnbf
{
   private:

      void m_Initialize( void );

   public:

      CRemoteAccessServiceNetBEUIFramer();
      CRemoteAccessServiceNetBEUIFramer( const RASPPPNBF *source );
      CRemoteAccessServiceNetBEUIFramer( const CRemoteAccessServiceNetBEUIFramer& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceNetBEUIFramer();

      void  Copy( const RASPPPNBF* source );
      void  Copy( const CRemoteAccessServiceNetBEUIFramer& source );
      BYTE  GetLana( void ) const;
      DWORD GetErrorCode( void ) const;
      DWORD GetNetBiosErrorCode( void ) const;
      void  GetErrorString( CString& return_string ) const;
      void  GetWorkstationName( CString& return_string ) const;
      CRemoteAccessServiceNetBEUIFramer& operator=( const CRemoteAccessServiceNetBEUIFramer& source );
};

/*
** We have to declare a typedef because of the funcky way Microsoft declared RASAMB in RAS.H
*/

typedef RASPPPIPX _raspppipx;

class CRemoteAccessServiceInternetworkPacketExchange : public _raspppipx
{
   private:

      void m_Initialize( void );

   public:

      CRemoteAccessServiceInternetworkPacketExchange();
      CRemoteAccessServiceInternetworkPacketExchange( const RASPPPIPX * source );
      CRemoteAccessServiceInternetworkPacketExchange( const CRemoteAccessServiceInternetworkPacketExchange& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceInternetworkPacketExchange();

      void   Copy( const RASPPPIPX * source );
      void   Copy( const CRemoteAccessServiceInternetworkPacketExchange& source );
      DWORD  GetErrorCode( void ) const;
      void   GetIPXAddress( CString& return_string ) const;
      CRemoteAccessServiceInternetworkPacketExchange& operator=( const CRemoteAccessServiceInternetworkPacketExchange& source );
};

/*
** We have to declare a typedef because of the funcky way Microsoft declared RASAMB in RAS.H
*/

typedef RASPPPIP _raspppip;

class CRemoteAccessServiceInternetProtocol : public _raspppip
{
   private:

      void m_Initialize( void );

   public:

      CRemoteAccessServiceInternetProtocol();
      CRemoteAccessServiceInternetProtocol( const RASPPPIP * source );
      CRemoteAccessServiceInternetProtocol( const CRemoteAccessServiceInternetProtocol& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessServiceInternetProtocol();

      void   Copy( const RASPPPIP * source );
      void   Copy( const CRemoteAccessServiceInternetProtocol& source );
      DWORD  GetErrorCode( void ) const;
      void   GetIPAddress( CString& return_string ) const;

#if ! defined( WINNT35COMPATIBLE )

      void   GetServerIPAddress( CString& return_string ) const;

#endif // WINNT35COMPATIBLE

      CRemoteAccessServiceInternetProtocol& operator=( const CRemoteAccessServiceInternetProtocol& source );
};

#pragma warning ( default : 4097 )

class CRemoteAccessService
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CRemoteAccessService( const CRemoteAccessService& ) {};
      CRemoteAccessService& operator=( const CRemoteAccessService& ) { return( *this ); };

   private:

      void m_Initialize( void );
      void m_InitializeThunk( void );
      void m_GetConnectionsIntoMemory( LPRASCONN& return_value, DWORD& number_of_entries );

   protected:

      CString m_Name;

      WFC_RAS_THUNK_P m_Thunk_p;

      BOOL m_AutomaticallyClose;

      LONG m_ErrorCode;

      DWORD m_NotifierType;

      LPVOID m_ConnectionCallbackFunctionPointer;

      HRASCONN m_ConnectionHandle;

      RASCONNSTATUS m_ConnectionStatus;

      RASDIALEXTENSIONS m_DialExtensions;

      DWORD m_UnusedPadBytesBecauseMicrosoftChangesTheSizeOfStructures[ 16 ];

   public:

      enum Protocols
      {
         protocolAuthenticationMessageBlock = RASP_Amb,
         protocolNetBEUIFramer              = RASP_PppNbf,
         protocolInternetworkPacketExchange = RASP_PppIpx,
         protocolInternetProtocol           = RASP_PppIp
      };

      enum DialOptions
      {
         dialUsePrefixAndSuffix        = RDEOPT_UsePrefixSuffix,
         dialAcceptPausedStates        = RDEOPT_PausedStates,
         dialIgnoreModemSpeaker        = RDEOPT_IgnoreModemSpeaker,
         dialSetModemSpeaker           = RDEOPT_SetModemSpeaker,
         dialIgnoreSoftwareCompression = RDEOPT_IgnoreSoftwareCompression,
         dialSetSoftwareCompression    = RDEOPT_SetSoftwareCompression
      };

      CRemoteAccessService();
      CRemoteAccessService( DWORD input_buffer_size );
      CRemoteAccessService( DWORD input_buffer_size, DWORD output_buffer_size );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRemoteAccessService();

      /*
      ** The Win32 API
      */

      virtual BOOL     Dial( LPCTSTR who_to_call );
      virtual HRASCONN GetConnection( LPCTSTR name_of_connection );
      virtual BOOL     GetConnections( CStringArray& connections );
      virtual BOOL     GetConnectionStatus( void );
      virtual LONG     GetErrorCode( void ) const;
      virtual BOOL     GetErrorString( CString& error_string );
      virtual void     GetName( CString& name ) const;
      virtual BOOL     GetPhoneBookEntries( CStringArray& phone_book_entries );
      virtual BOOL     GetProtocolInformation( CRemoteAccessServiceAuthenticationMessageBlock& data_to_get );
      virtual BOOL     GetProtocolInformation( CRemoteAccessServiceNetBEUIFramer& data_to_get );
      virtual BOOL     GetProtocolInformation( CRemoteAccessServiceInternetworkPacketExchange& data_to_get );
      virtual BOOL     GetProtocolInformation( CRemoteAccessServiceInternetProtocol& data_to_get );
      virtual BOOL     HangUp( LPCTSTR name_of_connection = NULL );
      virtual BOOL     IsConnected( void );
      virtual BOOL     SetAutomaticallyClose( BOOL auto_close ); // Returns replaces setting
      virtual LPVOID   SetConnectionCallback( LPVOID RasDialFunc1_function_pointer );
      virtual HWND     SetConnectionCallbackWindow( HWND window_handle );
      virtual DWORD    SetDialOptions( DWORD dial_options );

      /*
      ** API's to make life a little easier 
      */

      virtual BOOL Open( LPCTSTR who_to_call );
      virtual BOOL Close( LPCTSTR name_of_connection = NULL ); // returns when RAS really hangs up

      /*
      ** Functions related to RAS
      */

      static BOOL EnableLogging( BOOL enable_logging, LPCTSTR machine_name = NULL ); // Creates DEVICE.LOG
      static BOOL GetKeepConnectionsAfterLogoff( LPCTSTR machine_name = NULL );
      static BOOL SetKeepConnectionsAfterLogoff( BOOL keep_connections = TRUE, LPCTSTR machine_name = NULL );
};

#endif // REMOTE_ACCESS_SERVICE_CLASS_HEADER
