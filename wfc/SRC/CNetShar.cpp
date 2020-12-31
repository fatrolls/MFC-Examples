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
** $Workfile: cnetshar.cpp $
** $Revision: 27 $
** $Modtime: 3/12/00 8:30a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/*
** CNetworkShareInformation stuff
*/

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkShareInformation, CObject, 1 )
IMPLEMENT_SERIAL( CNetworkShares, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkShareInformation::CNetworkShareInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::CNetworkShareInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkShareInformation::CNetworkShareInformation( const SHARE_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::CNetworkShareInformation( SHARE_INFO_1 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkShareInformation::CNetworkShareInformation( const SHARE_INFO_2 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::CNetworkShareInformation( SHARE_INFO_2 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkShareInformation::CNetworkShareInformation( const CNetworkShareInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::CNetworkShareInformation( CNetworkShareInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkShareInformation::~CNetworkShareInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::~CNetworkShareInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkShareInformation::Copy( const SHARE_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::Copy( SHARE_INFO_1 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->shi1_netname, NetworkName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->shi1_remark,  Remark      );

      Type = source->shi1_type;
   }
   catch( ... )
   {
      Empty();
   }
}

void CNetworkShareInformation::Copy( const SHARE_INFO_2 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::Copy( SHARE_INFO_2 * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->shi2_netname, NetworkName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->shi2_remark,  Remark  );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->shi2_path,    PathName    );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->shi2_passwd,  Password  );

      Type                = source->shi2_type;
      Permissions         = source->shi2_permissions;
      MaximumNumberOfUses = source->shi2_max_uses;
      CurrentNumberOfUses = source->shi2_current_uses;
   }
   catch( ... )
   {
      Empty();
   }
}

void CNetworkShareInformation::Copy( const CNetworkShareInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   NetworkName         = source.NetworkName;
   Type                = source.Type;
   Remark              = source.Remark;
   Permissions         = source.Permissions;
   MaximumNumberOfUses = source.MaximumNumberOfUses;
   CurrentNumberOfUses = source.CurrentNumberOfUses;
   PathName            = source.PathName;
   Password            = source.Password;
}

void CNetworkShareInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::Empty()" ) );
   m_Initialize();
}

void CNetworkShareInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::m_Initialize()" ) );
   NetworkName.Empty();
   Type                = 0;
   Remark.Empty();
   Permissions         = 0;
   MaximumNumberOfUses = 0;
   CurrentNumberOfUses = 0;
   PathName.Empty();
   Password.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkShareInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkShareInformation::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << NetworkName;
      archive << Type;
      archive << Remark;
      archive << Permissions;
      archive << MaximumNumberOfUses;
      archive << CurrentNumberOfUses;
      archive << PathName;
      archive << Password;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> NetworkName;
      archive >> Type;
      archive >> Remark;
      archive >> Permissions;
      archive >> MaximumNumberOfUses;
      archive >> CurrentNumberOfUses;
      archive >> PathName;
      archive >> Password;
   }
}

#endif // WFC_NO_SERIALIZATION

const CNetworkShareInformation& CNetworkShareInformation::operator = ( const CNetworkShareInformation& source )
{
   ASSERT( this != &source );

   if ( this != &source )
   {
      Copy( source );
   }

   return( *this );
}

/*
** CNetworkConnections Stuff
*/

CNetworkShares::CNetworkShares()
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::CNetworkShares()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkShares::CNetworkShares( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::CNetworkShares( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   Open( machine_name );
}

CNetworkShares::~CNetworkShares()
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::~CNetworkShares()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Initialize();
}

BOOL CNetworkShares::Add( CNetworkShareInformation& share_to_add )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::Add()" ) );

   // Network APIs think only in UNICODE. Yes, Microsoft screwed up the
   // function prototypes...

   WCHAR wide_network_name[ 1024 ];
   WCHAR wide_remark[ 1024 ];
   WCHAR wide_path[ 1024 ];
   WCHAR wide_password[ 1024 ];

   _tcscpy( (LPTSTR) wide_network_name, share_to_add.NetworkName );
   _tcscpy( (LPTSTR) wide_remark,       share_to_add.Remark      );
   _tcscpy( (LPTSTR) wide_path,         share_to_add.PathName    );
   _tcscpy( (LPTSTR) wide_password,     share_to_add.Password    );

   // Thanks go to Mark Brakstor (markb@vdr.com) for finding a bug here.

#if ! defined( UNICODE )
   ::ASCII_to_UNICODE( (const char *) share_to_add.NetworkName, wide_network_name );
   ::ASCII_to_UNICODE( (const char *) share_to_add.Remark,      wide_remark       );
   ::ASCII_to_UNICODE( (const char *) share_to_add.PathName,    wide_path         );
   ::ASCII_to_UNICODE( (const char *) share_to_add.Password,    wide_password     );
#endif // UNICODE

   SHARE_INFO_2 share_info_2;

   ::ZeroMemory( &share_info_2, sizeof( share_info_2 ) );

   share_info_2.shi2_netname      = (LMSTR) wide_network_name;
   share_info_2.shi2_type         = share_to_add.Type;
   share_info_2.shi2_remark       = (LMSTR) wide_remark;
   share_info_2.shi2_permissions  = share_to_add.Permissions;
   share_info_2.shi2_max_uses     = share_to_add.MaximumNumberOfUses;
   share_info_2.shi2_current_uses = share_to_add.CurrentNumberOfUses;
   share_info_2.shi2_path         = (LMSTR) wide_path;
   share_info_2.shi2_passwd       = (LMSTR) wide_password;

   DWORD parameter_error = 0;

   m_ErrorCode = ::NetShareAdd( (LMSTR) m_WideMachineName,
                                        2,
                              (LPBYTE) &share_info_2,
                                       &parameter_error );

   if ( m_ErrorCode == NERR_Success )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACEVAL( TEXT( "OOPS! Can't NetShareAdd, parameter error " ), parameter_error );
      return( FALSE );
   }
}

DWORD CNetworkShares::Check( const CString& name_of_device )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::Check()" ) );

   // Network APIs think only in UNICODE. Yes, Microsoft screwed up the
   // function prototypes...

   WCHAR wide_device_name[ 4096 ];

   ::ZeroMemory( wide_device_name, sizeof( wide_device_name ) );

   _tcscpy( (LPTSTR) wide_device_name, name_of_device );

#if ! defined( UNICODE )
   ::ASCII_to_UNICODE( (const char *) name_of_device, wide_device_name );
#endif // UNICODE

   DWORD device_type = 0;

   m_ErrorCode = ::NetShareCheck( (LMSTR) m_WideMachineName,
                                  (LMSTR) wide_device_name,
                                         &device_type );
   
   if ( m_ErrorCode == NERR_Success )
   {
      return( device_type );
   }
   else
   {
      return( 0 );
   }
}

void CNetworkShares::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::Close()" ) );

   CNetwork::Close();

   if ( m_2InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer = NULL;
   }

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 1" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }
}

BOOL CNetworkShares::Delete( CNetworkShareInformation& share_to_delete )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::Delete()" ) );

   // Network APIs think only in UNICODE. Yes, Microsoft screwed up the
   // function prototypes...

   WCHAR wide_network_name[ 1024 ];

   _tcscpy( (LPTSTR) wide_network_name, share_to_delete.NetworkName );

#if ! defined( UNICODE )
   ::ASCII_to_UNICODE( (const char *) share_to_delete.NetworkName, wide_network_name );
#endif // UNICODE

   m_ErrorCode = ::NetShareDel( (LMSTR) m_WideMachineName,
                                (LMSTR) wide_network_name,
                                        0 );

   if ( m_ErrorCode == NERR_Success )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

void CNetworkShares::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::m_Initialize()" ) );
   m_ErrorCode             = 0;
   m_2Index                = 0;
   m_2InformationBuffer    = NULL;
   m_2ResumeHandle         = 0;
   m_2CurrentEntryNumber   = 0;
   m_2NumberOfEntriesRead  = 0;
   m_2TotalNumberOfEntries = 0;
   m_1Index                = 0;
   m_1InformationBuffer    = NULL;
   m_1ResumeHandle         = 0;
   m_1CurrentEntryNumber   = 0;
   m_1NumberOfEntriesRead  = 0;
   m_1TotalNumberOfEntries = 0;
}

BOOL CNetworkShares::Enumerate( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::Enumerate()" ) );

   if ( m_2InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer = NULL;
   }

   m_2Index                = 0;
   m_2CurrentEntryNumber   = 0;
   m_2NumberOfEntriesRead  = 0;
   m_2ResumeHandle         = 0;
   m_2TotalNumberOfEntries = 0;

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 1" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }

   m_1Index                = 0;
   m_1CurrentEntryNumber   = 0;
   m_1NumberOfEntriesRead  = 0;
   m_1ResumeHandle         = 0;
   m_1TotalNumberOfEntries = 0;

   return( m_GetChunk() );
}

BOOL CNetworkShares::GetNext( CNetworkShareInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::GetNext()" ) );

   // We need to see which buffer we're working with...

   if ( m_2InformationBuffer != NULL )
   {
      if ( m_2Index < m_2NumberOfEntriesRead )
      {
         information.Copy( &m_2InformationBuffer[ m_2Index ] );
         m_2Index++;

         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }
   else if ( m_1InformationBuffer != NULL )
   {
      if ( m_1Index < m_1NumberOfEntriesRead )
      {
         information.Copy( &m_1InformationBuffer[ m_1Index ] );
         m_1Index++;
         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }

   information.Empty();
   return( FALSE );
}

BOOL CNetworkShares::m_GetChunk( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::m_GetChunk()" ) );

   // Try to get the most information as possible. Start off by asking for
   // data that requires lots of security access privileges

   m_2Index = 0;

   // Let's see if we have already been reading

   if ( m_2NumberOfEntriesRead != 0 && m_2ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer        = NULL;
      m_2CurrentEntryNumber       = 0;
      m_2NumberOfEntriesRead      = 0;
      m_2ResumeHandle             = 0;
      m_2TotalNumberOfEntries     = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetShareEnum( (LMSTR) m_WideMachineName,
                                         2, 
                             (LPBYTE *) &m_2InformationBuffer,
                                         64 * 1024,
                                        &m_2NumberOfEntriesRead,
                                        &m_2TotalNumberOfEntries,
                                        &m_2ResumeHandle );

   if ( m_ErrorCode == NERR_Success || m_ErrorCode == ERROR_MORE_DATA )
   {
      if ( m_ErrorCode == NERR_Success )
      {
         m_2ResumeHandle = 0;
      }

      return( TRUE );
   }

   // Make really sure the OS didn't modify our variables...

   if ( m_2InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer = NULL;
   }

   m_2CurrentEntryNumber   = 0;
   m_2NumberOfEntriesRead  = 0;
   m_2ResumeHandle         = 0;
   m_2TotalNumberOfEntries = 0;

   if ( m_ErrorCode == ERROR_ACCESS_DENIED )
   {
      WFCTRACE( TEXT( "Access is denied, trying at a lower level" ) );

      m_1Index = 0;

      // Let's see if we have already been reading

      if ( m_1NumberOfEntriesRead != 0 && m_1ResumeHandle == NULL )
      {
         // Yup, we've finished reading
         WFCTRACE( TEXT( "Freeing Buffer 1" ) );
         ::NetApiBufferFree( m_1InformationBuffer );
         m_1InformationBuffer        = NULL;
         m_1CurrentEntryNumber       = 0;
         m_1NumberOfEntriesRead      = 0;
         m_1ResumeHandle             = 0;
         m_1TotalNumberOfEntries     = 0;
         return( FALSE );
      }

      m_ErrorCode = ::NetShareEnum( (LMSTR) m_WideMachineName,
                                            1, 
                                (LPBYTE *) &m_1InformationBuffer,
                                            64 * 1024,
                                           &m_1NumberOfEntriesRead,
                                           &m_1TotalNumberOfEntries,
                                           &m_1ResumeHandle );


      if ( m_ErrorCode == NERR_Success || m_ErrorCode == ERROR_MORE_DATA )
      {
         WFCTRACE( TEXT( "Got lower level information" ) );

         if ( m_ErrorCode == NERR_Success )
         {
            m_1ResumeHandle = 0;
         }

         return( TRUE );
      }
   }

   return( FALSE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkShares::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkShares::Serialize()" ) );

   CNetwork::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << m_ErrorCode;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> m_ErrorCode;
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetworkShares</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles network shares.">
</HEAD>

<BODY>

<H1>CNetworkShares : <A HREF="CNetwork.htm">CNetwork</A></H1>
$Revision: 27 $<BR>
<HR>

<H2>Description</H2>
This class allows you to add, delete or enumerate shares in Win32.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CNetworkShares</B>()
<B>CNetworkShares</B>( LPCTSTR machine_name )</PRE><DD>
Creates the object and let's you specify which machine to 
execute on (i.e. which machine's shares you want to play with).

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>Add</B>( const CNetworkShareInformation&amp; share_to_add )</PRE><DD>
Creates a new share with the options you specify.
The return value will be TRUE if the share was created, FALSE otherwise.

<DT><PRE>BOOL <B>Check</B>( LPCTSTR computer_name = NULL, DWORD type = accountMachine )</PRE><DD>
Checks whether or not a computer is sharing a device.
The return value will be TRUE if the device is shared, FALSE otherwise.

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the connection with the machine and cleans up any
internal buffers used.

<DT><PRE>BOOL <B>Delete</B>( const CNetworkShareInformation&amp; share_to_delete )</PRE><DD>
Deletes a share.
The return value will be TRUE if the share was deleted, FALSE otherwise.

<DT><PRE>BOOL <B>Enumerate</B>( void )</PRE><DD>
Initializes the object for enumeration.

<DT><PRE>BOOL <B>GetNext</B>( CNetworkShareInformation&amp; information )</PRE><DD>
Retrieves the next CNetworkShareInformation.
When you reach the end of the list, <B>GetNext</B>() will return FALSE.

</DL>

<H2>Example</H2>

<PRE><CODE>void test_CNetworkShares( LPCTSTR machine_name )
{
   <A HREF="Wfctrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CNetworkShares()&quot; ) );

   <B>CNetworkShares</B> shares( machine_name );

   CNetworkShareInformation share_information;

   if ( shares.Enumerate() != FALSE )
   {
      _tprintf( TEXT( &quot;Share Information for %s:\n&quot; ), (LPCTSTR) shares.GetMachineName() );

      while( shares.GetNext( share_information ) != FALSE )
      {
         _tprintf( TEXT( &quot; NetworkName         - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) share_information.NetworkName         );
         _tprintf( TEXT( &quot; Type                - %lu &quot; ),               share_information.Type                );

         switch( share_information.Type )
         {
            case STYPE_DISKTREE:

               _tprintf( TEXT( &quot;Disk&quot; ) );
               break;

            case STYPE_PRINTQ:

               _tprintf( TEXT( &quot;Printer&quot; ) );
               break;

            case STYPE_DEVICE:

               _tprintf( TEXT( &quot;Communications Device&quot; ) );
               break;

            case STYPE_IPC:

               _tprintf( TEXT( &quot;IPC&quot; ) );
               break;

            case STYPE_DFS:

               _tprintf( TEXT( &quot;Distributed File System&quot; ) );
               break;

            case STYPE_SPECIAL:

               _tprintf( TEXT( &quot;Special&quot; ) );
               break;

            default:

               _tprintf( TEXT( &quot;Unknown Type&quot; ) );
               break;
         }

         _tprintf( TEXT( &quot;\n&quot; ) );
         _tprintf( TEXT( &quot; Remark              - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) share_information.Remark              );
         _tprintf( TEXT( &quot; Permissions         - %lu\n&quot; ),              share_information.Permissions         );
         _tprintf( TEXT( &quot; MaximumNumberOfUses - %d\n&quot; ),               share_information.MaximumNumberOfUses );
         _tprintf( TEXT( &quot; CurrentNumberOfUses - %d\n&quot; ),               share_information.CurrentNumberOfUses );
         _tprintf( TEXT( &quot; PathName            - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) share_information.PathName            );
         _tprintf( TEXT( &quot; Password            - \&quot;%s\&quot;\n\n&quot; ), (LPCTSTR) share_information.Password          );
      }
   }
   else
   {
      DWORD error_code = shares.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( &quot;CNetworkShares.Enumerate( share_information ), ErrorCode == %d \&quot;%s\&quot;\n&quot; ), error_code, (LPCTSTR) error_message );
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CNetworkShares</B> uses the following API's:

<UL>
<LI>NetApiBufferFree
<LI>NetShareAdd
<LI>NetShareCheck
<LI>NetShareDel
<LI>NetShareEnum
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cnetshar.cpp $<BR>
$Modtime: 3/12/00 8:30a $
</BODY>

</HTML>
#endif
