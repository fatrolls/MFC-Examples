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
	ON_COMMAND(ID_CONVERT_256TORGB, OnConvert256toRGB)
	ON_UPDATE_COMMAND_UI(ID_CONVERT_256TORGB, OnUpdateConvert256toRGB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	m_hDIB=NULL;
	m_nBmpFormat=BMP_FORMAT_NONE;
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
	pCmdUI->Enable(m_hDIB != NULL);
}

DWORD CGDIDoc::GetColorTableSize(WORD wBitCount)
{
	DWORD dwSizeCT;

	switch(wBitCount)
	{                
		case 1:
		{
			dwSizeCT=2;
			m_nBmpFormat=BMP_FORMAT_MONO;
			break;
		}
		case 4:
		{
			dwSizeCT=16;
			m_nBmpFormat=BMP_FORMAT_16COLOR;
			break;
		}
		case 8:
		{
			dwSizeCT=256;
			m_nBmpFormat=BMP_FORMAT_256COLOR;
			break;
		}
		case 24:
		{
			dwSizeCT=0;
			m_nBmpFormat=BMP_FORMAT_24BIT;
		}
	}
	return dwSizeCT;
}

void CGDIDoc::OnConvert256toRGB() 
{
	LPBITMAPINFO lpBi;
	LPBITMAPINFO lpBi24;
	HGLOBAL hDIB24;
	DWORD dwSize;
	int nSizeCT;
	int i, j;
	LPSTR lpRowSrc;
	LPSTR lpRowTgt;
	BYTE byIndex;
	RGBQUAD rgbQuad;
	POSITION pos;
	CGDIView *ptrView;

	lpBi=(LPBITMAPINFO)::GlobalLock(m_hDIB);
	ASSERT(lpBi);
	nSizeCT=GetColorTableSize(lpBi->bmiHeader.biBitCount);
	dwSize=
	(
		sizeof(BITMAPINFOHEADER)+
		WIDTHBYTES(24*lpBi->bmiHeader.biWidth)*lpBi->bmiHeader.biHeight
	);
	hDIB24=::GlobalAlloc(GHND, dwSize);
	ASSERT(hDIB24);
	lpBi24=(LPBITMAPINFO)::GlobalLock(hDIB24);
	*lpBi24=*lpBi;
	lpBi24->bmiHeader.biBitCount=24;
	lpBi24->bmiHeader.biSizeImage=WIDTHBYTES
	(
		24*lpBi->bmiHeader.biWidth
	)*lpBi->bmiHeader.biHeight;
	lpBi24->bmiHeader.biClrUsed=0;
	for(j=0; j<lpBi->bmiHeader.biHeight; j++)
	{
		lpRowSrc=
		(
			(LPSTR)lpBi+
			sizeof(BITMAPINFOHEADER)+
			nSizeCT*sizeof(RGBQUAD)+
			WIDTHBYTES(lpBi->bmiHeader.biBitCount*lpBi->bmiHeader.biWidth)*j
		);
		lpRowTgt=
		(
			(LPSTR)lpBi24+
			sizeof(BITMAPINFOHEADER)+
			WIDTHBYTES(lpBi24->bmiHeader.biBitCount*lpBi24->bmiHeader.biWidth)*j
		);
		for(i=0; i<lpBi->bmiHeader.biWidth; i++)
		{
			byIndex=*lpRowSrc;
			rgbQuad=lpBi->bmiColors[byIndex];
			*lpRowTgt=rgbQuad.rgbBlue;
			*(lpRowTgt+1)=rgbQuad.rgbGreen;
			*(lpRowTgt+2)=rgbQuad.rgbRed;
			lpRowSrc++;
			lpRowTgt+=3;
		}
	}
	::GlobalUnlock(m_hDIB);
	::GlobalFree(m_hDIB);
	::GlobalUnlock(hDIB24);
	m_hDIB=hDIB24;
	m_nBmpFormat=BMP_FORMAT_24BIT;

	pos=GetFirstViewPosition();
	ptrView=(CGDIView *)GetNextView(pos);
	ASSERT(ptrView->IsKindOf(RUNTIME_CLASS(CGDIView)));
	ptrView->LoadBitmap(m_hDIB);
}

void CGDIDoc::OnUpdateConvert256toRGB(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nBmpFormat == BMP_FORMAT_256COLOR);
}
