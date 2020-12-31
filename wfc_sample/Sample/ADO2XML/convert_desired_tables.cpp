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
** $Workfile: convert_desired_tables.cpp $
** $Revision: 2 $
** $Modtime: 3/21/00 4:25a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void convert_desired_tables( const CExtensibleMarkupLanguageElement * settings, const CDatabaseParameters& database_parameters )
{
   WFCTRACEINIT( TEXT( "convert_desired_tables()" ) );

   _ConnectionPtr connection_p = NULL;

   if ( open_connection_to_database( database_parameters, connection_p ) == false )
   {
      WFCTRACE( TEXT( "Can't open connection to database." ) );
      _tprintf( TEXT( "Can't open connection to database.\n" ) );
      return;
   }

   // Get the names of the tables in that database

   CStringArray table_names;

	if ( get_table_names( connection_p, table_names ) == false )
	{
      WFCTRACE( TEXT( "Can't get table names." ) );
      _tprintf( TEXT( "Can't get table names.\n" ) );
	   return;
	}

   WFCTRACEVAL( TEXT( "Number of tables " ), table_names.GetSize() );

   //CString desired_table_name( TEXT( "Categories" ) );
   CString desired_table_name;

   if ( table_names.GetSize() > 0 )
   {
      int loop_index = 0;

      CString table_name;
      CString where_clause; // Get this from the XML configuration data

      while( loop_index < table_names.GetSize() )
      {
         table_name = table_names.GetAt( loop_index );

         WFCTRACEVAL( TEXT( "Table " ), table_name );

         if (  desired_table_name.GetLength() == 0 ||
               desired_table_name.Compare( table_name ) == 0 )
         {
            convert_table( connection_p, table_name, where_clause );
         }

         loop_index++;
      }
   }

   try
   {
      connection_p->Close();
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
}
