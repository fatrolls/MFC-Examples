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
** $Workfile: CSharedMemoryObject.cpp $
** $Revision: 4 $
** $Modtime: 3/17/00 4:36p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CSharedMemoryObject::CSharedMemoryObject()
{
   WFCLTRACEINIT( TEXT( "CSharedMemoryObject::CSharedMemoryObject()" ) );
   m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;
   m_Pointer   = NULL;
   m_Size      = 0;
}

CSharedMemoryObject::~CSharedMemoryObject()
{
   WFCLTRACEINIT( TEXT( "CSharedMemoryObject::~CSharedMemoryObject()" ) );

   Close();

   m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;
   m_Pointer   = NULL;
   m_Size      = 0;
}

void CSharedMemoryObject::Close( void )
{
   WFCLTRACEINIT( TEXT( "CSharedMemoryObject::Close()" ) );

   if ( m_MapHandle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      return;
   }

   if ( m_Pointer != NULL )
   {
      if ( ::UnmapViewOfFile( m_Pointer ) == FALSE )
      {
         WFCTRACEERROR( ::GetLastError() );
      }

      m_Pointer = NULL;
   }

   if ( ::CloseHandle( m_MapHandle ) == FALSE )
   {
      WFCTRACEERROR( ::GetLastError() );
   }

   m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;
   m_Size = 0;
   m_Name.Empty();
}

BOOL CSharedMemoryObject::Create( const CString& object_name, DWORD size_in_bytes )
{
   WFCLTRACEINIT( TEXT( "CSharedMemoryObject::Create()" ) );

   Close();

   m_MapHandle = ::CreateFileMapping( reinterpret_cast< HANDLE >( 0xFFFFFFFF ),
                                      NULL,
                                      PAGE_READWRITE,
                                      0,
                                      size_in_bytes,
                                      object_name );

   if ( m_MapHandle == NULL )
   {
      WFCTRACEERROR( ::GetLastError() );
      WFCTRACE( TEXT( "Errored while trying to CreateFileMapping()" ) );
      m_MapHandle = (HANDLE) INVALID_HANDLE_VALUE;
      return( FALSE );
   }

   m_Size = size_in_bytes;
   m_Name = object_name;

   m_Pointer = ::MapViewOfFile( m_MapHandle, FILE_MAP_ALL_ACCESS, 0, 0, m_Size );

   if ( m_Pointer == NULL )
   {
      WFCTRACEERROR( ::GetLastError() );
      Close();
      return( FALSE );
   }

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CSharedMemoryObject</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that make handling shared memory easy.">
</HEAD>

<BODY>

<H1>CSharedMemoryObject</H1>
$Revision: 4 $<BR>
<HR>

<H2>Description</H2>

This class allows you to create shared memory objects easily.
A shared memory segment is a chunk of memory that is shared
between multiple processes in a system. Shared memory is
great for things like holding status information. For example,
you could have a process that reads position information from
a GPS unit and puts it into shared memory. You could have many
other applications connect to that shared memory and read the
position data.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the object. You can no longer use the pointer.

<DT><PRE>BOOL <B>Create</B>( const CString&amp; object_name, DWORD size_in_bytes )</PRE><DD>
Creates a shared memory object. If the object specified by
<CODE>object_name</CODE> already exists, you will attach to it. In other
words, when <B>Create</B>() returns TRUE, you will have a shared
memory object whether it was newly created or attached to an existing one.

<DT><PRE>void <B>GetName</B>( CString&amp; object_name ) const</PRE><DD>
Returns the name of the shared memory object.

<DT><PRE>void * <B>GetPointer</B>( void ) const</PRE><DD>
Returns the pointer to the shared memory segment. It will return
NULL if <B>Create</B>() has not yet been called.

<DT><PRE>DWORD <B>GetSize</B>( void ) const</PRE><DD>
Returns the size in bytes fo the shared memory object. It
will return zero if <B>Create</B>() has not yet been called.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void update_time( constCString&amp queue_name )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;update_time()&quot; ) );

   <B>CSharedMemoryObject</B> queue;

   if ( queue.<B>Create</B>( queue_name, sizeof( APPLICATION_QUEUE ) != FALSE )
   {
      APPLICATION_QUEUE * queue_p = NULL;

      queue_p = (APPLICATION_QUEUE *) queue.<B>GetPointer</B>();

      if ( queue_p != NULL )
      {
         <A HREF="CSystemTime.htm">CSystemTime</A> system_time;

         system_time.Get();

         queue_p-&gt;last_updated = system_time;
      }
   }
}</CODE></PRE>

<H2>API's Used</H2>

<UL>
<LI>CloseHandle
<LI>CreateFileMapping
<LI>GetLastError
<LI>MapViewOfFile
<LI>UnmapViewOfFile
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CSharedMemoryObject.cpp $<BR>
$Modtime: 3/17/00 4:36p $
</BODY>

</HTML>
#endif
