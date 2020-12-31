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
** $Workfile: CDesktop.cpp $
** $Revision: 19 $
** $Modtime: 1/04/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CDesktop::CDesktop()
{
   WFCLTRACEINIT( TEXT( "CDesktop::CDesktop()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_AutomaticallyClose = FALSE;
   m_DesktopHandle      = NULL;
   m_ErrorCode          = 0;
}

CDesktop::CDesktop( HDESK desktop_handle )
{
   WFCLTRACEINIT( TEXT( "CDesktop::CDesktop( HDESK )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_AutomaticallyClose = FALSE;
   m_DesktopHandle      = NULL;
   m_ErrorCode          = 0;

   Attach( desktop_handle );
}

CDesktop::~CDesktop()
{
   WFCLTRACEINIT( TEXT( "CDesktop::~CDesktop()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_AutomaticallyClose != FALSE )
   {
      Close();
   }

   m_AutomaticallyClose = FALSE;
   m_DesktopHandle      = NULL;
   m_ErrorCode          = 0;
}

void CDesktop::Attach( HDESK desktop_handle )
{
   WFCLTRACEINIT( TEXT( "CDesktop::Attach()" ) );

   if ( m_DesktopHandle != NULL && m_AutomaticallyClose != FALSE )
   {
      Close();
   }

   m_DesktopHandle      = desktop_handle;
   m_AutomaticallyClose = FALSE; // We didn't open it so don't close it
}

BOOL CDesktop::Close( void )
{
   WFCLTRACEINIT( TEXT( "CDesktop::Close()" ) );

   BOOL return_value = TRUE;

   if ( m_DesktopHandle != NULL )
   {
      return_value = ::CloseDesktop( m_DesktopHandle );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "CloseDesktop() failed" ) );
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         m_DesktopHandle = NULL;
         return_value    = TRUE;
      }
   }
   else
   {
      WFCTRACE( TEXT( "Desktop already closed." ) );
   }

   return( return_value );
}

BOOL CDesktop::Create( const CString& name_of_desktop, DWORD desired_access, LPSECURITY_ATTRIBUTES security_attributes_p, LPCTSTR display_device_name, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CDesktop::Create()" ) );

   BOOL return_value = FALSE;

   if ( m_DesktopHandle != NULL && m_AutomaticallyClose != FALSE )
   {
      Close();
   }

   m_AutomaticallyClose = FALSE;

   // We were passed a pointer, don't trust it

   try
   {
      // The first parameter is mis-typed, it should be const but it ain't.
      // This means we must code around it.

      TCHAR desktop_name[ 513 ];

      ::ZeroMemory( desktop_name, sizeof( desktop_name ) );
      
      (void) _tcsncpy( desktop_name, name_of_desktop, DIMENSION_OF( desktop_name ) - 1 );

      // The second parameter is also mis-typed. Go figure...

      LPTSTR display_name = NULL;

      TCHAR display_name_string[ 513 ];

      ::ZeroMemory( display_name_string, sizeof( display_name_string ) );

      if ( display_device_name != NULL )
      {
         (void) _tcsncpy( display_name_string, display_device_name, DIMENSION_OF( display_name_string ) - 1 );
         display_name = display_name_string;
      }
      else
      {
         display_name = NULL;
      }

      // CreateDesktop is not const correct

      m_DesktopHandle = ::CreateDesktop( desktop_name,
                                         display_name,
                                         NULL, // because the docs say so
                                         flags,
                                         desired_access,
                                         security_attributes_p );

      if ( m_DesktopHandle == NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return_value = FALSE;
      }
      else
      {
         m_AutomaticallyClose = TRUE; // We created it, we'll kill it
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CDesktop::GetAutomaticallyClose( void ) const
{
   return( m_AutomaticallyClose );
}

HDESK CDesktop::GetHandle( void ) const
{
   return( m_DesktopHandle );
}

BOOL CALLBACK CDesktop__WindowEnumerator( HWND window_handle, LPARAM lParam )
{
   CDWordArray * window_array = reinterpret_cast<CDWordArray *>( lParam );

   // We were passed a pointer by the caller, don't trust it

   __try
   {
      if ( window_array != NULL )
      {
         window_array->Add( (DWORD) window_handle );
      }
   }
   __except( EXCEPTION_EXECUTE_HANDLER )
   {
      return( FALSE );
   }

   return( TRUE );
}

BOOL CDesktop::GetWindows( CDWordArray& window_handles )
{
   WFCLTRACEINIT( TEXT( "CDesktop::GetWindows()" ) );

   // Always start out with a known state of the array

   window_handles.RemoveAll();

   BOOL return_value = FALSE;

   if ( m_DesktopHandle == NULL )
   {
      WFCTRACE( TEXT( "Desktop is not yet opened" ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   return_value = ::EnumDesktopWindows( m_DesktopHandle, CDesktop__WindowEnumerator, (LPARAM) &window_handles );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

DWORD CDesktop::GetErrorCode( void ) const
{
   return( m_ErrorCode );
}

void CDesktop::GetThread( DWORD thread_id )
{
   WFCLTRACEINIT( TEXT( "CDesktop::GetThread()" ) );

   if ( thread_id != 0 )
   {
      m_DesktopHandle = ::GetThreadDesktop( thread_id );
   }
   else
   {
      m_DesktopHandle = ::GetThreadDesktop( ::GetCurrentThreadId() );
   }
}

BOOL CDesktop::Open( const CString& name_of_desktop, DWORD desired_access, DWORD flags, BOOL inheritable )
{
   WFCLTRACEINIT( TEXT( "CDesktop::Open()" ) );

   BOOL return_value = FALSE;

   if ( m_DesktopHandle != NULL && m_AutomaticallyClose != FALSE )
   {
      Close();
   }

   m_AutomaticallyClose = FALSE;

   // The first parameter is mis-typed, it should be const but it ain't.
   // This means we must code around it

   TCHAR desktop_name[ 513 ];

   ::ZeroMemory( desktop_name, sizeof( desktop_name ) );
      
   (void) _tcsncpy( desktop_name, name_of_desktop, DIMENSION_OF( desktop_name ) - 1 );

   // OpenDesktop() is not const correct

   m_DesktopHandle = ::OpenDesktop( desktop_name, flags, inheritable, desired_access );

   if ( m_DesktopHandle == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return_value = FALSE;
   }
   else
   {
      WFCTRACE( TEXT( "Succeeded." ) );
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CDesktop::OpenInput( DWORD desired_access, DWORD flags, BOOL inheritable )
{
   WFCLTRACEINIT( TEXT( "CDesktop::OpenInput()" ) );

   BOOL return_value = FALSE;

   if ( m_DesktopHandle != NULL && m_AutomaticallyClose != FALSE )
   {
      Close();
   }

   m_AutomaticallyClose = FALSE;

   m_DesktopHandle = ::OpenInputDesktop( flags, inheritable, desired_access );

   if ( m_DesktopHandle == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return_value = FALSE;
   }
   else
   {
      WFCTRACE( TEXT( "Succeeded." ) );
      return_value = TRUE;
   }

   return( return_value );
}

void CDesktop::SetAutomaticallyClose( BOOL automatically_close )
{
   if ( automatically_close == FALSE )
   {
      m_AutomaticallyClose = FALSE;
   }
   else
   {
      m_AutomaticallyClose = TRUE;
   }
}

BOOL CDesktop::SetThread( void )
{
   WFCLTRACEINIT( TEXT( "CDesktop::SetThread()" ) );

   BOOL return_value = FALSE;

   return_value = ::SetThreadDesktop( m_DesktopHandle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CDesktop::SwitchTo( const CDesktop& desktop_to_switch_to )
{
   WFCLTRACEINIT( TEXT( "CDesktop::SwitchTo()" ) );

   BOOL return_value = FALSE;

   return_value = ::SwitchDesktop( desktop_to_switch_to.m_DesktopHandle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

CDesktop::operator HDESK () const
{
   return( m_DesktopHandle );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CDesktop</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles the Win32 Desktop (not to be confused with the GUI desktop).">
</HEAD>

<BODY>

<H1>CDesktop</H1>
$Revision: 19 $<BR>
<HR>

<H2>Description</H2>
This class allows you to play with desktops.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B><A NAME="Attach">Attach</A></B>( HDESK desktop_handle )</PRE><DD>
Attaches an existing desktop handle to this object.

<DT><PRE>BOOL <B><A NAME="Close">Close</A></B>( void )</PRE><DD>
Closes the desktop.

<DT><PRE>BOOL <B><A NAME="Create">Create</A></B>( const CString&amp; name_of_desktop,
                   DWORD    desired_access = DESKTOP_CREATEWINDOW,
      LPSECURITY_ATTRIBUTES security_attributes_p = NULL,
                   LPCTSTR  display_device_name = NULL,
                   DWORD    flags = 0 )</PRE><DD>
Creates a new desktop.

<DT><PRE>BOOL <B><A NAME="GetAutomaticallyClose">GetAutomaticallyClose</A></B>( void ) const</PRE><DD>
Returns whether the encapsulated desktop will be closed in the
destructor.

<DT><PRE>DWORD <B><A NAME="GetErrorCode">GetErrorCode</A></B>( void ) const</PRE><DD>
Returns the last error encountered.

<DT><PRE>HDESK <B><A NAME="GetHandle">GetHandle</A></B>( void ) const</PRE><DD>
Returns the encapsulated HDESK handle.

<DT><PRE>void <B><A NAME="GetThread">GetThread</A></B>( DWORD thread_id = 0 )</PRE><DD>
Attaches this <B>CDesktop</B> to the dekstop of the specified
<CODE>thread_id</CODE>.

<DT><PRE>BOOL <B><A NAME="GetWindows">GetWindows</A></B>( CDWordArray&amp; window_handles )</PRE><DD>
Gathers a list of all window handles for the desktop.

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( const CString&amp; desktop_name,  DWORD desired_access = DESKTOP_CREATEWINDOW, DWORD flags = 0, BOOL inherit = FALSE )</PRE><DD>
Opens the desktop.

<DT><PRE>BOOL <B><A NAME="OpenInput">OpenInput</A></B>( DWORD desired_access = accessCreateWindow, DWORD flags = 0, BOOL inherit = FALSE )</PRE><DD>
Opens the desktop for input.

<DT><PRE>void <B><A NAME="SetAutomaticallyClose">SetAutomaticallyClose</A></B>( BOOL automatically_close = TRUE )</PRE><DD>
Tells <B>CDesktop</B> to call <B>Close</B>() in the destructor.

<DT><PRE>BOOL <B><A NAME="SetThread">SetThread</A></B>( void )</PRE><DD>
Sets the current thread's desktop to this <B>CDesktop</B>.

<DT><PRE>BOOL <B><A NAME="SwitchTo">SwitchTo</A></B>( const CDesktop&amp; new_desktop )</PRE><DD>
Makes the <CODE>new_desktop</CODE> visible and activates it.

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>
<UL>
<LI>CloseDesktop
<LI>EnumDesktopWindows
<LI>GetCurrentThreadId
<LI>GetLastError
<LI>GetThreadDesktop
<LI>SetThreadDesktop
<LI>SwitchDesktop
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CDesktop.cpp $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>

</HTML>
#endif
