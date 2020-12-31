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
** $Workfile: CFileTransferProtocol.cpp $
** $Revision: 14 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CFileTransferProtocol::CFileTransferProtocol( LPCTSTR user_name, LPCTSTR password )
{
   WFCLTRACEINIT( TEXT( "CFileTransferProtocol::CFileTransferProtocol()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( user_name == NULL )
   {
      SetUserName( TEXT( "anonymous" ) );
   }
   else
   {
      // We were passed a pointer, don't trust it

      try
      {
         SetUserName( user_name );
      }
      catch( ... )
      {
         SetUserName( TEXT( "anonymous" ) );
      }
   }

   TCHAR default_user_name[ 512 ];
   DWORD size_of_user_name = 0;

   ZeroMemory( default_user_name, sizeof( default_user_name ) );

   size_of_user_name = DIMENSION_OF( default_user_name );

   ::GetUserName( default_user_name, &size_of_user_name );

   CString ip_address;

   CSimpleSocket::GetMyAddress( ip_address );

   CString default_password( default_user_name );

   default_password += TEXT( "@" );
   default_password += ip_address;

   SetPassword( default_password );

   if ( password != NULL )
   {
      // We were passed a pointer, don't trust it

      try
      {
         SetPassword( password );
      }
      catch( ... )
      {
         // Do Nothing
      }
   }
}

CFileTransferProtocol::~CFileTransferProtocol()
{
   WFCLTRACEINIT( TEXT( "CFileTransferProtocol::~CFileTransferProtocol()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_UserName.Empty();
   m_Password.Empty();
}

void CFileTransferProtocol::GetDirectory( const CUniformResourceLocator& url, CStringArray& directory, LPCTSTR filter )
{
   WFCLTRACEINIT( TEXT( "CFileTransferProtocol::GetDirectory()" ) );

   CInternetSession * internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

   CFtpConnection * connection_p = reinterpret_cast< CFtpConnection * >( NULL );

   CFtpFileFind * file_find_p = reinterpret_cast< CFtpFileFind * >( NULL );

   CByteArray read_buffer;

   try
   {
      CString temp_string;

      temp_string.Format( TEXT( "CFileTransferProtocol::GetDirectory( \"%s\" ) : %lu" ), (LPCTSTR) url, (DWORD) ::GetTickCount() );

      WFCTRACEVAL( TEXT( "Unique ID is " ), temp_string );

      try
      {
         internet_session_p = new CInternetSession( temp_string );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG

         exception_p->Delete();
         return;
      }
      catch( ... )
      {
         return;
      }

      try
      {
         connection_p = internet_session_p->GetFtpConnection( url.MachineName, m_UserName, m_Password );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
      }
      catch( ... )
      {
      }

      if ( connection_p == NULL )
      {
         internet_session_p->Close();
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

         return;
      }

      if ( url.PathName.GetLength() != 0 )
      {
         try
         {
            if ( connection_p->SetCurrentDirectory( url.PathName ) == FALSE )
            {
               WFCTRACEVAL( TEXT( "Can't change directory to " ), url.PathName );
            }
         }
         catch( ... )
         {
         }
      }

      try
      {
         file_find_p = new CFtpFileFind( connection_p );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
      }
      catch( ... )
      {
      }

      if ( file_find_p == NULL )
      {
         connection_p->Close();
         delete connection_p;
         connection_p = reinterpret_cast< CFtpConnection * >( NULL );

         internet_session_p->Close();
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

         return;
      }

      if ( file_find_p->FindFile( filter ) != FALSE )
      {
         directory.Add( file_find_p->GetFileName() );

         while( file_find_p->FindNextFile() != FALSE )
         {
            WFCTRACEVAL( TEXT( "Now Adding " ), file_find_p->GetFileName() );
            directory.Add( file_find_p->GetFileName() );
         }
      }

      delete file_find_p;
      file_find_p = reinterpret_cast< CFtpFileFind * >( NULL );

      connection_p->Close();
      delete connection_p;
      connection_p = reinterpret_cast< CFtpConnection * >( NULL );

      internet_session_p->Close();
      delete internet_session_p;
      internet_session_p = reinterpret_cast< CInternetSession * >( NULL );
   }
   catch( ... )
   {
   }
}

void CFileTransferProtocol::GetFile( const CUniformResourceLocator& url, CByteArray& file_contents )
{
   WFCLTRACEINIT( TEXT( "CFileTransferProtocol::GetFile()" ) );

   // Start with an empty array
   file_contents.RemoveAll();

   CInternetSession * internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

   CFtpConnection * connection_p = reinterpret_cast< CFtpConnection * >( NULL );

   CByteArray read_buffer;

   try
   {
      CString temp_string;

      temp_string.Format( TEXT( "CFileTransferProtocol::GetFile( %s ) : %lu" ), (LPCTSTR) url, (DWORD) ::GetTickCount() );

      WFCTRACEVAL( TEXT( "Unique ID is " ), temp_string );

      try
      {
         internet_session_p = new CInternetSession( temp_string );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
         return;
      }
      catch( ... )
      {
         return;
      }

      try
      {
         connection_p = internet_session_p->GetFtpConnection( url.MachineName, m_UserName, m_Password );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
      }
      catch( ... )
      {
      }

      if ( connection_p == NULL )
      {
         internet_session_p->Close();
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

         return;
      }

      CInternetFile * source_file_p = reinterpret_cast< CInternetFile * >( NULL );

      try
      {
         source_file_p = connection_p->OpenFile( url.PathName );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
      }
      catch( ... )
      {
      }

      if ( source_file_p == NULL )
      {
         connection_p->Close();
         delete connection_p;
         connection_p = reinterpret_cast< CFtpConnection * >( NULL );

         internet_session_p->Close();
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

         return;
      }

      read_buffer.SetSize( 65535 * 4 ); // A really big buffer...
      source_file_p->SetReadBufferSize( read_buffer.GetSize() );

      UINT number_of_bytes_read = 0;

      try
      {
         do
         {
            number_of_bytes_read = source_file_p->Read( read_buffer.GetData(), read_buffer.GetSize() );

            if ( number_of_bytes_read > 0 )
            {
               read_buffer.SetSize( number_of_bytes_read );
               file_contents.Append( read_buffer );
               read_buffer.SetSize( 65535 * 4 );
            }
         }
         while( number_of_bytes_read > 0 );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
      }
      catch( ... )
      {
      }

      source_file_p->Close();
      delete source_file_p;
      source_file_p = reinterpret_cast< CInternetFile * >( NULL );

      connection_p->Close();
      delete connection_p;
      connection_p = reinterpret_cast< CFtpConnection * >( NULL );

      internet_session_p->Close();
      delete internet_session_p;
      internet_session_p = reinterpret_cast< CInternetSession * >( NULL );
   }
   catch( ... )
   {
      try
      {
         internet_session_p->Close();
      }
      catch( ... )
      {
         ;
      }

      try
      {
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );
      }
      catch( ... )
      {
         ;
      }
   }
}

void CFileTransferProtocol::GetPassword( CString& password ) const
{
   password = m_Password;
}

void CFileTransferProtocol::GetUserName( CString& user_name ) const
{
   user_name = m_UserName;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CFileTransferProtocol::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CFileTransferProtocol at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_UserName is " ) << m_UserName << TEXT( "\n" );
   dump_context << TEXT( "   m_Passowrd is " ) << m_Password << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

BOOL CFileTransferProtocol::PutFile( const CUniformResourceLocator& url, const CByteArray& file_contents )
{
   WFCLTRACEINIT( TEXT( "CFileTransferProtocol::PutFile()" ) );

   CInternetSession * internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

   CFtpConnection * connection_p = reinterpret_cast< CFtpConnection * >( NULL );

   CByteArray read_buffer;

   BOOL return_value = FALSE;

   try
   {
      CString temp_string;

      temp_string.Format( TEXT( "CFileTransferProtocol::PutFile( %s ) : %lu" ), (LPCTSTR) url, (DWORD) ::GetTickCount() );

      WFCTRACEVAL( TEXT( "Unique ID is " ), temp_string );

      try
      {
         internet_session_p = new CInternetSession( temp_string );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
         return( FALSE );
      }
      catch( ... )
      {
         return( FALSE );
      }

      try
      {
         connection_p = internet_session_p->GetFtpConnection( url.MachineName, m_UserName, m_Password );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
         connection_p = reinterpret_cast< CFtpConnection * >( NULL );
      }
      catch( ... )
      {
         connection_p = reinterpret_cast< CFtpConnection * >( NULL );
      }

      if ( connection_p == NULL )
      {
         internet_session_p->Close();
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

         return( FALSE );
      }

      CInternetFile * source_file_p = reinterpret_cast< CInternetFile * >( NULL );

      try
      {
         source_file_p = connection_p->OpenFile( url.PathName, GENERIC_WRITE );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
         source_file_p = reinterpret_cast< CInternetFile * >( NULL );
      }
      catch( ... )
      {
         source_file_p = reinterpret_cast< CInternetFile * >( NULL );
      }

      if ( source_file_p == NULL )
      {
         connection_p->Close();
         delete connection_p;
         connection_p = reinterpret_cast< CFtpConnection * >( NULL );

         internet_session_p->Close();
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );

         return( FALSE );
      }

      try
      {
         source_file_p->Write( file_contents.GetData(), file_contents.GetSize() );
      }
      catch( CInternetException * exception_p )
      {
#if defined( _DEBUG )

         TCHAR error_message[ 513 ];

         ZeroMemory( error_message, sizeof( error_message ) );

         exception_p->GetErrorMessage( error_message, DIMENSION_OF( error_message ) );

         WFCTRACEVAL( TEXT( "Error is " ), CString( error_message ) );

#endif // _DEBUG
         exception_p->Delete();
         return_value = FALSE;
      }
      catch( ... )
      {
         return_value = FALSE;
      }

      return_value = TRUE;

      source_file_p->Close();
      delete source_file_p;
      source_file_p = reinterpret_cast< CInternetFile * >( NULL );

      connection_p->Close();
      delete connection_p;
      connection_p = reinterpret_cast< CFtpConnection * >( NULL );

      internet_session_p->Close();
      delete internet_session_p;
      internet_session_p = reinterpret_cast< CInternetSession * >( NULL );
   }
   catch( ... )
   {
      try
      {
         internet_session_p->Close();
      }
      catch( ... )
      {
         ;
      }

      try
      {
         delete internet_session_p;
         internet_session_p = reinterpret_cast< CInternetSession * >( NULL );
      }
      catch( ... )
      {
         ;
      }
   }

   return( return_value );
}

void CFileTransferProtocol::SetPassword( const CString& password )
{
   m_Password = password;
}

void CFileTransferProtocol::SetUserName( const CString& user_name )
{
   m_UserName = user_name;
}

#endif // WFC_STL

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CFileTransferProtocol</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that encapsulates FTP (file transfer protocol).">
</HEAD>

<BODY>

<H1>CFileTransferProtocol</H1>

$Revision: 14 $
<HR>

<H2>Description</H2>

This class simplifies FTP. It solves the problem of getting a single
file or a directory listing from an FTP server.

<H2>Constructors</H2>

<DL COMPACT>

<DT><B>CFileTransferProtocol</B>( LPCTSTR user_name = NULL, LPCTSTR password = NULL )</PRE><DD>
Constructs the object. If <CODE>user_name</CODE> is NULL, &quot;anonymous&quot;
will be used instead. If <CODE>password</CODE> is NULL, an e-mail address
will be created using the current user
name (retrieved via <B>GetUsername</B>()) and the dotted IP address
(retrieved via <A HREF="SOCKETS.htm">CSimpleSocket</A>::GetMyAddress())
of the computer. For example, if your user name is &quot;Bob&quot; and
your IP address is 1.2.3.4, the default password will be
&quot;Bob@1.2.3.4&quot;.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>GetDirectory</B>( const <A HREF="CURL.htm">CUniformResourceLocator</A>&amp; url, CStringArray&amp; directory )</PRE><DD>
Retrieves the directory listing from the URL given. For example,
&quot;ftp://ftp.microsoft.com/bussys&quot;

<DT><PRE>void <B>GetFile</B>( const <A HREF="CURL.htm">CUniformResourceLocator</A>&amp; url, CByteArray&amp; file_contents )</PRE><DD>
Retrieves the file specified in <CODE>url</CODE> and puts it into <CODE>file_contents</CODE>.

<DT><PRE>void <B>GetPassword</B>( CString&amp; password ) const</PRE><DD>
Retrieves the password to be used to log in to the ftp servers.

<DT><PRE>void <B>GetUserName</B>( CString&amp; user_name ) const</PRE><DD>
Retrieves the login ID to be used when logging in to ftp servers.

<DT><PRE>BOOL <B>PutFile</B>( const <A HREF="CURL.htm">CUniformResourceLocator</A>&amp; url, const CByteArray&amp; file_contents )</PRE><DD>
Sends the contents of <CODE>file_contents</CODE> to the ftp server specified in <CODE>url</CODE>.
It will return TRUE if the contents were sent, FALSE if it didn't.

<DT><PRE>void <B>SetPassword</B>( const CString&amp; password )</PRE><DD>
Sets the password to be used to log in to the ftp servers.

<DT><PRE>void <B>SetUserName</B>( const CString&amp; user_name )</PRE><DD>
Sets the login ID to be used when logging in to ftp servers.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;

void test_CFileTransferProtocol( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CFileTransferProtocol()&quot; ) );

   <B>CFileTransferProtocol</B> ftp;

   CStringArray directory;

   <A HREF="CURL.htm">CUniformResourceLocator</A> url( TEXT( &quot;ftp://ftp.microsoft.com/&quot; ) );

   ftp.GetDirectory( url, directory );

   _tprintf( TEXT( &quot;Directory for %s\n&quot; ), (LPCTSTR) url );

   int index = 0;

   while( index < directory.GetSize() )
   {
      WFCTRACE( directory.GetAt( index ) );
      _tprintf( TEXT( &quot;%s\n&quot; ), (LPCTSTR) directory.GetAt( index ) );
      index++;
   }

   CByteArray file_contents;

   url = TEXT( &quot;ftp://ftp.microsoft.com/disclaimer.txt&quot; );

   ftp.GetFile( url, file_contents );

   _tprintf( TEXT( &quot;Retrieved %d bytes\n&quot; ), (int) file_contents.GetSize() );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CFileTransferProtocol.cpp $<BR>
$Modtime: 1/04/00 5:15a $
</BODY>

</HTML>
#endif
