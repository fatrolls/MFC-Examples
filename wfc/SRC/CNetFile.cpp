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
** $Workfile: cnetfile.cpp $
** $Revision: 23 $
** $Modtime: 3/12/00 8:14a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkFiles, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkFiles::CNetworkFiles()
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::CNetworkFiles()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkFiles::CNetworkFiles( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::CNetworkFiles( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   Open( machine_name );
}

CNetworkFiles::~CNetworkFiles()
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::~CNetworkFiles()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Initialize();
}

void CNetworkFiles::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::Close()" ) );

   CNetwork::Close();

   if ( m_103InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing 103 buffer" ) );
      ::NetApiBufferFree( m_103InformationBuffer );
      m_103InformationBuffer = NULL;
   }
}

BOOL CNetworkFiles::Close( CNetworkFileInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::Close()" ) );

   m_ErrorCode = ::NetFileClose( (LMSTR) m_WideMachineName, information.ID );

   if ( m_ErrorCode == NERR_Success )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

void CNetworkFiles::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::m_Initialize()" ) );
   m_ErrorCode               = 0;
   m_103Index                = 0;
   m_103InformationBuffer    = NULL;
   m_103ResumeHandle         = 0;
   m_103CurrentEntryNumber   = 0;
   m_103NumberOfEntriesRead  = 0;
   m_103TotalNumberOfEntries = 0;
}

BOOL CNetworkFiles::Enumerate( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::Enumerate()" ) );

   if ( m_103InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing 103 buffer" ) );
      ::NetApiBufferFree( m_103InformationBuffer );
      m_103InformationBuffer = NULL;
   }

   m_103Index                = 0;
   m_103CurrentEntryNumber   = 0;
   m_103NumberOfEntriesRead  = 0;
   m_103ResumeHandle         = 0;
   m_103TotalNumberOfEntries = 0;

   return( m_GetChunk() );
}

BOOL CNetworkFiles::GetNext( CNetworkFileInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::GetNext()" ) );

   if ( m_103InformationBuffer != NULL )
   {
      if ( m_103Index < m_103NumberOfEntriesRead )
      {
         information.Copy( &m_103InformationBuffer[ m_103Index ] );
         m_103Index++;

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

BOOL CNetworkFiles::m_GetChunk( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::m_GetChunk()" ) );

   m_103Index = 0;

   if ( m_103NumberOfEntriesRead != 0 && m_103ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 103" ) );
      ::NetApiBufferFree( m_103InformationBuffer );
      m_103InformationBuffer    = NULL;
      m_103CurrentEntryNumber   = 0;
      m_103NumberOfEntriesRead  = 0;
      m_103ResumeHandle         = 0;
      m_103TotalNumberOfEntries = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetFileEnum( (LMSTR) m_WideMachineName,
                                        NULL, 
                                        NULL, 
                                        3, 
                            (LPBYTE *) &m_103InformationBuffer,
                                        64 * 1024,
                                       &m_103NumberOfEntriesRead,
                                       &m_103TotalNumberOfEntries,
                                       &m_103ResumeHandle );

   if ( m_ErrorCode != NERR_Success || m_103InformationBuffer == NULL )
   {
      return( FALSE );
   }

   return( TRUE );
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkFiles::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkFiles::Serialize()" ) );

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
<TITLE>WFC - CNetworkFiles</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles network files.">
</HEAD>

<BODY>

<H1>CNetworkFiles : <A HREF="CNetwork.htm">CNetwork</A></H1>
$Revision: 23 $<BR>
<HR>

<H2>Description</H2>
This class allows you to NetFilexxx API in Win32.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><DFN><B>Close</B></DFN><DD>Closes the connection to the machine. If you pass
a CNetworkFileInformation object to Close, it will close that opened file.

<DT><DFN><B>Enumerate</B></DFN><DD>Initializes the object for enumeration.

<DT><DFN><B>GetNext</B></DFN><DD>Retrieves the next CNetworkFileInformation.
When you reach the end of the list, GetNext() will return FALSE.

<DT><DFN><B>Serialize</B></DFN><DD>After all we are a CObject...

</DL>

<H2>Example</H2>
<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cnetfile.cpp $<BR>
$Modtime: 3/12/00 8:14a $
</BODY>

</HTML>
#endif
