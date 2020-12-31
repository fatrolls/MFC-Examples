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
** $Workfile: wfc_enable_privilege.cpp $
** $Revision: 1 $
** $Modtime: 1/17/00 9:32a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_enable_privilege( LPCTSTR privilege_name )
{
   WFCLTRACEINIT( TEXT( "wfc_enable_privilege()" ) );

   try
   {
      HANDLE token_handle = NULL;

      if ( OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Can't OpenProcessToken()" ) );
         return( FALSE );
      }

      TOKEN_PRIVILEGES token_privileges;

      ZeroMemory( &token_privileges, sizeof( token_privileges ) );

      if ( LookupPrivilegeValue( NULL, privilege_name, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACEVAL( TEXT( "Can't LookupPrivilegeValue for " ), CString( privilege_name ) );
         wfc_close_handle( token_handle );
         return( FALSE );
      }

      token_privileges.PrivilegeCount             = 1;
      token_privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

      if ( AdjustTokenPrivileges( token_handle, FALSE, &token_privileges, 0, (PTOKEN_PRIVILEGES) NULL, 0 ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
         wfc_close_handle( token_handle );
         return( FALSE );
      }

      wfc_close_handle( token_handle );

      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_enable_privilege</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that encapsulates CloseHandle(). It will spit out a debugging message if CloseHandle() fails.">
</HEAD>

<BODY>

<H1>wfc_enable_privilege</H1>
$Revision: 1 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_enable_privilege</B>( LPCTSTR privilege_name )</PRE>

<H2>Description</H2>
This function returns TRUE if the <CODE>privilege_name</CODE>
was acquired. It will return FALSE if that privilege could
not be enabled.

<H2>Example</H2>

<PRE><CODE>int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( number_of_command_line_arguments &lt; 2 )
   {
      return( EXIT_SUCCESS );
   }

   int loop_index = 1;

   while( loop_index &lt; number_of_command_line_arguments )
   {
      if ( <B>wfc_enable_privilege</B>( command_line_arguments[ loop_index ] ) == FALSE )
      {
         _tprintf( TEXT( &quot;Could not enable the \&quot;%s\&quot; privilege.\n&quot; ),
                   command_line_arguments[ loop_index ] );
      }

      loop_index++;
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_enable_privilege</B>() uses the following API's:
<UL>
<LI>AdjustTokenPrivileges
<LI>GetCurrentProcess
<LI>GetLastError
<LI>LookupPrivilegeValue
<LI>OpenProcessToken
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_enable_privilege.cpp $<BR>
$Modtime: 1/17/00 9:32a $
</BODY>

</HTML>
#endif
