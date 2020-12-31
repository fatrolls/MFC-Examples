#include <wfc.h>
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
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: SKYPAGE.CPP $
** $Revision: 3 $
** $Modtime: 3/08/98 3:19p $
*/

int _tmain( int argc, LPCTSTR argv[] )
{
   CSkyWord pager;

   pager.SetMessage( TEXT( "Howdy" ) );
   pager.SetAccount( TEXT( "1111111" ) );

   if ( pager.Send() != FALSE )
   {
      _tprintf( TEXT( "Message not sent.\n" ) );
   }
   else
   {
      _tprintf( TEXT( "Message sent.\n" ) );
   }

   return( EXIT_SUCCESS );
}
