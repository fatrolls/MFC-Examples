// SkinCtrlMgr.cpp: implementation of the CSkinCtrlMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SkinCtrlMgr.h"
#include "SkinCtrl.h"
#include "SkinCtrls.h"
#include "..\shared\SysColors.h"
#include "..\shared\wclassdefines.h"
#include "..\shared\winclasses.h"

#ifndef NO_SKIN_INI
#include "SkininiGlobalsfile.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// private 'parent' class purely for msg reflection 
class CSkinCtrlReflector : public CSkinCtrl
{
public:
	CSkinCtrlReflector(DWORD dwBaseStyle = 0) { m_dwBaseStyle = dwBaseStyle; }
	virtual ~CSkinCtrlReflector() {}

	COLORREF GetBkgndColor() 
	{ 
		return GetColor(COLOR_PARENTBKGND); 
	}

	LRESULT OnMsg(UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_ENABLE: // default handling by CSkinCtrl causes some funny effects
			return CSubclassWnd::WindowProc(GetHwnd(), msg, wp, lp);
		}

		return CSkinCtrl::OnMsg(msg, wp, lp);
	}

};

CSkinCtrlMgr::CSkinCtrlMgr() : 
	m_bHotCtrls(TRUE), m_nHotTimer(-1), m_ptMouse(0, 0), m_pHotCtrl(NULL), m_bClosing(FALSE), 
	m_bSkinning(FALSE), m_pCallback(NULL)
{
//	CSkinBase::CreateThemeManifest("CSkinCtrlMgr", "CSkinCtrlMgr");
}

CSkinCtrlMgr::~CSkinCtrlMgr()
{
	ReleaseAll();
}

BOOL CSkinCtrlMgr::Initialize(BOOL bHotCtrls, INewSkinCtrl* pCallback)
{
	if (CSkinBase::GetOS() >= SBOS_XP && CSkinBase::IsThemingEnabled())
		return FALSE;

	GetInstance().m_pCallback = pCallback;
	GetInstance().m_bHotCtrls = bHotCtrls;

	return GetInstance().InitHooks();
}

BOOL CSkinCtrlMgr::InitHooks()
{
	CHookMgr<CSkinCtrlMgr>::InitHooks(HM_CALLWNDPROC);

	// only initialize once
	if (m_bHotCtrls && m_nHotTimer == -1)
		m_nHotTimer = SetTimer(NULL, 0, 100, TimerHotProc);

	return TRUE;
}

void CSkinCtrlMgr::EnableHotCtrls()
{
	GetInstance().EnableHotCtrls(TRUE);
}

void CSkinCtrlMgr::DisableHotCtrls()
{
	GetInstance().EnableHotCtrls(FALSE);
}

void CSkinCtrlMgr::EnableSkinDraw(BOOL bEnable)
{
	CSkinCtrl::EnableSkinDraw(bEnable);
}

void CSkinCtrlMgr::SetRenderer(ISkinCtrlRender* pRenderer)
{
	CSkinCtrl::SetRenderer(pRenderer);
}

void CSkinCtrlMgr::Reset() 
{
	GetInstance().m_skGlobals.Reset();
}

void CSkinCtrlMgr::Release() 
{
	GetInstance().ReleaseAll();
}

void CSkinCtrlMgr::ReleaseAll() 
{ 
	m_bClosing = TRUE;
	m_pCallback = NULL;

	CSkinBase::EnableTheming(TRUE);

	if (m_bHotCtrls)
	{
		KillTimer(NULL, m_nHotTimer);
		m_nHotTimer = -1;
	}

#ifndef NO_SKIN_INI
	UnloadSkin(); 
#endif

	if (m_mapCtrls.GetCount())
	{
		DebugMapContents();
		DeleteMap();
	}

	m_skGlobals.Reset();
	m_bClosing = FALSE;
}

void CSkinCtrlMgr::OnCallWndProc(const MSG& msg)
{   
	m_bSkinning = TRUE; 

	switch (msg.message)
	{
	case WM_STYLECHANGED:
		if (msg.wParam == GWL_STYLE)
		{
			LPSTYLESTRUCT lpSS = (LPSTYLESTRUCT)msg.lParam;

			if (lpSS->styleNew & WS_VISIBLE)
			{
				BOOL bRes = Skin(msg.hwnd);
			}
		}
		break;
		
	case WM_PARENTNOTIFY:
		{
			if (LOWORD(msg.wParam) == WM_CREATE)
			{
				BOOL bRes = Skin((HWND)msg.lParam);
			}
		}
		break;
		
	case WM_WINDOWPOSCHANGED: // alternative to WM_SHOWWINDOW
		if (msg.wParam)
		{
			WINDOWPOS* pWPos = (WINDOWPOS*)msg.lParam;
			
			if (pWPos->flags & SWP_SHOWWINDOW)
				BOOL bRes = Skin(msg.hwnd);
		}
		break;
		
	case WM_SHOWWINDOW:
		if (msg.wParam)
		{
			BOOL bRes = Skin(msg.hwnd);
		}
		break;
		
	case WM_NCDESTROY:
		{
			BOOL bRes = Unskin(msg.hwnd);
		}
		break;
	}

	m_bSkinning = FALSE;
}

BOOL CSkinCtrlMgr::Unskin(HWND hCtrl)
{
	CSkinCtrl* pCtrl = GetSkinCtrl(hCtrl);

	if (pCtrl)
	{
		if (m_pHotCtrl == pCtrl)
			m_pHotCtrl = NULL;

		pCtrl->DetachWindow();
		delete pCtrl;

		m_mapCtrls.RemoveKey(hCtrl);

		return TRUE;
	}

	// else
	return FALSE;
}

void CSkinCtrlMgr::DeleteMap()
{
	POSITION pos = m_mapCtrls.GetStartPosition();

	while (pos)
	{
		HWND hwnd = NULL;
		CSkinCtrl* pCtrl = NULL;

		m_mapCtrls.GetNextAssoc(pos, hwnd, pCtrl);
		delete pCtrl;
	}

	m_mapCtrls.RemoveAll();
}

void CSkinCtrlMgr::EnableHotCtrls(BOOL bEnable)
{
	m_bHotCtrls = bEnable;

	if (bEnable && m_nHotTimer == -1)
		m_nHotTimer = SetTimer(NULL, 0, 100, TimerHotProc);

	else if (!bEnable && m_nHotTimer != -1)
	{
		KillTimer(NULL, m_nHotTimer);
		m_nHotTimer = -1;
	}
}

CSkinCtrl* CSkinCtrlMgr::NewSkinCtrl(const CString& sClass, DWORD dwStyle)
{
	if (sClass.CompareNoCase(WC_BUTTON) == 0)
		return CSkinButton::NewButton(dwStyle);
	
	else if (sClass.CompareNoCase(WC_STATIC) == 0)
		return new CSkinStatic();
	
	else if (sClass.CompareNoCase(WC_EDIT) == 0)
		return new CSkinEdit();
	
	else if (sClass.CompareNoCase(WC_COMBOBOX) == 0)
		return new CSkinCombobox();
	
	else if (sClass.CompareNoCase(WC_COMBOLBOX) == 0)
		return new CSkinCombolbox();

	else if (sClass.CompareNoCase(WC_LISTBOX) == 0)
		return new CSkinListbox();
	
	else if (sClass.CompareNoCase(WC_SCROLLBAR) == 0)
		return new CSkinScrollbar();
	
	else if (sClass.CompareNoCase(WC_TOOLBAR) == 0)
		return new CSkinToolbar();
	
	else if (sClass.CompareNoCase(WC_SPIN) == 0)
		return new CSkinUpdown();
	
	else if (sClass.CompareNoCase(WC_PROGRESS) == 0)
		return new CSkinProgress();
	
	else if (sClass.CompareNoCase(WC_SLIDER) == 0)
		return new CSkinTrackbar();
	
	else if (sClass.CompareNoCase(WC_LISTVIEW) == 0)
		return new CSkinListview();
	
	else if (sClass.CompareNoCase(WC_TREEVIEW) == 0)
		return new CSkinTreeview();
	
	else if (sClass.CompareNoCase(WC_TABCONTROL) == 0)
		return new CSkinTabcontrol();
	
	else if (sClass.CompareNoCase(WC_ANIMATE) == 0)
		return new CSkinAnimate();
	
	else if (sClass.CompareNoCase(WC_RICHEDIT) == 0 || sClass.CompareNoCase(WC_RICHEDIT20) == 0)
		return new CSkinRichedit();
	
	else if (sClass.CompareNoCase(WC_DATETIMEPICK) == 0)
		return new CSkinDatetimepick();
	
	else if (sClass.CompareNoCase(WC_MONTHCAL) == 0)
		return new CSkinMonthcal();
	
	else if (sClass.CompareNoCase(WC_IPADDRESS) == 0)
		return new CSkinIPaddress();
	
	else if (sClass.CompareNoCase(WC_PAGESCROLLER) == 0)
		return new CSkinPager();
	
	else if (sClass.CompareNoCase(WC_COMBOBOXEX) == 0)
		return new CSkinComboboxex();
	
	else if (sClass.CompareNoCase(WC_HEADER) == 0)
		return new CSkinHeader();
	
	else if (sClass.CompareNoCase(WC_DIALOGBOX) == 0)
		return new CSkinDialog();
	
	else if (sClass.CompareNoCase(WC_TOOLTIPS) == 0)
		return new CSkinTooltip();
	
	else if (sClass.CompareNoCase(WC_THUMBNAILVIEW) == 0)
		return new CSkinOther();
	
	else if (sClass.CompareNoCase("Link Window") == 0)
		return new CSkinStatic();
	
	// **************************************************************************
	// classes we _don't_ skin

	else if (sClass.CompareNoCase(WC_HOTKEY) == 0)
		return NULL; // new CSkinHotkey();
	
	// shelldefview is the class that does the owner drawing for the open filedialog
	else if (sClass.CompareNoCase(WC_SHELLDLLDEFVIEW) == 0)
		return NULL; // new CSkinSHDLLDefView;
	
	else if (sClass.CompareNoCase(WC_STATUSBAR) == 0)
		return NULL; // new CSkinStatusbar;
	
	else if (sClass.CompareNoCase(WC_REBAR) == 0)
		return NULL; // new CSkinRebar;
	
	else if (sClass.CompareNoCase(WC_MDICLIENT) == 0)
		return NULL;
	
	else if (sClass.CompareNoCase(WC_IE) == 0)
		return NULL; // new CSkinOther(0);

	// these two are related to IE
	else if (sClass.CompareNoCase(WC_SHELLEMBEDDING) == 0 || sClass.CompareNoCase(WC_SHDOCOBJVW) == 0)
		return NULL;

	else if (sClass.Find(WC_CONTROLBAR) == 0)
		return NULL;//new CSkinControlbar;

	else if (sClass.Find(WC_MFCVIEW) == 0)
		return NULL;//new CSkinView;

	else if (sClass.Find(WC_MFCSPLITTER) == 0)
		return NULL;//new CSkinSplitter;

	// we don't do menus
	else if (sClass.CompareNoCase(WC_MENU) == 0)
		return NULL;

	// **************************************************************************

	return NULL;//new CSkinOther(0);
}

BOOL CSkinCtrlMgr::Skin(HWND hCtrl)
{
	CString sClass(CWinClasses::GetClass(hCtrl));
	CSkinCtrl* pSkinCtrl = GetSkinCtrl(hCtrl);
	
	if (pSkinCtrl)
	{
		pSkinCtrl->OnSetIni();
		return TRUE; // already done
	}

	DWORD dwStyle = GetWindowLong(hCtrl, GWL_STYLE);
	BOOL bSkin = (dwStyle & WS_CHILD) || CWinClasses::IsControlClass(sClass);

	if (bSkin)
	{
		// try callback first
		if (m_pCallback)
		{
			BOOL bWants = m_pCallback->NewSkinCtrl(hCtrl, pSkinCtrl);

			if (bWants && !pSkinCtrl)
				return FALSE;
		}

		// finally do it ourselves
		if (!pSkinCtrl)
		{
			CString sClass(CWinClasses::GetClassEx(hCtrl)); // converts Afx class names into something more useful

			pSkinCtrl = NewSkinCtrl(sClass, dwStyle);
		}
	}
	else
	{
		// if the window has any children then skin purely for message reflection purposes
		if (::GetWindow(hCtrl, GW_CHILD))
		{
			BOOL bDlg = CWinClasses::IsClass(hCtrl, WC_DIALOGBOX);

			pSkinCtrl = new CSkinCtrlReflector(bDlg ? SKCS_ERASEBKGND : 0);
		}
	}
	
	if (pSkinCtrl && pSkinCtrl->AttachWindow(CWnd::FromHandle(hCtrl)))
	{
		pSkinCtrl->SetGlobals(&m_skGlobals);
		m_mapCtrls[hCtrl] = pSkinCtrl;
		SkinAllChildren(hCtrl);

		return TRUE;
	}
	
	// else
	delete pSkinCtrl;
	
	return TRUE;
}

BOOL CSkinCtrlMgr::ModifyStyle(HWND hCtrl, DWORD dwStylesToRemove, DWORD dwStylesToAdd)
{
	CSkinCtrl* pSkin = Instance().GetSkinCtrl(hCtrl);

	if (!pSkin)
		return FALSE;

	// else
	pSkin->ModifyStyle(dwStylesToRemove, dwStylesToAdd);

	return TRUE;
}

BOOL CSkinCtrlMgr::ModifyStyle(CWnd* pParent, UINT uCtrlID, DWORD dwStylesToRemove, DWORD dwStylesToAdd)
{
	HWND hCtrl = GetDlgItem(*pParent, uCtrlID);

	if (!hCtrl)
		return FALSE;

	// else
	return ModifyStyle(hCtrl, dwStylesToRemove, dwStylesToAdd);
}

CSkinCtrl* CSkinCtrlMgr::GetSkinCtrl(HWND hCtrl)
{
	CSkinCtrl* pSkin = NULL;
	
	if (m_mapCtrls.Lookup(hCtrl, pSkin))
		return pSkin;
	
	return NULL;
}

void CALLBACK CSkinCtrlMgr::TimerHotProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	// if draw is disabled just return
	if (!CSkinCtrl::s_bDrawingEnabled)
		return;

	// if the user is in the middle of something just return
	if (::GetCapture() != NULL)
		return;

	if (GetAsyncKeyState(MK_LBUTTON) & 0x8000)
		return;

	CPoint ptNew, ptOld(Instance().m_ptMouse);
	::GetCursorPos(&ptNew);

	HWND hNewWnd = RealChildFromPoint(ptNew);

	// check for disabled parent windows
	if (hNewWnd)
	{
		HWND hParent = ::GetParent(hNewWnd);

		while (hParent)
		{
			if (!::IsWindowEnabled(hParent))
			{
				hNewWnd = NULL;
				break;
			}
			else if (!(GetWindowLong(hParent, GWL_STYLE) & WS_CHILD))
				break;
			
			hParent = ::GetParent(hParent);
		}
	}

	CSkinCtrl* pOldSkin = Instance().m_pHotCtrl;
	CSkinCtrl* pNewSkin = Instance().GetSkinCtrl(hNewWnd);

	// save these off before we modify them
	Instance().m_ptMouse = ptNew;
	Instance().m_pHotCtrl = pNewSkin;

	if (pOldSkin || pNewSkin)
	{
		if (pOldSkin == pNewSkin)
		{
			int nOldHitTest = pOldSkin->SendMessage(WM_NCHITTEST, 0, MAKELPARAM(ptOld.x, ptOld.y));
			int nNewHitTest = pOldSkin->SendMessage(WM_NCHITTEST, 0, MAKELPARAM(ptNew.x, ptNew.y));

			CRect rWindow;
			pOldSkin->GetWindowRect(rWindow);
			ptOld.Offset(-rWindow.TopLeft());
			ptNew.Offset(-rWindow.TopLeft());

			pOldSkin->OnUpdateHotspots(&ptOld, &ptNew, nOldHitTest, nNewHitTest);
		}
		else 
		{
			TRACE ("CSkinCtrlMgr::UpdateHotspots(%s, %s)\n", 
				pOldSkin ? CWinClasses::GetClass(pOldSkin->GetHwnd()) : "NULL",
				hNewWnd ? CWinClasses::GetClass(hNewWnd) : "NULL");

			if (pOldSkin)
			{
				int nOldHitTest = pOldSkin->SendMessage(WM_NCHITTEST, 0, MAKELPARAM(ptOld.x, ptOld.y));

				CRect rWindow;
				pOldSkin->GetWindowRect(rWindow);
				ptOld.Offset(-rWindow.TopLeft());

				pOldSkin->OnUpdateHotspots(&ptOld, NULL, nOldHitTest, HTNOWHERE);

				// recursively do parents too
				HWND hParent = ::GetParent(pOldSkin->GetHwnd());

				while (hParent)
				{
					CSkinCtrl* pParentSkin = Instance().GetSkinCtrl(hParent);

					if (pParentSkin)
						pParentSkin->OnUpdateHotspots(&ptOld, NULL, nOldHitTest, HTNOWHERE);
					else
						break;

					hParent = ::GetParent(hParent);
				}
			}

			if (pNewSkin)
			{
				int nNewHitTest = pNewSkin->SendMessage(WM_NCHITTEST, 0, MAKELPARAM(ptNew.x, ptNew.y));

				CRect rWindow;
				pNewSkin->GetWindowRect(rWindow);
				ptNew.Offset(-rWindow.TopLeft());

				pNewSkin->OnUpdateHotspots(NULL, &ptNew, HTNOWHERE, nNewHitTest);

				// recursively do parents too
				HWND hParent = ::GetParent(hNewWnd);

				while (hParent)
				{
					CSkinCtrl* pParentSkin = Instance().GetSkinCtrl(hParent);

					if (pParentSkin)
						pParentSkin->OnUpdateHotspots(NULL, &ptNew, HTNOWHERE, nNewHitTest);
					else
						break;

					hParent = ::GetParent(hParent);
				}
			}
		}
	}
}

HBRUSH CSkinCtrlMgr::DoCtlColor(HWND hCtrl, CDC* pDC)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);

	if (!pSkin || !pSkin->WantsDraw(SKCS_CTLCOLOR))
		return NULL;
	
	return pSkin->OnCtlColor(pDC);
}

BOOL CSkinCtrlMgr::DoDrawItem(HWND hCtrl, LPDRAWITEMSTRUCT lpDIS)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);

	if (!pSkin || !pSkin->WantsDraw(SKCS_DRAWITEM))
		return FALSE;
	
	return pSkin->OnDrawItem(lpDIS);
}

void CSkinCtrlMgr::DoScroll(HWND hCtrl, UINT nSBCode, UINT nPos, BOOL bHorz)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);

	if (pSkin)
		pSkin->OnScroll(nSBCode, nPos, bHorz);
}

LRESULT CSkinCtrlMgr::DoCustomDraw(HWND hCtrl, NMHDR* pNMHDR)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);
	LRESULT lResult = CDRF_DODEFAULT;
	
	if (pSkin && pSkin->WantsDraw(SKCS_CUSTOMDRAW))
	{	
		NMCUSTOMDRAW* pNMCD = (NMCUSTOMDRAW*)pNMHDR;

		if (pNMCD->dwDrawStage == CDDS_PREPAINT)
			lResult = CDRF_NOTIFYITEMDRAW;	
		
		else // rest of drawing is control specific
			lResult = pSkin->OnCustomDraw(pNMCD, pNMCD->dwDrawStage);
	}

	return lResult;
}

LRESULT CSkinCtrlMgr::DoNotify(HWND hCtrl, NMHDR* pNMHDR)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);
	
	if (pSkin)
		return pSkin->OnNotify(pNMHDR);

	return 0;
}

void CSkinCtrlMgr::DoNotify(HWND hCtrl, UINT uNotify, UINT uID, CWnd* pChild)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);
	
	if (pSkin)
		pSkin->OnNotify(uNotify, uID, pChild);
	else
	{
		TRACE ("CSkinCtrlMgr::DoNotify - skin no longer exists\n");
	}
}

LRESULT CSkinCtrlMgr::DoNotifyReflect(HWND hCtrl, NMHDR* pNMHDR, LRESULT lrParent)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);
	
	if (pSkin)
		return pSkin->OnNotifyReflect(pNMHDR, lrParent);

	// else
	TRACE ("CSkinCtrlMgr::DoNotify - skin no longer exists\n");
	return 0;
}

void CSkinCtrlMgr::DoNotifyReflect(HWND hCtrl, UINT uNotify, LRESULT lrParent)
{
	CSkinCtrl* pSkin = GetSkinCtrl(hCtrl);
	
	if (pSkin)
		pSkin->OnNotifyReflect(uNotify, lrParent);
}

void CSkinCtrlMgr::GetCursorPos(LPPOINT pCursor)
{
	ASSERT (pCursor);
	*pCursor = m_ptMouse;
}

void CSkinCtrlMgr::RedrawAll()
{
	CSkinCtrl* pSkin = NULL;
	HWND hwnd = NULL;
	POSITION pos = Instance().m_mapCtrls.GetStartPosition();
	
	while (pos)
	{
		Instance().m_mapCtrls.GetNextAssoc(pos, hwnd, pSkin);
		ASSERT (pSkin);
		
		if (pSkin && pSkin->GetCtrl())
			pSkin->OnSetIni();
	}
}

#ifndef NO_SKIN_INI

void CSkinCtrlMgr::UnloadSkin()
{
	Instance().m_skGlobals.UnloadSkin();

	// update controls
	if (!m_bClosing)
		RedrawAll();
}

BOOL CSkinCtrlMgr::LoadSkin(const CSkinIniGlobalsFile* pIniFile)
{
	if (!pIniFile || !pIniFile->IsValid())
		return FALSE;

	Instance().m_skGlobals.LoadSkin(pIniFile);

	// update controls
	RedrawAll();

	return TRUE;
}

#endif

BOOL CSkinCtrlMgr::IsHot(LPRECT pRect)
{
	return ::PtInRect(pRect, m_ptMouse);
}

void CSkinCtrlMgr::DebugMapContents()
{
#ifdef _DEBUG
	// then any popups
	int nItem = 0;
	POSITION pos = m_mapCtrls.GetStartPosition();

	while (pos)
	{
		nItem++;
		HWND hwnd = NULL;
		CSkinCtrl* pCtrl = NULL;

		m_mapCtrls.GetNextAssoc(pos, hwnd, pCtrl);
		ASSERT (pCtrl);

		TRACE("CSkinCtrlMgr::CMap::Item%d - hWnd = %08X, classname = %s\n", nItem, hwnd, CWinClasses::GetClass(pCtrl->GetHwnd()));
	}
#endif
}

void CSkinCtrlMgr::SkinAllChildren(HWND hCtrl)
{
	HWND hChild = ::GetWindow(hCtrl, GW_CHILD); 
	
	while (hChild)    
	{
		Skin(hChild);
		hChild = GetNextWindow(hChild, GW_HWNDNEXT);
	}
}

BOOL CSkinCtrlMgr::SetControlBitmap(int nItem, CBitmap bitmap[IM_LAST], COLORREF crMask)
{
	return Instance().m_skGlobals.SetControlBitmap(nItem, bitmap, crMask);
}

BOOL CSkinCtrlMgr::SetControlBitmap(int nItem, UINT uIDBitmap[IM_LAST], COLORREF crMask)
{
	return Instance().m_skGlobals.SetControlBitmap(nItem, uIDBitmap, crMask);
}

void CSkinCtrlMgr::SetColor(int nColor, COLORREF color)
{
	Instance().m_skGlobals.SetColor(nColor, color);
}

typedef HWND (WINAPI *REALCHILDWINDOWFROMPOINT)(HWND hwndParent, POINT ptParentClientCoords);

HWND CSkinCtrlMgr::RealChildFromPoint(CPoint ptHitTest)
{
	HWND hWnd = ::WindowFromPoint(ptHitTest);

	if (hWnd && (GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD))
	{
		// if the window is a dialog check whether we're within a tabctrl
		if (CWinClasses::IsClass(hWnd, WC_DIALOGBOX))
		{
			HWND hChild = ::GetWindow(hWnd, GW_CHILD);
			
			while (hChild)
			{
				CRect rChild;
				::GetWindowRect(hChild, rChild);
				
				if (rChild.PtInRect(ptHitTest))
				{
					hWnd = hChild;
					break;
				}
				
				hChild = ::GetWindow(hChild, GW_HWNDNEXT);
			}
		}
		else
		{
			// now check that another control is not being masked by say a group box
			HWND hParent = ::GetParent(hWnd);
			
			if (hParent)
			{
				// have to call
				HMODULE hUser32 = ::LoadLibrary("User32.dll");

				if (hUser32)
				{
					// note this function is not available under win95 so we also have a fallback
					REALCHILDWINDOWFROMPOINT fnRealWndFromPoint = (REALCHILDWINDOWFROMPOINT)GetProcAddress(hUser32, "RealChildWindowFromPoint");

					if (fnRealWndFromPoint)
					{
						// convert to parent client coords
						::ScreenToClient(hParent, &ptHitTest);

						hWnd = fnRealWndFromPoint(hParent, ptHitTest);
					}
					else // win95
					{
						// iterate all the child controls of the parent until we hit one which
						// does not return HTTRANSPARENT or HTNOWHERE to WM_NCHITTEST
						HWND hChild = ::GetWindow(hParent, GW_CHILD);
						ASSERT (hChild);
						
						while (hChild)
						{
							UINT uHitTest = SendMessage(hChild, WM_NCHITTEST, 0, MAKELPARAM(ptHitTest.x, ptHitTest.y));
							
							if ((int)uHitTest > 0)
							{
								hWnd = hChild;
								break;
							}
							
							hChild = ::GetWindow(hChild, GW_HWNDNEXT);
						}
					}
				}
			}
		}
	}
	else if (CWinClasses::IsClass(hWnd, WC_DIALOGBOX))
	{
		// if the window is a dialog check whether we're within a tabctrl
		HWND hChild = ::GetWindow(hWnd, GW_CHILD);
		
		while (hChild)
		{
			CRect rChild;
			::GetWindowRect(hChild, rChild);
			
			if (rChild.PtInRect(ptHitTest))
			{
				hWnd = hChild;
				break;
			}
			
			hChild = ::GetWindow(hChild, GW_HWNDNEXT);
		}
	}

	return (hWnd && (GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD)) ? hWnd : NULL;
}

