//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================


// StreamDib.cpp : implementation file
//

#include "stdafx.h"
#include "StreamDib.h"

#ifndef __AFXTEMPL_H__
	#include <afxtempl.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// Definitions

IMPLEMENT_DYNAMIC(CStreamDib, CObject)
									  
#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStreamDib

CStreamDib::CStreamDib()
{
	m_lpbi = NULL;
	m_size = CSize(0, 0);	// Initialize size to NULL;

	m_Palette.m_hObject = NULL;
	m_Bitmap.m_hObject = NULL;
}

CStreamDib::~CStreamDib()
{
	if (m_lpbi != NULL)
	{
		delete m_lpbi;
		m_lpbi = NULL;
	}

	// Kill off bitmap and palette
	if (m_Palette.m_hObject != NULL)
		m_Palette.DeleteObject();

	if (m_Bitmap.m_hObject != NULL)
		m_Bitmap.DeleteObject();
}


/////////////////////////////////////////////////////////////////////////////
// CStreamDib Attributes

CPalette* CStreamDib::GetPalette()
{
	if (m_Palette.m_hObject == NULL)
		return NULL;

	return &m_Palette;
}

CBitmap* CStreamDib::GetBitmap()
{
	if (m_Bitmap.m_hObject == NULL)
		return NULL;

	return &m_Bitmap;
}


CSize CStreamDib::GetSize()
{
	return m_size;
}

/////////////////////////////////////////////////////////////////////////////
// CStreamDib Operations

BOOL CStreamDib::LoadBitmap(VARIANT FAR* pvarData) 
{
	SAFEARRAY FAR*	psaObjectData = NULL;

	// Check that we have an actual SAFEARRAY of VT_UI1 (BYTES).  
	if (pvarData == NULL || pvarData->vt != (VT_ARRAY | VT_UI1))
		return FALSE;

	// Attempt to copy the data so we can use it.
	// Attempt to Read the Object	
	if (::SafeArrayCopy(pvarData->parray, &psaObjectData) != S_OK || 
		!ReadObject(psaObjectData))
	{
		::SafeArrayDestroy(psaObjectData);
		return FALSE;
	}
	
	// Cleanup
	::SafeArrayDestroy(psaObjectData);

	// Operation has succeeded
	return TRUE;
}

BOOL CStreamDib::ReadObject(SAFEARRAY FAR* psaObject)
{
	LPSTORAGE		lpStorage = NULL;	// An OLE 2.0 IStorage object
	LPSTREAM		lpStream = NULL;	// An OLE 2.0 Data Stream
	LARGE_INTEGER	liOffset;

	// Reading the object takes two forms.  First the header structure
	// needs to be examined to see if the SAFEARRAY contains an OLE
	// object.  It doesn't determine if the object is a picture or not.

	if ((lpStorage = ReadObjectHeader(psaObject)) == NULL)
		return FALSE;

	// Open a stream on the storage.  We want the OLE 1.0 Native
	// Data stream.
	if (FAILED(lpStorage->OpenStream(L"\1Ole10Native", NULL,
		STGM_DIRECT|STGM_READ|STGM_SHARE_EXCLUSIVE, 0, &lpStream)))
	{
		lpStorage->Release();
		lpStorage = NULL;
		return FALSE;
	}

	// Access keeps its picture data 4 bytes from the beginning of the
	// Stream.  Seek the stream 4 bytes to the beginning of the 
	// BITMAPFILEHEADER.
	liOffset.LowPart = 4;
	liOffset.HighPart = 0;
	if (FAILED(lpStream->Seek(liOffset, STREAM_SEEK_SET, NULL)))
	{
		lpStream->Release();
		lpStorage->Release();
		return FALSE;
	}

	// Attempt to read the picture data in.  If the object is not a
	// picture, it will return FALSE.
	BOOL bRet = ReadObjectData(lpStream);

	// Shutdown
	lpStream->Release();
	lpStream = NULL;

	lpStorage->Release();
	lpStorage = NULL;

	return bRet;
}

LPSTORAGE CStreamDib::ReadObjectHeader(SAFEARRAY FAR* psaObject)
{
	void HUGEP*				pArray = NULL;
	struct OLEOBJECTHEADER* pHeader = NULL;
	LPBYTE					lpData = NULL;
	BOOL					bAccessed = FALSE;	
	LPOLE1STREAM			lpStream = NULL;
	LPSTORAGE				lpStorage = NULL;

	try
	{
		if (psaObject == NULL)
			AfxThrowOleException(E_INVALIDARG);
	
		// Attempt to read the object header from the safearray.  Check the 
		// type signature of the header.  If it is correct, then read in 
		// the rest of the information.
	
		// Access the data in the array.
		if (FAILED(::SafeArrayAccessData(psaObject, &pArray)))
			AfxThrowOleException(E_INVALIDARG);
		bAccessed = TRUE;	
		
		pHeader = (OLEOBJECTHEADER*)pArray;
		if (pHeader->typ != 0x1C15)	// 0x1C15 is Access cookie for OLE Object
			AfxThrowOleException(E_INVALIDARG);

		// Object is an Access OLE object set the 'IsObject' flag to TRUE
		//m_bIsObject = TRUE;
	
		// Call OleConvertOLESTREAMToIStorage to convert the Access object
		// (in OLE 1.0 format) to an OLE 2.0 format.
		lpData = (LPBYTE)pArray + pHeader->cbHdr;
	
		// Create the OLESTREAM
		lpStream = CreateOleStream(lpData, GetStreamSize(psaObject, pHeader->cbHdr));

		// Create an OLE Storage (use a temporary file)
		if (FAILED(::StgCreateDocfile(NULL, 
			STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_DIRECT|
			STGM_DELETEONRELEASE,0, &lpStorage)))
			AfxThrowOleException(E_INVALIDARG);
	
		if (FAILED(::OleConvertOLESTREAMToIStorage((LPOLESTREAM)lpStream,
			lpStorage, NULL)))
			AfxThrowOleException(E_INVALIDARG);
	
		DeleteOleStream(lpStream);
		::SafeArrayUnaccessData(psaObject);
		bAccessed = FALSE;
	}
	catch(COleException *ex)
	{
		ex->Delete();

		if (bAccessed)
			::SafeArrayUnaccessData(psaObject);
		
		if (lpStream != NULL)
			DeleteOleStream(lpStream);

		if (lpStorage != NULL)
			lpStorage->Release();

		return NULL;
	}
	return lpStorage;
}

BOOL CStreamDib::ReadObjectData(LPSTREAM lpStream)
{
	if (lpStream == NULL)
		return FALSE;

	// If the seek was successful, load the bitmap from the stream
	BOOL bRet = LoadBitmap(lpStream);
	
	return bRet;		
}

///////////////////////////////////////////////////////////////////////////
// LPOLE1STREAM creation function

LPOLE1STREAM CStreamDib::CreateOleStream(LPBYTE lpData, DWORD dwSize)
{
	ASSERT(lpData != NULL);
	
	// Create a new OLESTREAMVTBL to handle callbacks
	LPOLESTREAMVTBL pvt = new OLESTREAMVTBL;
	
	// Initialize callbacks w/ our global functions
	pvt->Get = &Get;	
	pvt->Put = &Put;
	
	// Create an OLE1STREAM
	LPOLE1STREAM pStream = new OLE1STREAM;
	
	// Initialize it with the OLESTREAMVTBL and data
	pStream->pvt = pvt;
	pStream->dwSize = dwSize;
	pStream->lpData = lpData;
	
	return pStream;
}

void CStreamDib::DeleteOleStream(LPOLE1STREAM pStream)
{
	// Delete all the data members of the OLE1STREAM and 
	// NULL the OLE1STREAM::lpData member (it will be 
	// destroyed during ::SafeArrayDestroy().
	
	ASSERT(pStream != NULL);
	ASSERT(pStream->pvt != NULL);
	
	// Delete or NULL member data
	delete pStream->pvt;
	pStream->lpData = NULL;
	
	// Delete the stream itself
	delete pStream;
	pStream = NULL;
}


DWORD CStreamDib::GetStreamSize(SAFEARRAY FAR* psaObject, DWORD dwOffset)
{
	ASSERT(psaObject != NULL);
	LONG lBoundLower, lBoundUpper;

	::SafeArrayGetLBound(psaObject, 0, &lBoundLower);
	::SafeArrayGetUBound(psaObject, 0, &lBoundUpper);

	DWORD dwSize = ((DWORD)(lBoundUpper - lBoundLower)) - dwOffset;
	if (dwSize < 0)
		dwSize = 0;

	return dwSize;
}

BOOL CStreamDib::LoadBitmap(LPSTREAM lpStream)
{
	LPBYTE lpFileHeader = NULL;
	ULONG ulRead;
	int nColors;
	LPBYTE lpInfo = NULL;
	BYTE* pBits = NULL;

	try
	{
		if (lpStream == NULL)
			AfxThrowMemoryException();

		// Read in the BITMAPFILEHEADER
		lpFileHeader = new BYTE[sizeof(BITMAPFILEHEADER)];
		if (FAILED(lpStream->Read((void*)lpFileHeader, 
			sizeof(BITMAPFILEHEADER), &ulRead)))
			AfxThrowMemoryException();

		ASSERT(ulRead == sizeof(BITMAPFILEHEADER));

		LPBITMAPFILEHEADER lpfh = (LPBITMAPFILEHEADER)lpFileHeader;
		if (lpfh->bfType != ((WORD) 'B' | ('M' << 8)))
			AfxThrowMemoryException();

		// Read in the BITMAPINFO struct
		// size equals BITMAPINFOHEADER plus difference between
		// the bfOffBits and the header.  SO, sounds like you
		// should allocate a bfOffBits
		DWORD dwSize = lpfh->bfOffBits - sizeof(BITMAPFILEHEADER);
		lpInfo = new BYTE[dwSize];

		if (FAILED(lpStream->Read((void*)lpInfo, dwSize, &ulRead)))
			AfxThrowMemoryException();
		ASSERT(ulRead == dwSize);

		LPBITMAPINFO lpbi = (LPBITMAPINFO)lpInfo;

		// This code only supports 2, 16, and 256 color bitmaps
		if (lpbi->bmiHeader.biBitCount != 1 &&
		    lpbi->bmiHeader.biBitCount != 4 &&
				lpbi->bmiHeader.biBitCount != 8)
			AfxThrowMemoryException();

		if (lpbi->bmiHeader.biClrUsed != 0)
			nColors = lpbi->bmiHeader.biClrUsed;
		else
			nColors = 1 << lpbi->bmiHeader.biBitCount;

		MergePalette(lpbi->bmiColors, nColors);

		CSize size(lpbi->bmiHeader.biWidth, lpbi->bmiHeader.biHeight);
		m_size = size;
		CreateBitmap(size);
	
		// Read in the actual BITMAP
		dwSize = lpfh->bfSize - lpfh->bfOffBits;
		pBits = new BYTE[dwSize];

		if (FAILED(lpStream->Read((void*)pBits, dwSize, &ulRead)))
			AfxThrowMemoryException();
		ASSERT(ulRead == dwSize);

		// BLOCK: Set the DIB sections bits from the DIB we are loading
		{
			CWindowDC dc(NULL);
			VERIFY( SetDIBits( dc.m_hDC, (HBITMAP)m_Bitmap.m_hObject, 0, 
				lpbi->bmiHeader.biHeight, pBits, lpbi, DIB_RGB_COLORS ) 
				== lpbi->bmiHeader.biHeight );
		}

		delete lpInfo;
		delete lpFileHeader;
		delete pBits;
		lpInfo = NULL;
		lpFileHeader = NULL;
		pBits = NULL;
	}
	catch(CMemoryException *ex)
	{
		ex->Delete();
		if (lpInfo != NULL)
		{
			delete lpInfo;
			lpInfo = NULL;
		}

		if (lpFileHeader != NULL)
		{
			delete lpFileHeader;
			lpFileHeader = NULL;
		}

		if (pBits != NULL)
		{
			delete pBits;
			pBits = NULL;
		}

		return FALSE;
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////
// Implementation Functions

void CStreamDib::MergePalette(RGBQUAD* pColors, int nColors)
{
	CMap<DWORD, DWORD, BOOL, BOOL> PaletteMap;
	DWORD dword;
	BOOL bScrap;
	int i;
	POSITION pos;

	memcpy( m_rgbPalette, rgbStd256, sizeof(RGBQUAD) * 256 );

	for(i=0; i<nColors; i++)
	{
		PaletteMap.SetAt(MAKEDWORD(pColors[i]),TRUE);
	}

	i = 0;
	while (PaletteMap.GetCount() < 256)
		PaletteMap.SetAt(MAKEDWORD(m_rgbPalette[i++]),FALSE);
		 

	for(i=0,pos=PaletteMap.GetStartPosition(); pos!=NULL; i++)
	{
		PaletteMap.GetNextAssoc(pos,dword,bScrap);			
		m_rgbPalette[i]=MAKERGBQUAD(dword);
	}
}


void CStreamDib::CreateBitmap(CSize& size)
{
	BYTE*			pBits;

	if (m_Bitmap.m_hObject != NULL)
		m_Bitmap.DeleteObject();

	ASSERT(m_lpbi == NULL);

	// Fill in the BITMAPINFOHEADER
	m_lpbi = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER) 
		+ (256 * sizeof(RGBQUAD))];
	m_lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_lpbi->bmiHeader.biWidth = size.cx;
	m_lpbi->bmiHeader.biHeight = size.cy;
	m_lpbi->bmiHeader.biPlanes = 1;
	m_lpbi->bmiHeader.biBitCount = 8;
	m_lpbi->bmiHeader.biCompression = BI_RGB;
	m_lpbi->bmiHeader.biSizeImage = WIDTHBYTES((DWORD)size.cx * 8) * size.cy;
	m_lpbi->bmiHeader.biXPelsPerMeter = 0;
	m_lpbi->bmiHeader.biYPelsPerMeter = 0;
	m_lpbi->bmiHeader.biClrUsed = 0;
	m_lpbi->bmiHeader.biClrImportant = 0;

	// Fill in the color table
	UINT uUsage = DIB_RGB_COLORS;

	memcpy( m_lpbi->bmiColors, m_rgbPalette, sizeof(RGBQUAD) * 256 );

	CWindowDC dc(NULL);
	HBITMAP hBitmap = CreateDIBSection( dc.m_hDC, m_lpbi, uUsage, 
		(VOID**)&pBits, NULL, 0 );
	
	m_Bitmap.Attach(hBitmap);

	delete [] (BYTE *)m_lpbi;
	m_lpbi = NULL;
}

DWORD FAR PASCAL Get(LPOLESTREAM pstm, void FAR* pb, DWORD cb)
{
	// Check the validity of the stream and that we are not reading more
	// bytes than are in the stream.
	LPOLE1STREAM pStream = (LPOLE1STREAM)pstm;
	if ((pStream == NULL) || (pStream->lpData == NULL) || 
		(pStream->dwSize < cb))
		return 0L;
	
	// ASSUME that buffers do not overlap.
	memcpy(pb, pStream->lpData, cb);
	pStream->lpData += cb;		// Update pointer
	pStream->dwSize -= cb;
	
	return cb;
}

DWORD FAR PASCAL Put(LPOLESTREAM pstm, const void FAR* pb, DWORD cb)
{
	// Check the validity of the stream and that we are not writing
	// more data than we have space for.
	LPOLE1STREAM pStream = (LPOLE1STREAM)pstm;
	if ((pStream == NULL) || (pStream->lpData == NULL) || (pb == NULL) ||
		(pStream->dwSize < cb))
		return 0L;
	
	// ASSUME that buffers don't overlap.
	memcpy(pStream->lpData, pb, cb);
	pStream->lpData += cb;		// Update pointer
	pStream->dwSize -= cb;
	
	return cb;
}
