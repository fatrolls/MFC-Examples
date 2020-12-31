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
** $Workfile: add_to_xml.cpp $
** $Revision: 2 $
** $Modtime: 5/16/98 4:26p $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL serialize_network_user_information( CXMLArchive * archive_p, const CString& name, void * parameter )
{
   WFCTRACEINIT( TEXT( "serialize_network_user_information()" ) );

   if ( parameter == NULL )
   {
      WFCTRACE( TEXT( "parameter is nULL!" ) );
      return( NULL );
   }

   CNetworkUserInformation * user_p = NULL;

   user_p = reinterpret_cast< CNetworkUserInformation * >( parameter );

   // We were passed a pointer, don't trust it

   try
   {
      if ( archive_p->IsStoring() != FALSE )
      {
         // We are storing
         archive_p->Write( TEXT( "NAME" ),               user_p->Name              );
         archive_p->Write( TEXT( "FULL_NAME" ),          user_p->FullName          );
         archive_p->Write( TEXT( "LOGON_HOURS" ),        user_p->LogonHours        );
         archive_p->Write( TEXT( "ENCRYPTED_PASSWORD" ), user_p->EncryptedPassword );
         archive_p->Write( TEXT( "PASSWORD_AGE" ),       user_p->PasswordAge       );
         archive_p->Write( TEXT( "LAST_LOGON" ),         user_p->LastLogon, FALSE  );
         archive_p->Write( TEXT( "LAST_LOGOFF" ),        user_p->LastLogoff, FALSE );
      }
      else
      {
         archive_p->Read( TEXT( "NAME" ),               user_p->Name              );
         archive_p->Read( TEXT( "FULL_NAME" ),          user_p->FullName          );
         archive_p->Read( TEXT( "LOGON_HOURS" ),        user_p->LogonHours        );
         archive_p->Read( TEXT( "ENCRYPTED_PASSWORD" ), user_p->EncryptedPassword );
         archive_p->Read( TEXT( "PASSWORD_AGE" ),       user_p->PasswordAge       );
         archive_p->Read( TEXT( "LAST_LOGON" ),         user_p->LastLogon         );
         archive_p->Read( TEXT( "LAST_LOGOFF" ),        user_p->LastLogoff        );
      }
   }
   catch( ... )
   {
      return( FALSE );
   }
}

void add_to_xml( CNetworkUserInformation& user, CExtensibleMarkupLanguageElement * parent_element_p )
{
   WFCTRACEINIT( TEXT( "add_to_xml()" ) );

   if ( parent_element_p == NULL )
   {
      WFCTRACE( TEXT( "Parent element is NULL!" ) );
      return;
   }

//   parent_element_p->AddText( TEXT( "\n\n" ) ); // Make resulting file more humanly readable

   CExtensibleMarkupLanguageElement * element_p = NULL;

   element_p = CExtensibleMarkupLanguageElement::NewElement( parent_element_p );

   if ( element_p == NULL )
   {
      return;
   }

   element_p->SetTag( TEXT( "USER" ) );

   CXMLArchive archive;

   archive.WriteTo( element_p );

   archive.SerializeObject( TEXT( "USER" ),
                            reinterpret_cast< void * >( &user ),
                            serialize_network_user_information );
}

