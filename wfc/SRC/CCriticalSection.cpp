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
** $Workfile: CCriticalSection.cpp $
** $Revision: 6 $
** $Modtime: 1/04/00 5:09a $
*/

// Change the next line to a 1 if you want your own CCriticalSection

#if 0 

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif

CCriticalSection::CCriticalSection()
{
   WFCLTRACEINIT( "CCriticalSection::CCriticalSection()" );
   WFCTRACEVAL( "pointer is ", (VOID *) this );

   ::InitializeCriticalSection( &m_CriticalSection );
}

CCriticalSection::~CCriticalSection()
{
   WFCLTRACEINIT( "CCriticalSection::~CCriticalSection()" );
   WFCTRACEVAL( "pointer is ", (VOID *) this );

   ::DeleteCriticalSection( &m_CriticalSection );
}

void CCriticalSection::Enter( void )
{
   WFCLTRACEINIT( "CCriticalSection::Enter()" );
   ::EnterCriticalSection( &m_CriticalSection );
}

void CCriticalSection::Exit( void )
{
   WFCLTRACEINIT( "CCriticalSection::Exit()" );
   ::LeaveCriticalSection( &m_CriticalSection );
}

#if( _WIN32_WINNT >= 0x0400 )

BOOL CCriticalSection::TryToEnter( void )
{
   WFCLTRACEINIT( "CCriticalSection::TryToEnter()" );

   BOOL return_value = FALSE;

   return_value = ::TryEnterCriticalSection( &m_CriticalSection );

   return( return_value );
}

#endif // _WIN32_WINNT

#endif // 0

#if 0
<WFC_DOCUMENTATION>
<HTML>
<HEAD>
<TITLE>WFC - CCriticalSection</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Obsolete encapsulation of critical sections.">
</HEAD>
<BODY>
<H1>CCriticalSection</H1>
$Revision: 6 $<BR>
<HR>
<H2>Description</H2>
This class allows you to play with critical sections. It is
obsolete since Microsoft added a CCriticalSection
class to MFC.
<H2>Data Members</H2>
None.
<H2>Methods</H2>
<DL COMPACT>
<DT><PRE>void <B>Enter</B>( void )</PRE><DD>
Blocks execution until the critical section can be entered.
<DT><PRE>void <B>Exit</B>( void )</PRE><DD>
Allows other threads to now enter the critical section.
<DT><PRE>BOOL <B>TryToEnter</B>( void )</PRE><DD>
Will attempt to enter the critical section. If is succeeds
then TRUE will be returned. If it cannot enter the critical
section the FALSE is immediately returned, no blocking takes
place.
</DL>
<H2>Example</H2>
<PRE><CODE>Sorry.</CODE></PRE>
<H2>API's Used</H2>
<DL COMPACT>
<LI>DeleteCriticalSection
<LI>EnterCriticalSection
<LI>InitializeCriticalSection
<LI>LeaveCriticalSection
<LI>TryEnterCriticalSection
</DL>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: CCriticalSection.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>
</HTML>
</WFC_DOCUMENTATION>
#endif
