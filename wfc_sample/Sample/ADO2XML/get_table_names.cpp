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
** $Workfile: get_table_names.cpp $
** $Revision: 2 $
** $Modtime: 3/21/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

/*
** While I'm not known for writing obfuscated code, I did get this error
** while trying to compile this module:
** --------------------Configuration: ADO2XML - Win32 Debug--------------------
** Compiling...
** get_table_names.cpp
** Command line error D2030 : INTERNAL COMPILER ERROR in 'C:\Program Files\Microsoft Visual Studio\VC98\BIN\cl.exe'
**     Please choose the Technical Support command on the Visual C++
**     Help menu, or open the Technical Support help file for more information
** Error executing cl.exe.
**
** get_table_names.obj - 1 error(s), 0 warning(s)
**
** As usual, Microsoft provides us no information to debug the situation.
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

bool get_table_names( _ConnectionPtr& connection_p, CStringArray& table_names )
{
   WFCTRACEINIT( TEXT( "get_table_names()" ) );

	table_names.RemoveAll();

   bool return_value = true;

   HRESULT result = S_OK;

   _RecordsetPtr recordset_p = NULL;

   try
   {
      try
      {
         recordset_p = connection_p->OpenSchema( adSchemaTables );
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

      _bstr_t table_name;
      _bstr_t table_type;

      CString desired_table_type( TEXT( "TABLE" ) );

      while( ! recordset_p->EndOfFile )
      {
         try
         {
            table_name = recordset_p->Fields->GetItem( "TABLE_NAME" )->Value;
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

         try
         {
            table_type = recordset_p->Fields->GetItem( "TABLE_TYPE" )->Value;
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

         WFCTRACEVAL( TEXT( "Table Name " ), CString( (LPCTSTR) table_name ) );
         WFCTRACEVAL( TEXT( "Table Type " ), CString( (LPCTSTR) table_type ) );
         WFCTRACE( TEXT( "\n" ) );

         if ( desired_table_type.Compare( table_type ) == 0 )
         {
            // We found a normal table (not system related)

            table_names.Add( (LPCTSTR) table_name );
         }

         try
         {
            recordset_p->MoveNext();
         }
         catch( _com_error &exception )
         {
            WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
            print_COM_error( exception );
            //return( false ); // Commented out to fix Microsoft's compiler error, see above
         }
         catch( ... )
         {
            WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
            //return( false ); // Commented out to fix Microsoft's compiler error, see above
         }
      }

      try
      {
         recordset_p->Close();
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

      return( return_value );
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
