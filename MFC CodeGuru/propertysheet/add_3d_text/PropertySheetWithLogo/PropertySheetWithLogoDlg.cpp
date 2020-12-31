// PropertySheetWithLogoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropertySheetWithLogoDlg.h"
#include "propertysheetwithlogo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetWithLogoDlg

IMPLEMENT_DYNAMIC(CPropertySheetWithLogoDlg, CPropertySheet)

CPropertySheetWithLogoDlg::CPropertySheetWithLogoDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPropertySheetWithLogoDlg::CPropertySheetWithLogoDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPropertySheetWithLogoDlg::~CPropertySheetWithLogoDlg()
{
}


BEGIN_MESSAGE_MAP(CPropertySheetWithLogoDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CPropertySheetWithLogoDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
void CPropertySheetWithLogoDlg::SetLogoText(CString Text)
{
	m_LogoText = Text;
}

void CPropertySheetWithLogoDlg::SetLogoFont(CString Name, int nHeight/* = 24*/,
	int nWeight/* = FW_BOLD*/, BYTE bItalic/* = true*/, BYTE bUnderline/* = false*/)
{
	if(m_fontLogo.m_hObject)
		m_fontLogo.Detach();

	m_fontLogo.CreateFont(nHeight, 0, 0, 0, nWeight, bItalic, bUnderline,0,0,0,0,0,0, Name);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetWithLogoDlg message handlers

void CPropertySheetWithLogoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_LogoText.IsEmpty())
		return;

	CRect rectTabCtrl;
	GetTabControl()->GetWindowRect(rectTabCtrl);
	ScreenToClient(rectTabCtrl);

	CRect rectOk;
	GetDlgItem(IDOK)->GetWindowRect(rectOk);
	ScreenToClient(rectOk);

	dc.SetBkMode(TRANSPARENT);

	CRect rectText;
	rectText.left = rectTabCtrl.left;
	rectText.top = rectOk.top;
	rectText.bottom = rectOk.bottom;
	rectText.right = rectOk.left;

	CFont * OldFont = dc.SelectObject(&m_fontLogo);

	// draw text in DC
	COLORREF OldColor = dc.SetTextColor( ::GetSysColor( COLOR_3DHILIGHT));

	dc.DrawText( m_LogoText, rectText + CPoint(1,1), DT_SINGLELINE | DT_LEFT | DT_VCENTER);
	dc.SetTextColor( ::GetSysColor( COLOR_3DSHADOW));
	dc.DrawText( m_LogoText, rectText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

	// restore old text color
	dc.SetTextColor( OldColor);
	// restore old font
	dc.SelectObject(OldFont);
	
	// Do not call CPropertySheet::OnPaint() for painting messages
}

BOOL CPropertySheetWithLogoDlg::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	SetLogoFont("Arial");
	
	return bResult;
}
