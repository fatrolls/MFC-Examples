#include "my_xml.h"
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
** $Workfile: get_bytes.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:20p $
*/

BOOL get_bytes( const CString& filename, CByteArray& bytes )
{
   WFCTRACEINIT( TEXT( "get_bytes()" ) );

	bytes.RemoveAll();

	CFile file;

   if ( file.Open( filename, CFile::modeRead ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), filename );
      return( FALSE );
   }

   bytes.SetSize( file.GetLength() );

   file.Read( bytes.GetData(), bytes.GetSize() );

   file.Close();

   WFCTRACEVAL( TEXT( "Number of bytes read is " ), bytes.GetSize() );

	return( TRUE );
}