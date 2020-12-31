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
** $Workfile: CGarbageCollector.cpp $
** $Revision: 16 $
** $Modtime: 1/17/00 9:05a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CGarbageCollector::CGarbageCollector()
{
   WFCLTRACEINIT( TEXT( "CGarbageCollector::CGarbageCollector()" ) );

   m_ReferenceCount = 0;
   m_SelfDestruct   = FALSE;
}

CGarbageCollector::~CGarbageCollector()
{
   WFCLTRACEINIT( TEXT( "CGarbageCollector::~CGarbageCollector()" ) );

   m_ReferenceCount = 0;
   m_SelfDestruct   = FALSE;
}

void CGarbageCollector::AddReference( void )
{
   WFCLTRACEINIT( TEXT( "CGarbageCollector::AddReference()" ) );

   ::InterlockedIncrement( (long *) &m_ReferenceCount );

   WFCTRACEVAL( TEXT( "Reference count is now " ), m_ReferenceCount );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CGarbageCollector::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CGarbageCollector at " ) << (VOID *) this    << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_ReferenceCount is " ) << m_ReferenceCount << TEXT( "\n" );
   dump_context << TEXT( "   m_SelfDestruct is   " );

   if ( m_SelfDestruct == FALSE )
   {
      dump_context << TEXT( "False\n" );
   }
   else
   {
      dump_context << TEXT( "True\n" );
   }

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

long CGarbageCollector::GetReferenceCount( void ) const
{
   return( m_ReferenceCount );
}

BOOL CGarbageCollector::GetSelfDestruct( void ) const
{
   return( m_SelfDestruct );
}

void CGarbageCollector::Release( BOOL * object_was_deleted )
{
   WFCLTRACEINIT( TEXT( "CGarbageCollector::Release()" ) );

   if ( m_ReferenceCount <= 0 )
   {
      WFCTRACE( TEXT( "Reference count is already zero!" ) );
      ASSERT( FALSE );
   }

   try
   {
      if ( ::InterlockedDecrement( (long *) &m_ReferenceCount ) == 0 )
      {
         if ( m_SelfDestruct != FALSE )
         {
            if ( object_was_deleted != NULL )
            {
               *object_was_deleted = TRUE;
            }

            delete this;
         }
         else
         {
            if ( object_was_deleted != NULL )
            {
               *object_was_deleted = FALSE;
            }
         }
      }
      else
      {
         if ( object_was_deleted != NULL )
         {
            *object_was_deleted = FALSE;
         }
      }
   }
   catch( ... )
   {
      // Do Nothing
   }
}

void CGarbageCollector::SetSelfDestruct( BOOL self_destruct )
{
   WFCLTRACEINIT( TEXT( "CGarbageCollector::SetSelfDestruct()" ) );

   if ( self_destruct != FALSE )
   {
      m_SelfDestruct = TRUE;
   }
   else
   {
      m_SelfDestruct = FALSE;
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CGarbageCollector</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that makes it easy to implement copy-on-write (reference counted) objects.">
</HEAD>

<BODY>

<H1>CGarbageCollector</H1>
$Revision: 16 $<HR>

<H2>Description</H2>
This class implements a simple garbage collector. You inherit from
<B>CGarbageCollector</B> and your class will self destruct when the
reference count reaches zero. <B>CGarbageCollector</B> should only
be set to self destruct when it has been created via <CODE>new</CODE>.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>AddReference</B>( void )</PRE><DD>
This increments the reference count and prevents the
object from being deleted.

<DT><PRE>void <B>Dump</B>( CDumpContext&amp; dump_context ) const</PRE><DD>
Present only in debug builds. Dumps interesting information about
<B>CGarbageCollector</B> to the <CODE>dump_context</CODE> provided.

<DT><PRE>BOOL <B>GetSelfDestruct</B>( void ) const</PRE><DD>
Returns whether this object will self destruct when the
reference count reaches zero.

<DT><PRE>long <B>GetReferenceCount</B>( void ) const</PRE><DD>
Returns the reference count.

<DT><PRE>void <B>Release</B>( BOOL * deleted = NULL )</PRE><DD>
Decrements the reference count and checks to see if it is zero.
If the reference count is zero, the object will self destruct
(i.e. call <CODE>delete this</CODE>). If <CODE>deleted</CODE> is
not NULL, it will be filled with TRUE if the object was deleted
or FALSE if there are still references to it somewhere.

<DT><PRE>void <B>SetSelfDestruct</B>( BOOL self_destruct = TRUE )</PRE><DD>
This should be called after <B>CGarbageCollector</B> has been
created via <CODE>new</CODE>.

</DL>

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

class CThreadData : public <B>CGarbageCollector</B>
{
   protected:

      DWORD m_Data;

   public:

      void SetData( DWORD data ) { m_Data = data; };
      DWORD GetData( void ) const { return( m_Data ); };
};

void worker_thread( void * parameter )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;worker_thread()&quot; ) );

   CThreadData * thread_data = (CThreadData *) parameter;

   // Make sure the thread data is around until we call Release
   thread_data-&gt;AddReference();

   // Go do something that takes a really long time

   Sleep( 10000 );

   thread_data-&gt;Release();
}

void start_thread( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;start_thread()&quot; ) );

   CThreadData * data_p = NULL;
   
   try
   {
      data_p = new CThreadData;
   }
   catch( ... )
   {
      return;
   }

   data_p-&gt;AddReference();
   data_p-&gt;SetSelfDestruct( TRUE );

   _beginthread( worker_thread, 0, data_p );

   Sleep( 0 );

   data_p-&gt;Release();
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CGarbageCollector.cpp $<BR>
$Modtime: 1/17/00 9:05a $
</BODY>

</HTML>
#endif
