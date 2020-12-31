#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"
#include "SelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTHBYTES(bits) ((((bits)+31)/32)*4)

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
	ON_COMMAND(ID_CAPTURE_GO, OnCaptureGo)
	ON_COMMAND(ID_CAPTURE_SETTING, OnCaptureSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	LPLOGPALETTE lpLogPal;

	lpLogPal=(LPLOGPALETTE)::GlobalAlloc
	(
		GMEM_FIXED,
		sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*(PALETTE_SIZE-1)
	);
	lpLogPal->palVersion=PALVERSION;
	lpLogPal->palNumEntries=PALETTE_SIZE;
	VERIFY(m_palDraw.CreatePalette(lpLogPal));
	::GlobalFree(lpLogPal);

	m_hDIB=NULL;
	m_hWnd=NULL;
}

CGDIDoc::~CGDIDoc()
{
	if(m_hDIB != NULL)::GlobalFree(m_hDIB);
}

BOOL CGDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CGDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
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
		dwSizeCT=GetColorTableSize(bi.biBitCount);
		bmf.bfOffBits=sizeof(bmf)+bi.biSize+dwSizeCT*sizeof(RGBQUAD);
		ar.Write((char *)&bmf, sizeof(bmf));
		ar.Write((LPSTR)lpBi, bi.biSize+dwSizeCT*sizeof(RGBQUAD)+bi.biSizeImage);
		::GlobalUnlock(hDib);
	}
	else
	{
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

void CGDIDoc::OnCaptureGo() 
{
	CGDIView *pView;
	POSITION pos;

	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWMINIMIZED);
	pos=GetFirstViewPosition();
	pView=(CGDIView *)GetNextView(pos);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGDIView)));
	pView->PrepareCapture();
}

void CGDIDoc::GetCaptureBitmap(CBitmap *pBmp)
{
	if(m_hDIB != NULL)::GlobalFree(m_hDIB);
	m_hDIB=ConvertDDBtoDIB(pBmp);
	UpdateAllViews(NULL);
}

HGLOBAL CGDIDoc::ConvertDDBtoDIB(CBitmap *pBmp)
{
	BITMAP bm;
    BITMAPINFOHEADER bi;
	LPBITMAPINFO lpBi;
    DWORD dwSizeCT;
	DWORD dwDibLen;
	CGDIView *ptrView;
	POSITION pos;
	HGLOBAL hDib;
	LPLOGPALETTE lpLogPal;
	int i;
	CPalette palSys;
	CPalette *pPalOld;
	RGBQUAD rgbQuad[PALETTE_SIZE];

	pos=GetFirstViewPosition();
	ptrView=(CGDIView *)GetNextView(pos);
	ASSERT(ptrView->IsKindOf(RUNTIME_CLASS(CGDIView)));
	CClientDC dc(ptrView);

	lpLogPal=(LPLOGPALETTE)::GlobalAlloc
	(
		GMEM_FIXED,
		sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*(PALETTE_SIZE-1)
	);
	lpLogPal->palVersion=PALVERSION;
	lpLogPal->palNumEntries=PALETTE_SIZE;

	for(i=0; i<PALETTE_SIZE; i++)
	{
		*((WORD *)(&lpLogPal->palPalEntry[i].peRed))=i;
		lpLogPal->palPalEntry[i].peBlue=0;
		lpLogPal->palPalEntry[i].peFlags=PC_EXPLICIT;
	}

	VERIFY(palSys.CreatePalette(lpLogPal));
	pPalOld=dc.SelectPalette(&palSys, FALSE);
	dc.RealizePalette();

	pBmp->GetBitmap(&bm);
	bi.biSize=sizeof(BITMAPINFOHEADER);		
    bi.biWidth=bm.bmWidth;
    bi.biHeight=bm.bmHeight;
    bi.biPlanes=bm.bmPlanes;
    bi.biBitCount=bm.bmPlanes*bm.bmBitsPixel;
	bi.biCompression=BI_RGB;				
	bi.biSizeImage=0;
	bi.biXPelsPerMeter=0;
	bi.biYPelsPerMeter=0;
	bi.biClrUsed=0;                                                        
	bi.biClrImportant=0;
	
    dwSizeCT=GetColorTableSize(bi.biBitCount);
    dwDibLen=bi.biSize+dwSizeCT*sizeof(RGBQUAD);
    
	hDib=::GlobalAlloc(GHND, dwDibLen);		
	lpBi=(LPBITMAPINFO)::GlobalLock(hDib);

    lpBi->bmiHeader=bi;
	VERIFY
	(
		::GetDIBits															
		(
			dc.GetSafeHdc(), 
			(HBITMAP)pBmp->GetSafeHandle(), 
			0, 
			(WORD)bi.biHeight, 
			NULL,
			lpBi,
			DIB_RGB_COLORS
		)
	);

	memcpy((LPSTR)rgbQuad, (LPSTR)lpBi->bmiColors, sizeof(RGBQUAD)*PALETTE_SIZE);
	for(i=0; i<PALETTE_SIZE; i++)
	{
		lpLogPal->palPalEntry[i].peRed=rgbQuad[i].rgbRed;
		lpLogPal->palPalEntry[i].peGreen=rgbQuad[i].rgbGreen;
		lpLogPal->palPalEntry[i].peBlue=rgbQuad[i].rgbBlue;
		lpLogPal->palPalEntry[i].peFlags=NULL;
	}
	ASSERT(m_palDraw.GetSafeHandle() != NULL);
	m_palDraw.SetPaletteEntries(0, PALETTE_SIZE, lpLogPal->palPalEntry);
	::GlobalFree(lpLogPal);

	bi=lpBi->bmiHeader;
    ::GlobalUnlock(hDib);
    if(bi.biSizeImage == 0)													
    {                                                                         
        bi.biSizeImage=WIDTHBYTES(bi.biBitCount*bi.biWidth)*bi.biHeight;
    }
    dwDibLen+=bi.biSizeImage;
	hDib=::GlobalReAlloc(hDib, dwDibLen, GHND);
	ASSERT(hDib);
	lpBi=(LPBITMAPINFO)::GlobalLock(hDib);                                 
	ASSERT(hDib);
    VERIFY
    (
    	::GetDIBits
    	(
    		dc.GetSafeHdc(), 
    		(HBITMAP)pBmp->GetSafeHandle(), 
    		0, 
    		(WORD)bi.biHeight, 
    		(LPSTR)lpBi+sizeof(BITMAPINFOHEADER)+dwSizeCT*sizeof(RGBQUAD),
			lpBi,
			DIB_RGB_COLORS
		)
	);
	::GlobalUnlock(hDib);

	dc.SelectPalette(pPalOld, FALSE);

	return hDib;
}

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

void CGDIDoc::OnCaptureSetting() 
{
	CSelDlg dlg;
	
	if(dlg.DoModal() == IDOK)
	{
		m_hWnd=dlg.GetSelectedWnd();
	}
}
