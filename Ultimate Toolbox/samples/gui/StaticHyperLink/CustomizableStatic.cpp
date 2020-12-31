// CustomizableStatic.cpp : implementation file
//

#include "stdafx.h"
#include "StaticHyperLink.h"
#include "CustomizeStaticDlg.h"
#include "CustomizableStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizableStatic

CCustomizableStatic::CCustomizableStatic()
{
}

CCustomizableStatic::~CCustomizableStatic()
{
}


BEGIN_MESSAGE_MAP(CCustomizableStatic, COXStatic)
	//{{AFX_MSG_MAP(CCustomizableStatic)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizableStatic message handlers

void CCustomizableStatic::OnRButtonDown(UINT nFlags, CPoint point) 
{
	COXStatic::OnRButtonDown(nFlags, point);

	// TODO: Add your message handler code here and/or call default
	CCustomizeStaticDlg customizeDlg;
	customizeDlg.m_pStatic=this;
	if(customizeDlg.DoModal()==IDOK)
	{
		AdjustToFitText();
		FormatToolTipText();
	}
}
