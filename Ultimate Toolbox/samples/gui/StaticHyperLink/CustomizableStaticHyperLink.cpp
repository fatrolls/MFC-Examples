// CustomizableStaticHyperLink.cpp : implementation file
//

#include "stdafx.h"
#include "StaticHyperLink.h"
#include "CustomizeSHLDlg.h"
#include "CustomizableStaticHyperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizableStaticHyperLink

CCustomizableStaticHyperLink::CCustomizableStaticHyperLink()
{
}

CCustomizableStaticHyperLink::~CCustomizableStaticHyperLink()
{
}


BEGIN_MESSAGE_MAP(CCustomizableStaticHyperLink, COXStaticHyperLink)
	//{{AFX_MSG_MAP(CCustomizableStaticHyperLink)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizableStaticHyperLink message handlers

void CCustomizableStaticHyperLink::OnRButtonDown(UINT nFlags, CPoint point) 
{
	COXStaticHyperLink::OnRButtonDown(nFlags, point);

	// TODO: Add your message handler code here and/or call default
	CCustomizeSHLDlg customizeDlg;
	customizeDlg.m_pStaticHyperLink=this;
	if(customizeDlg.DoModal()==IDOK)
	{
		AdjustToFitText();
		FormatToolTipText();
	}
}
