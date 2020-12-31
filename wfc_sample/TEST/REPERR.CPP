#include "test.h"
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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: REPERR.CPP $
** $Revision: 4 $
** $Modtime: 1/31/00 7:42p $
*/

void ReportError( DWORD error_code )
{
   LPVOID lpMessageBuffer;
   FormatMessage(
  FORMAT_MESSAGE_ALLOCATE_BUFFER |
  FORMAT_MESSAGE_FROM_SYSTEM,
  NULL,
  error_code,
  MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
  (LPTSTR) &lpMessageBuffer,
  0,
  NULL );

   OutputDebugString( (LPCTSTR) lpMessageBuffer );
   OutputDebugString( TEXT( "\n" ) );
   LocalFree( (HLOCAL) lpMessageBuffer );
}
