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
** $Workfile: CQueue.cpp $
** $Revision: 23 $
** $Modtime: 1/17/00 9:10a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CQueue::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CQueue at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_AddIndex is    " ) << m_AddIndex    << TEXT( "\n" );
   dump_context << TEXT( "   m_GetIndex is    " ) << m_GetIndex    << TEXT( "\n" );
   dump_context << TEXT( "   m_Size is        " ) << m_Size        << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CQueue</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, queue">
<META name="description" content="The C++ class that gives you a high-performance thread-safe queue.">
</HEAD>

<BODY>

<H1>CQueue</H1>
$Revision: 23 $<HR>

<H2>Description</H2>

This class a simple, thread-safe but high-performance queue.
It allows one thread to add to the queue while another
thread can get from the queue <STRONG>without blocking</STRONG>.
Normally, getting something from a queue blocks anyone from
adding to that queue. This is a performance bottleneck.
<B>CQueue</B> was designed for speed.
<P>

<B>CQueue</B> automatically grows the queue when needed.
It is a first-in, first-out queue. In other words, the order in which
things were added to the queue is the order in which they will be
retrieved from the queue.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CQueue</B>( DWORD initial_queue_size = 1024 )</B></PRE><DD>
Constructs the object. You can specify an initial size for the queue.
The larger the queue the fewer the growth periods (which can be
expensive).

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="Add">Add</A></B>( DWORD new_item )
BOOL <B>Add</B>( void * item )</PRE><DD>
This is how you add something to the queue. The queue will
automatically grow to accomodate new items.

<DT><PRE>void <B><A NAME="Dump">Dump</A></B>( CDumpContext&amp; dump_context ) const</PRE><DD>
Present only in debug builds. Dumps interesting information about
<B>CQueue</B> to the <CODE>dump_context</CODE> provided.

<DT><PRE>void <B><A NAME="Empty">Empty</A></B>( void )</PRE><DD>
Empties the queue. There will be no entries in the queue
when you call this method.

<DT><PRE>BOOL <B><A NAME="Get">Get</A></B>( DWORD&amp; item )
BOOL <B>Get</B>( void * &amp; item )</PRE><DD>
This is how you get something from the queue. It will
return TRUE if a value was successfully retrieved from 
the queue. It will return FALSE when there is nothing
in the queue to pull.

<DT><PRE>DWORD <B><A NAME="GetLength">GetLength</A></B>( void ) const</PRE><DD>
Returns the number of items in the queue.
<B>Warning!</B> This method will prevent anything from being added
or gotten from the queue. It must prevent queue operations for
the time it takes to compute the number of elements in the queue.
In other words, calling this method is a performance hit.

<DT><PRE>DWORD <B><A NAME="GetMaximumLength">GetMaximumLength</A></B>( void ) const</PRE><DD>
Returns the maximum size of the current queue. This is <I>not</I>
the maximum number of things the queue can hold. It is the maximum
number of items the queue can hold before it enters a growth
period. Currently, when the queue fills, its size doubles.

</DL>

<H2>Performance</H2>

It is boring to use <B>CQueue</B> on a single-CPU machine. The chances
of entering a deadlock are pretty much nil. However, <B>CQueue</B>
really shines on multiple-CPU boxes.
To test this, I created a simple toy program that creates two threads.
One constantly adds to the test queue while the other thread constantly
gets from the test queue. Using a single locking mechanism
on a two-CPU machine, I was able to get this performance from the
queue code in a 30 second test:

<TABLE BORDER="0">
<TR><TD>Number of Adds</TD><TD>1,517,100 (50,570 operations per second)</TD></TR>
<TR><TD>Number of Gets</TD><TD>1,200,136 (40,004 operations per second)</TD></TR>
<TR><TD>Number of Items Left In Queue </TD><TD>316,974</TD></TR>
<TR><TD>Queue Grew To Maximum Size</TD><TD>524,288</TD></TR>
<TR><TD>Average CPU Usage</TD><TD>58%</TD></TR>
</TABLE>

Using the double-locking technique, I got these numbers:

<TABLE BORDER="0">
<TR><TD>Number of Adds</TD><TD>11,675,987 (389,199 operations per second)</TD></TR>
<TR><TD>Number of Gets</TD><TD>11,675,537 (389,184 operations per second)</TD></TR>
<TR><TD>Number of Items Left In Queue </TD><TD>462</TD></TR>
<TR><TD>Maximum Size</TD><TD>1024</TD></TR>
<TR><TD>Average CPU Usage</TD><TD>100%</TD></TR>
</TABLE>

As you can see, the double-locking mechanism is the best.

<B>CQueue</B>

<H2>Example</H2>

<PRE><CODE>void test_CQueue( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CQueue()&quot; ) );

   <B>CQueue</B> queue( 4 );

   queue.Add( 1 );
   queue.Add( 2 );
   queue.Add( 3 );

   WFCTRACE( TEXT( &quot;Next addition should cause growth&quot; ) );

   queue.Add( 4 );
   queue.Add( 5 );

   DWORD item = 0;

   while( queue.Get( item ) != FALSE )
   {
      WFCTRACEVAL( TEXT( &quot;Got &quot;, item ) );
   }

   queue.Add( 6 );
   queue.Add( 7 );
   queue.Add( 8 );

   queue.Get( item );

   queue.Add( 9 );
   queue.Add( 10 );

   while( queue.Get( item ) != FALSE )
   {
      WFCTRACEVAL( TEXT( &quot;Got &quot;, item ) );
   }
}</CODE></PRE>

<HR>

<I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CQueue.cpp $<BR>
$Modtime: 1/17/00 9:10a $
</BODY>

</HTML>
#endif
