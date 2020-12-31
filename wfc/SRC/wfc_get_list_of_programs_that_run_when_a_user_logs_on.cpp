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
** $Workfile: wfc_get_list_of_programs_that_run_when_a_user_logs_on.cpp $
** $Revision: 2 $
** $Modtime: 1/05/00 3:52a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void PASCAL wfc_get_list_of_programs_that_run_when_a_user_logs_on( CStrinArray& program_names )
{
   // Programs can hide is a lots of places, here's a few

   // HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run
   // HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\WinLogon\Userinit 
}

#if 0
<WFC_DOCUMENTATION>
<HTML>
<HEAD>
<TITLE>WFC - wfc_get_list_of_programs_that_run_when_a_user_logs_on</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that tells you if you are running with Administrator priveleges.">
</HEAD>
<BODY>
<H1>wfc_get_list_of_programs_that_run_when_a_user_logs_on</H1>
$Revision: 2 $<HR>
<H2>Declaration</H2>
<PRE>BOOL <B>wfc_get_list_of_programs_that_run_when_a_user_logs_on</B>( CStringArray&amp; program_names )</PRE>
<H2>Description</H2>
This function returns TRUE if your program is running
with Administrator priveleges, FALSE if you don't have
Administrator proveleges. It uses the method described in
the Microsoft Knowledge Base article
<A HREF="http://www.microsoft.com/kb/articles/q118/6/26.htm" TARGET="_parent">Q118626</A>.
<H2>Example</H2><PRE><CODE>int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   if ( <B>wfc_am_i_administrator</B>() != FALSE )
   {
      _tprintf( TEXT( &quot;You are Administrator or in the Administrators group\n&quot; ) );
   }
   else
   {
      _tprintf( TEXT( &quot;You are nothing, a nobody!\n&quot; ) );
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>
<H2>API's Used</H2>
<B>wfc_am_i_administrator</B>() uses the following API's:
<UL>
<LI>AllocateAndInitializeSid
<LI>EqualSid
<LI>FreeSid
<LI>GetCurrentProcess
<LI>GetCurrentThread
<LI>GetLastError
<LI>GetTokenInformation
<LI>OpenProcessToken
<LI>OpenThreadToken
</UL>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: wfc_get_list_of_programs_that_run_when_a_user_logs_on.cpp $<BR>
$Modtime: 1/05/00 3:52a $
</BODY>
</HTML>
</WFC_DOCUMENTATION>
#endif
