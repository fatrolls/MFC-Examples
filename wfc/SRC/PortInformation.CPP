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
** $Workfile: PortInformation.CPP $
** $Revision: 13 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CPortInformation, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

CPortInformation::CPortInformation()
{
   WFCLTRACEINIT( TEXT( "CPortInformation::CPortInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CPortInformation::CPortInformation( const PORT_INFO_1 * source )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::CPortInformation( PORT_INFO_1 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPortInformation::CPortInformation( const PORT_INFO_2 * source )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::CPortInformation( PORT_INFO_2 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPortInformation::CPortInformation( const CPortInformation& source )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::CPortInformation( CPortInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPortInformation::~CPortInformation()
{
   WFCLTRACEINIT( TEXT( "CPortInformation::~CPortInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CPortInformation::Copy( const PORT_INFO_1 * source )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::Copy( PORT_INFO_1 )" ) );
   ASSERT( source != NULL );

   Empty();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      if ( source->pName != NULL )
      {
         Name = source->pName;
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CPortInformation::Copy( const PORT_INFO_2 * source )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::Copy( PORT_INFO_2 )" ) );
   ASSERT( source != NULL );

   Empty();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      if ( source->pPortName != NULL )
      {
         Name = source->pPortName;
      }

      if ( source->pMonitorName != NULL )
      {
         Monitor = source->pMonitorName;
      }

      if ( source->pDescription != NULL )
      {
         Description = source->pDescription;
      }

      Type = source->fPortType;

      TypeToString( Type, TypeName );
   }
   catch( ... )
   {
      Empty();
   }
}

void CPortInformation::Copy( const CPortInformation& source )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::Copy( const CPortInformation& source )" ) );

   Name     = source.Name;
   Monitor  = source.Monitor;
   Type     = source.Type;
   TypeToString( Type, TypeName );
}

void CPortInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CPortInformation::Empty()" ) );
   Name.Empty();
   Monitor.Empty();
   Description.Empty();
   TypeName.Empty();
   Type = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CPortInformation::Serialize( CArchive& archive )
{
   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << Name;
      archive << Monitor;
      archive << Description;
      archive << Type;
   }
   else
   {
      archive >> Name;
      archive >> Monitor;
      archive >> Description;
      archive >> Type;

      TypeToString( Type, TypeName );
   }
}

#endif // WFC_NO_SERIALIZATION

void CPortInformation::TypeToString( DWORD type, CString& string ) const
{
   WFCLTRACEINIT( TEXT( "CPortInformation::TypeToString()" ) );

   string.Empty(); // Always start out with an empty string

   if ( type & PORT_TYPE_WRITE )
   {
      string = TEXT( "Write" );
   }

   if ( type & PORT_TYPE_READ )
   {
      if ( string.GetLength() != 0 )
      {
         string += TEXT( ", " );
      }

      string += TEXT( "Read" );
   }

   if ( type & PORT_TYPE_REDIRECTED )
   {
      if ( string.GetLength() != 0 )
      {
         string += TEXT( ", " );
      }

      string += TEXT( "Redirected" );
   }

   if ( type & PORT_TYPE_NET_ATTACHED )
   {
      if ( string.GetLength() != 0 )
      {
         string += TEXT( ", " );
      }

      string += TEXT( "Net Attached" );
   }
}

CPortInformation& CPortInformation::operator = ( const CPortInformation& source )
{
   Copy( source );
   return( *this );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CPortInformation::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CPortInformation at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Name        = \"" ) << Name        << TEXT( "\"\n" );
   dump_context << TEXT( "   Monitor     = \"" ) << Monitor     << TEXT( "\"\n" );
   dump_context << TEXT( "   Description = \"" ) << Description << TEXT( "\"\n" );
   dump_context << TEXT( "   Type        =  "  ) << Type        << TEXT( "\n"   );
   dump_context << TEXT( "   TypeName    = \"" ) << TypeName    << TEXT( "\"\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CPortInformation</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>

<BODY>

<H1>CPortInformation : CObject</H1>
$Revision: 13 $<HR><H2>Description</H2>
This class provides that same basic infotmation as the PORT_INFO_2 data structure.

<H2>Data Members</H2>

<DL COMPACT>

<DT><DFN><B>Name</B></DFN><DD>Name of the port like "COM1:" or "LPT1:".
<DT><DFN><B>Monitor</B></DFN><DD>I ain't quite figured this one out yet.
<DT><DFN><B>Description</B></DFN><DD>Presumably the description the user typed
in when they shared this port.
<DT><DFN><B>Type</B></DFN><DD>What type the port is.
<DT><DFN><B>Type</B></DFN><DD>The type in human readable form.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><DFN><B>Copy</B></DFN><DD>Copies another CPortInformation or a PORT_INFO_1
structure or a PORT_INFO_2 structure.
<DT><DFN><B>Empty</B></DFN><DD>Clears all data members.
<DT><DFN><B>Serialize</B></DFN><DD>Saves/restores the object.
<DT><DFN><B>TypeToString</B></DFN><DD>Converts the Type member variable to a human
readable string.
</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: PortInformation.CPP $<BR>
$Modtime: 1/05/00 3:37a $
</BODY>

</HTML>
#endif
