// GMessageBox.cpp : implementation file
//

#include "stdafx.h"
#include "GMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GMessageBox dialog

GMessageBox* GMessageBox::m_gBox = NULL;

GMessageBox::GMessageBox(CWnd* pParent, CString strText, CString strCaption, UINT uType, COLORREF clr)
{
	//{{AFX_DATA_INIT(GMessageBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	m_strText = strText;
	m_strCaption = strCaption;
	m_uType = uType;
	m_gBox = NULL;
	if (clr == COLOR_WINDOW)
		m_clrFace = GetSysColor(clr);
	else
		m_clrFace = clr;
}

GMessageBox::~GMessageBox()
{
	if (m_btnOK.GetSafeHwnd())
		m_btnOK.UnsubclassWindow();
	if (m_btnCancel.GetSafeHwnd())
		m_btnCancel.UnsubclassWindow();
	if (m_btnAbort.GetSafeHwnd())
		m_btnAbort.UnsubclassWindow();
	if (m_btnRetry.GetSafeHwnd())
		m_btnRetry.UnsubclassWindow();
	if (m_btnIgnore.GetSafeHwnd())
		m_btnIgnore.UnsubclassWindow();
	if (m_btnYes.GetSafeHwnd())
		m_btnYes.UnsubclassWindow();
	if (m_btnNo.GetSafeHwnd())
		m_btnNo.UnsubclassWindow();
	if (m_btnClose.GetSafeHwnd())
		m_btnClose.UnsubclassWindow();
	if (m_btnClose.GetSafeHwnd())
			m_btnClose.UnsubclassWindow();
    if (GetSafeHwnd())
		UnsubclassWindow();
}

void GMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GMessageBox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GMessageBox, CBCGPDialog)
	//{{AFX_MSG_MAP(GMessageBox)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GMessageBox message handlers
COLORREF GMessageBox::GetFaceColor()
{
	return m_clrFace;
}

UINT GMessageBox::DoGModal()
{
	m_gBox = this;
    HHOOK hHook = SetWindowsHookEx(WH_CALLWNDPROCRET, (HOOKPROC)MessageBoxCallbackProc, NULL, ::GetCurrentThreadId());
	UINT nRet = ::MessageBox(m_pParent == NULL? NULL : m_pParent->m_hWnd, m_strText, m_strCaption, m_uType);
	UnhookWindowsHookEx(hHook);
	m_gBox = NULL;
	return nRet;
}


void GMessageBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (GetSafeHwnd() != NULL && m_btnOK.GetSafeHwnd() == NULL && GetDlgItem(IDOK) != NULL)
	{
		m_btnOK.SubclassWindow(GetDlgItem(IDOK)->m_hWnd);
		m_btnOK.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnOK.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnCancel.GetSafeHwnd() == NULL && GetDlgItem(IDCANCEL) != NULL)
	{
		m_btnCancel.SubclassWindow(GetDlgItem(IDCANCEL)->m_hWnd);
		m_btnCancel.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnCancel.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnYes.GetSafeHwnd() == NULL && GetDlgItem(IDYES) != NULL)
	{
		m_btnYes.SubclassWindow(GetDlgItem(IDYES)->m_hWnd);
		m_btnYes.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnYes.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnNo.GetSafeHwnd() == NULL && GetDlgItem(IDNO) != NULL)
	{
		m_btnNo.SubclassWindow(GetDlgItem(IDNO)->m_hWnd);
		m_btnNo.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnNo.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnClose.GetSafeHwnd() == NULL && GetDlgItem(IDCLOSE) != NULL)
	{
		m_btnClose.SubclassWindow(GetDlgItem(IDCLOSE)->m_hWnd);
		m_btnClose.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnClose.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnHelp.GetSafeHwnd() == NULL && GetDlgItem(IDHELP) != NULL)
	{
		m_btnHelp.SubclassWindow(GetDlgItem(IDHELP)->m_hWnd);
		m_btnHelp.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnHelp.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnAbort.GetSafeHwnd() == NULL && GetDlgItem(IDABORT) != NULL)
	{
		m_btnAbort.SubclassWindow(GetDlgItem(IDABORT)->m_hWnd);
		m_btnAbort.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnAbort.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnRetry.GetSafeHwnd() == NULL && GetDlgItem(IDRETRY) != NULL)
	{
		m_btnRetry.SubclassWindow(GetDlgItem(IDRETRY)->m_hWnd);
		m_btnRetry.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnRetry.SetFaceColor(m_clrFace);
	}
	if (GetSafeHwnd() != NULL && m_btnIgnore.GetSafeHwnd() == NULL && GetDlgItem(IDIGNORE) != NULL)
	{
		m_btnIgnore.SubclassWindow(GetDlgItem(IDIGNORE)->m_hWnd);
		m_btnIgnore.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_FLAT;
		if (m_clrFace != GetSysColor(COLOR_WINDOW))
			m_btnIgnore.SetFaceColor(m_clrFace);
	}
}

LRESULT CALLBACK MessageBoxCallbackProc(int code, WPARAM wParam, LPARAM lparam)
{
	CWPRETSTRUCT*pS = (CWPRETSTRUCT*)lparam;
	GMessageBox::m_gBox->m_hwnd = pS->hwnd;
	if (pS->message == WM_INITDIALOG)
	{
		CWnd* pWnd = CWnd::FromHandle(GMessageBox::m_gBox->m_hwnd);
		if (GMessageBox::m_gBox->GetSafeHwnd() == NULL)
		{
			GMessageBox::m_gBox->SubclassWindow(GMessageBox::m_gBox->m_hwnd);
			if (GMessageBox::m_gBox->GetFaceColor() != GetSysColor(COLOR_WINDOW))
				GMessageBox::m_gBox->SetBackgroundColor(GMessageBox::m_gBox->GetFaceColor());
		}
	}
	return 0;
}

UINT AfxGMessageBox(CWnd* pParent, CString strText, CString strCaption, UINT uType, COLORREF clrFace)
{
    GMessageBox box(pParent, strText, strCaption, uType, clrFace);
	return box.DoGModal();
}