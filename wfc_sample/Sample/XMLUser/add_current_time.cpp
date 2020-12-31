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
** $Workfile: add_current_time.cpp $
** $Revision: 1 $
** $Modtime: 4/07/98 7:51p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void add_current_time( CExtensibleMarkupLanguageElement * parent_element_p )
{
   CXMLArchive archive;

   archive.WriteTo( parent_element_p );

   CSystemTime current_time;

   current_time.Get();

   archive.Write( TEXT( "REPORT_TIME" ), current_time );
}
