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
** $Workfile: output_types.cpp $
** $Revision: 1 $
** $Modtime: 3/19/00 7:56a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void output_types( DWORD data_type_enum )
{
   WFCTRACEINIT( TEXT( "output_types()" ) );

   CString data_type_name;

   convert_DataTypeEnum_to_string( data_type_enum, data_type_name );

   _tprintf( TEXT( "         <TYPE>\n" ) );

   // ADO data type, other functions will go here to convert the
   // ADO type to C, C++, etc.

   normalize_string( data_type_name );
   _tprintf( TEXT( "            <ADO>%s</ADO>\n" ), (LPCTSTR) data_type_name );

   switch( data_type_enum )
   {
      case adEmpty:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_EMPTY</DBTYPE>\n" ) );
         break;

      case adTinyInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_I1</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>char</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>char</CPLUSPLUS>\n" ) );
         break;

      case adSmallInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_I2</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbInteger</DAO>\n" ) );
         _tprintf( TEXT( "            <C>short</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>short</CPLUSPLUS>\n" ) );
         break;

      case adInteger:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_I4</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbLong</DAO>\n" ) );
         _tprintf( TEXT( "            <C>long</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>long</CPLUSPLUS>\n" ) );
         break;

      case adBigInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_I8</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>long long</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>long long</CPLUSPLUS>\n" ) );
         _tprintf( TEXT( "            <WIN32>__int64</WIN32>\n" ) );
         break;

      case adUnsignedTinyInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_UI1</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbByte</DAO>\n" ) );
         _tprintf( TEXT( "            <C>unsigned char</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>unsigned char</CPLUSPLUS>\n" ) );
         break;

      case adUnsignedSmallInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_UI2</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>unsigned short</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>unsigned short</CPLUSPLUS>\n" ) );
         _tprintf( TEXT( "            <WIN32>WORD</WIN32>\n" ) );
         break;

      case adUnsignedInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_UI4</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>unsigned long</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>unsigned long</CPLUSPLUS>\n" ) );
         _tprintf( TEXT( "            <WIN32>DWORD</WIN32>\n" ) );
         break;

      case adUnsignedBigInt:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_UI8</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>unsigned long long</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>unsigned long long</CPLUSPLUS>\n" ) );
         _tprintf( TEXT( "            <WIN32>__uint64</WIN32>\n" ) );
         break;

      case adSingle:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_R4</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbSingle</DAO>\n" ) );
         _tprintf( TEXT( "            <C>float</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>float</CPLUSPLUS>\n" ) );
         _tprintf( TEXT( "            <WIN32>float</WIN32>\n" ) );
         break;

      case adDouble:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_R8</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbDouble</DAO>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adCurrency:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_CY</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbCurrency</DAO>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adDecimal:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_DECIMAL</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adNumeric:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_NUMERIC</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbDecimal</DAO>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adBoolean:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_BOOL</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbBoolean</DAO>\n" ) );
         _tprintf( TEXT( "            <C>BOOL</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>bool</CPLUSPLUS>\n" ) );
         break;

      case adError:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_ERROR</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>unsigned long</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>unsigned long</CPLUSPLUS>\n" ) );
         break;

      case adUserDefined:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_UDT</DBTYPE>\n" ) );
         break;

      case adVariant:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_VARIANT</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>_variant_t</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>_variant_t</CPLUSPLUS>\n" ) );
         break;

      case adIDispatch:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_IDISPATCH</DBTYPE>\n" ) );
         break;

      case adIUnknown:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_IUNKNOWN</DBTYPE>\n" ) );
         break;

      case adGUID:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_GUID</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbGUID</DAO>\n" ) );
         break;

      case adDate:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_DATE</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbDate</DAO>\n" ) );
         break;

      case adDBDate:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_DBDATE</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adDBTime:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_DBTIME</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adDBTimeStamp:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_DBTIMESTAMP</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>double</C>\n" ) );
         _tprintf( TEXT( "            <CPLUSPLUS>double</CPLUSPLUS>\n" ) );
         break;

      case adBSTR:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_BSTR</DBTYPE>\n" ) );
         break;

      case adChar:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_STR</DBTYPE>\n" ) );
         break;

      case adVarChar:
      case adLongVarChar:
      case adWChar:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_WSTR</DBTYPE>\n" ) );
         break;

      case adVarWChar:

         _tprintf( TEXT( "            <DAO>dbText</DAO>\n" ) );
         break;

      case adLongVarWChar:

         _tprintf( TEXT( "            <DAO>dbMemo</DAO>\n" ) );
         break;

      case adBinary:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_BYTES</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <DAO>dbBinary</DAO>\n" ) );
         break;

      case adVarBinary:
      case adLongVarBinary:

         _tprintf( TEXT( "            <DAO>dbLongBinary</DAO>\n" ) );
         break;

      case adChapter:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_HCHAPTER</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <C>unsigned long</C>\n" ) );
         _tprintf( TEXT( "            <CPLUS>unsigned long</CPLUS>\n" ) );
         _tprintf( TEXT( "            <WIN32>DWORD</WIN32>\n" ) );
         break;

      case adFileTime:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_FILETIME</DBTYPE>\n" ) );
         _tprintf( TEXT( "            <WIN32>FILETIME</WIN32>\n" ) );
         break;

      case adDBFileTime:
      case adPropVariant:

         _tprintf( TEXT( "            <DBTYPE>DBTYPE_PROP_VARIANT</DBTYPE>\n" ) );
         break;

      case adVarNumeric:
      default:

         break;
   }

   _tprintf( TEXT( "         </TYPE>\n" ) );
}
