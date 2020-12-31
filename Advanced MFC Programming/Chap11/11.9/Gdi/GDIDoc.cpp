#include "stdafx.h"
#include "GDI.h"
#include "GDIView.h"
#include "GDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
	ON_COMMAND(ID_GRID, OnGrid)
	ON_UPDATE_COMMAND_UI(ID_GRID, OnUpdateGrid)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(TOOL_HEAD_ID, TOOL_TAIL_ID, OnDrawTool)
	ON_UPDATE_COMMAND_UI_RANGE(TOOL_HEAD_ID, TOOL_TAIL_ID, OnUpdateDrawTool)
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
	m_nRatio=1;
	m_bGridOn=FALSE;
	m_nCurrentTool=TOOL_PEN;
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

CGDIView *CGDIDoc::GetCGDIView()
{
	POSITION pos;
	CGDIView *ptrView;

	pos=GetFirstViewPosition();
	ptrView=(CGDIView *)GetNextView(pos);
	ASSERT(ptrView->IsKindOf(RUNTIME_CLASS(CGDIView)));
	return ptrView;
}

void CGDIDoc::OnZoomIn() 
{
	int nRatio;

	if(m_nRatio	< 16)
	{
		nRatio=m_nRatio*2;
		GetCGDIView()->ChangeTrackerRectRatio(nRatio);
		m_nRatio=nRatio;
		UpdateAllViews(NULL);
		GetCGDIView()->UpdateScrollSizes();
	}
}

void CGDIDoc::OnZoomOut() 
{
	int nRatio;

	if(m_nRatio	> 1)
	{
		nRatio=m_nRatio/2;
		GetCGDIView()->ChangeTrackerRectRatio(nRatio);
		m_nRatio=nRatio;
		UpdateAllViews(NULL);
		GetCGDIView()->UpdateScrollSizes();
	}
}

void CGDIDoc::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nRatio < 16 && m_hDIB != NULL);	
}

void CGDIDoc::OnUpdateZoomOut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nRatio > 1 && m_hDIB != NULL);
}

void CGDIDoc::OnGrid() 
{
	m_bGridOn=m_bGridOn ? FALSE:TRUE;
	UpdateAllViews(NULL);
}

void CGDIDoc::OnUpdateGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bGridOn == TRUE);
}

void CGDIDoc::OnDrawTool(UINT nID) 
{
	m_nCurrentTool=nID-TOOL_HEAD_ID;
	if(m_nCurrentTool != TOOL_RECTSEL && m_nCurrentTool != TOOL_FREESEL)
	{
		GetCGDIView()->ResetTracker();
		UpdateAllViews(NULL);
	}
}

void CGDIDoc::OnUpdateDrawTool(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck((UINT)m_nCurrentTool+TOOL_HEAD_ID == pCmdUI->m_nID);	
}

HGLOBAL CGDIDoc::CreateCopyCutDIB()
{
	HGLOBAL hDIB;
	LPBITMAPINFO lpBi;
	LPSTR lpRowSrc;
	LPSTR lpRowTgt;
	BITMAPINFOHEADER bi;
	CRect rect;
	CRect rectSrc;
	CSize sizeTgtOffset;
	CSize sizeCopy;
	int i;
	int nPalSize;
	DWORD dwDIBSize;
	LPPALETTEENTRY lpPalEntry;

	lpBi=(LPBITMAPINFO)::GlobalLock(m_hDIB);
	ASSERT(lpBi != NULL);
	bi=lpBi->bmiHeader;
	if(bi.biBitCount != 8)
	{
		::GlobalUnlock(m_hDIB);
		return NULL;
	}
	::GlobalUnlock(m_hDIB);
	lpBi=NULL;
	rect=GetCGDIView()->GetNormalizedTrackerRect();
	dwDIBSize=
	(
		sizeof(BITMAPINFOHEADER)+
		GetColorTableSize(bi.biBitCount)*sizeof(RGBQUAD)+
		WIDTHBYTES(rect.Width()*bi.biBitCount)*rect.Height()
	);
	hDIB=::GlobalAlloc(GHND | GMEM_SHARE, dwDIBSize);
	ASSERT(hDIB != NULL);
	lpBi=(LPBITMAPINFO)::GlobalLock(hDIB);
	ASSERT(lpBi != NULL);
	lpBi->bmiHeader=bi;
	lpBi->bmiHeader.biWidth=rect.Width();
	lpBi->bmiHeader.biHeight=rect.Height();
	lpBi->bmiHeader.biSizeImage=WIDTHBYTES
	(
		bi.biBitCount*rect.Width()
	)*rect.Height();
	nPalSize=GetColorTableSize(lpBi->bmiHeader.biBitCount);
	lpPalEntry=(LPPALETTEENTRY)new BYTE[nPalSize*sizeof(PALETTEENTRY)];
	m_palDraw.GetPaletteEntries(0, nPalSize, lpPalEntry);
	for(i=0; i<nPalSize; i++)
	{
		lpBi->bmiColors[i].rgbRed=lpPalEntry[i].peRed;
		lpBi->bmiColors[i].rgbGreen=lpPalEntry[i].peGreen;
		lpBi->bmiColors[i].rgbBlue=lpPalEntry[i].peBlue;
		lpBi->bmiColors[i].rgbReserved=NULL;
	}
	delete []lpPalEntry;

	rectSrc=rect;
	sizeTgtOffset.cx=0;
	sizeTgtOffset.cy=0;
	if(rect.left < 0)
	{
		rectSrc.left=0;
		sizeTgtOffset.cx=-rect.left;
	}
	if(rect.top < 0)
	{
		rectSrc.top=0;
		sizeTgtOffset.cy=-rect.top;
	}
	if(rect.right >= bi.biWidth)
	{
		rectSrc.right=bi.biWidth-1;
	}
	if(rect.bottom >= bi.biHeight)
	{
		rectSrc.bottom=bi.biHeight-1;
	}
	for(i=0; i<rectSrc.Height(); i++)
	{
		lpRowSrc=
		(
			(LPSTR)m_lpBits+
			WIDTHBYTES
			(
				bi.biBitCount*bi.biWidth
			)*(bi.biHeight-rectSrc.top-i-1)+
			rectSrc.left
		);
		lpRowTgt=
		(
			(LPSTR)lpBi+
			sizeof(BITMAPINFOHEADER)+
			sizeof(RGBQUAD)*nPalSize+
			WIDTHBYTES
			(
				lpBi->bmiHeader.biBitCount*lpBi->bmiHeader.biWidth
			)*(lpBi->bmiHeader.biHeight-sizeTgtOffset.cy-i-1)
		);
		memcpy
		(
			lpRowTgt,
			lpRowSrc,
			WIDTHBYTES(lpBi->bmiHeader.biBitCount*rectSrc.Width())
		);
	}
	::GlobalUnlock(hDIB);
	return hDIB;
}

void CGDIDoc::OnEditCopy() 
{
	if(GetCGDIView()->OpenClipboard() == TRUE)
	{
		HGLOBAL hDIB;

		::EmptyClipboard();
		hDIB=CreateCopyCutDIB();
		ASSERT(hDIB != NULL);
		::SetClipboardData(CF_DIB, hDIB);
		::CloseClipboard();
	}
}

void CGDIDoc::OnEditCut() 
{
	if(GetCGDIView()->OpenClipboard() == TRUE)
	{
		HGLOBAL hDIB;

		::EmptyClipboard();
		hDIB=CreateCopyCutDIB();
		ASSERT(hDIB != NULL);
		::SetClipboardData(CF_DIB, hDIB);
		::CloseClipboard();
		GetCGDIView()->FillSelectionWithBgdColor();
		UpdateAllViews(NULL);
	}
}

void CGDIDoc::OnEditPaste() 
{
	if(GetCGDIView()->OpenClipboard() == TRUE)
	{
		HGLOBAL hDIB;
		LPBYTE lpByte;
		HGLOBAL hDIBPaste;
		LPBYTE lpBytePaste;

		ASSERT(hDIB != NULL);
		hDIB=::GetClipboardData(CF_DIB);
		ASSERT(hDIB);
		hDIBPaste=::GlobalAlloc(GHND, ::GlobalSize(hDIB));
		ASSERT(hDIBPaste);
		lpByte=(LPBYTE)::GlobalLock(hDIB);
		ASSERT(lpByte);
		lpBytePaste=(LPBYTE)::GlobalLock(hDIBPaste);
		ASSERT(lpBytePaste);
		memcpy(lpBytePaste, lpByte, ::GlobalSize(hDIB));
		::GlobalUnlock(hDIB);
		::GlobalUnlock(hDIBPaste);
		::CloseClipboard();
		GetCGDIView()->PasteDIB(hDIB);
		::GlobalFree(hDIBPaste);
	}
}

void CGDIDoc::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetCGDIView()->IsTrackerValid());
}

void CGDIDoc::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetCGDIView()->IsTrackerValid());
}

void CGDIDoc::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_DIB) && m_hDIB != NULL);
}
