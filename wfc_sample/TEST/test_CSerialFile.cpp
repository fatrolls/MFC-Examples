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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: test_CSerialFile.cpp $
** $Revision: 3 $
** $Modtime: 1/31/00 7:48p $
*/

void test_CSerialFile( void )
{
   WFCTRACEINIT( TEXT( "test_CSerialFile()" ) );

   CSerialFile serial;

   if ( serial.Open( TEXT( "COM2:9600,n,8,1" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open port" ) );
      return;
   }

   CCommunicationsConfiguration configuration;

   if ( serial.ConfigurationDialog( configuration ) == FALSE )
   {
#if defined( _DEBUG ) && ! defined( WFC_STL )
      configuration.Dump( afxDump );
#endif // _DEBUG
      WFCTRACEVAL( TEXT( "ConfigurationDialog() failed with " ), serial.GetErrorCode() );
      return;
   }
   else
   {
      if ( serial.GetConfiguration( configuration ) != FALSE )
      {
#if defined( _DEBUG ) && ! defined( WFC_STL )
         serial.Dump( afxDump );
#endif // _DEBUG
      }
   }
}

