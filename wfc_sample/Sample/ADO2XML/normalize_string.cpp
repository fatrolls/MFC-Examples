#include "ado2xml.h"
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
** $Workfile: normalize_string.cpp $
** $Revision: 1 $
** $Modtime: 3/19/00 7:44a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void normalize_string( CString& string_to_normalize )
{
   replace( string_to_normalize, TEXT( "&"  ), TEXT( "&amp;"  ) );
   replace( string_to_normalize, TEXT( ">"  ), TEXT( "&gt;"   ) );
   replace( string_to_normalize, TEXT( "<"  ), TEXT( "&lt;"   ) );
   replace( string_to_normalize, TEXT( "\"" ), TEXT( "&quot;" ) );
   replace( string_to_normalize, TEXT( "'"  ), TEXT( "&apos;" ) );
}

