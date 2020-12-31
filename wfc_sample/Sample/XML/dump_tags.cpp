#include "my_xml.h"
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
** $Workfile: dump_tags.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:20p $
*/

void dump_tags( const CExtensibleMarkupLanguageDocument& document )
{
   WFCTRACEINIT( TEXT( "dump_tags()" ) );

   CExtensibleMarkupLanguageElement * element_p = NULL;

   element_p = document.GetRootElement();

   if ( element_p == NULL )
   {
      WFCTRACE( TEXT( "Root element is NULL!" ) );
      return;
   }

   dump_element( element_p, 0 );
}