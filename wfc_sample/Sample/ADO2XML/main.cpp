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
** $Workfile: main.cpp $
** $Revision: 1 $
** $Modtime: 3/18/00 7:29a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#endif // WFC_STL

int _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   // Start COM
   CoInitialize( NULL );

   VARIANT v;

   CDatabaseParameters database_parameters;

   // Get these parameters from our config file (XML of course)
   database_parameters.SetProvider( TEXT( "Microsoft.Jet.OLEDB.4.0" ) );

   // List of MDB's on my system

   //database_parameters.SetDataSource( TEXT( "c:\\program files\\microsoft visual studio\\common\\tools\\vcm\\vcm.mdb" ) );
   //database_parameters.SetDataSource( TEXT( "c:\\program files\\common files\\microsoft shared\\pushpins\\autopins\\am7ppins.mdb" ) );
   //database_parameters.SetDataSource( TEXT( "c:\\winnt\\msapps\\repostry\\repostry.mdb" ) );
   database_parameters.SetDataSource( TEXT( "d:\\msoffice\\access\\samples\\northwind.mdb" ) );
   //database_parameters.SetDataSource( TEXT( "f:\\cd\nt4sp6a\\i386\\empty_pb.mdb" ) );

   CExtensibleMarkupLanguageDocument settings;

   convert_desired_tables( settings.GetRootElement(), database_parameters );

   // Stop COM
   CoUninitialize();
   return( EXIT_SUCCESS );
}
