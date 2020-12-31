// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\PukamSoft\PukamSoft.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

void CEditDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	m_Edit.MoveWindowEng(CRect(0,0,cx,cy+2),TRUE);
}

BOOL CEditDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_USER && LOWORD(pMsg->wParam) == MSG_KEYDOWN && pMsg->lParam == VK_RETURN)
	{
		ReleaseCapture();
		m_csEditText = m_Edit.GetControlText();
		m_csEditText = UnFormatNumberString(m_csEditText);
		GetParent()->PostMessage(WM_USER,MSG_EDITUPDATE,(LPARAM)&m_csEditText);
		return 1;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

int CEditDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Edit.CreateSkinControl("",CRect(0,0,0,0),this,ID_EDIT,BORDER_STYLE_3D|TEXT_ALIGN_RIGHT);
	SetEditControlProperties(m_Edit);
	
	return 0;
}

void CEditDlg::SetEditControlProperties(CSkinnedEdit& SkinnedEditControl)
{
	SkinnedEditControl.SetBackgroundColor(-1,RGB(255,255,255));
	SkinnedEditControl.SetForegroundColor(RGB(0,0,0));
}

void CEditDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	dc.FillSolidRect(&rcClient,RGB(255,255,255));
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CEditDlg::SetEditControlType(UINT nType)
{
	m_Edit.SetControlType(nType);
}

void CEditDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		m_Edit.SetFocus();
		SetCapture();
	}
}

void CEditDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (nFlags == MK_LBUTTON)
	{
		CRect rcClientRect;
		GetClientRect(&rcClientRect);

		if(!rcClientRect.PtInRect(point))
		{
			ReleaseCapture();
			GetParent()->PostMessage(WM_USER,MSG_HIDEEDIT,0L);
			return;
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}
