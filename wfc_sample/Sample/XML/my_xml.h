#if ! defined( MY_XML_APPLICATION_HEADER_FILE )

#define MY_XML_APPLICATION_HEADER_FILE

/*
** Author: Samuel R. Blackburn
** Internet: sblackbu@erols.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: my_xml.h $
** $Revision: 3 $
** $Modtime: 3/07/98 8:45a $
*/

#if ( _MSC_VER > 1000 )
#pragma once
#endif // _MSC_VER

#include <wfc.h>

BOOL get_bytes( const CString& filename, CByteArray& bytes );
BOOL parse_document( const CString& filename, CExtensibleMarkupLanguageDocument& document );

void dump_element( CExtensibleMarkupLanguageElement * element_p, DWORD indentation_level );
void dump_tags( const CExtensibleMarkupLanguageDocument& document );

#endif // MY_XML_APPLICATION_HEADER_FILE
