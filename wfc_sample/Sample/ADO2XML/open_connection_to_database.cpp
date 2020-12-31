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
** $Workfile: open_connection_to_database.cpp $
** $Revision: 2 $
** $Modtime: 3/21/00 4:39a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

bool open_connection_to_database( const CDatabaseParameters& database_parameters, _ConnectionPtr& connection_p )
{
   WFCTRACEINIT( TEXT( "open_connection_to_database()" ) );

   CString connection_string;

   database_parameters.GetConnectionString( connection_string );

   WFCTRACEVAL( TEXT( "Connection string is " ), connection_string );

   HRESULT result = S_OK;

   try
   {
      _bstr_t connection_string_as_bstring( (LPCTSTR) connection_string );

      try
      {
         result = connection_p.CreateInstance( __uuidof( Connection ) );
      }
      catch( _com_error &exception )
      {
         WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
         print_COM_error( exception );
      }
      catch( ... )
      {
         WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
      }

      if ( FAILED( result ) )
      {
         WFCTRACEVAL( TEXT( "Failing at line " ), __LINE__ );

         // Throw an exception to figure out what went wrong

         _com_issue_error( result );
         return( false );
      }

      connection_p->CommandTimeout = 300; // Five minutes

      DWORD options = 0;

      _bstr_t user_name_bstring( "" );
      _bstr_t user_password_bstring( "" );

      try
      {
         result = connection_p->Open( connection_string_as_bstring,
                                      user_name_bstring,
                                      user_password_bstring,
                                      options );
      }
            catch( _com_error &exception )
      {
         WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
         print_COM_error( exception );
      }
      catch( ... )
      {
         WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
      }

      if ( FAILED( result ) )
      {
         WFCTRACEVAL( TEXT( "Failing at line " ), __LINE__ );

         // Throw an exception to figure out what went wrong

         connection_p->Close();
         _com_issue_error( result );
         return( false );
      }

      return( true );
   }
   catch( _com_error &exception )
   {
      print_provider_error( connection_p );
      print_COM_error( exception );
      return( false );
   }
   catch( ... )
   {
      return( false );
   }
}
