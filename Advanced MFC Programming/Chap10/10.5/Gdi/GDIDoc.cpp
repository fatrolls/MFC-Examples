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