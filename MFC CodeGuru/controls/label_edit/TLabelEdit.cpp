// TLabelEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TLabelEdit.h"
#include "TLabelList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define wndClassName _T("TLabelEdit")

/////////////////////////////////////////////////////////////////////////////
// CTLabelEdit

LRESULT CALLBACK WindowProcEdit(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KILLFOCUS:
			CTLabelEdit::HideEdit();
		return NULL;
	}
	return  CallWindowProc(CTLabelEdit::m_wndEditDefaultWndProc, hwnd,uMsg,wParam,lParam);
}

WNDPROC CTLabelEdit::m_wndEditDefaultWndProc = NULL;
CWnd* CTLabelEdit::m_pWndEdit = NULL;

CTLabelEdit::CTLabelEdit(LPCTSTR pDefaultText):m_sDefaultString(pDefaultText)
{
}

CTLabelEdit::~CTLabelEdit()
{
	if (m_pWndEdit && IsEditDestroyable()) delete m_pWndEdit;
	m_pWndEdit = NULL;
}

BEGIN_MESSAGE_MAP(CTLabelEdit, CWnd)
	//{{AFX_MSG_MAP(CTLabelEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTLabelEdit message handlers

BOOL CTLabelEdit::RegClassLabelEdit()
{
	WNDCLASS wndClass;
		wndClass.style = CS_DBLCLKS;
		wndClass.lpfnWndProc = ::DefWindowProc;
		wndClass.cbClsExtra = NULL;
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = AfxGetInstanceHandle();
		wndClass.hIcon = NULL;
		wndClass.hCursor = NULL;
		wndClass.hbrBackground = NULL;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = wndClassName;
	return AfxRegisterClass(&wndClass);
}

void CTLabelEdit::PreSubclassWindow() 
{
	ASSERT (GetParent() != NULL);
	CWnd::PreSubclassWindow();
	CRect rect; GetClientRect(rect);
	if (m_wndStatic.Create(_T(""), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_LEFT , rect, this))
		m_wndStatic.SetFont(GetParent()->GetFont());
	CString sCaption;
	GetWindowText(sCaption);
	SetText(sCaption);
}

void CTLabelEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();

	CWnd::OnLButtonDown(nFlags, point);
}

void CTLabelEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);

	ShowEdit();

}

void CTLabelEdit::SetText(LPCSTR lpszCaption)
{
	CString sCaption(lpszCaption);
	m_wndStatic.SetWindowText(sCaption.IsEmpty() ? (LPCTSTR)m_sDefaultString : lpszCaption);
}

CString CTLabelEdit::GetText()
{
	CString sCaption;
	m_wndStatic.GetWindowText(sCaption);
	sCaption = sCaption == m_sDefaultString ? _T("") : sCaption;
	return sCaption;
}

HBRUSH CTLabelEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHT));
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CTLabelEdit::IsEditDestroyable()
{
	return TRUE;
}

void CTLabelEdit::ShowEdit()
{
	CRect rect; GetClientRect(rect);
	if (m_pWndEdit) HideEdit();
	m_pWndEdit = new CEdit();
	((CEdit*)m_pWndEdit)->Create(WS_CHILD | ES_NOHIDESEL | ES_LEFT | ES_AUTOHSCROLL , rect, this, 0);
	ASSERT (m_pWndEdit && ::IsWindow(m_pWndEdit->m_hWnd));
	m_pWndEdit->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_pWndEdit->SetFont(GetParent()->GetFont());
	CString sCaption;
	m_wndStatic.GetWindowText(sCaption);
	m_pWndEdit->SetWindowText(sCaption);
	m_pWndEdit->ShowWindow(SW_SHOW);
	m_wndStatic.ShowWindow(SW_HIDE);
	((CEdit*)m_pWndEdit)->SetSel(MAKELONG(0,-1));
	m_wndEditDefaultWndProc = (WNDPROC)SetWindowLong(m_pWndEdit->m_hWnd, GWL_WNDPROC, (long)WindowProcEdit);
	CWnd* pWnd = (CWnd*)m_pWndEdit;
	SetWindowLong(pWnd->m_hWnd, GWL_USERDATA, (long)this);
	pWnd->SetWindowPos(0,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	pWnd->SetFocus();
}

void CTLabelEdit::HideEdit()
{
	if (m_pWndEdit && m_wndEditDefaultWndProc)
	{
		CTLabelEdit* pLabelEdit = ((CTLabelEdit*)GetWindowLong(m_pWndEdit->m_hWnd, GWL_USERDATA));
		(WNDPROC)SetWindowLong(m_pWndEdit->m_hWnd, GWL_WNDPROC, (long)m_wndEditDefaultWndProc);
		m_wndEditDefaultWndProc = NULL;
		CString sCaption;
		m_pWndEdit->GetWindowText(sCaption);
		pLabelEdit->SetText(sCaption);
		if (pLabelEdit->IsEditDestroyable())
			delete m_pWndEdit;
		else
		{
			CTLabelList* pList = (CTLabelList*)pLabelEdit;
			pList->ShowWindow(SW_SHOW);
			pList->GetWindowControl()->ShowWindow(SW_HIDE);
		}
		m_pWndEdit = NULL;
		CWnd* pWnd = (CWnd*)&pLabelEdit->m_wndStatic;
		pWnd->ShowWindow(SW_SHOW);
		pWnd->SetWindowPos(0,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}
}


void CTLabelList::ShowEdit()
{
	CRect rect; GetClientRect(rect);
	CWnd* pWnd = GetWindowControl();
	if (m_pWndEdit)
		HideEdit();
	pWnd->ShowWindow(SW_SHOW);
	m_wndStatic.ShowWindow(SW_HIDE);
	// For draw
	pWnd->SetWindowPos(&CWnd::wndBottom,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
	pWnd->SetFocus();
	m_pWndEdit = GetEditControl();
	ASSERT (m_pWndEdit != NULL);
	SetWindowLong(m_pWndEdit->m_hWnd, GWL_USERDATA, (long)this);
	m_wndEditDefaultWndProc = (WNDPROC)SetWindowLong(m_pWndEdit->m_hWnd, GWL_WNDPROC, (long)WindowProcEdit);
	ShowWindow(SW_HIDE); // for relay LButtonDown to this control...see wndBottom
}
