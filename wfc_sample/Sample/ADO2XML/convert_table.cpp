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
** $Workfile: convert_table.cpp $
** $Revision: 1 $
** $Modtime: 3/19/00 7:58a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

bool convert_table( _ConnectionPtr& connection_p, const CString& table_name, const CString& where_clause )
{
   WFCTRACEINIT( TEXT( "convert_table()" ) );

   if ( table_name.GetLength() <= 0 )
   {
      WFCTRACE( TEXT( "table_name is empty!" ) );
      return( false );
   }

   output_schema( connection_p, table_name, where_clause );

   HRESULT result = S_OK;

   _RecordsetPtr recordset_p = NULL;

   result = recordset_p.CreateInstance( __uuidof( Recordset ) );

   if ( FAILED( result ) )
   {
      WFCTRACEVAL( TEXT( "Failed at line " ), __LINE__ );
      return( false );
   }

   CString select_string( TEXT( "SELECT * FROM [" ) );

   select_string += table_name;
   select_string += TEXT( "]" );

   if ( where_clause.GetLength() > 0 )
   {
      select_string += TEXT( " " );
      select_string += where_clause;
   }

   _bstr_t select_string_as_bstring( select_string );

   result = recordset_p->Open( select_string_as_bstring,
                               _variant_t( (IDispatch *) connection_p ),
                               adOpenForwardOnly,
                               adLockReadOnly,
                               adCmdText );

   if ( FAILED( result ) )
   {
      WFCTRACEVAL( TEXT( "Failed at line " ), __LINE__ );
      recordset_p->Close();
      return( false );
   }

   WFCTRACEVAL( TEXT( "Number of fields in table is " ), recordset_p->Fields->Count );

   _tprintf( TEXT( "<ADO2XML:TABLE>\n" ) );

   CString output_string( table_name );

   normalize_string( output_string );
   _tprintf( TEXT( "   <NAME>%s</NAME>\n" ), (LPCTSTR) output_string );

   // Now call output_fields_schema( recordset_p->Fields ) which will
   // call output_field_schema( Fields[ index ] );

   int field_index = 0;

   DWORD record_count = 0;

   bool exit_loop = false;

   while( ! recordset_p->EndOfFile && exit_loop == false )
   {
      _tprintf( TEXT( "   <RECORD>\n" ) );

      field_index = 0;

      while( field_index < recordset_p->Fields->Count )
      {
         // We must cast the field_index from an int to a short because
         // Microsoft doesn't know how to convert an int to a variant but they
         // do know how to convert a short to a variant. Go figure.
         //_tprintf( TEXT( "      <INDEX>%d</INDEX>" ), field_index );
         output_field( recordset_p->Fields->Item[ (short) field_index ] );

         field_index++;
      }

      record_count++;

      if ( record_count > 1 )
      {
         exit_loop = true;
      }

      _tprintf( TEXT( "   </RECORD>\n" ) );

      recordset_p->MoveNext();
   }

   recordset_p->Close();

   _tprintf( TEXT( "</ADO2XML:TABLE>\n" ) );

   return( true );
}
