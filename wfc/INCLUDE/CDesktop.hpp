#if ! defined( DESKTOP_CLASS_HEADER )

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
** $Workfile: CDesktop.hpp $
** $Revision: 8 $
** $Modtime: 1/04/00 4:43a $
*/

#define DESKTOP_CLASS_HEADER

class CDesktop
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CDesktop( const CDesktop& ) {};
      CDesktop& operator=( const CDesktop& ) { return( *this ); };

   protected:

      HDESK m_DesktopHandle;

      DWORD m_ErrorCode;

      BOOL m_AutomaticallyClose;

   public:

      // Construction

      CDesktop();
      CDesktop( HDESK desktop_handle );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CDesktop();

      enum _Accesses
      {
         accessCreateMenu      = DESKTOP_CREATEMENU,
         accessCreateWindow    = DESKTOP_CREATEWINDOW,
         accessEnumerate       = DESKTOP_ENUMERATE,
         accessHookControl     = DESKTOP_HOOKCONTROL,
         accessJournalPlayback = DESKTOP_JOURNALPLAYBACK,
         accessJournalRecord   = DESKTOP_JOURNALRECORD,
         accessReadObjects     = DESKTOP_READOBJECTS,
         accessSwitchDesktop   = DESKTOP_SWITCHDESKTOP,
         accessWriteObjects    = DESKTOP_WRITEOBJECTS
      };

      /*
      ** Methods
      */

      virtual void  Attach( HDESK desktop_handle );
      virtual BOOL  Close( void );
      virtual BOOL  Create( const CString& name_of_desktop, 
                                  DWORD    desired_access = DESKTOP_CREATEWINDOW,
                     LPSECURITY_ATTRIBUTES security_attributes_p = NULL, 
                                  LPCTSTR  display_device_name = NULL, 
                                  DWORD    flags = 0 );
      virtual BOOL  GetAutomaticallyClose( void ) const;
      virtual DWORD GetErrorCode( void ) const;
      virtual HDESK GetHandle( void ) const;
      virtual void  GetThread( DWORD thread_id = 0 );
      virtual BOOL  GetWindows( CDWordArray& window_handles ); // EnumDesktopWindows
      virtual BOOL  Open( const CString& desktop_name, DWORD desired_access = DESKTOP_CREATEWINDOW, DWORD flags = 0, BOOL inherit = FALSE );
      virtual BOOL  OpenInput( DWORD desired_access = accessCreateWindow, DWORD flags = 0, BOOL inherit = FALSE );
      virtual void  SetAutomaticallyClose( BOOL automatically_close = TRUE );
      virtual BOOL  SetThread( void );
      virtual BOOL  SwitchTo( const CDesktop& desktop_to_switch_to );

      /*
      ** Operators
      */

      operator HDESK () const;
};

#endif // DESKTOP_CLASS_HEADER
