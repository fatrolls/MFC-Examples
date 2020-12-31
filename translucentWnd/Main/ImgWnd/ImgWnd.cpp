#include "stdafx.h"
#include "ImgWnd.h"
#include "TranslucentDialog.h"
#include "resource.h"



CImgWnd::CImgWnd(const wchar_t* wszFile, UINT nID, CWnd* pParentWnd/*=NULL*/)
: CDialog(nID, (m_pTranslucentWnd = new CTranslucentDialog(nID, wszFile, this, pParentWnd)))
{
	m_ColorKey = RGB(0,255,0);
	m_Brush.CreateSolidBrush(m_ColorKey);
}

CImgWnd::~CImgWnd()
{
	if (m_pTranslucentWnd != NULL)
	{
		delete m_pTranslucentWnd;
		m_pTranslucentWnd = NULL;
	}
}

INT_PTR CImgWnd::DoModal()
{
	return m_pTranslucentWnd->DoModal();
}


BEGIN_MESSAGE_MAP(CImgWnd, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


void CImgWnd::OnOK()
{
	CWnd* hParent = GetParent();
	if (hParent != NULL)
	{
		HWND hWnd = hParent->m_hWnd; 
		::SendMessage(hWnd, WM_CLOSE, 0, 0); 
	}

	CDialog::OnOK();
}

void CImgWnd::OnCancel()
{
	CWnd* hParent = GetParent();
	if (hParent != NULL)
	{
		HWND hWnd = hParent->m_hWnd; 
		::SendMessage(hWnd, WM_CLOSE, 0, 0); 
	}

	CDialog::OnCancel();
}

BOOL CImgWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置为层级窗口
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	VERIFY(dwStyle & WS_POPUP);
	VERIFY((dwStyle & WS_BORDER) == 0);
	VERIFY((dwStyle & WS_SIZEBOX) == 0);
	VERIFY((dwStyle & WS_DLGFRAME) == 0);

	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	VERIFY((dwExStyle & WS_EX_APPWINDOW) == 0);

	::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle|WS_EX_LAYERED);
	::SetLayeredWindowAttributes(GetSafeHwnd(), m_ColorKey, 0, 1);

	return TRUE;
}

HBRUSH CImgWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor == CTLCOLOR_DLG)
		return m_Brush;

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CImgWnd::DoCreate()
{
	Create(m_lpszTemplateName, m_pParentWnd);
	ShowWindow(SW_SHOW);
}