#if ! defined( WFC_FLOAT_HEADER_FILE )

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
** $Workfile: wfcfloat.h $
** $Revision: 1 $
** $Modtime: 3/27/98 3:35p $
*/

#define WFC_FLOAT_HEADER_FILE

#if ! defined( _UNICODE )

// Non-UNICODE versions

#if ! defined( _ttof )
#define _ttof( a ) atof( a )
#endif // _ttof

#else // _UNICODE

// UNICODE versions

#if ! defined( _ttof )
#define _ttof( a ) wfc_unicode_atof( a )
#endif // _ttof

#endif // _UNICODE

double wfc_unicode_atof( LPCWSTR unicode_string );

#endif // WFC_FLOAT_HEADER_FILE
