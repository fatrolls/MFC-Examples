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
** $Workfile: output_field.cpp $
** $Revision: 2 $
** $Modtime: 3/21/00 4:53a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

void output_field( FieldPtr& field_p )
{
   WFCTRACEINIT( TEXT( "output_field()" ) );

   // Now we look at the type of the field and output accordingly

   try
   {
      DWORD data_type = field_p->GetType();

#if defined( _DEBUG )

      {
         _bstr_t _field_name;

         try
         {
            _field_name = field_p->GetName();
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

         CString __field_name( (LPCTSTR) _field_name );

         WFCTRACEVAL( TEXT( "Processing field " ), __field_name );

         convert_DataTypeEnum_to_string( data_type, __field_name );
         WFCTRACEVAL( TEXT( "Field Type " ), __field_name );
      }

#endif // _DEBUG

      long size_of_field_data = 0;
      
      try
      {
         size_of_field_data = field_p->GetActualSize();
      }
      catch( _com_error &exception )
      {
         WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
         print_COM_error( exception );
         size_of_field_data = (-1);
      }
      catch( ... )
      {
         WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
         size_of_field_data = (-1);
      }

      if ( size_of_field_data == (-1) )
      {
         // HHHMMM, must be NULL
         // The size is usually set to -1 when nothing is written to the
         // database field. This leads to an interesting situation with
         // regard to bool types. It means that bool must have three
         // values! They are true, false and unknown. We must handle the
         // unknown type. We do this by adding a child element to the
         // VALUE element names NULL. This makes it easy on the parsing
         // side to create an IsNULL() function.

         _tprintf( TEXT( "      <VALUE><NULL /></VALUE>\n" ) );
         return;
      }

      WFCTRACEVAL( TEXT( "size_of_field_data is " ), size_of_field_data );

      switch( data_type )
      {
         case adEmpty:

            _tprintf( TEXT( "      <VALUE><!-- adEmpty --></VALUE>\n" ) );
            break;

         case adTinyInt:
         case adSmallInt:
         case adInteger:
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
         case adGUID:

            try
            {
               _variant_t field_data;

               try
               {
                  field_data = field_p->GetValue();
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

               if ( field_data.vt == VT_NULL )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_NULL --></VALUE>\n" ) );
                  return;
               }

               if ( field_data.vt == VT_EMPTY )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_EMPTY --></VALUE>\n" ) );
                  return;
               }

               WFCTRACEVARIANT( TEXT( "field_data " ), field_data );

               try
               {
                  field_data.ChangeType( VT_BSTR );

                  // BSTR's are UNICODE

                  CString output_string;
                  
                  wfc_convert_lpcwstr_to_cstring( field_data.bstrVal, output_string );
                  normalize_string( output_string );

                  _tprintf( TEXT( "      <VALUE>%s</VALUE>\n" ), (LPCTSTR) output_string );
               }
               catch( _com_error &exception )
               {
                  WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
                  print_COM_error( exception );
                  _tprintf( TEXT( "      <VALUE><!-- COM Exception Caught --></VALUE>\n" ) );
               }
               catch( ... )
               {
                  WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
                  _tprintf( TEXT( "      <VALUE><!-- C++ Exception Caught --></VALUE>\n" ) );
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

            break;

         case adUserDefined:

            _tprintf( TEXT( "      <VALUE><!-- adUserDefined --></VALUE>\n" ) );
            break;

         case adVariant:

            _tprintf( TEXT( "      <VALUE><!-- adVariant --></VALUE>\n" ) );
            break;

         case adIDispatch:

            _tprintf( TEXT( "      <VALUE><!-- adIDispatch --></VALUE>\n" ) );
            break;

         case adIUnknown:

            _tprintf( TEXT( "      <VALUE><!-- adIUnknown --></VALUE>\n" ) );
            break;

         case adDBTime:

            try
            {
               _variant_t field_data = field_p->GetValue();

               if ( field_data.vt == VT_NULL )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_NULL --></VALUE>\n" ) );
                  return;
               }

               if ( field_data.vt == VT_EMPTY )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_EMPTY --></VALUE>\n" ) );
                  return;
               }

               try
               {
                  field_data.ChangeType( VT_BSTR );

                  CString output_string;
                  
                  wfc_convert_lpcwstr_to_cstring( field_data.bstrVal, output_string );
                  normalize_string( output_string );

                  _tprintf( TEXT( "      <VALUE>%s</VALUE>\n" ), (LPCTSTR) output_string );
               }
               catch( _com_error &exception )
               {
                  WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
                  print_COM_error( exception );
                  _tprintf( TEXT( "      <VALUE><!-- COM Exception Caught --></VALUE>\n" ) );
               }
               catch( ... )
               {
                  WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
                  _tprintf( TEXT( "      <VALUE><!-- C++ Exception Caught --></VALUE>\n" ) );
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

            break;

         case adDate:
         case adDBDate:
         case adDBTimeStamp:

            try
            {
               _variant_t field_data;
               
               try
               {
                  field_data = field_p->GetValue();
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

               if ( field_data.vt == VT_NULL )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_NULL --></VALUE>\n" ) );
                  return;
               }

               if ( field_data.vt == VT_EMPTY )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_EMPTY --></VALUE>\n" ) );
                  return;
               }

               WFCTRACEVARIANT( TEXT( "Field data " ), field_data );

               SYSTEMTIME system_time;

               ZeroMemory( &system_time, sizeof( system_time ) );

               if ( VariantTimeToSystemTime( V_DATE( &field_data ), &system_time ) != FALSE )
               {
                  // ISO 8601 format
                  // "%Y-%m-%dT%H:%M:%S"

                  double fractional_seconds = (double) system_time.wSecond;
                  double fractions_of_a_second = 0.0;

                  if ( system_time.wMilliseconds > 0 )
                  {
                     fractions_of_a_second = (double) ( (double) 1000.0L / (double) system_time.wMilliseconds );
                  }

                  fractional_seconds += fractions_of_a_second;

                  _tprintf( TEXT( "      <VALUE>%d-%d-%dT%02d:%02:%08.5lf</VALUE>\n" ),
                            (int) system_time.wYear,
                            (int) system_time.wMonth,
                            (int) system_time.wDay,
                            (int) system_time.wHour,
                            (int) system_time.wMinute,
                                  fractional_seconds );
               }
               else
               {
                  _tprintf( TEXT( "      <VALUE><!-- Error converting variant to system time --></VALUE>\n" ) );
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

            break;

         case adChar:

            try
            {
               _variant_t field_data;
               
               try
               {
                  field_data = field_p->GetValue();
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

               if ( field_data.vt == VT_NULL )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_NULL --></VALUE>\n" ) );
                  return;
               }

               if ( field_data.vt == VT_EMPTY )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_EMPTY --></VALUE>\n" ) );
                  return;
               }

               field_data.ChangeType( VT_BSTR );

               CString output_string;
                  
               wfc_convert_lpcwstr_to_cstring( field_data.bstrVal, output_string );
               normalize_string( output_string );

               _tprintf( TEXT( "      <VALUE>%s</VALUE>\n" ), (LPCTSTR) output_string );
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

            break;

         case adBSTR:

            try
            {
               _variant_t field_data;
               
               try
               {
                  field_data = field_p->GetValue();
               }
               catch( _com_error &exception )
               {
                  WFCTRACEVAL( TEXT( "COM exception caught at line " ), __LINE__ );
                  print_COM_error( exception );
                  _tprintf( TEXT( "      <VALUE><!-- COM Exception Caught --></VALUE>\n" ) );
               }
               catch( ... )
               {
                  WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
                  _tprintf( TEXT( "      <VALUE><!-- C++ Exception Caught --></VALUE>\n" ) );
               }

               if ( field_data.vt == VT_NULL )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_NULL --></VALUE>\n" ) );
                  return;
               }

               if ( field_data.vt == VT_EMPTY )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_EMPTY --></VALUE>\n" ) );
                  return;
               }

               field_data.ChangeType( VT_BSTR );

               CString output_string;
                  
               wfc_convert_lpcwstr_to_cstring( field_data.bstrVal, output_string );
               normalize_string( output_string );

               _tprintf( TEXT( "      <VALUE>%s</VALUE>\n" ), (LPCTSTR) output_string );
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

            break;

         case adVarChar:

            _tprintf( TEXT( "      <VALUE><!-- adVarChar --></VALUE>\n" ) );
            break;

         case adLongVarChar:

            _tprintf( TEXT( "      <VALUE><!-- adLongVarChar --></VALUE>\n" ) );
            break;

         case adWChar:
         case adVarWChar:

            try
            {
               _variant_t field_data;
               
               try
               {
                  field_data = field_p->GetValue();
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

               if ( field_data.vt == VT_NULL )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_NULL --></VALUE>\n" ) );
                  return;
               }

               if ( field_data.vt == VT_EMPTY )
               {
                  _tprintf( TEXT( "      <VALUE><!-- VT_EMPTY --></VALUE>\n" ) );
                  return;
               }

               _tprintf( TEXT( "      <VALUE>%S</VALUE>\n" ), (LPCTSTR) field_data.bstrVal );
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

            break;

         case adLongVarWChar:

            try
            {
               CByteArray blob;

               get_blob( field_p, blob );

               if ( blob.GetSize() > 0 )
               {
                  // Make really sure we are null terminated

                  blob.Add( 0 );
                  blob.Add( 0 );
                  blob.Add( 0 );
                  blob.Add( 0 );

                  CString output_string;
                  
                  wfc_convert_lpcwstr_to_cstring( (LPCWSTR) blob.GetData(), output_string );
                  normalize_string( output_string );

                  _tprintf( TEXT( "      <VALUE>%s</VALUE>\n" ), (LPCTSTR) output_string );
               }
               else
               {
                  _tprintf( TEXT( "      <VALUE></VALUE>\n" ) );
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

            break;

         case adBinary:
         case adVarBinary:
         case adLongVarBinary:

            try
            {
               CString xml_representation;

               try
               {
                  CByteArray blob;

                  get_blob( field_p, blob );

                  CBase64Coding mime_encoder;

                  mime_encoder.Encode( blob, xml_representation );
               }
               catch( _com_error &exception )
               {
                  WFCTRACE( TEXT( "COM execption caught converting blob." ) );
                  print_COM_error( exception );
               }
               catch( ... )
               {
                  WFCTRACE( TEXT( "Exception caught converting blob." ) );
               }

               _tprintf( TEXT( "      <VALUE>%s</VALUE>\n" ), (LPCTSTR) xml_representation );
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

            break;

         case adChapter:

            _tprintf( TEXT( "      <VALUE><!-- adChapter --></VALUE>\n" ) );
            break;

         case adFileTime:

            _tprintf( TEXT( "      <VALUE><!-- adFileTime --></VALUE>\n" ) );
            break;

         case adDBFileTime:

            _tprintf( TEXT( "      <VALUE><!-- adDBFileTime --></VALUE>\n" ) );
            break;

         case adPropVariant:

            _tprintf( TEXT( "      <VALUE><!-- adPropVariant --></VALUE>\n" ) );
            break;

         case adVarNumeric:

            _tprintf( TEXT( "      <VALUE><!-- adVarNumeric --></VALUE>\n" ) );
            break;

         default:

            WFCTRACE( TEXT( "Unknown Type." ) );
            _tprintf( TEXT( "      <VALUE><!-- default case, unknown type %d --></VALUE>\n" ), (int) data_type );
            break;
      }
   }
   catch( _com_error &exception )
   {
      WFCTRACE( TEXT( "COM exception caught." ) );
      print_COM_error( exception );
   }
   catch( ... )
   {
      WFCTRACEVAL( TEXT( "Exception caught at line " ), __LINE__ );
   }
}
