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
** $Workfile: print_provider_error.cpp $
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

void print_provider_error( _ConnectionPtr connection_p )
{
   WFCTRACEINIT( TEXT( "print_provider_error()" ) );

   ErrorPtr error_p = NULL;

   if ( connection_p->Errors->Count > 0 )
   {
      long number_of_errors = connection_p->Errors->Count;
      long loop_index       = 0;

      WFCTRACEVAL( TEXT( "There are this many errors " ), number_of_errors );

      _tprintf( TEXT( "There are %ld provider errors.\n" ), number_of_errors );

      while( loop_index < number_of_errors )
      {
         error_p = connection_p->Errors->GetItem( loop_index );

         WFCTRACEVAL( TEXT( "Error " ), error_p->Number );
         WFCTRACEVAL( TEXT( "Description " ), CString( error_p->Description ) );
         WFCTRACEVAL( TEXT( "Source " ), CString( error_p->Source ) );

         _tprintf( TEXT( "%08lX - %s\n" ), error_p->Number, (LPCTSTR) error_p->Description );
         loop_index++;
      }
   }
}
