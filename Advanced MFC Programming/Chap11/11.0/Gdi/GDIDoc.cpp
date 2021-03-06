#include "stdafx.h"
#include "GDI.h"

#include "GDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTHBYTES(bits) ((((bits)+31)/32)*4)

COLORREF colorDef[COLOR_BUTTON_NUM]=
{
	RGB(0x00, 0x00, 0x00),
	RGB(0x80, 0x00, 0x00),
	RGB(0x00, 0x80, 0x00),
	RGB(0x80, 0x80, 0x00),
	RGB(0x00, 0x00, 0x80),
	RGB(0x80, 0x00, 0x80),
	RGB(0x00, 0x80, 0x80),
	RGB(0xC0, 0xC0, 0xC0),
	RGB(0xC0, 0xFF, 0xC0),
	RGB(0xA6, 0xCA, 0xF0),
	RGB(0xFF, 0xF0, 0xF0),
	RGB(0xA0, 0xA0, 0xA4),
	RGB(0x80, 0x80, 0x80),
	RGB(0xFF, 0x00, 0x00),
	RGB(0x00, 0xFF, 0x00),
	RGB(0xFF, 0xFF, 0x00),
	RGB(0x00, 0x00, 0xFF),
	RGB(0xFF, 0x00, 0xFF),
	RGB(0x00, 0xFF, 0xFF),
	RGB(0xFF, 0xFF, 0xFF)
};

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	LPLOGPALETTE lpLogPal;
	int i;

	lpLogPal=(LPLOGPALETTE) new BYTE
	[
		sizeof(LOGPALETTE)+(PALETTE_SIZE-1)*sizeof(PALETTEENTRY)
	];
	lpLogPal->palVersion=0x300;
	lpLogPal->palNumEntries=PALETTE_SIZE;
	for(i=0; i<COLOR_BUTTON_NUM; i++)
	{
		lpLogPal->palPalEntry[i].peRed=GetRValue(colorDef[i]);
		lpLogPal->palPalEntry[i].peGreen=GetGValue(colorDef[i]);
		lpLogPal->palPalEntry[i].peBlue=GetBValue(colorDef[i]);;
		lpLogPal->palPalEntry[i].peFlags=NULL;

	}
	VERIFY(m_palDraw.CreatePalette(lpLogPal));
	delete [](BYTE *)lpLogPal;

	m_hDIB=NULL;
}

CGDIDoc::~CGDIDoc()
{
}

BOOL CGDIDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;

	return TRUE;
}

void CGDIDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		HGLOBAL hDib;
		BITMAPFILEHEADER bmf;
		BITMAPINFOHEADER bi;
		LPBITMAPINFOHEADER lpBi;
		DWORD dwSizeCT;

		hDib=m_hDIB;
		ASSERT(hDib);
		bmf.bfType='MB';
		bmf.bfSize=sizeof(bmf)+::GlobalSize(hDib);
		bmf.bfReserved1=0;
		bmf.bfReserved2=0;
		lpBi=(LPBITMAPINFOHEADER)::GlobalLock(hDib);
		bi=*lpBi;
		if(bi.biSizeImage == 0)
		{
			bi.biSizeImage=WIDTHBYTES(bi.biBitCount*bi.biWidth)*bi.biHeight;
		}
		dwSizeCT=GetColorTableSize(bi.biBitCount);
		bmf.bfOffBits=sizeof(bmf)+bi.biSize+dwSizeCT*sizeof(RGBQUAD);
		ar.Write((char *)&bmf, sizeof(bmf));
		ar.Write((LPSTR)lpBi, bi.biSize+dwSizeCT*sizeof(RGBQUAD)+bi.biSizeImage);
		::GlobalUnlock(hDib);
	}
	else
	{
		BITMAPFILEHEADER bf;
		DWORD dwSize;
		LPSTR lpDIB;

		if(m_hDIB != NULL)
		{
			::GlobalFree(m_hDIB);	
			m_hDIB=NULL;
		}
		if
		(
			ar.Read
			(
				(LPSTR)&bf,
				sizeof(BITMAPFILEHEADER)
			) != sizeof(BITMAPFILEHEADER)
		)return;

		if(bf.bfType != 'MB')return;
		dwSize=bf.bfSize-sizeof(BITMAPFILEHEADER);
		m_hDIB=(HBITMAP)::GlobalAlloc(GHND, dwSize);
		ASSERT(m_hDIB);
		lpDIB=(LPSTR)::GlobalLock(m_hDIB);
		ASSERT(lpDIB);
		if(ar.Read(lpDIB, dwSize) != dwSize)
		{
			::GlobalUnlock(m_hDIB);
			::GlobalFree(m_hDIB);
			m_hDIB=NULL;
		}
		else ::GlobalUnlock(m_hDIB);
	}
}

#ifdef _DEBUG
void CGDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

DWORD CGDIDoc::GetColorTableSize(WORD wBitCount)
{
	DWORD dwSizeCT;

	switch(wBitCount)
	{                
		case 1:
		{
			dwSizeCT=2;
			break;
		}
		case 4:
		{
			dwSizeCT=16;
			break;
		}
		case 8:
		{
			dwSizeCT=256;
			break;
		}
		case 24:
		{
			dwSizeCT=0;
		}
	}
	return dwSizeCT;
}
