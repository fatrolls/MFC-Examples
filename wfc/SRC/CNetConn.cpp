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
** $Workfile: cnetconn.cpp $
** $Revision: 24 $
** $Modtime: 3/12/00 8:12a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkConnections, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkConnections::CNetworkConnections()
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::CNetworkConnections()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkConnections::CNetworkConnections( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::CNetworkConnections( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   Open( machine_name );
}

CNetworkConnections::~CNetworkConnections()
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::~CNetworkConnections()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Initialize();
}

void CNetworkConnections::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::Close()" ) );
   CNetwork::Close();

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetworkConnections::Dump( CDumpContext& dump_context ) const
{
   CNetwork::Dump( dump_context );

   dump_context << TEXT( "m_1ResumeHandle = "         ) << m_1ResumeHandle         << TEXT( "\n" );
   dump_context << TEXT( "m_1CurrentEntryNumber = "   ) << m_1CurrentEntryNumber   << TEXT( "\n" );
   dump_context << TEXT( "m_1NumberOfEntriesRead = "  ) << m_1NumberOfEntriesRead  << TEXT( "\n" );
   dump_context << TEXT( "m_1TotalNumberOfEntries = " ) << m_1TotalNumberOfEntries << TEXT( "\n" );
}

#endif // _DEBUG

BOOL CNetworkConnections::Enumerate( LPCTSTR share_or_computer_name )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::Enumerate()" ) );

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing first information buffer" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }

   if ( share_or_computer_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
#if ! defined( UNICODE )
      ::ASCII_to_UNICODE( share_or_computer_name, (LPWSTR) m_WideShareOrComputerName );
#else
      _tcscpy( m_WideShareOrComputerName, share_or_computer_name );
#endif // UNICODE

      m_1Index                = 0;
      m_1CurrentEntryNumber   = 0;
      m_1NumberOfEntriesRead  = 0;
      m_1ResumeHandle         = 0;
      m_1TotalNumberOfEntries = 0;

      return( m_GetChunk() );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CNetworkConnections::GetNext( CNetworkConnectionInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::GetNext()" ) );

   if ( m_1InformationBuffer != NULL )
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

BOOL CNetworkConnections::m_GetChunk( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkCOnnections::m_GetChunk()" ) );

   m_1Index = 0;

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

   m_ErrorCode = ::NetConnectionEnum( (LMSTR) m_WideMachineName,
                                      (LMSTR) m_WideShareOrComputerName, 
                                              1, 
                                  (LPBYTE *) &m_1InformationBuffer,
                                              64 * 1024,
                                             &m_1NumberOfEntriesRead,
                                             &m_1TotalNumberOfEntries,
                                             &m_1ResumeHandle );

   if ( m_ErrorCode == NERR_Success || m_ErrorCode == ERROR_MORE_DATA )
   {
      return( TRUE );
   }

   return( FALSE );
}

void CNetworkConnections::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::m_Initialize()" ) );
   m_ErrorCode             = 0;
   m_1InformationBuffer    = NULL;
   m_1ResumeHandle         = 0;
   m_1CurrentEntryNumber   = 0;
   m_1NumberOfEntriesRead  = 0;
   m_1TotalNumberOfEntries = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkConnections::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnections::Serialize()" ) );
   CNetwork::Serialize( archive );

   if ( archive.IsStoring() )
   {
      //archive << m_WideShareOrComputerName;
   }
   else
   {
      //archive >> m_WideShareOrComputerName;
   }
}

#endif // WFC_NO_SERIALIZATION

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetworkConnections</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles network connections.">
</HEAD>

<BODY>

<H1>CNetworkConnections : <A HREF="CNetwork.htm">CNetwork</A></H1>
$Revision: 24 $<BR>
<HR>

<H2>Description</H2>

This class allows you to enumerate the network connections.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CNetworkConnections</B>()
<B>CNetworkConnections</B>( LPCTSTR machine_name )</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the connection to the machine.

<DT><PRE>BOOL <B>Enumerate</B>( LPCTSTR share_or_computer_name )</PRE><DD>
Initializes the object for enumeration.

<DT><PRE>BOOL <B>GetNext</B>( CNetworkConnectionInformation&amp; information )</PRE><DD>
Retrieves the next set of connection information.

<DT><PRE>void <B>Serialize</B>( CArchive&amp; archive )</PRE><DD>
After all we are a CObject...

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>

<B>CNetworkConnections</B> uses the following API's:

<UL>
<LI>NetApiBufferFree
<LI>NetConnectionEnum
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cnetconn.cpp $<BR>
$Modtime: 3/12/00 8:12a $
</BODY>

</HTML>
#endif
