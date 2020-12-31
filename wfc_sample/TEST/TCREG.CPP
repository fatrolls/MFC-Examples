#include "test.h"
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
** $Workfile: TCREG.CPP $
** $Revision: 5 $
** $Modtime: 2/01/00 8:08p $
*/

void test_CRegistry( void )
{
   WFCTRACEINIT( TEXT( "test_CRegistry()" ) );

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyCurrentUser ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to registry" ) );
      WFCTRACEVAL( TEXT( "At Line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   // Open HKEY_CURRENT_USER\Software

   if ( registry.Open( TEXT( "Software" ), (CRegistry::CreatePermissions)(CRegistry::permissionRead | CRegistry::permissionSetValue ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open key" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   // Let's create a sub-key

   if ( registry.Create( TEXT( "Software\\WFC" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't create sub-key WFC" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   // Let's create another sub-key

   if ( registry.Create( TEXT( "Software\\WFC\\Sub Key #1" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't create sub-key Sub Key #1" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   // Let's create another sub-key

   if ( registry.Create( TEXT( "Software\\WFC\\Sub Key #2" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't create sub-key Sub Key #1" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   // Now let's enumerate the sub keys.

   CString sub_key_name;
   CString class_name;

   DWORD index = 0;

   if ( registry.Open( TEXT( "Software\\WFC" ), (CRegistry::CreatePermissions)(CRegistry::permissionRead | CRegistry::permissionSetValue ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open key" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   while( registry.EnumerateKeys( index, sub_key_name, class_name ) != FALSE )
   {
      WFCTRACEVAL( TEXT( "Sub Key Name " ), sub_key_name );
      WFCTRACEVAL( TEXT( "Class Name " ), class_name );
      index++;
   }

   index = 0;

   BYTE buffer[ 4096 ];

   DWORD size_of_buffer = 4096;
   CRegistry::KeyValueTypes data_type;

   while( registry.EnumerateValues( index, sub_key_name, data_type, buffer, size_of_buffer ) != FALSE )
   {
      WFCTRACEVAL( TEXT( "Sub Key Name " ), sub_key_name );
      index++;
   }

   CStringArray string_array;

   string_array.RemoveAll();

   if ( registry.GetStringArrayValue( TEXT( "Sources" ), string_array ) != FALSE )
   {
      int index = 0;
      int number_of_strings = string_array.GetSize();

      WFCTRACEVAL( TEXT( "Number of strings is " ), number_of_strings );

      CString temp_string;

      while( index < number_of_strings )
      {
         temp_string = string_array[ index ];

         WFCTRACEVAL( TEXT( " " ), index + 1 );
         WFCTRACE( temp_string );
         index++;
      }

      if ( registry.SetStringArrayValue( TEXT( "TempSources" ), string_array ) == FALSE )
      {
         ReportError( registry.GetErrorCode() );
      }
   }

   if ( registry.SetValue( TEXT( "QFile" ), TEXT( "Sammy" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "registry.SetValue failed" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
   }
   else
   {
      WFCTRACE( TEXT( "Set QFile to Sammy" ) );
   }

   CString temp_sammy( TEXT( "" ) );

   if ( registry.GetValue( TEXT( "QFile" ), temp_sammy ) == FALSE )
   {
      WFCTRACE( TEXT( "registry.GetValue failed" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
   }
   else
   {
      if ( temp_sammy.Compare( TEXT( "Sammy" ) ) == 0 )
      {
         WFCTRACE( TEXT( "GetValue OK" ) );
      }
      else
      {
         WFCTRACEVAL( TEXT( "FAIL! QFile is " ), temp_sammy );
         WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      }
   }
}
