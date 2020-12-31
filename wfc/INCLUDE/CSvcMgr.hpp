#if ! defined( SERVICE_MANAGER_CLASS_HEADER )

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
** $Workfile: csvcmgr.hpp $
** $Revision: 16 $
** $Modtime: 1/04/00 4:54a $
*/

#define SERVICE_MANAGER_CLASS_HEADER

class CServiceNameAndStatusA : public _ENUM_SERVICE_STATUSA
{
   public:

      CServiceNameAndStatusA();
      virtual ~CServiceNameAndStatusA();
      virtual void Copy( const _ENUM_SERVICE_STATUSA *source );
      virtual void Empty( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CServiceNameAndStatusW : public _ENUM_SERVICE_STATUSW
{
   public:

      CServiceNameAndStatusW();
      virtual ~CServiceNameAndStatusW();
      virtual void Copy( const _ENUM_SERVICE_STATUSW *source );
      virtual void Empty( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#if defined( UNICODE )
#define CServiceNameAndStatus CServiceNameAndStatusW
#else
#define CServiceNameAndStatus CServiceNameAndStatusA
#endif // UNICODE

class CServiceControlManager
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CServiceControlManager( const CServiceControlManager& ) {};
      CServiceControlManager& operator=( const CServiceControlManager& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      SC_HANDLE m_ManagerHandle;

      SC_LOCK m_DatabaseLockHandle;

      ENUM_SERVICE_STATUS *m_Buffer;

      DWORD m_BufferSize;
      DWORD m_CurrentEntryNumber;
      DWORD m_ErrorCode;
      DWORD m_NumberOfEntries;

      CString m_MachineName;

   public:

      CServiceControlManager();
      virtual ~CServiceControlManager();

      virtual void  Close( void );
      virtual BOOL  Continue( LPCTSTR service_name );
      virtual BOOL  EnableInteractiveServices( BOOL enable_interactive_services = TRUE );
      virtual BOOL  EnumerateStatus( DWORD state = SERVICE_ACTIVE,
                                     DWORD type  = SERVICE_WIN32 );
      virtual BOOL  GetConfiguration( LPCTSTR service_name, CServiceConfiguration& configuration );
      virtual BOOL  GetDependencies( LPCTSTR service_name, CStringArray& dependencies );
      virtual BOOL  GetDisplayName( LPCTSTR real_name, CString& friendly_name );
      virtual DWORD GetErrorCode( void ) const;
      virtual SC_HANDLE GetHandle( void ) const;
      virtual BOOL  GetKeyName( LPCTSTR friendly_name, CString& real_name );
      virtual BOOL  GetNext( CServiceNameAndStatus& status );
      virtual BOOL  Install( LPCTSTR service_name, LPCTSTR friendly_name, LPCTSTR name_of_executable_file );
      virtual BOOL  IsDatabaseLocked( CString& who_locked_it, CTimeSpan& how_long_it_has_been_locked );
      virtual BOOL  LockDatabase( void );
      virtual BOOL  Open( DWORD   what_to_open  = SC_MANAGER_ALL_ACCESS,
                          LPCTSTR database_name = NULL,
                          LPCTSTR machine_name  = NULL );
      virtual BOOL  Pause( LPCTSTR service_name );
      virtual BOOL  Remove( LPCTSTR service_name );
      virtual BOOL  SetConfiguration( LPCTSTR service_name,
                                      DWORD   when_to_start           = SERVICE_NO_CHANGE,
                                      DWORD   type_of_service         = SERVICE_NO_CHANGE,
                                      DWORD   error_control           = SERVICE_NO_CHANGE,
                                      LPCTSTR name_of_executable_file = NULL,
                                      LPCTSTR load_order_group        = NULL,
                                      LPCTSTR dependencies            = NULL,
                                      LPCTSTR start_name              = NULL,
                                      LPCTSTR password                = NULL,
                                      LPCTSTR display_name            = NULL );
      virtual BOOL  Start( LPCTSTR service_name, DWORD service_argc = 0, LPCTSTR *service_argv = NULL );
      virtual BOOL  Stop( LPCTSTR service_name );
      virtual BOOL  UnlockDatabase( void );
};

#endif // SERVICE_MANAGER_CLASS_HEADER
