/**************************************************************************
 *
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *
 *  Copyright (C) 1992 - 1996 Microsoft Corporation.  All Rights Reserved.
 *
 **************************************************************************/
/****************************************************************************
 *
 *  WRITEAVI.C
 *
 *  Creates the file OUTPUT.AVI, an AVI file consisting of a rotating clock
 *  face.  This program demonstrates using the functions in AVIFILE.DLL
 *  to make writing AVI files simple.
 *
 *  This is a stripped-down example; a real application would have a user
 *  interface and check for errors.
 *
 ***************************************************************************/
#include "stdafx.h"
#include <windowsx.h>
#include <memory.h>
#include <mmsystem.h>
#include <vfw.h>

#include "writeavi.h"

static HANDLE  MakeDib( HBITMAP hbitmap, UINT bits )
{
	HANDLE              hdib ;
	HDC                 hdc ;
	BITMAP              bitmap ;
	UINT                wLineLen ;
	DWORD               dwSize ;
	DWORD               wColSize ;
	LPBITMAPINFOHEADER  lpbi ;
	LPBYTE              lpBits ;
	
	GetObject(hbitmap,sizeof(BITMAP),&bitmap) ;

	//
	// DWORD align the width of the DIB
	// Figure out the size of the colour table
	// Calculate the size of the DIB
	//
	wLineLen = (bitmap.bmWidth*bits+31)/32 * 4;
	wColSize = sizeof(RGBQUAD)*((bits <= 8) ? 1<<bits : 0);
	dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
		(DWORD)(UINT)wLineLen*(DWORD)(UINT)bitmap.bmHeight;

	//
	// Allocate room for a DIB and set the LPBI fields
	//
	hdib = GlobalAlloc(GHND,dwSize);
	if (!hdib)
		return hdib ;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib) ;

	lpbi->biSize = sizeof(BITMAPINFOHEADER) ;
	lpbi->biWidth = bitmap.bmWidth ;
	lpbi->biHeight = bitmap.bmHeight ;
	lpbi->biPlanes = 1 ;
	lpbi->biBitCount = (WORD) bits ;
	lpbi->biCompression = BI_RGB ;
	lpbi->biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize ;
	lpbi->biXPelsPerMeter = 0 ;
	lpbi->biYPelsPerMeter = 0 ;
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;
	lpbi->biClrImportant = 0 ;

	//
	// Get the bits from the bitmap and stuff them after the LPBI
	//
	lpBits = (LPBYTE)(lpbi+1)+wColSize ;

	hdc = CreateCompatibleDC(NULL) ;

	GetDIBits(hdc,hbitmap,0,bitmap.bmHeight,lpBits,(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	// Fix this if GetDIBits messed it up....
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	DeleteDC(hdc) ;
	GlobalUnlock(hdib);

	return hdib ;
}

CAVIFile::CAVIFile(LPCTSTR lpszFileName, int xdim, int ydim)
 :	FName(lpszFileName),
	xDim(xdim), yDim(ydim), bOK(true), nFrames(0)
{
	pfile = NULL;
	ps = NULL;
	psCompressed = NULL;
	psText = NULL;
	aopts[0] = &opts;
	WORD wVer = HIWORD(VideoForWindowsVersion());
	if (wVer < 0x010A)
	{
		// oops, we are too old, blow out of here
		bOK = false;
	}
	else
	{
		AVIFileInit();
	}
}

CAVIFile::~CAVIFile()
{
	if (ps)
		AVIStreamClose(ps);

	if (psCompressed)
		AVIStreamClose(psCompressed);

	if (psText)
		AVIStreamClose(psText);

	if (pfile)
		AVIFileClose(pfile);

	WORD wVer = HIWORD(VideoForWindowsVersion());
	if (wVer >= 0x010A)
	{
		AVIFileExit();
	}
}

bool CAVIFile::AddFrame(CBitmap& bmp)
{
	HRESULT hr;
	char szMessage[BUFSIZE];

	if (!bOK)
		return false;
	LPBITMAPINFOHEADER alpbi = (LPBITMAPINFOHEADER)GlobalLock(MakeDib(bmp, 8));
	if (alpbi == NULL)
		return false;
	if (xDim>=0 && xDim != alpbi->biWidth)
	{
		GlobalFreePtr(alpbi);
		return false;
	}
	if (yDim>=0 && yDim != alpbi->biHeight)
	{
		GlobalFreePtr(alpbi);
		return false;
	}
	xDim = alpbi->biWidth;
	yDim = alpbi->biHeight;
	if (nFrames == 0)
	{
		hr = AVIFileOpen(&pfile,		    // returned file pointer
			       FName,							// file name
				   OF_WRITE | OF_CREATE,		    // mode to open file with
				   NULL);							// use handler determined
													// from file extension....
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}
		_fmemset(&strhdr, 0, sizeof(strhdr));
		strhdr.fccType                = streamtypeVIDEO;// stream type
		strhdr.fccHandler             = 0;
		strhdr.dwScale                = 1;
		strhdr.dwRate                 = 15;		    // 15 fps
		strhdr.dwSuggestedBufferSize  = alpbi->biSizeImage;
		SetRect(&strhdr.rcFrame, 0, 0,		    // rectangle for stream
			(int) alpbi->biWidth,
			(int) alpbi->biHeight);

		// And create the stream;
		hr = AVIFileCreateStream(pfile,		    // file pointer
						         &ps,		    // returned stream pointer
								 &strhdr);	    // stream header
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		_fmemset(&opts, 0, sizeof(opts));

		if (!AVISaveOptions(NULL, 0, 1, &ps, (LPAVICOMPRESSOPTIONS FAR *) &aopts))
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		hr = AVIMakeCompressedStream(&psCompressed, ps, &opts, NULL);
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		hr = AVIStreamSetFormat(psCompressed, 0,
					   alpbi,	    // stream format
				       alpbi->biSize +   // format size
				       alpbi->biClrUsed * sizeof(RGBQUAD));
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		// Fill in the stream header for the text stream....

		// The text stream is in 60ths of a second....
/*
		_fmemset(&strhdr, 0, sizeof(strhdr));
		strhdr.fccType                = streamtypeTEXT;
		strhdr.fccHandler             = mmioFOURCC('D', 'R', 'A', 'W');
		strhdr.dwScale                = 1;
		strhdr.dwRate                 = 60;
		strhdr.dwSuggestedBufferSize  = sizeof(szText);
		SetRect(&strhdr.rcFrame, 0, (int) alpbi->biHeight,
			(int) alpbi->biWidth, (int) alpbi->biHeight + TEXT_HEIGHT);

		// ....and create the stream.
		hr = AVIFileCreateStream(pfile, &psText, &strhdr);
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}

		dwTextFormat = sizeof(dwTextFormat);
		hr = AVIStreamSetFormat(psText, 0, &dwTextFormat, sizeof(dwTextFormat));
		if (hr != AVIERR_OK)
		{
			GlobalFreePtr(alpbi);
			bOK = false;
			return false;
		}
*/
	}

	// Jetzt eigentliches Schreiben
	hr = AVIStreamWrite(psCompressed,	// stream pointer
		nFrames * 10,				// time of this frame
		1,				// number to write
		(LPBYTE) alpbi +		// pointer to data
			alpbi->biSize +
			alpbi->biClrUsed * sizeof(RGBQUAD),
			alpbi->biSizeImage,	// size of this frame
		AVIIF_KEYFRAME,			 // flags....
		NULL,
		NULL);
	if (hr != AVIERR_OK)
	{
		GlobalFreePtr(alpbi);
		bOK = false;
		return false;
	}

	// Make some text to put in the file ...
	//LoadString(hInstance, IDS_TEXTFORMAT, szMessage, BUFSIZE );
	/*
	strcpy(szMessage, "This is frame #%d");
		
	int iLen = wsprintf(szText, szMessage, (int)(nFrames + 1));

	// ... and write it as well.
	hr = AVIStreamWrite(psText,
			nFrames * 40,
			1,
			szText,
			iLen + 1,
			AVIIF_KEYFRAME,
			NULL,
			NULL);
	if (hr != AVIERR_OK)
	{
		GlobalFreePtr(alpbi);
		bOK = false;
		return false;
	}
	*/
	GlobalFreePtr(alpbi);

	nFrames++;
	return true;
}

