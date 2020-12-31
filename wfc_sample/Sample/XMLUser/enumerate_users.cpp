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
** $Workfile: enumerate_users.cpp $
** $Revision: 2 $
** $Modtime: 5/16/98 4:24p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void enumerate_users( CExtensibleMarkupLanguageDocument& document, LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "enumerate_users()" ) );

   CExtensibleMarkupLanguageElement * root_element_p = document.GetRootElement();

   CNetworkUsers users( machine_name );

   CNetworkUserInformation user_information;

   CString friendly_machine_name;

   if ( users.Enumerate() != FALSE )
   {
      CExtensibleMarkupLanguageElement * element_p = NULL;

      element_p = CExtensibleMarkupLanguageElement::NewElement( root_element_p );

      element_p->SetTag( TEXT( "MACHINE" ) );

      add_machine_name( users, element_p );

      add_level( users.GetLevel(), element_p );

      add_current_time( element_p );

      while( users.GetNext( user_information ) != FALSE )
      {
         add_to_xml( user_information, element_p );
      }
   }
   else
   {
      DWORD error_code = users.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetworkUsers.Enumerate( user_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}
