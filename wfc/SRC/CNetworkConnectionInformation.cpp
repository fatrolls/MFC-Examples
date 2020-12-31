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
** $Workfile: CNetworkConnectionInformation.cpp $
** $Revision: 9 $
** $Modtime: 1/04/00 5:16a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkConnectionInformation, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkConnectionInformation::CNetworkConnectionInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::CNetworkConnectionInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkConnectionInformation::CNetworkConnectionInformation( const CONNECTION_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::CNetworkConnectionInformation( CONNECTION_INFO_1 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkConnectionInformation::CNetworkConnectionInformation( const CNetworkConnectionInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::CNetworkConnectionInformation( CNetworkConnectionInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkConnectionInformation::~CNetworkConnectionInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::~CNetworkConnectionInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkConnectionInformation::Copy( const CONNECTION_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::Copy()" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->coni1_username, UserName );
      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) source->coni1_netname,  NetName  );

      ID            = source->coni1_id;
      Type          = source->coni1_type;
      NumberOfOpens = source->coni1_num_opens;
      NumberOfUsers = source->coni1_num_users;
      Time          = source->coni1_time;
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkConnectionInformation::Copy( const CNetworkConnectionInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Check to make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   ID            = source.ID;
   Type          = source.Type;
   NumberOfOpens = source.NumberOfOpens;
   NumberOfUsers = source.NumberOfUsers;
   Time          = source.Time;
   UserName      = source.UserName;
   NetName       = source.NetName;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetworkConnectionInformation::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "ID = "            ) << ID            << TEXT( "\n"   );
   dump_context << TEXT( "Type = "          ) << Type          << TEXT( "\n"   );
   dump_context << TEXT( "NumberOfOpens = " ) << NumberOfOpens << TEXT( "\n"   );
   dump_context << TEXT( "NumberOfUsers = " ) << NumberOfUsers << TEXT( "\n"   );
   dump_context << TEXT( "Time = "          ) << Time          << TEXT( "\n"   );
   dump_context << TEXT( "UserName = \""    ) << UserName      << TEXT( "\"\n" );
   dump_context << TEXT( "NetName = \""     ) << NetName       << TEXT( "\"\n" );
}

#endif // _DEBUG

void CNetworkConnectionInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::Empty()" ) );
   m_Initialize();
}

void CNetworkConnectionInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::m_Initialize()" ) );
   UserName.Empty();
   NetName.Empty();
   ID            = 0;
   Type          = 0;
   NumberOfUsers = 0;
   NumberOfOpens = 0;
   Time          = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkConnectionInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkConnectionInformation::Serialize()" ) );
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << ID;
      archive << Type;
      archive << NumberOfOpens;
      archive << NumberOfUsers;
      archive << UserName;
      archive << NetName;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> ID;
      archive >> Type;
      archive >> NumberOfOpens;
      archive >> NumberOfUsers;
      archive >> UserName;
      archive >> NetName;
   }
}

#endif // WFC_NO_SERIALIZATION

const CNetworkConnectionInformation& CNetworkConnectionInformation::operator=( const CNetworkConnectionInformation& source )
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
<TITLE>WFC - CNetworkConnectionInformation</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles network connections information.">
</HEAD>

<BODY>

<H1>CNetworkConnectionInformation : CObject</H1>
$Revision: 9 $<BR>
<HR>

<H2>Description</H2>
This class allows you to enumerate the network connections.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CNetworkConnectionInformation</B>()
<B>CNetworkConnectionInformation</B>( LPCTSTR machine_name )</PRE><DD>
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
$Workfile: CNetworkConnectionInformation.cpp $<BR>
$Modtime: 1/04/00 5:16a $
</BODY>

</HTML>
#endif
