#if ! defined( NETWORK_CLASS_HEADER )

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
** $Workfile: cnetwork.hpp $
** $Revision: 18 $
** $Modtime: 1/04/00 4:51a $
*/

#define NETWORK_CLASS_HEADER

#if ! defined( WNNC_NET_CLEARCASE )
#define WNNC_NET_CLEARCASE 0x00160000
#endif // WNNC_NET_CLEARCASE

class CNetwork
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CNetwork )
#endif // WFC_NO_SERIALIZATION

   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CNetwork( const CNetwork& ) {};
      CNetwork& operator=( const CNetwork& ) { return( *this ); };

   protected:

      LPWSTR m_WideMachineName;
      LPWSTR m_WideDoubleBackslashPreceededMachineName;

      CString m_MachineName;
      CString m_FriendlyMachineName;

      DWORD m_ErrorCode;

      BYTE  *m_PortBuffer;
      DWORD  m_NumberOfPorts;
      DWORD  m_PortNumber;

      virtual void m_Initialize( void );

   public:

      enum NetworkType //  From WINNETWK.H
      {
         MSNet      = WNNC_NET_MSNET,
         LanMan     = WNNC_NET_LANMAN,
         Netware    = WNNC_NET_NETWARE,
         Vines      = WNNC_NET_VINES,
         TenNet     = WNNC_NET_10NET,
         Locus      = WNNC_NET_LOCUS,
         SunPcNFS   = WNNC_NET_SUN_PC_NFS,
         LanStep    = WNNC_NET_LANSTEP,
         NineTiles  = WNNC_NET_9TILES,
         Lantastic  = WNNC_NET_LANTASTIC,
         AS400      = WNNC_NET_AS400,
         FtpNFS     = WNNC_NET_FTP_NFS,
         PathWorks  = WNNC_NET_PATHWORKS,
         LifeNet    = WNNC_NET_LIFENET,
         PowerLan   = WNNC_NET_POWERLAN,
         BWNFS      = WNNC_NET_BWNFS,
         Cogent     = WNNC_NET_COGENT,
         Farallon   = WNNC_NET_FARALLON,
         AppleTalk  = WNNC_NET_APPLETALK,
         Intergraph = WNNC_NET_INTERGRAPH,
         SymfoNet   = WNNC_NET_SYMFONET,
         ClearCase  = WNNC_NET_CLEARCASE
      };

      CNetwork( LPCTSTR machine_name = NULL );
      virtual ~CNetwork();

      virtual BOOL    AbortShutdown( void );
      virtual void    Close( void );
      virtual BOOL    EnumeratePorts( void );
      virtual DWORD   GetErrorCode( void ) const;
      virtual LPCTSTR GetMachineName( void );
      virtual void    GetFriendlyMachineName( CString& name ) const;
      virtual BOOL    GetNext( CPortInformation& port );
      virtual BOOL    GetTime( CTime& machine_time );
      virtual BOOL    GetTime( CSystemTime& machine_time );
      virtual BOOL    IsRebootable( void );
      virtual void    Open( LPCTSTR machine_name = NULL );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void    Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual BOOL    SetPrivilege( LPCTSTR privilege_name, BOOL add_privilege = TRUE );
      virtual BOOL    Shutdown( BOOL    reboot                            = TRUE,
                                BOOL    force_applications_to_close       = TRUE,
                                LPCTSTR message_to_display                = NULL,
                                DWORD   number_of_seconds_before_shutdown = 0 );
      operator LPCWSTR() const { return( m_WideMachineName ); }
      operator LPWSTR()  const { return( m_WideMachineName ); }

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // NETWORK_CLASS_HEADER
