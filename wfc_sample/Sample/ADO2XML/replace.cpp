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
** $Workfile: replace.cpp $
** $Revision: 1 $
** $Modtime: 3/19/00 7:42a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void replace( CString& string, const CString& what_to_replace, const CString& what_to_replace_it_with )
{
   CString translated_string;

   int string_length = what_to_replace.GetLength();
   int location      = string.Find( what_to_replace );

   while( location >= 0 )
   {
      // Append the data up to the what_to_replace to our translated string

      translated_string += string.Left( location );
      translated_string += what_to_replace_it_with;

      string = string.Right( string.GetLength() - ( location + string_length ) );

      location = string.Find( what_to_replace );
   }

   translated_string += string;
   string = translated_string;
}

