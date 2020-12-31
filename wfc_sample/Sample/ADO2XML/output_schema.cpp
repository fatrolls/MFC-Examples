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
** $Workfile: output_schema.cpp $
** $Revision: 2 $
** $Modtime: 3/21/00 4:49a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

bool output_schema( _ConnectionPtr& connection_p, const CString& table_name, const CString& where_clause )
{
   WFCTRACEINIT( TEXT( "output_schema()" ) );

   if ( table_name.GetLength() <= 0 )
   {
      WFCTRACE( TEXT( "table_name is empty!" ) );
      return( false );
   }

   HRESULT result = S_OK;

   _RecordsetPtr recordset_p = NULL;

   try
   {
      result = recordset_p.CreateInstance( __uuidof( Recordset ) );
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

   try
   {
      result = recordset_p->Open( select_string_as_bstring,
                                  _variant_t( (IDispatch *) connection_p ),
                                  adOpenForwardOnly,
                                  adLockReadOnly,
                                  adCmdText );
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
      WFCTRACEVAL( TEXT( "Failed at line " ), __LINE__ );
      recordset_p->Close();
      return( false );
   }

   WFCTRACEVAL( TEXT( "Number of fields in table is " ), recordset_p->Fields->Count );

   _tprintf( TEXT( "<ADO2XML:SCHEMA>\n" ) );
   _tprintf( TEXT( "   <TABLE>\n" ) );

   CString output_string( table_name );
                  
   normalize_string( output_string );

   _tprintf( TEXT( "      <NAME>%s</NAME>\n" ), (LPCTSTR) output_string );

   // Now call output_fields_schema( recordset_p->Fields ) which will
   // call output_field_shcema( Fields[ index ] );

   int field_index = 0;

   DWORD data_type = 0;

   CString data_type_name;

   try
   {
      while( field_index < recordset_p->Fields->Count )
      {
         // We must cast the field_index from an int to a short because
         // Microsoft doesn't know how to convert an int to a variant but they
         // do know how to convert a short to a variant. Go figure.

         try
         {
            data_type_name = (LPCTSTR) recordset_p->Fields->Item[ (short) field_index ]->GetName();
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

         WFCTRACEVAL( TEXT( "Field name is " ), data_type_name );

         _tprintf( TEXT( "      <FIELD>\n" ) );

         normalize_string( data_type_name );

         _tprintf( TEXT( "         <NAME>%s</NAME>\n" ), (LPCTSTR) data_type_name );
         _tprintf( TEXT( "         <INDEX>%lu</INDEX>\n" ), (unsigned long) field_index );

         try
         {
            data_type = recordset_p->Fields->Item[ (short) field_index ]->GetType();
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

         output_types( data_type );

         // Now output size information

         switch( data_type )
         {
            case adEmpty:

               break;

            case adTinyInt:
            case adSmallInt:
            case adInteger:
            case adBigInt:
            case adUnsignedTinyInt:
            case adUnsignedSmallInt:
            case adUnsignedInt:
            case adUnsignedBigInt:
            case adSingle:
            case adDouble:
            case adCurrency:
            case adDecimal:
            case adNumeric:
            case adBoolean:
            case adError:
            case adUserDefined:
            case adVariant:
            case adIDispatch:
            case adIUnknown:
            case adGUID:
            case adDate:
            case adDBDate:
            case adDBTime:
            case adDBTimeStamp:
            case adBSTR:
            case adChar:
            case adVarChar:
            case adLongVarChar:
            case adWChar:
            case adVarWChar:
            case adLongVarWChar:
            case adBinary:
            case adVarBinary:
            case adLongVarBinary:
            case adChapter:
            case adFileTime:
            case adDBFileTime:
            case adPropVariant:
            case adVarNumeric:
            default:

               _tprintf( TEXT( "         <SIZE>%lu</SIZE>\n" ), (unsigned long) recordset_p->Fields->Item[ (short) field_index ]->GetDefinedSize() );

               break;
         }

         _tprintf( TEXT( "      </FIELD>\n" ) );

         field_index++;
      }
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

   _tprintf( TEXT( "   </TABLE>\n" ) );
   _tprintf( TEXT( "</ADO2XML:SCHEMA>\n" ) );

   return( true );
}
