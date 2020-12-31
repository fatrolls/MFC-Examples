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
** $Workfile: RemoteAccessServicePort.CPP $
** $Revision: 17 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CRemoteAccessServicePort, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

// Construction

CRemoteAccessServicePort::CRemoteAccessServicePort()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::CRemoteAccessServicePort()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CRemoteAccessServicePort::CRemoteAccessServicePort( const CRemoteAccessServicePort& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::CRemoteAccessServicePort( const CRemoteAccessServicePort& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CRemoteAccessServicePort::CRemoteAccessServicePort( const RAS_PORT_0 * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::CRemoteAccessServicePort( const RAS_PORT_0 * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServicePort::CRemoteAccessServicePort( const RAS_PORT_1 * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::CRemoteAccessServicePort( const RAS_PORT_1 * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServicePort::~CRemoteAccessServicePort()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::~CRemoteAccessServicePort()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

// Methods

void CRemoteAccessServicePort::Copy( const RAS_PORT_0 * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::Copy( const RAS_PORT_0 * )" ) );
   ASSERT( source != NULL );

   // Choose to live
   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->wszPortName,    Name       );
      ::wfc_convert_lpcwstr_to_cstring( source->wszDeviceType,  DeviceType );
      ::wfc_convert_lpcwstr_to_cstring( source->wszDeviceName,  DeviceName );
      ::wfc_convert_lpcwstr_to_cstring( source->wszMediaName,   MediaName  );
      Flags   = source->Flags;
      ::wfc_convert_lpcwstr_to_cstring( source->wszUserName,    UserName        );
      ::wfc_convert_lpcwstr_to_cstring( source->wszComputer,    ComputerName    );
      SessionStartTime = CTime( source->dwStartSessionTime );
      ::wfc_convert_lpcwstr_to_cstring( source->wszLogonDomain, LogonDomainName );
      IsAdvancedServer = source->fAdvancedServer;

      // Now set the rest of the field to NULL
      LineCondition            = 0;
      HardwareCondition        = 0;
      LineSpeedInBitsPerSecond = 0;
      NumberOfStatistics       = 0;
      NumberOfMediaParameters  = 0;
      SizeOfMediaParameters    = 0;

      /*
      ** WARNING!!!!
      ** Someone at Microsoft let the children play in the header files again.
      ** In version 4.2 of Visual C++, the following RAS_PORT_0 structure member
      ** was called "MediaID", in the 4.2b patch, it was renamed to "reserved"
      ** There was no mention of it anywhere. I didn't find out about it until
      ** Patrick Clarke (pclarke@trintech.com) reported the problem. My fix is
      ** a real hack. I detest hacks! If anyone has a non-hacking way of dealing
      ** with data structures (not unions) containing random field names, please
      ** let me know.
      */

      DWORD temp_dword = ( ( (DWORD) source ) + offsetof( RAS_PORT_0, Flags ) ) - sizeof( DWORD );

      DWORD * address_of_randomly_named_field = (DWORD *) temp_dword;
      
      MediaID = *address_of_randomly_named_field;
   }
   catch( ... )
   {
      Empty();
   }
}

void CRemoteAccessServicePort::Copy( const RAS_PORT_1 * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::Copy( const RAS_PORT_1 * )" ) );
   ASSERT( source != NULL );

   // Choose to live
   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, do not trust it

   try
   {
      Copy( &source->rasport0 );

      // Now copy the non-RAS_PORT_0 stuff

      LineCondition            = source->LineCondition;
      HardwareCondition        = source->HardwareCondition;
      LineSpeedInBitsPerSecond = source->LineSpeed;
      NumberOfStatistics       = source->NumStatistics;
      NumberOfMediaParameters  = source->NumMediaParms;
      SizeOfMediaParameters    = source->SizeMediaParms;
   }
   catch( ... )
   {
      Empty();
   }
}

void CRemoteAccessServicePort::Copy( const CRemoteAccessServicePort& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::Copy( const CRemoteAccessServicePort& )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Name                     = source.Name;
   DeviceType               = source.DeviceType;
   DeviceName               = source.DeviceName;
   MediaName                = source.MediaName;
   MediaID                  = source.MediaID;
   Flags                    = source.Flags;
   UserName                 = source.UserName;
   ComputerName             = source.ComputerName;
   SessionStartTime         = source.SessionStartTime;
   LogonDomainName          = source.LogonDomainName;
   IsAdvancedServer         = source.IsAdvancedServer;
   LineCondition            = source.LineCondition;
   HardwareCondition        = source.HardwareCondition;
   LineSpeedInBitsPerSecond = source.LineSpeedInBitsPerSecond;
   NumberOfStatistics       = source.NumberOfStatistics;
   NumberOfMediaParameters  = source.NumberOfMediaParameters;
   SizeOfMediaParameters    = source.SizeOfMediaParameters;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CRemoteAccessServicePort::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CRemoteAccessServicePort at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   Name is                     " ) << Name                     << TEXT( "\n" );
   dump_context << TEXT( "   DeviceType is               " ) << DeviceType               << TEXT( "\n" );
   dump_context << TEXT( "   DeviceName is               " ) << DeviceName               << TEXT( "\n" );
   dump_context << TEXT( "   MediaName is                " ) << MediaName                << TEXT( "\n" );
   dump_context << TEXT( "   MediaID is                  " ) << MediaID;

   switch( MediaID )
   {
      case mediaSerial:

         dump_context << TEXT( " (Serial)\n" );
         break;

      case mediaUnknown:

         dump_context << TEXT( " (Unknown)\n" );
         break;

      case mediaRAS10Serial:

         dump_context << TEXT( " (RAS10 Serial)\n" );
         break;

      case mediaX25:

         dump_context << TEXT( " (X.25)\n" );
         break;

      case mediaISDN:

         dump_context << TEXT( " (ISDN)\n" );
         break;

      default:

         dump_context << TEXT( " (really unknown)\n" );
         break;
   }

   dump_context << TEXT( "   Flags is                    " ) << Flags;

   CString flags;

   if ( Flags & USER_AUTHENTICATED )
   {
      flags = TEXT( "USER_AUTHENTICATED" );
   }

   if ( Flags & MESSENGER_PRESENT )
   {
      if ( flags.GetLength() > 0 )
      {
         flags += TEXT( " | " );
      }

      flags += TEXT( "MESSENGER_PRESENT" );
   }

   if ( Flags & PPP_CLIENT )
   {
      if ( flags.GetLength() > 0 )
      {
         flags += TEXT( " | " );
      }

      flags += TEXT( "PPP_CLIENT" );
   }

   if ( Flags & GATEWAY_ACTIVE )
   {
      if ( flags.GetLength() > 0 )
      {
         flags += TEXT( " | " );
      }

      flags += TEXT( "GATEWAY_ACTIVE" );
   }

   if ( Flags & REMOTE_LISTEN )
   {
      if ( flags.GetLength() > 0 )
      {
         flags += TEXT( " | " );
      }

      flags += TEXT( "REMOTE_LISTEN" );
   }

   if ( Flags & PORT_MULTILINKED )
   {
      if ( flags.GetLength() > 0 )
      {
         flags += TEXT( " | " );
      }

      flags += TEXT( "PORT_MULTILINKED" );
   }

   dump_context << TEXT( "(" ) << flags << TEXT( ")\n" );

   dump_context << TEXT( "   UserName is                 " ) << UserName                 << TEXT( "\n" );
   dump_context << TEXT( "   ComputerName is             " ) << ComputerName             << TEXT( "\n" );
   dump_context << TEXT( "   SessionStartTime is         " ) << SessionStartTime         << TEXT( "\n" );
   dump_context << TEXT( "   LogonDomainName is          " ) << LogonDomainName          << TEXT( "\n" );
   
   if ( IsAdvancedServer != FALSE )
   {
      dump_context << TEXT( "   IsAdvancedServer is         TRUE\n" );
   }
   else
   {
      dump_context << TEXT( "   IsAdvancedServer is         FALSE\n" );
   }

   dump_context << TEXT( "   LineCondition is            " ) << LineCondition            << TEXT( "\n" );
   dump_context << TEXT( "   HardwareCondition is        " ) << HardwareCondition        << TEXT( "\n" );
   dump_context << TEXT( "   LineSpeedInBitsPerSecond is " ) << LineSpeedInBitsPerSecond << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfStatistics is       " ) << NumberOfStatistics       << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfMediaParameters is  " ) << NumberOfMediaParameters  << TEXT( "\n" );
   dump_context << TEXT( "   SizeOfMediaParameters is    " ) << SizeOfMediaParameters    << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CRemoteAccessServicePort::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::m_Initialize()" ) );
   Name.Empty();
   DeviceType.Empty();
   DeviceName.Empty();
   MediaName.Empty();
   MediaID                  = 0;
   Flags                    = 0;
   UserName.Empty();
   ComputerName.Empty();
   //SessionStartTime.Empty();
   LogonDomainName.Empty();
   IsAdvancedServer         = FALSE;
   LineCondition            = 0;
   HardwareCondition        = 0;
   LineSpeedInBitsPerSecond = 0;
   NumberOfStatistics       = 0;
   NumberOfMediaParameters  = 0;
   SizeOfMediaParameters    = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CRemoteAccessServicePort::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::Serialize()" ) );

   CObject::Serialize( archive );

   BYTE temp_bool = 0;

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Name;
      archive << DeviceType;
      archive << DeviceName;
      archive << MediaName;
      archive << MediaID;
      archive << Flags;
      archive << UserName;
      archive << ComputerName;
      archive << SessionStartTime;
      archive << LogonDomainName;

      if ( IsAdvancedServer != FALSE )
      {
         temp_bool = 1;
      }
      else
      {
         temp_bool = 0;
      }

      archive << temp_bool;
      archive << LineCondition;
      archive << HardwareCondition;
      archive << LineSpeedInBitsPerSecond;
      archive << NumberOfStatistics;
      archive << NumberOfMediaParameters;
      archive << SizeOfMediaParameters;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Name;
      archive >> DeviceType;
      archive >> DeviceName;
      archive >> MediaName;
      archive >> MediaID;
      archive >> Flags;
      archive >> UserName;
      archive >> ComputerName;
      archive >> SessionStartTime;
      archive >> LogonDomainName;
      archive >> temp_bool;

      if ( temp_bool == 0 )
      {
         IsAdvancedServer = FALSE;
      }
      else
      {
         IsAdvancedServer = TRUE;
      }

      archive >> LineCondition;
      archive >> HardwareCondition;
      archive >> LineSpeedInBitsPerSecond;
      archive >> NumberOfStatistics;
      archive >> NumberOfMediaParameters;
      archive >> SizeOfMediaParameters;
   }
}

#endif // WFC_NO_SERIALIZATION

// Operators

CRemoteAccessServicePort& CRemoteAccessServicePort::operator=( const CRemoteAccessServicePort& source )
{
   Copy( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRemoteAccessServicePort</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>

<BODY>

<H1>CRemoteAccessServicePort : CObject</H1>
$Revision: 17 $
<HR>

<H2>Description</H2>

This class is based on the RAS_USER_0 structure.

<H2>Data Members</H2>

<B>None.</B>

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Copy</B><DD>Copies another CRemoteAccessServicePort or a RAS_USER_0 structure.
<DT><B>Empty</B><DD>Clears all data members.
<DT><B>Serialize</B><DD>After all, we are a CObject . . .

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: RemoteAccessServicePort.CPP $<BR>
$Modtime: 1/05/00 3:43a $
</BODY>

</HTML>
#endif
