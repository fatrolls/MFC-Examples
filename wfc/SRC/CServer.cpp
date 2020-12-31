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
** $Workfile: cserver.cpp $
** $Revision: 24 $
** $Modtime: 5/02/00 6:30p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CServer, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CServer::CServer()
{
   WFCLTRACEINIT( TEXT( "CServer::CServer()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CServer::CServer( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CServer::CServer( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Open( machine_name );
}

CServer::~CServer()
{
   WFCLTRACEINIT( TEXT( "CServer::~CServer()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
}

void CServer::Close( void )
{
   WFCLTRACEINIT( TEXT( "CServer::Close()" ) );
   CNetwork::Close();
   m_Initialize();
}

void CServer::GetComment( CString& comment )
{
   WFCLTRACEINIT( TEXT( "CServer::GetComment()" ) );

   comment.Empty();

   /*
   ** Test m_ServerName of emptiness because a lot of comments are blank
   */

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   comment = m_Comment;
}

void CServer::GetDomain( CString& name )
{
   WFCLTRACEINIT( TEXT( "CServer::GetDomain()" ) );

   name.Empty();

   /*
   ** Yes, domain is a member of the 503 structure, but that call doesn't work.
   ** We've got to use 599. Although for numsessions we have to use 503, go figure
   */

   if ( m_Retrieved503 == FALSE )
   {
      m_Get_503_Data();
   }

   name = m_Domain;
}

DWORD CServer::GetMajorVersion( void )
{
   WFCLTRACEINIT( TEXT( "CServer::GetMajorVersion()" ) );

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   return( m_MajorVersion );
}

DWORD CServer::GetMinorVersion( void )
{
   WFCLTRACEINIT( TEXT( "GetMinorVersion()" ) );

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   return( m_MinorVersion );
}

DWORD CServer::GetNumberOfOpens( void )
{
   WFCLTRACEINIT( TEXT( "CServer::GetNumberOfOpens()" ) );

   if ( m_Retrieved503 == FALSE )
   {
      m_Get_503_Data();
   }

   return( m_NumberOfOpens );
}

DWORD CServer::GetNumberOfUsers( void )
{
   WFCLTRACEINIT( TEXT( "CServer::GetNumberOfUsers()" ) );

   if ( m_Retrieved503 == FALSE )
   {
      m_Get_503_Data();
   }

   return( m_NumberOfUsers );
}

void CServer::GetName( CString& name )
{
   WFCLTRACEINIT( TEXT( "CServer::GetName()" ) );

   name.Empty();

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   name = m_MachineName;
}

DWORD CServer::GetPlatform( void )
{
   WFCLTRACEINIT( TEXT( "CServer::GetPlatform()" ) );

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   return( m_Platform );
}

void CServer::GetPlatformName( CString& name )
{
   WFCLTRACEINIT( TEXT( "CServer::GetPlatformName()" ) );

   name.Empty();

   /*
   ** Test m_ServerName of emptiness because a lot of comments are blank
   */

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   switch( m_Platform )
   {
      case SV_PLATFORM_ID_OS2:

         name = TEXT( "OS/2" );
         return;

      case SV_PLATFORM_ID_NT:

         name = TEXT( "NT" );
         return;

      default:

         CString temp_name( TEXT( "" ) );

         temp_name.Format( TEXT( "Unknown Type %d" ), m_Platform );
         name = temp_name;
         return;
   }
}

void CServer::GetPlatformNameAndVersion( CString& name )
{
   WFCLTRACEINIT( TEXT( "CServer::GetPlatformNameAndVersion()" ) );

   name.Empty();

   CString temp_name;

   GetPlatformName( temp_name );

   name.Format( TEXT( "%s %d.%d" ), (LPCTSTR) temp_name, m_MajorVersion, m_MinorVersion );
}

DWORD CServer::GetType( void )
{
   WFCLTRACEINIT( TEXT( "CServer::GetType()" ) );

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   return( m_Type );
}

void CServer::GetUserPath( CString& path )
{
   WFCLTRACEINIT( TEXT( "CServer::GetUserPath()" ) );

   path.Empty();

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   path = m_UserPath;
}

DWORD CServer::GetUsers( void )
{
   WFCLTRACEINIT( TEXT( "CServer::GetUsers()" ) );

   if ( m_Retrieved102 == FALSE )
   {
      m_Get_102_Data();
   }

   return( m_Users );
}

void CServer::m_Get_102_Data( void )
{
   WFCLTRACEINIT( TEXT( "CServer::m_Get_102_Data()" ) );

   LPBYTE buffer = (LPBYTE) NULL;

   /*
   ** One of the children got loose in the header files again...
   **
   ** Also, we can't get 101 information because it doesn't work if you supply
   ** a machine name... Go Figure...
   */

   m_ErrorCode = ::NetServerGetInfo( (LMSTR) m_WideMachineName, 102, &buffer );

   if ( m_ErrorCode != NERR_Success )
   {
      WFCTRACEERROR( m_ErrorCode );
   }

   if ( buffer != NULL )
   {
      SERVER_INFO_102 * information_p = (SERVER_INFO_102 *) buffer;

      m_MachineName  = CString( (LPCWSTR) information_p->sv102_name );
      m_UserPath     = CString( (LPCWSTR) information_p->sv102_userpath );
      m_Comment      = CString( (LPCWSTR) information_p->sv102_comment );

      m_Users        = information_p->sv102_users;
      m_Platform     = information_p->sv102_platform_id;
      m_MajorVersion = information_p->sv102_version_major;
      m_MinorVersion = information_p->sv102_version_minor;
      m_Type         = information_p->sv102_type;
      m_Retrieved102 = TRUE;
   }
}

void CServer::m_Get_503_Data( void )
{
   WFCLTRACEINIT( TEXT( "CServer::m_Get_503_Data()" ) );

   LPBYTE buffer = (LPBYTE) NULL;

   /*
   ** One of the children got loose in the header files again...
   */

   m_ErrorCode = ::NetServerGetInfo( (LMSTR) m_WideMachineName, 503, &buffer );

   if ( m_ErrorCode != NERR_Success )
   {
      WFCTRACEERROR( m_ErrorCode );
   }

   if ( buffer != NULL )
   {
      SERVER_INFO_503 *information_p = (SERVER_INFO_503 *) buffer;

      /*
      ** Now store the info we want...
      */

      m_NumberOfUsers = information_p->sv503_sessusers;
      m_NumberOfOpens = information_p->sv503_sessopens;
      m_Domain        = CString( (LPCWSTR) information_p->sv503_domain );
      m_Retrieved503  = TRUE;
   }
}

void CServer::m_Get_599_Data( void )
{
   WFCLTRACEINIT( TEXT( "CServer::m_Get_599_Data()" ) );

   LPBYTE buffer = (LPBYTE) NULL;

   /*
   ** One of the children got loose in the header files again...
   */

   m_ErrorCode = ::NetServerGetInfo( (LMSTR) m_WideMachineName, 599, &buffer );

   if ( m_ErrorCode != NERR_Success )
   {
      WFCTRACEERROR( m_ErrorCode );
   }

   if ( buffer != NULL )
   {
      SERVER_INFO_599 * information_p = (SERVER_INFO_599 *) buffer;

      if ( information_p->sv599_domain == NULL )
      {
         information_p->sv599_domain = (LMSTR) " ";
      }

      /*
      ** Now store the info we want...
      */

      m_Domain       = CString( (LPCWSTR) information_p->sv599_domain );
      m_Retrieved599 = TRUE;
   }
}

void CServer::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CServer::m_Initialize()" ) );

   m_Comment.Empty();
   m_UserPath.Empty();

   m_Retrieved102 = FALSE;
   m_Retrieved503 = FALSE;
   m_Retrieved599 = FALSE;

   m_MajorVersion  = 0;
   m_MinorVersion  = 0;
   m_NumberOfUsers = 0;
   m_NumberOfOpens = 0;
   m_Platform      = 0;
   m_Type          = 0;
   m_Users         = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CServer::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CServer::Serialize()" ) );

   CNetwork::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << m_Comment;
      archive << m_UserPath;
      archive << m_Domain;
      archive << m_MajorVersion;
      archive << m_MinorVersion;
      archive << m_NumberOfOpens;
      archive << m_NumberOfUsers;
      archive << m_Platform;
      archive << m_Type;
      archive << m_Users;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> m_Comment;
      archive >> m_UserPath;
      archive >> m_Domain;
      archive >> m_MajorVersion;
      archive >> m_MinorVersion;
      archive >> m_NumberOfOpens;
      archive >> m_NumberOfUsers;
      archive >> m_Platform;
      archive >> m_Type;
      archive >> m_Users;
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CServer</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class gives you information about NT domain servers.">
</HEAD>

<BODY>

<H1>CServer : <A HREF="CNetwork.htm">CNetwork</A></H1>
$Revision: 24 $<BR>
<HR>

<H2>Description</H2>

This class allows you to gather information about a server. It can get you information
similiar to the Server Control Panel applet. I am not proud of this class. It is 
inconsistent and ugly. I'll rewrite it one of these days.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the connection with the machine and cleans up any
internal buffers used.

<DT><PRE>void <B>GetComment</B>( CString&amp; comment )</PRE><DD>
Retrieves the comment about the server.

<DT><PRE>void <B>GetDomain</B>( CString&amp; domain_name )</PRE><DD>
Retrieves the name of the domain the server is a member of.

<DT><PRE>DWORD <B>GetMajorVersion</B>( void )</PRE><DD>
Retrieves the major portion of the operating system 
version number. For example, in NT 3.51, 3 would be the major version portion.

<DT><PRE>DWORD <B>GetMinorVersion</B>( void )</PRE><DD>
Retrieves the minor portion of the operating system 
version number. For example, in NT 3.51, 51 would be the minor version portion.

<DT><PRE>void <B>GetName</B>( CString&amp; name )</PRE><DD>
Retrieves the name of the server.

<DT><PRE>DWORD <B>GetNumberOfOpens</B>( void )</PRE><DD>
Retrieves the number of open files/pipes on the server.

<DT><PRE>DWORD <B>GetNumberOfUsers</B>( void )</PRE><DD>
Retrieves the users currently using the server.

<DT><PRE>DWORD <B>GetPlatform</B>( void )</PRE><DD>
Tells you what kind of machine the server is.

<DT><PRE>void <B>GetPlatformName</B>( CString&amp; name )</PRE><DD>
Tells you what kind of machine the server is in 
a human readable form.

<DT><PRE>void <B>GetPlatformNameAndVersion</B>( CString&amp; name_and_platform )</PRE><DD>
An even more human friendly way of getting
the server's operating system and version in a a human readable form.

<DT><PRE>DWORD <B>GetType</B>( void )</PRE><DD>
Retrieves type of the server.

<DT><PRE>void <B>GetUserPath</B>( CString&amp; path )</PRE><DD>
Retrieves the user's path.

<DT><PRE>DWORD <B>GetUsers</B>( void )</PRE><DD>
Retrieves the number of users of the server.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CServer( LPCTSTR machine_name )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CServer()&quot; ) );

   <B>CServer</B> server;

   server.Open( machine_name );

   CString name;
   CString comment;
   CString path;
   CString os;
   CString domain;

   DWORD major_version   = 0;
   DWORD minor_version   = 0;
   DWORD type            = 0;
   DWORD users           = 0;
   DWORD number_of_users = 0;
   DWORD number_of_opens = 0;

   server.GetUserPath( path );
   server.GetName( name );
   server.GetComment( comment );
   server.GetPlatformName( os );
   server.GetDomain( domain );

   major_version   = server.GetMajorVersion();
   minor_version   = server.GetMinorVersion();
   type            = server.GetType();
   users           = server.GetUsers();
   number_of_users = server.GetNumberOfUsers();
   number_of_opens = server.GetNumberOfOpens();

   _tprintf( TEXT( &quot;Server Name:      \&quot;%s\&quot;\n&quot; ), (LPCTSTR) name    );
   _tprintf( TEXT( &quot;Server Domain:    \&quot;%s\&quot;\n&quot; ), (LPCTSTR) domain  );
   _tprintf( TEXT( &quot;Server Comment:   \&quot;%s\&quot;\n&quot; ), (LPCTSTR) comment );
   _tprintf( TEXT( &quot;Server User Path: \&quot;%s\&quot;\n&quot; ), (LPCTSTR) path    );
   _tprintf( TEXT( &quot;Server OS:        \&quot;%s\&quot;\n&quot; ), (LPCTSTR) os      );
   _tprintf( TEXT( &quot;Server Version:    %d.%d\n&quot; ), major_version, minor_version );
   _tprintf( TEXT( &quot;Server Users:      %d\n&quot; ),    users );
   _tprintf( TEXT( &quot;Number Of Users:   %d\n&quot; ),    number_of_users );
   _tprintf( TEXT( &quot;Number Of Opens:   %d\n&quot; ),    number_of_opens );
}</CODE></PRE>

<H2>API's Used</H2>

<DL COMPACT>
<LI>NetServerGetInfo
</DL>

<HR><I>Copyright, 2000, <A HREF="wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cserver.cpp $<BR>
$Modtime: 5/02/00 6:30p $
</BODY>

</HTML>
#endif
