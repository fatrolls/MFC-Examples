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
** $Workfile: add_machine_name.cpp $
** $Revision: 1 $
** $Modtime: 3/23/98 7:09p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void add_machine_name( CNetworkUsers& users, CExtensibleMarkupLanguageElement * parent_element_p )
{
   CExtensibleMarkupLanguageElement * element_p = NULL;

   element_p = CExtensibleMarkupLanguageElement::NewElement( parent_element_p );

   if ( element_p == NULL )
   {
      return;
   }

   element_p->SetTag( TEXT( "NAME" ) );

   CString machine_name;

   users.GetFriendlyMachineName( machine_name );

   element_p->AddText( machine_name );
}

