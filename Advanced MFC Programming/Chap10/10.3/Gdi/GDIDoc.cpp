#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
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

