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
** $Workfile: CCriticalSectionGuard.cpp $
** $Revision: 7 $
** $Modtime: 1/04/00 5:09a $
*/

#if 0
<WFC_DOCUMENTATION>
<HTML>
<HEAD>
<TITLE>WFC - CCriticalSectionGuard</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Idiot proofs entering and exitting of critical sections.">
</HEAD>
<BODY>
<H1>CCriticalSectionGuard</H1>
$Revision: 7 $<BR>
<HR>
<H2>Description</H2>
This class makes it easy to use a <B>CCriticalSection</B> (an MFC class).
The critical section is entered in the contructor and left in the
destructor. This reduces coding mistakes when you have functions with
multiple returns. When the <B>CCriticalSectionGuard</B> class falls
out of scope, the critical section is unlocked. It makes cleanup easy.
This ensures that the critical section will be exitted no matter where
you choose to exit the function.
<H2>Constructors</H2>
<DL COMPACT>
<DT><PRE><B>CCriticalSectionGuard</B>( CCriticalSection * section )
<B>CCriticalSectionGuard</B>( CCriticalSection&amp; section )</PRE><DD>
Constructs the object. It calls the <B>Lock</B>() method of the
CCriticalSection. The destructor calls </B>Unlock</B>().
</DL>
<H2>Example</H2>
<PRE><CODE>void CMyClass::Method( void )
{
   <B>CCriticalSectionGuard</B> guard( m_MyCriticialSection );

   if ( ::GetTickCount() % 2 ) == 1 )
   {
      return;
   }

   if ( ::GetTickCount() % 5 ) == 0 )
   {
      return;
   }

   ::KillTimer( m_WindowHandle, 1 );
}</CODE></PRE>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: CCriticalSectionGuard.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>
</HTML>
</WFC_DOCUMENTATION>
#endif
