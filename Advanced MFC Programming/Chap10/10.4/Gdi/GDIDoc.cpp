#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIDTHBYTES(bits) ((((bits)+31)/32)*4)

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	m_hDIB=NULL;
}

CGDIDoc::~CGDIDoc()
{
	if(m_hDIB != NULL)
	{
		::GlobalFree(m_hDIB);	
		m_hDIB=NULL;
	}
}

BOOL CGDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

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

		hDib=ConvertDDBtoDIB(&m_bmpDraw);
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
		::GlobalFree(hDib);
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
		m_hDIB=::GlobalAlloc(GHND, dwSize);
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

void CGDIDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);
}

void CGDIDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bmpDraw.GetSafeHandle() != NULL);
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
	CPalette *pPalOld;
	HGLOBAL hDib;

	pos=GetFirstViewPosition();
	ptrView=(CGDIView *)GetNextView(pos);
	ASSERT(ptrView->IsKindOf(RUNTIME_CLASS(CGDIView)));
	CClientDC dc(ptrView);

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
    
    pPalOld=dc.SelectPalette(&m_palDraw, FALSE);
	dc.RealizePalette();
    
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