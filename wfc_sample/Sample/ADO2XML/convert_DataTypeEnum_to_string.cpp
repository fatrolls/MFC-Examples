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
** $Workfile: convert_DataTypeEnum_to_string.cpp $
** $Revision: 1 $
** $Modtime: 3/07/00 4:53a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void convert_DataTypeEnum_to_string( DWORD data_type_enum, CString& string_to_fill )
{
   // These are the strings written to the Schema XML section under
   // TYPE.ADO

   switch( data_type_enum )
   {
      case adEmpty:

         string_to_fill = TEXT( "adEmpty" );
         break;

      case adTinyInt:

         string_to_fill = TEXT( "adTinyInt" );
         break;

      case adSmallInt:

         string_to_fill = TEXT( "adSmallInt" );
         break;

      case adInteger:

         string_to_fill = TEXT( "adInteger" );
         break;

      case adBigInt:

         string_to_fill = TEXT( "adBigInt" );
         break;

      case adUnsignedTinyInt:

         string_to_fill = TEXT( "adUnsignedTinyInt" );
         break;

      case adUnsignedSmallInt:

         string_to_fill = TEXT( "adUnsignedSmallInt" );
         break;

      case adUnsignedInt:

         string_to_fill = TEXT( "adUnsignedInt" );
         break;

      case adUnsignedBigInt:

         string_to_fill = TEXT( "adUnsignedBigInt" );
         break;

      case adSingle:

         string_to_fill = TEXT( "adSingle" );
         break;

      case adDouble:

         string_to_fill = TEXT( "adDouble" );
         break;

      case adCurrency:

         string_to_fill = TEXT( "adCurrency" );
         break;

      case adDecimal:

         string_to_fill = TEXT( "adDecimal" );
         break;

      case adNumeric:

         string_to_fill = TEXT( "adNumeric" );
         break;

      case adBoolean:

         string_to_fill = TEXT( "adBoolean" );
         break;

      case adError:

         string_to_fill = TEXT( "adError" );
         break;

      case adUserDefined:

         string_to_fill = TEXT( "adUserDefined" );
         break;

      case adVariant:

         string_to_fill = TEXT( "adVariant" );
         break;

      case adIDispatch:

         string_to_fill = TEXT( "adIDispatch" );
         break;

      case adIUnknown:

         string_to_fill = TEXT( "adIUnknown" );
         break;

      case adGUID:

         string_to_fill = TEXT( "adGUID" );
         break;

      case adDate:

         string_to_fill = TEXT( "adDate" );
         break;

      case adDBDate:

         string_to_fill = TEXT( "adDBDate" );
         break;

      case adDBTime:

         string_to_fill = TEXT( "adDBTime" );
         break;

      case adDBTimeStamp:

         string_to_fill = TEXT( "adDBTimeStamp" );
         break;

      case adBSTR:

         string_to_fill = TEXT( "adBSTR" );
         break;

      case adChar:

         string_to_fill = TEXT( "adChar" );
         break;

      case adVarChar:

         string_to_fill = TEXT( "adVarChar" );
         break;

      case adLongVarChar:

         string_to_fill = TEXT( "adLongVarChar" );
         break;

      case adWChar:

         string_to_fill = TEXT( "adWChar" );
         break;

      case adVarWChar:

         string_to_fill = TEXT( "adVarWChar" );
         break;

      case adLongVarWChar:

         string_to_fill = TEXT( "adLongVarWChar" );
         break;

      case adBinary:

         string_to_fill = TEXT( "adBinary" );
         break;

      case adVarBinary:

         string_to_fill = TEXT( "adVarBinary" );
         break;

      case adLongVarBinary:

         string_to_fill = TEXT( "adLongVarBinary" );
         break;

      case adChapter:

         string_to_fill = TEXT( "adChapter" );
         break;

      case adFileTime:

         string_to_fill = TEXT( "adFileTime" );
         break;

      case adDBFileTime:

         string_to_fill = TEXT( "adDBFileTime" );
         break;

      case adPropVariant:

         string_to_fill = TEXT( "adPropVariant" );
         break;

      case adVarNumeric:

         string_to_fill = TEXT( "adVarNumeric" );
         break;

      default:

         string_to_fill.Format( TEXT( "Unknown(%lu)" ), data_type_enum );
         break;
   }
}

