#include "XMLUser.h"
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
** $Workfile: main.cpp $
** $Revision: 2 $
** $Modtime: 5/16/98 4:19p $
*/


#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CExtensibleMarkupLanguageDocument document;

   if ( number_of_command_line_arguments < 2 )
   {
      // Enumerate the users on the local machine
      enumerate_users( document, NULL );
   }
   else
   {
      int index = 1;

      while( index < number_of_command_line_arguments )
      {
         if ( _tcslen( command_line_arguments[ index ] ) == 0 )
         {
            // Get the local machine as part of a list of servers
            enumerate_users( document, NULL );
         }
         else
         {
            enumerate_users( document, command_line_arguments[ index ] );
         }

         index++;
      }
   }

   document.SetAutomaticIndentation();

   save_document( document );
   parse_document();

   return( EXIT_SUCCESS );
}
