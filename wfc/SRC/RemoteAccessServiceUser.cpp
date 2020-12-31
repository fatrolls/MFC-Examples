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
** $Workfile: RemoteAccessServiceUser.cpp $
** $Revision: 16 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// 1999-07-18
// Thanks go to Vagif Abilov (vagif@online.no) for finding a bug here.
// I was not IMPLEMENT_SERIAL()'ing

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CRemoteAccessServiceUser, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CRemoteAccessServiceUser::CRemoteAccessServiceUser()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::CRemoteAccessServiceUser()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CRemoteAccessServiceUser::CRemoteAccessServiceUser( const CRemoteAccessServiceUser& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::CRemoteAccessServiceUser( CRemoteAccessServiceUser& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceUser::CRemoteAccessServiceUser( const RAS_USER_0 * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::CRemoteAccessServiceUser( RAS_USER_0 * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CRemoteAccessServiceUser::~CRemoteAccessServiceUser()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::~CRemoteAccessServiceUser()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CRemoteAccessServiceUser::Copy( const RAS_USER_0 * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::Copy( const RAS_USER_0 * )" ) );
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
      Privileges = source->bfPrivilege;
      ::wfc_convert_lpcwstr_to_cstring( source->szPhoneNumber, PhoneNumber );
   }
   catch( ... )
   {
      Empty();
   }
}

void CRemoteAccessServiceUser::Copy( const CRemoteAccessServiceUser& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::Copy( const CRemoteAccessServiceUser& )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Privileges  = source.Privileges;
   PhoneNumber = source.PhoneNumber;
}

void CRemoteAccessServiceUser::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServiceUser::Empty()" ) );
   Privileges = 0;
   PhoneNumber.Empty();
}

// 1999-07-18
// Thanks go to Vagif Abilov (vagif@online.no) for finding a bug here.
// I had forgotten to put in the assignment operator

CRemoteAccessServiceUser& CRemoteAccessServiceUser::operator = ( const CRemoteAccessServiceUser& source )
{
   if ( this != &source )
   {
      Copy( source );
   }

   return( *this );
}

// 1999-07-18
// Thanks go to Vagif Abilov (vagif@online.no) for finding a bug here.
// I had forgotten to put in the Dump() method

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )
 
void CRemoteAccessServiceUser::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "a CRemoteAccessServiceUser at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   Privileges is " )  << Privileges  << TEXT( "\n" );
   dump_context << TEXT( "   PhoneNumber is " ) << PhoneNumber << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG







// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRemoteAccessServiceUser</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>

<BODY>

<H1>CRemoteAccessServiceUser : CObject</H1>
$Revision: 16 $
<HR>

<H2>Description</H2>
This class is based on the RAS_USER_0 structure.

<H2>Data Members</H2>

<B>None.</B>

<H2>Methods</H2>

<DL COMPACT>
<DT><B>Copy</B><DD>Copies another CRemoteAccessServiceUser or a RAS_USER_0 structure.
</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: RemoteAccessServiceUser.cpp $<BR>
$Modtime: 1/05/00 3:43a $
</BODY>

</HTML>
#endif
