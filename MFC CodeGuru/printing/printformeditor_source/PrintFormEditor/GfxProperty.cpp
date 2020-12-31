// GfxProperty.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "GfxProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGfxProperty dialog

static HHOOK hk_hHookProc = NULL;
static CGfxProperty * pOneAndOnlyProperty = NULL;
bool   bLockingProperty = false;

LRESULT CALLBACK KillFocusHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (pOneAndOnlyProperty)
	{
		CWPRETSTRUCT * pRet = (CWPRETSTRUCT *) lParam;

/*		if (pRet->message == WM_KEYDOWN)
		{
			if ((int) pRet->wParam == VK_RETURN) pOneAndOnlyProperty->DoIt();
		}
		else if (pRet->message == WM_KEYUP)
		{
			if ((int) pRet->wParam == VK_RETURN) pOneAndOnlyProperty->DoIt();
		}
		else if (pRet->message == WM_CHAR)
		{
			if ((int) pRet->wParam == VK_RETURN) pOneAndOnlyProperty->DoIt();
		}
		else */
		if (!bLockingProperty && pRet->message == WM_SETFOCUS)
		{
			HWND pFocusing = (HWND) pRet->wParam;
			if (pFocusing == pOneAndOnlyProperty->GetSafeHwnd() || ::IsChild(pOneAndOnlyProperty->GetSafeHwnd(), pFocusing))
			{
				if (!(pRet->hwnd == pOneAndOnlyProperty->GetSafeHwnd() || ::IsChild(pOneAndOnlyProperty->GetSafeHwnd(), pRet->hwnd)))
				{
					if (pOneAndOnlyProperty->wndPin.bCheckStatus == false)
					{
						pOneAndOnlyProperty->DestroyWindow();
						ASSERT(pOneAndOnlyProperty == NULL);
					}
				}
			}
		}
	}

	return CallNextHookEx(hk_hHookProc, nCode, wParam, lParam);
}

void CGfxProperty::InstallHook(BOOL bInstall)
{
	if(bInstall && hk_hHookProc == NULL)
	{
		hk_hHookProc = ::SetWindowsHookEx(WH_CALLWNDPROCRET, (HOOKPROC) KillFocusHookProc, NULL, ::GetCurrentThreadId()); 
	}
	else if(!bInstall && hk_hHookProc != NULL)
	{
		::UnhookWindowsHookEx(hk_hHookProc);
		hk_hHookProc = NULL;
	}
}



CGfxProperty::CGfxProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CGfxProperty::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGfxProperty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	COLORREF cr = RGB(192,192,192);

	wndPin.SetBitmap(IDB_PROPPIN1, &cr);
	wndPin.SetBitmap(IDB_PROPPIN2, &cr, true);
	wndPin.SetBitmapCheckPress(IDB_PROPPIN3, &cr);

	wndPin.EnableCheckMode();
	wndHelp.SetBitmap(IDB_PROPHELP, &cr);

	iActSel = -1;

	pTabRect = NULL;

	pDocument = NULL;
	pWnd = NULL;
}

CGfxProperty::~CGfxProperty()
{
	ASSERT(hk_hHookProc == NULL);
	ASSERT(pOneAndOnlyProperty == NULL);
	if (hk_hHookProc) InstallHook(false);
	pOneAndOnlyProperty = NULL;

	if (pTabRect) GlobalFree((HGLOBAL) pTabRect);
	pTabRect = NULL;
	csTabArray.RemoveAll();
	pPages.RemoveAll();
}

void CGfxProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGfxProperty)
	DDX_Control(pDX, IDOK, wndOk);
	DDX_Control(pDX, IDC_BT_PIN, wndPin);
	DDX_Control(pDX, IDC_BT_HELP, wndHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGfxProperty, CDialog)
	//{{AFX_MSG_MAP(CGfxProperty)
	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(IDC_BT_HELP, OnBtHelp)
	ON_BN_CLICKED(IDC_BT_PIN, OnBtPin)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGfxProperty message handlers

void CGfxProperty::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CGfxProperty::OnOK() 
{
	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * d = (CDialog *) pPages.GetAt(t);
		d->UpdateData();
	}

	if (pOneAndOnlyProperty->wndPin.bCheckStatus == false)
		CDialog::OnOK();
}

void CGfxProperty::DoIt()
{
	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * d = (CDialog *) pPages.GetAt(t);
		d->UpdateData();
	}

//	OnOK();
}

BOOL CGfxProperty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(pOneAndOnlyProperty == NULL);
	pOneAndOnlyProperty = this;
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGfxProperty::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);

}

void CGfxProperty::InvalidateTab(const int idx)
{
	if (idx >= 0 && idx < csTabArray.GetSize())
	{
		InvalidateRect(pTabRect[idx], false);
	}
}

void CGfxProperty::OnBtHelp() 
{
//	CString path = csAppDir;
	CString path("WAtsProp.hlp");

	DWORD base = 10;
	int nline = 8;
	nline = 2;
	base = 60;
	CString toWin = path;
	toWin += ">subtopic";

	::WinHelp(GetSafeHwnd(), (const char *) toWin, HELP_CONTEXT, base);


	HANDLE hhwi;
	LPHELPWININFO lphwi;
	WORD wSize;
	char *szWndName = "subtopic";

	wSize = sizeof(HELPWININFO) + lstrlen(szWndName);
	hhwi = GlobalAlloc(GHND, wSize);
	lphwi = (LPHELPWININFO)GlobalLock(hhwi);

	lphwi->wStructSize = wSize;
	lphwi->x           = 654;
	lphwi->y           = 10;;
	lphwi->dx          = 364;
	lphwi->dy          = nline*26+80;
	lphwi->wMax        = SW_SHOW;
	lstrcpy(lphwi->rgchMember, szWndName);

	::WinHelp(GetSafeHwnd(), (const char *) path, HELP_SETWINPOS, (DWORD) lphwi);

	GlobalUnlock(hhwi);
	GlobalFree(hhwi);
	
}

void CGfxProperty::OnBtPin() 
{
	// TODO: Add your control notification handler code here
	
}

void CGfxProperty::OnLButtonDown(UINT nFlags, CPoint point) 
{
	for (int t = 0; t < csTabArray.GetSize(); t++)
	{ 
		if (pTabRect[t].PtInRect(point))
		{ 
			SetCurSel(t);
			break;
		}
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CGfxProperty::OnPaint() 
{
	CPaintDC dc(this);

	CRect irc;
	GetClientRect(&irc);
	irc.InflateRect(-5,-5);
	irc.top += (CG_TAB_HEIGHT-2);

	dc.Draw3dRect(&irc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
	irc.InflateRect(-1, -1);
	dc.Draw3dRect(&irc, GetSysColor(COLOR_3DHILIGHT), RGB(0,0,0));
	irc.InflateRect(-1, -1);

	CFont *ofn = dc.SelectObject(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	int obk = dc.SetBkMode(TRANSPARENT);

	if (pTabRect)
	{
		for (int t = 0; t < csTabArray.GetSize(); t++)
		{ 
			if (t != iActSel)
			{ 
				DrawTabRect(&dc, &pTabRect[t], false);
				dc.TextOut(pTabRect[t].left+7,pTabRect[t].top+3, csTabArray.GetAt(t));
			}
		}
		for (t = 0; t < csTabArray.GetSize(); t++)
		{ 
			if (t == iActSel)
			{ 
				DrawTabRect(&dc, &pTabRect[t], true);
				dc.TextOut(pTabRect[t].left+6,pTabRect[t].top+3, csTabArray.GetAt(t));
			}
		}
	}
	else
	{
		static char cNoProp[] = "Nessuna proprietà disponibile";
		CSize sz = dc.GetTextExtent(cNoProp, lstrlen(cNoProp));
		dc.DrawText(cNoProp, lstrlen(cNoProp), irc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	dc.SetBkMode(obk);
	dc.SelectObject(ofn);
}

void CGfxProperty::OnDestroy() 
{
	InstallHook(false);
	pOneAndOnlyProperty = NULL;

	CString path("Help\\WAtsProp.hlp");
	::WinHelp(GetSafeHwnd(), (const char *) path, HELP_QUIT, 0);

//	ClearTabArray();
	if (pTabRect) GlobalFree((HGLOBAL) pTabRect);
	pTabRect = NULL;
	iActSel = -1;
	csTabArray.RemoveAll();
	pPages.RemoveAll();
	pDocument = NULL;
	pWnd = NULL;
	

	CDialog::OnDestroy();
}

void CGfxProperty::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CGfxProperty::DrawTabRect(CDC * pdc, CRect rc, bool bSel)
{
	if (bSel == false)
	{
		CPen wpen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen bpen(PS_SOLID, 1, RGB(0,0,0));
		CPen dpen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen npen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));

		CPen *open = pdc->SelectObject(&wpen);
		pdc->MoveTo(rc.left, rc.bottom-1);
		pdc->LineTo(rc.left, rc.top+2);
		pdc->LineTo(rc.left+2, rc.top);
		pdc->LineTo(rc.right-1, rc.top);

		pdc->SelectObject(&dpen);
		pdc->MoveTo(rc.right-1, rc.top);
		pdc->LineTo(rc.right-1, rc.bottom);

		pdc->SelectObject(&bpen);
		pdc->MoveTo(rc.right, rc.top+2);
		pdc->LineTo(rc.right, rc.bottom);

		pdc->SelectObject(&npen);
		pdc->MoveTo(rc.right, rc.bottom);
		pdc->LineTo(rc.left, rc.bottom);

		pdc->SelectObject(&wpen);
		pdc->MoveTo(rc.right, rc.bottom+1);
		pdc->LineTo(rc.left, rc.bottom+1);
	}
	else
	{
		rc.top -= 2;
		rc.left -= 3;
		rc.right += 2;

		CPen wpen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		CPen bpen(PS_SOLID, 1, RGB(0,0,0));
		CPen dpen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		CPen npen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));

		CPen *open = pdc->SelectObject(&wpen);
		pdc->MoveTo(rc.left, rc.bottom+1);
		pdc->LineTo(rc.left, rc.top+2);
		pdc->LineTo(rc.left+2, rc.top);
		pdc->LineTo(rc.right-1, rc.top);

		pdc->SelectObject(&dpen);
		pdc->MoveTo(rc.right-1, rc.top);
		pdc->LineTo(rc.right-1, rc.bottom+2);

		pdc->SelectObject(&bpen);
		pdc->MoveTo(rc.right, rc.top+2);
		pdc->LineTo(rc.right, rc.bottom+2);

		pdc->SelectObject(&npen);
		pdc->MoveTo(rc.right-2, rc.bottom+1);
		pdc->LineTo(rc.left, rc.bottom+1);
		
		pdc->MoveTo(rc.right-2, rc.bottom);
		pdc->LineTo(rc.left, rc.bottom);

		pdc->MoveTo(rc.left-1, rc.bottom-1);
		pdc->LineTo(rc.left-1, rc.top-1);

		pdc->MoveTo(rc.left+1, rc.bottom-1);
		pdc->LineTo(rc.left+1, rc.top+2);

	}
}


void CGfxProperty::SetCurSel(int iSel)
{
	if (iActSel == iSel) return;

	if (pPages.GetSize() <= 0 || pTabRect == NULL) return;

	if (iActSel>=0) 
	{
		CRect rc = pTabRect[iActSel];
		rc.left -= 3;
		rc.bottom += 2;
		rc.top -= 2;
		rc.right += 3;
		InvalidateRect(&rc);
	}
	iActSel = iSel;

	CRect rc = pTabRect[iActSel];
	rc.left -= 3;
	rc.bottom += 2;
	rc.top -= 2;
	rc.right += 3;
	InvalidateRect(&rc);

	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * d = (CDialog *) pPages.GetAt(t);
		if (t == iActSel)
		{
			if (!(d->IsWindowVisible())) d->ShowWindow(SW_SHOWNOACTIVATE);
		}
		else
		{
			if (d->IsWindowVisible()) d->ShowWindow(SW_HIDE);
		}
	}
}


void CGfxProperty::SetDialogSize()
{
	CRect rc;
	GetClientRect(&rc);
	int cx = 403-40;
	int cy = 162-CG_TAB_HEIGHT-40;//40;

	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * d = (CDialog *) pPages.GetAt(t);
		MaximizeDlgRect(d, cx, cy);
	}

	SetWindowPos(0,0,0,cx+40,cy+CG_TAB_HEIGHT+40, SWP_NOMOVE|SWP_NOZORDER);

	for (t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * d = (CDialog *) pPages.GetAt(t);
		d->SetWindowPos(0, 8, CG_TAB_HEIGHT+9, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
	}
}


void CGfxProperty::ClearTabArray()
{
	if (pTabRect) GlobalFree((HGLOBAL) pTabRect);
	pTabRect = NULL;
	iActSel = -1;
	csTabArray.RemoveAll();
	HideAllPages();
	pPages.RemoveAll();
	pDocument = NULL;
	pWnd = NULL;
	if (GetSafeHwnd()) Invalidate();
}

void CGfxProperty::MaximizeDlgRect(CDialog * pDlg, int & cx, int & cy)
{
	CRect drc;
	pDlg->GetClientRect(&drc);
	if (cx<drc.Width()) cx = drc.Width();
	if (cy<drc.Height()) cy = drc.Height();
}

void CGfxProperty::AddPage(CDialog * pPage, const char * pText)
{
	csTabArray.Add(CString(pText));
	pPages.Add((void *) pPage);

	if (pTabRect) pTabRect = (CRect *) GlobalReAlloc((HGLOBAL)pTabRect, sizeof(CRect) * csTabArray.GetSize(), GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pTabRect = (CRect *) GlobalAlloc(GPTR, sizeof(CRect) * csTabArray.GetSize());
	
	ASSERT(pTabRect);
	CClientDC dc(this);
	
	CFont *ofn = dc.SelectObject(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));

	int sx = 60;
	for (int t = 0; t < csTabArray.GetSize(); t ++)
	{ 
		CSize sz = dc.GetTextExtent(csTabArray.GetAt(t));
		pTabRect[t] = CRect(sx, 3, sx+sz.cx+18, CG_TAB_HEIGHT+3);
		sx += sz.cx+20;
	}
	dc.SelectObject(ofn);
	SetDialogSize();
}

void CGfxProperty::HideAllPages()
{
	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * d = (CDialog *) pPages.GetAt(t);
		if (d && d->GetSafeHwnd()) d->DestroyWindow();
	}
}


BOOL CGfxProperty::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CGfxProperty::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	return CDialog::WindowProc(message, wParam, lParam);
}

void CGfxProperty::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	InstallHook(bShow);
}

