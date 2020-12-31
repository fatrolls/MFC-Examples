// OXMetafileViewer.cpp : implementation file
//

#include "stdafx.h"
#include "OXMetafileViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(COXMetafileViewer, COXScrollWnd)


/////////////////////////////////////////////////////////////////////////////
// COXMetafileViewer

COXMetafileViewer::COXMetafileViewer()
{
	SetSmoothScrolling(TRUE);
}

COXMetafileViewer::~COXMetafileViewer()
{
	m_MetaFile.CloseFile();
}


BEGIN_MESSAGE_MAP(COXMetafileViewer, COXScrollWnd)
	//{{AFX_MSG_MAP(COXMetafileViewer)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COXMetafileViewer message handlers



void COXMetafileViewer::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	OnPrepareDC(&dc);

	// get the size of image
	CRect rect;
	GetClientRect(rect);
	CSize sizeMetafileSize=GetMetafileSize();
	rect.right=rect.left+sizeMetafileSize.cx;
	rect.bottom=rect.top+sizeMetafileSize.cy;
	CRect rectPaint=rect;
	// transform coordinates of boundary rectangle
	// taking into account current zoom level
	NormalToScaled(&rectPaint);

	///
	DrawMetafile(&dc,rectPaint);

	// Do not call COXScrollWnd::OnPaint() for painting messages
}

BOOL COXMetafileViewer::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	ASSERT_VALID(pDC);

	CRect rect;
	GetClientRect(rect);
	CBrush brush(::GetSysColor(COLOR_WINDOW));
	pDC->FillRect(rect,&brush);

	return TRUE;
}

BOOL COXMetafileViewer::LoadFile(LPCTSTR lpszPathName) 
{
	if(m_MetaFile.LoadFile(lpszPathName)!=NULL)
		return InitializeImage();
	else
		return FALSE;
}


BOOL COXMetafileViewer::LoadResource(UINT nIDResource, 
									 CString strResType/*=_T("METAFILE")*/) 
{
	if(m_MetaFile.LoadFile(nIDResource,strResType)!=NULL)
		return InitializeImage();
	else
		return FALSE;
}

BOOL COXMetafileViewer::InitializeImage(const CSize& sizePage/*=CSize(10,10)*/,
										const CSize& sizeLine/*=CSize(1,1)*/)
{
	CSize sizeMetafileSize=GetMetafileSize();
	SetScrollSizes(MM_TEXT,sizeMetafileSize,sizePage,sizeLine);
	SetZoomAlign(ZA_CENTER);

	if(IsAlwaysFitWindow())
		ZoomToWindow();
	else
		RedrawWindow();
	
	return TRUE;
}


BOOL COXMetafileViewer::DrawMetafile(CDC* pDC, const CRect& rectDest)
{
	// set neccessary map mode
	int oldMapMode;
	oldMapMode=pDC->SetMapMode(MM_TEXT);

	CRect rect=rectDest;
	BOOL bSuccess=m_MetaFile.PlayFile(pDC,&rect);

	pDC->SetMapMode(oldMapMode);

	return bSuccess;
}

CSize COXMetafileViewer::GetMetafileSize()
{
	return m_MetaFile.GetSize();
}


