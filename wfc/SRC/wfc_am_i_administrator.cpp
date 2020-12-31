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
** $Workfile: wfc_am_i_administrator.cpp $
** $Revision: 12 $
** $Modtime: 1/17/00 9:31a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_am_i_administrator( void )
{
   // Plagerized from Microsoft Knowledge Base article Q118626

   HANDLE access_token_handle = NULL;

   BYTE buffer[ 1024 ];

   PTOKEN_GROUPS token_groups_p = (PTOKEN_GROUPS) buffer;

   DWORD buffer_size = 0;

   BOOL success = FALSE;

   if ( OpenThreadToken( GetCurrentThread(),
                         TOKEN_QUERY,
                         TRUE,
                        &access_token_handle ) == FALSE )
   {
      if ( GetLastError() != ERROR_NO_TOKEN )
      {
         return( FALSE );
      }

      // retry against process token if no thread token exists

      if ( OpenProcessToken( GetCurrentProcess(),
                             TOKEN_QUERY,
                            &access_token_handle ) == FALSE )
      {
         return( FALSE );
      }
   }

   success = GetTokenInformation( access_token_handle,
                                  TokenGroups,
                                  buffer,
                                  1024,
                                 &buffer_size );

   wfc_close_handle( access_token_handle );
   access_token_handle = NULL;

   if ( success == FALSE )
   {
      return( FALSE );
   }

   SID_IDENTIFIER_AUTHORITY nt_authority_sid = SECURITY_NT_AUTHORITY;

   PSID administrators_sid_p = NULL;

   if ( AllocateAndInitializeSid( &nt_authority_sid,
                                   2,
                                   SECURITY_BUILTIN_DOMAIN_RID,
                                   DOMAIN_ALIAS_RID_ADMINS,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                   0,
                                  &administrators_sid_p ) == FALSE )
   {
      return( FALSE );
   }

   // assume that we don't find the admin SID.
   success = FALSE;

   UINT x = 0;

   for( x = 0; x < token_groups_p->GroupCount; x++ )
   {
      if ( EqualSid( administrators_sid_p, token_groups_p->Groups[ x ].Sid ) != FALSE )
      {
         success = TRUE;
         break;
      }
   }

   FreeSid( administrators_sid_p );

   return( success );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_am_i_administrator</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="Simple C function that tells you if you are running with Administrator priveleges.">
</HEAD>

<BODY>

<H1>wfc_am_i_administrator</H1>
$Revision: 12 $<HR>

<H2>Declaration</H2>

<PRE>BOOL <B>wfc_am_i_administrator</B>( void )</PRE>

<H2>Description</H2>

This function returns TRUE if your program is running
with Administrator priveleges, FALSE if you don't have
Administrator proveleges. It uses the method described in
the Microsoft Knowledge Base article
<A HREF="http://www.microsoft.com/kb/articles/q118/6/26.htm" TARGET="_parent">Q118626</A>.

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

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

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_am_i_administrator.cpp $<BR>
$Modtime: 1/17/00 9:31a $
</BODY>

</HTML>
#endif
