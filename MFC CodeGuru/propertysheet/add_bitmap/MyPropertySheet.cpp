// MyPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "JVF Access.h"
#include "MyPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMyPropertySheet)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPropertySheet message handlers

void CMyPropertySheet::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBitmap bmp, *poldbmp;
	CDC memdc;
	CRect rect;
	
	//Load the bitmap resource 
	bmp.LoadBitmap(IDB_TIMENET95); 

	//Create a compatible memory DC
	memdc.CreateCompatibleDC(&dc);

	//Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmp);//bmp

	//Copy (BitBlt) bitmap from memory DC to screen DC
	GetClientRect(&rect);
	dc.BitBlt(10, rect.bottom - 22, 88, 16, &memdc, 0, 0, SRCCOPY);

	memdc.SelectObject(poldbmp);
	
	// Do not call CPropertySheet::OnPaint() for painting messages
}
