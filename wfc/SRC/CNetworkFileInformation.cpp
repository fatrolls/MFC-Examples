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
** $Workfile: CNetworkFileInformation.cpp $
** $Revision: 8 $
** $Modtime: 1/04/00 5:18a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkFileInformation, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkFileInformation::CNetworkFileInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::CNetworkFileInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkFileInformation::CNetworkFileInformation( const FILE_INFO_3 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::CNetworkFileInformation( FILE_INFO_3 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkFileInformation::CNetworkFileInformation( const CNetworkFileInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::CNetworkFileInformation( CNetworkFileInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkFileInformation::~CNetworkFileInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::~CNetworkFileInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkFileInformation::Copy( const FILE_INFO_3 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->fi3_pathname, PathName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->fi3_username, UserName );

      ID            = source->fi3_id;
      Permissions   = source->fi3_permissions;
      NumberOfLocks = source->fi3_num_locks;
   }
   catch( ... )
   {
      m_Initialize();
      return;
   }
}

void CNetworkFileInformation::Copy( const CNetworkFileInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   ID            = source.ID;
   Permissions   = source.Permissions;
   NumberOfLocks = source.NumberOfLocks;
   PathName      = source.PathName;
   UserName      = source.UserName;
}

void CNetworkFileInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::Empty()" ) );
   m_Initialize();
}

void CNetworkFileInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::m_Initialize()" ) );
   UserName.Empty();
   PathName.Empty();
   ID            = 0;
   Permissions   = 0;
   NumberOfLocks = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkFileInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkFileInformation::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << UserName;
      archive << PathName;
      archive << ID;
      archive << Permissions;
      archive << NumberOfLocks;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> UserName;
      archive >> PathName;
      archive >> ID;
      archive >> Permissions;
      archive >> NumberOfLocks;
   }
}

#endif // WFC_NO_SERIALIZATION

const CNetworkFileInformation& CNetworkFileInformation::operator = ( const CNetworkFileInformation& source )
{
   ASSERT( this != &source );

   if ( this != &source )
   {
      Copy( source );
   }

   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetworkFileInformation</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles network files information.">
</HEAD>

<BODY>
<H1>CNetworkFileInformation : CObject</H1>
$Revision: 8 $<BR>
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
$Workfile: CNetworkFileInformation.cpp $<BR>
$Modtime: 1/04/00 5:18a $
</BODY>

</HTML>
#endif
