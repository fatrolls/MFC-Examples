#if ! defined( MIME2HTML_HEADER_INCLUDED )

#define MIME2HTML_HEADER_INCLUDED

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
** $Workfile: MIME2HTML.h $
** $Revision: 1 $
** $Modtime: 3/21/00 5:36p $
** $Reuse Tracing Code: 1 $
*/

#define WINVER (0x401)
#define WFC_STL

#include <wfc.h>

void dump_mime_mappings( void );
void dump_mime_type( const CString& mime_type_name );
bool get_command_line( const CString& extension_name, CString& command_line );
void normalize_string( CString& string_to_normalize );
void replace( CString& string, const CString& what_to_replace, const CString& what_to_replace_it_with );

#endif // MIME2HTML_HEADER_INCLUDED
