#include "XMLUser.h"
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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: save_document.cpp $
** $Revision: 2 $
** $Modtime: 3/23/98 8:09p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void save_document( const CExtensibleMarkupLanguageDocument& document )
{
   WFCTRACEINIT( TEXT( "save_document()" ) );

   CFile file;

   if ( file.Open( TEXT( "users.xml" ), CFile::modeWrite | CFile::modeCreate ) == FALSE )
   {
      _tprintf( TEXT( "Can't create users.xml\n" ) );
      return;
   }

   CByteArray bytes;

   document.WriteTo( bytes );

   file.Write( bytes.GetData(), bytes.GetSize() );
}
