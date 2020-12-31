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
*/

// Change the following to 1 if you want to compile
// your own CWaitCursor class

#if 0

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CWaitCursor::CWaitCursor( int cursor_number )
{
   if ( cursor_number == 0 )
   {
      AfxGetApp()->BeginWaitCursor();
      m_PreviousCursorHandle = NULL;
   }
   else
   {
      HCURSOR cursor_handle = AfxGetApp()->LoadCursor( cursor_number );
      m_PreviousCursorHandle = ::SetCursor( cursor_handle );
   }
}
      
CWaitCursor::~CWaitCursor()
{
   if ( m_PreviousCursorHandle == NULL )
   {
      AfxGetApp()->EndWaitCursor();
   }
   else
   {
      ::SetCursor( m_PreviousCursorHandle );
   }
}

#endif // 0
