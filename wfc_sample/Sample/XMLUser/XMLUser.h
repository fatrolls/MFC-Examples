#if ! defined( XML_USER_SAMPLE_HEADER )

#define XML_USER_SAMPLE_HEADER

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
** $Workfile: XMLUser.h $
** $Revision: 2 $
** $Modtime: 4/07/98 7:37p $
*/

#include <wfc.h>

void add_current_time( CExtensibleMarkupLanguageElement * parent_element_p );
void add_level( DWORD level, CExtensibleMarkupLanguageElement * parent_element_p );
void add_machine_name( CNetworkUsers& users, CExtensibleMarkupLanguageElement * parent_element_p );
void add_to_xml( CNetworkUserInformation& user, CExtensibleMarkupLanguageElement * parent_element_p );
void enumerate_users( CExtensibleMarkupLanguageDocument& document, LPCTSTR machine_name );
void parse_document( void );
void save_document( const CExtensibleMarkupLanguageDocument& document );

#endif // XML_USER_SAMPLE_HEADER
