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
** $Workfile: wfc_UNICODE_floating_point_routines.cpp $
** $Revision: 3 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

double wfc_unicode_atof( LPCWSTR unicode_string )
{
   char ascii_string[ 4096 ];

   ascii_string[ 0 ] = 0x00;
   ascii_string[ 1 ] = 0x00;

   UNICODE_to_ASCII( unicode_string, ascii_string );

   return( atof( ascii_string ) );
}

// End of source