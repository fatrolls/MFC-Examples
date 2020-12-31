#include "StdAfx.h"
#include "./Utility.h"


//-------------------------------------------------------------------------
// Function Name    :GetModulePath
// Parameter(s)     :HMODULE hModule	Get module handle
// Return           :The module file path
// Create			:2007-1-10 11:24	Jerry.Wang
// Memo             :Retrieve the path of the given module
//-------------------------------------------------------------------------
CString CUtility::GetModulePath(HMODULE hModule /* = NULL */)
{
	TCHAR buf[MAX_PATH] = {'\0'};
	CString strDir, strTemp;

	::GetModuleFileName( hModule, buf, MAX_PATH);
	strTemp = buf;
	strDir = strTemp.Left( strTemp.ReverseFind('\\') + 1 );
	return strDir;
}


//-------------------------------------------------------------------------
// Function Name    :IsFileExist
// Parameter(s)     :LPCTSTR lpszFilePath	File path
// Return           :
// Create			:2007-4-23 15:13	Jerry.Wang
// Memo             :verify the file exist
//-------------------------------------------------------------------------
BOOL CUtility::IsFileExist(LPCTSTR lpszFilePath)
{
	BOOL bExist = FALSE;
	HANDLE hFile = NULL;

	hFile = CreateFile( lpszFilePath
		, GENERIC_READ
		, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL
		, OPEN_EXISTING
		, 0
		, 0
		);

	if( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle( hFile );
		bExist = TRUE;
	}

	return bExist;
}


//-------------------------------------------------------------------------
// Function Name    :ExtractResourceToFile
// Parameter(s)     :UINT nResID			The resource id
//					:LPCTSTR lpszFilename	The file name
//					:HMODULE hModule		The module handle
// Return           :BOOL					Success on TRUE
// Create			:2007-1-8 17:35		Jerry.Wang
// Memo             :Extract resource to file
//-------------------------------------------------------------------------
BOOL CUtility::ExtractResourceToFile( LPCTSTR lpszType
									 , UINT nResID
									 , LPCTSTR lpszFilename
									 , HMODULE hModule
									 )
{
	HRSRC hRes = ::FindResource( hModule, MAKEINTRESOURCE(nResID), lpszType);
	if( hRes == NULL )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	DWORD dwSize = ::SizeofResource( hModule, hRes); 
	if( dwSize == 0 )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	HGLOBAL hGlobal = ::LoadResource( hModule, hRes); 
	if( hGlobal == NULL )
	{
		ATLASSERT(FALSE);
		return FALSE;
	}

	LPVOID pBuffer = ::LockResource(hGlobal); 
	if( pBuffer == NULL )
	{
		ATLASSERT(FALSE);
		::FreeResource(hGlobal); 
		return FALSE;
	}

	HANDLE hFile = ::CreateFile( lpszFilename
		, GENERIC_WRITE
		, FILE_SHARE_WRITE | FILE_SHARE_READ
		, NULL
		, CREATE_ALWAYS
		, 0
		, NULL
		);
	if( hFile == NULL )
	{
		ATLASSERT(FALSE);
		::FreeResource(hGlobal); 
		return FALSE;
	}

	DWORD dwWritten = 0;
	::WriteFile( hFile, pBuffer, dwSize, &dwWritten, NULL);
	if( dwWritten != dwSize )
	{
		ATLASSERT(FALSE);
		::FreeResource(hGlobal); 
		return FALSE;
	}

	::FlushFileBuffers(hFile);
	::CloseHandle(hFile);
	::FreeResource(hGlobal); 

	return TRUE;
}// ExtractResourceToFile


//-------------------------------------------------------------------------    
// Function Name    :LoadImage
// Parameter(s)     :UINT nID				The resource id
//					:LPCTSTR lpszType		The resource type
//					:HINSTANCE hInstance	The module handle
// Return           :Image *
// Create			:2009-3-12 14:28 Jerry.Wang                                     
// Memo             :Load the GDIPlus::Image from resource
//-------------------------------------------------------------------------   
Image * CUtility::LoadImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance /*=NULL*/)
{
	Image * pImage = NULL;

	if( lpszType == RT_BITMAP )
	{
		HBITMAP hBitmap = ::LoadBitmap( hInstance, MAKEINTRESOURCE(nID) );
		pImage = (Image*)Bitmap::FromHBITMAP(hBitmap, 0);
		::DeleteObject(hBitmap);
		return pImage;
	}		

	hInstance = (hInstance == NULL) ? ::AfxGetResourceHandle() : hInstance;
	HRSRC hRsrc = ::FindResource ( hInstance, MAKEINTRESOURCE(nID), lpszType); 
	ASSERT(hRsrc != NULL);

	DWORD dwSize = ::SizeofResource( hInstance, hRsrc);
	LPBYTE lpRsrc = (LPBYTE)::LoadResource( hInstance, hRsrc);
	ASSERT(lpRsrc != NULL);

	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
	LPBYTE pMem = (LPBYTE)::GlobalLock(hMem);
	memcpy( pMem, lpRsrc, dwSize);
	IStream * pStream = NULL;
	::CreateStreamOnHGlobal( hMem, FALSE, &pStream);

	pImage = Image::FromStream(pStream);

	::GlobalUnlock(hMem);
	pStream->Release();
	::FreeResource(lpRsrc);

	return pImage;
}