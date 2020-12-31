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
** $Workfile: RASPORT.CPP $
** $Revision: 10 $
** $Modtime: 1/05/00 3:40a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/*
** CRemoteAccessUser
*/

#if 0
<HTML>
<HEAD>
<TITLE>WFC - CRemoteAccessUser</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>
<BODY>
<H1>CRemoteAccessService : CObject</H1>
$Revision: 10 $
<HR><H2>Description</H2>
This class makes RAS a little easier. From a programming perspective, RAS is like most Microsoft API's: almost useful.
What's lacking from RAS is the ability to play with ports. I had to write software for a fault-tolerant mail postoffice
and wrote a little program to page a system administrator when something went wrong. I had to dedicate one modem to
this task because there's no way to tell RAS to release a port for other use. There's a RasPortxxx API that is not
exposed so we lowly developer's can't use it. In short, it is impossible to write the RASPHONE application using
the documented RAS API.
<H2>Data Members</H2><B>None.</B>
<H2>Methods</H2>
<DL COMPACT>
<DT><B>Close</B><DD>Same as HangUp except it will not return until RAS really
hangs up.
<DT><B>Dial</B><DD>Dials a phone book entry. Makes a connection.
<DT><B>GetConnection</B><DD>Gives you the HRASONN for the named connection.
<DT><B>GetConnections</B><DD>Gives you a list of connection names.
<DT><B>GetConnectionStatus</B><DD>Returns TRUE is you're connected.
<DT><B>GetErrorCode</B><DD>Holds the error code should any function return
FALSE.
<DT><B>GetErrorString</B><DD>Same as GetErrorCode() but it gives you a human
readable string instead of a number.
<DT><B>GetName</B><DD>Gives you the name of the connection that was successfully
Open()'d or Dial()'d.
<DT><B>GetPhoneBookEntries</B><DD>Gives you back a list of phone book entry
names. You can use these names to pass to Dial().
<DT><B>GetProtocolInformation</B><DD>Gives you back information about the
networking protocol used on the active connection.
<DT><B>HangUp</B><DD>Tells RAS to terminates the connection. <B>NOTE!</B>
When this function returns, <B><I>THE CONNECTION HAS NOT BEEN TERMINATED!!</I></B>
If you immediately exit from your thread/process after calling HangUp, the connection
will be left in a random state. It is much safer to use Close() instead.
<DT><B>IsConnected</B><DD>Returns TRUE if you're connected.
<DT><B>Open</B><DD>Same as Dial but lets you treat RAS like most other object
in WFC.
<DT><B>SetAutomaticallyClose</B><DD>When this property is TRUE, the destructor
will terminate the connection if there is one. 
<DT><B>SetConnectionCallback</B><DD>Lets you pass a pointer to a function so
you can monitor the progress of RAS.
<DT><B>SetConnectionCallbackWindow</B><DD>Lets you pass a window handle that will
receive WM_RASDIALEVENT messages so you can monitor the progress of RAS.
<DT><B>SetDialOptions</B><DD>Let's you set the dialing options.
</DL>
<H2>Example</H2><PRE><CODE>
void test_CRAS( void )
{
   CRemoteAccessService ras;

   CStringArray strings;

   ras.SetDialOptions( CRemoteAccessService::dialAcceptPausedStates );

   if ( ras.GetPhoneBookEntries( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( &quot;Phone Book Entries:\n&quot; ) );

      while( index &lt; number_of_entries )
      {
         TRACE1( TEXT( &quot;\&quot;%s\&quot;\n&quot; ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   strings.RemoveAll();

   if ( ras.GetConnections( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( &quot;\nCurrent Connections:\n&quot; ) );

      while( index &lt; number_of_entries )
      {
         TRACE1( TEXT( &quot;\&quot;%s\&quot;\n&quot; ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   if ( ras.Open( TEXT( &quot;EROLS&quot; ) ) == FALSE )
   {
      CString error_string;
      ras.GetErrorString( error_string );
      TRACE1( TEXT( &quot;Ras Open failed with \&quot;%s\&quot;!\n&quot; ), (LPCTSTR) error_string );
   }
   else
   {
      TRACE( &quot;RAS Open!\n&quot; );
   }

   strings.RemoveAll();

   if ( ras.GetConnections( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( &quot;\nCurrent Connections:\n&quot; ) );

      while( index &lt; number_of_entries )
      {
         TRACE1( TEXT( &quot;\&quot;%s\&quot;\n&quot; ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   if ( ras.HangUp( TEXT( &quot;EROLS&quot; ) ) != FALSE )
   {
      TRACE( TEXT( &quot;Hangup OK\n&quot; ) );
   }
}</CODE></PRE>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: RASPORT.CPP $<BR>
$Modtime: 1/05/00 3:40a $
</BODY>
</HTML>
#endif
