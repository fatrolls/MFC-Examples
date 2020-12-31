#if ! defined( SERVICE_CLASS_HEADER )

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
** $Workfile: cservice.hpp $
** $Revision: 18 $
** $Modtime: 1/04/00 4:54a $
*/

#define SERVICE_CLASS_HEADER

extern CRITICAL_SECTION g_ServiceCriticalSection;

#define SERVICE_NAME_LEN   256
#define ACCEPT_FLAGS ( SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN )

class CService
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CService( const CService& ) {};
      CService& operator=( const CService& ) { return( *this ); };

   private:

      void m_Initialize( void );

   public:

      static CService *m_StaticService_p;

      CService( LPTHREAD_START_ROUTINE thread_start_routine, DWORD accepted_controls = ACCEPT_FLAGS, DWORD wait_hint = 5000 );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CService( void );

      CStringArray CommandLineParameters;

      virtual BOOL Initialize( LPCTSTR name_of_service );
      void LogEvent( WORD event_type = EVENTLOG_ERROR_TYPE, LPTSTR message_string = NULL, DWORD error_code = NO_ERROR );
      virtual int  DialogBoxParam( HINSTANCE instance, LPCTSTR template_name, HWND parent_window, DLGPROC dialogbox_procedure, LPARAM lParam = 0 );
      virtual int  MessageBox( LPCTSTR text, LPCTSTR caption, UINT type );

   protected:

      HANDLE m_ExitEventHandle;
      HANDLE m_ThreadHandle;

      DWORD m_ControlsAccepted;
      DWORD m_CurrentState;
      DWORD m_ErrorCode;
      DWORD m_ThreadId;
      DWORD m_WaitHint;

      LPTHREAD_START_ROUTINE m_ThreadStartRoutine;

      SERVICE_STATUS_HANDLE m_ServiceStatusHandle;

      BOOL m_Debugging;
      BOOL m_Running;
      BOOL m_Paused;
      BOOL m_Exiting;

      SERVICE_TABLE_ENTRY m_ServiceTable[ 2 ];

      TCHAR m_ServiceName[ SERVICE_NAME_LEN + 1 ];

      static void CALLBACK ServiceControlManagerHandler( DWORD control_code );
      static void CALLBACK ServiceMain( DWORD argc, LPTSTR *argv );

      virtual void ParseCommandLineParameters( DWORD argc, LPTSTR *argv );
      virtual void OnControlCode( DWORD control_code );
      virtual void OnShutdown( void );
      virtual void OnStop( void );
      virtual BOOL OnPrepareServiceThread( void );
      virtual void OnPause( void );
      virtual void OnContinue( void );

      /*
      ** Thanks go to Juha Jalovaara (Juha@compuserve.com) for
      ** finding the flaw of Exit() not being virtual.
      */

      virtual void Exit( void );

      virtual BOOL SendStatusToServiceControlManager( DWORD current_state,
                                                      DWORD win32_exit_code = NO_ERROR,
                                                      DWORD check_point = 0, 
                                                      DWORD wait_hint = 0,
                                                      DWORD service_specific_code = NO_ERROR );

#if defined ( _DEBUG )
      virtual void AssertValid( void ) const;
      void DumpStatus( SERVICE_STATUS * status_p ) const;
#endif _DEBUG
};

#endif // SERVICE_CLASS_HEADER
