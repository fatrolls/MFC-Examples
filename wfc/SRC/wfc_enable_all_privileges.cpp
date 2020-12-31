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
** $Workfile: wfc_enable_all_privileges.cpp $
** $Revision: 2 $
** $Modtime: 5/04/00 6:57p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_enable_all_privileges( void )
{
   WFCLTRACEINIT( TEXT( "wfc_enable_all_privileges()" ) );

   BOOL return_value = TRUE;

   // From NTSECAPI.H

   if ( wfc_enable_privilege( SE_INTERACTIVE_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_NETWORK_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_BATCH_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SERVICE_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   // From WINNT.H

   if ( wfc_enable_privilege( SE_CREATE_TOKEN_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_ASSIGNPRIMARYTOKEN_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_LOCK_MEMORY_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_INCREASE_QUOTA_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_UNSOLICITED_INPUT_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_MACHINE_ACCOUNT_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_TCB_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SECURITY_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_TAKE_OWNERSHIP_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_LOAD_DRIVER_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SYSTEM_PROFILE_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SYSTEMTIME_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_PROF_SINGLE_PROCESS_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_INC_BASE_PRIORITY_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_CREATE_PAGEFILE_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_CREATE_PERMANENT_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_BACKUP_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_RESTORE_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SHUTDOWN_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_DEBUG_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_AUDIT_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SYSTEM_ENVIRONMENT_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_CHANGE_NOTIFY_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_REMOTE_SHUTDOWN_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   // New NT5 privileges and rights

   if ( wfc_enable_privilege( SE_DENY_INTERACTIVE_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_DENY_NETWORK_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_DENY_BATCH_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_DENY_SERVICE_LOGON_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_UNDOCK_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_SYNC_AGENT_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   if ( wfc_enable_privilege( SE_ENABLE_DELEGATION_NAME ) == FALSE )
   {
      return_value = FALSE;
   }

   return( return_value );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_enable_all_privileges</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that encapsulates CloseHandle(). It will spit out a debugging message if CloseHandle() fails.">
</HEAD>

<BODY>

<H1>wfc_enable_all_privileges</H1>
$Revision: 2 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_enable_all_privileges</B>( void )</PRE>

<H2>Description</H2>
This function returns TRUE if all privileges on a system
have been enabled. FALSE will be returned if at least one
privelege could not be enabled.
It will attempt to enable the following privileges:

<UL>
<LI><CODE>SE_INTERACTIVE_LOGON_NAME</CODE>
<LI><CODE>SE_NETWORK_LOGON_NAME</CODE>
<LI><CODE>SE_BATCH_LOGON_NAME</CODE>
<LI><CODE>SE_SERVICE_LOGON_NAME</CODE>
<LI><CODE>SE_CREATE_TOKEN_NAME</CODE>
<LI><CODE>SE_ASSIGNPRIMARYTOKEN_NAME</CODE>
<LI><CODE>SE_LOCK_MEMORY_NAME</CODE>
<LI><CODE>SE_INCREASE_QUOTA_NAME</CODE>
<LI><CODE>SE_UNSOLICITED_INPUT_NAME</CODE>
<LI><CODE>SE_MACHINE_ACCOUNT_NAME</CODE>
<LI><CODE>SE_TCB_NAME</CODE>
<LI><CODE>SE_SECURITY_NAME</CODE>
<LI><CODE>SE_TAKE_OWNERSHIP_NAME</CODE>
<LI><CODE>SE_LOAD_DRIVER_NAME</CODE>
<LI><CODE>SE_SYSTEM_PROFILE_NAME</CODE>
<LI><CODE>SE_SYSTEMTIME_NAME</CODE>
<LI><CODE>SE_PROF_SINGLE_PROCESS_NAME</CODE>
<LI><CODE>SE_INC_BASE_PRIORITY_NAME</CODE>
<LI><CODE>SE_CREATE_PAGEFILE_NAME</CODE>
<LI><CODE>SE_CREATE_PERMANENT_NAME</CODE>
<LI><CODE>SE_BACKUP_NAME</CODE>
<LI><CODE>SE_RESTORE_NAME</CODE>
<LI><CODE>SE_SHUTDOWN_NAME</CODE>
<LI><CODE>SE_DEBUG_NAME</CODE>
<LI><CODE>SE_AUDIT_NAME</CODE>
<LI><CODE>SE_SYSTEM_ENVIRONMENT_NAME</CODE>
<LI><CODE>SE_CHANGE_NOTIFY_NAME</CODE>
<LI><CODE>SE_REMOTE_SHUTDOWN_NAME</CODE>
<LI><CODE>SE_DENY_INTERACTIVE_LOGON_NAME</CODE>
<LI><CODE>SE_DENY_NETWORK_LOGON_NAME</CODE>
<LI><CODE>SE_DENY_BATCH_LOGON_NAME</CODE>
<LI><CODE>SE_DENY_SERVICE_LOGON_NAME</CODE>
<LI><CODE>SE_UNDOCK_NAME</CODE>
<LI><CODE>SE_SYNC_AGENT_NAME</CODE>
<LI><CODE>SE_ENABLE_DELEGATION_NAME</CODE>
</UL>

<H2>Example</H2>

<PRE><CODE>int _tmain( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( <B>wfc_enable_all_privileges</B>() == FALSE )
   {
      _tprintf( TEXT( &quot;Could not enable all privileges.\n&quot; ) );
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_enable_all_privileges</B>() uses the following API's:
<UL>
<LI>None.
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_enable_all_privileges.cpp $<BR>
$Modtime: 5/04/00 6:57p $
</BODY>

</HTML>
#endif
