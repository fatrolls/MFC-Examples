// XHtmlTree.cpp  Version 1.6 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// History
//     Version 1.6 - 2007 December 19
//     - Bug fixes and enhancements;  see CodeProject article for details
//
//     Version 1.5 - 2007 November 7
//     - Bug fixes and enhancements;  see CodeProject article for details
//
//     Version 1.4 - 2007 November 4
//     - Bug fixes and enhancements;  see CodeProject article for details
//
//     Version 1.3 - 2007 October 16
//     - Bug fixes and enhancements;  see CodeProject article for details
//
//     Version 1.2 - 2007 October 7
//     - Bug fixes and enhancements;  see CodeProject article for details
//
//     Version 1.1 - 2007 October 6
//     - Bug fixes and enhancements;  see CodeProject article for details
//
//     Version 1.0 - 2007 August 9
//     - Initial public release
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#pragma warning(disable : 4786)
#include "XHtmlTree.h"
#include "XNamedColors.h"
#include "XHtmlDraw.h"
#include "CreateCheckboxImageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef __noop
#if _MSC_VER < 1300
#define __noop ((void)0)
#endif
#endif

#undef TRACE
#define TRACE __noop


//=============================================================================
// if you want to see the TRACE output, uncomment this line:
#include "XTrace.h"
//=============================================================================


//=============================================================================
// REGISTERED XHTMLTREE MESSAGES
//=============================================================================
UINT WM_XHTMLTREE_CHECKBOX_CLICKED = ::RegisterWindowMessage(_T("WM_XHTMLTREE_CHECKBOX_CLICKED"));
UINT WM_XHTMLTREE_ITEM_EXPANDED    = ::RegisterWindowMessage(_T("WM_XHTMLTREE_ITEM_EXPANDED"));
UINT WM_XHTMLTREE_DISPLAY_TOOLTIP  = ::RegisterWindowMessage(_T("WM_XHTMLTREE_DISPLAY_TOOLTIP"));
UINT WM_XHTMLTREE_INIT_TOOLTIP     = ::RegisterWindowMessage(_T("WM_XHTMLTREE_INIT_TOOLTIP"));
#ifdef XHTMLDRAGDROP
UINT WM_XHTMLTREE_BEGIN_DRAG       = ::RegisterWindowMessage(_T("WM_XHTMLTREE_BEGIN_DRAG"));
UINT WM_XHTMLTREE_END_DRAG         = ::RegisterWindowMessage(_T("WM_XHTMLTREE_END_DRAG"));
UINT WM_XHTMLTREE_DROP_HOVER       = ::RegisterWindowMessage(_T("WM_XHTMLTREE_DROP_HOVER"));
#endif // XHTMLDRAGDROP
#ifdef XHTMLTREE_DEMO
UINT WM_XHTMLTREE_SCROLL_SPEED     = ::RegisterWindowMessage(_T("WM_XHTMLTREE_SCROLL_SPEED"));
#endif // XHTMLTREE_DEMO

#pragma warning(disable : 4996)	// disable bogus deprecation warning

const UINT HOT_TIMER			= 1;
const UINT LBUTTONDOWN_TIMER	= 2;
const UINT CTRL_UP_TIMER		= 3;
const UINT SHIFT_UP_TIMER		= 4;
const UINT SELECT_TIMER			= 5;
const UINT TOOLTIP_BASE_ID		= 10000;
const DWORD MIN_HOVER_TIME		= 1500;		// 1.5 seconds
const int SCROLL_ZONE			= 16;		// pixels for scrolling

int XHTMLTREEDATA::nCount		= 0;

//=============================================================================
BEGIN_MESSAGE_MAP(CXHtmlTree, CTreeCtrl)
//=============================================================================
	//{{AFX_MSG_MAP(CXHtmlTree)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT_EX(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT_EX(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT_EX(TVN_ENDLABELEDIT, OnEndlabeledit)
	//}}AFX_MSG_MAP

#ifdef XHTMLDRAGDROP
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
#endif // XHTMLDRAGDROP

#ifdef XHTMLTOOLTIPS
	ON_NOTIFY(UDM_TOOLTIP_DISPLAY, NULL, OnDisplayTooltip)	
#else
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
#endif // XHTMLTOOLTIPS

	ON_NOTIFY_REFLECT_EX(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT_EX(TVN_SELCHANGING, OnSelchanging)
END_MESSAGE_MAP()

//=============================================================================
CXHtmlTree::CXHtmlTree()
//=============================================================================
  :	m_bDestroyingTree(FALSE),
	m_bFirstTime(TRUE),
	m_bSmartCheck(FALSE),
	m_bCheckBoxes(FALSE),
	m_bSelectFollowsCheck(TRUE),
	m_bReadOnly(FALSE),
	m_bHtml(TRUE),
	m_bStripHtml(FALSE),
	m_bLogFont(FALSE),
	m_bToolTip(FALSE),
	m_bDragging(FALSE),
	m_bAutoScroll(TRUE),
	m_bImages(TRUE),
	m_pToolTip(0),
	m_hAnchorItem(0),
	m_hHotItem(0),
	m_hPreviousItem(0),
	m_hItemButtonDown(0),
	m_hPreviousDropItem(0),
	m_nPadding(0),
	m_nImageHeight(16),
	m_nToolCount(0),
	m_nDefaultTipWidth(0),
	m_nScrollTime(0),
	m_crCustomWindow(COLOR_NONE),
	m_crCustomWindowText(COLOR_NONE),
	m_nHorzPos(0),
	m_dwDropHoverTime(0),
	m_nNoDropCursor(0),
	m_nDropCopyCursor(0),
	m_nDropMoveCursor(0),
	m_hNoDropCursor(0),
	m_hDropCopyCursor(0),
	m_hDropMoveCursor(0),
	m_hPreviousCursor(0),
	m_hCurrentCursor(0),
	m_dwDragOps(XHTMLTREE_DO_DEFAULT)
{
	TRACE(_T("in CXHtmlTree::CXHtmlTree\n"));
	memset(&m_lf, 0, sizeof(m_lf));
	SetColors();

	m_hPreviousCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
}

//=============================================================================
CXHtmlTree::~CXHtmlTree()
//=============================================================================
{
	if (m_pToolTip)
		delete m_pToolTip;
	m_pToolTip = 0;

	if (m_StateImage.GetSafeHandle())
		m_StateImage.DeleteImageList();

	if (m_hNoDropCursor)
		DestroyCursor(m_hNoDropCursor);
	m_hNoDropCursor = NULL;

	if (m_hDropCopyCursor)
		DestroyCursor(m_hDropCopyCursor);
	m_hDropCopyCursor = NULL;

	if (m_hDropMoveCursor)
		DestroyCursor(m_hDropMoveCursor);
	m_hDropMoveCursor = NULL;

	TRACE(_T("XHTMLTREEDATA::nCount=%d\n"), XHTMLTREEDATA::nCount);
}

//=============================================================================
CXHtmlTree& CXHtmlTree::Initialize(BOOL bCheckBoxes /*= FALSE*/, 
								   BOOL bToolTip /*= FALSE*/)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::Initialize\n"));
	m_bDestroyingTree = TRUE;

	DeleteAllItems();

	if (m_pToolTip)
		delete m_pToolTip;
	m_pToolTip = 0;

	SetImageList(NULL, TVSIL_STATE);

	if (m_StateImage.GetSafeHandle())
		m_StateImage.DeleteImageList();

	m_bCheckBoxes         = bCheckBoxes;
	m_bToolTip            = bToolTip;
	m_bSmartCheck         = FALSE;
	m_bSelectFollowsCheck = TRUE;
	m_bHtml               = TRUE;
	m_bLogFont            = FALSE;
	m_nPadding            = 0;
	m_nImageHeight        = 16;
	m_bFirstTime          = TRUE;
	m_hAnchorItem         = 0;
	m_hHotItem            = 0;
	memset(&m_lf, 0, sizeof(m_lf));

	SetColors();

	if (m_bToolTip)
	{
		TRACE(_T("creating tooltip\n"));
#ifdef XHTMLTOOLTIPS
		m_pToolTip = new CPPToolTip;
#else
		m_pToolTip = new CToolTipCtrl;
#endif // XHTMLTOOLTIPS
		if (m_pToolTip)
		{
			m_pToolTip->Create(this);
		}
	}

	if (m_bCheckBoxes)
		CreateCheckboxImages();

	m_bDestroyingTree = FALSE;

	return *this;
}

//=============================================================================
// PreCreateWindow() is called when CXHtmlTree is used in a view.
//
BOOL CXHtmlTree::PreCreateWindow(CREATESTRUCT& cs) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::PreCreateWindow\n"));

	// style must include "no tooltips"
	cs.style |= TVS_NOTOOLTIPS;

	return CTreeCtrl::PreCreateWindow(cs);
}

//=============================================================================
void CXHtmlTree::PreSubclassWindow()
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::PreSubclassWindow\n"));
	DWORD dwStyle = GetStyle();

	if (dwStyle & TVS_CHECKBOXES)
		m_bCheckBoxes = TRUE;

	// these styles must not be set
	ModifyStyle(TVS_CHECKBOXES, TVS_NOTOOLTIPS);

#ifdef XHTMLDRAGDROP
	ModifyStyle(TVS_DISABLEDRAGDROP, 0);
#else
	ModifyStyle(0, TVS_DISABLEDRAGDROP);
#endif // XHTMLDRAGDROP

	if (m_bCheckBoxes)
		CreateCheckboxImages();

	CTreeCtrl::PreSubclassWindow();
}

//=============================================================================
BOOL CXHtmlTree::PreTranslateMessage(MSG* pMsg) 
//=============================================================================
{
	// allow edit control to receive messages, if 
	// label is being edited
	if (GetEditControl() && 
		((pMsg->message == WM_CHAR) ||
		 (pMsg->message == WM_KEYDOWN) ||
		 GetKeyState(VK_CONTROL)))
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE;
	}

	if (m_pToolTip && IsWindow(m_pToolTip->m_hWnd))
	{
		m_pToolTip->RelayEvent(pMsg);
	}

	//=========================================================================
	// WM_CHAR
	//=========================================================================
	if (pMsg->message == WM_CHAR)
	{
		if ((pMsg->wParam == VK_SPACE) && m_bCheckBoxes && !m_bReadOnly)
		{
			HTREEITEM hItem = GetSelectedItem();
			
			XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);
	
			if (pXTCD && !pXTCD->bSeparator)		//+++1.6
			{
				SetCheck(hItem, !pXTCD->bChecked);
			}

			return TRUE;
		}
	}

	//=========================================================================
	// WM_KEYDOWN
	//=========================================================================
	if (pMsg->message == WM_KEYDOWN)
	{
		TRACE(_T("WM_KEYDOWN: lParam=0x%X\n"), pMsg->lParam);

#ifdef XHTMLDRAGDROP
		//=====================================================================
		// VK_ESCAPE while dragging
		//=====================================================================
		if ((pMsg->wParam == VK_ESCAPE) && m_bDragging)
		{
			TRACE(_T("ESC seen during drag\n"));
			EndDragScroll();
			SendRegisteredMessage(WM_XHTMLTREE_END_DRAG, 0, 0);
			return TRUE;
		}

		//=====================================================================
		// VK_CONTROL while dragging
		//=====================================================================
		if ((pMsg->wParam == VK_CONTROL) && 
			(m_dwDragOps & XHTMLTREE_DO_CTRL_KEY))
		{
			// check if Ctrl key down for first time
			if ((pMsg->lParam & 0x40000000) == 0)
			{
				if (IsOverItem() && m_bDragging)
				{
					SetDragCursor();
				}

				SetTimer(CTRL_UP_TIMER, 100, NULL);
			}
		}

		//=====================================================================
		// VK_SHIFT while dragging
		//=====================================================================
		if ((pMsg->wParam == VK_SHIFT) && 
			(m_dwDragOps & XHTMLTREE_DO_SHIFT_KEY))
		{
			// check if Shift key down for first time
			if ((pMsg->lParam & 0x40000000) == 0)
			{
				HTREEITEM hItem = IsOverItem();
				if (hItem && m_bDragging)
				{
					if (IsSeparator(hItem))					//+++1.6
					{
						SelectDropTarget(NULL);
						SetInsertMark(0, 0);
						SetInsertMark(hItem, TRUE);
					}
					else
					{
						SetInsertMark(0, 0);
						SelectDropTarget(hItem);
					}
				}
				SetTimer(SHIFT_UP_TIMER, 100, NULL);
			}
		}
#endif // XHTMLDRAGDROP

		//=====================================================================
		// VK_RIGHT or VK_LEFT
		//=====================================================================
		if ((pMsg->wParam == VK_RIGHT) || (pMsg->wParam == VK_LEFT))
		{
			BOOL bRight = pMsg->wParam == VK_RIGHT;

			HTREEITEM hItem = GetSelectedItem();
			
			XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);
		
			if (pXTCD && pXTCD->bEnabled && pXTCD->nChildren)
			{
				BOOL bExpanded = pXTCD->bExpanded;
				BOOL bOldExpanded = pXTCD->bExpanded;
				if (!bExpanded && bRight)
					bExpanded = TRUE;
				if (bExpanded && !bRight)
					bExpanded = FALSE;
				if (bOldExpanded != bExpanded)
				{
					Expand(hItem, bExpanded ? TVE_EXPAND : TVE_COLLAPSE);
					return TRUE;
				}
			}
		}

		//=====================================================================
		// VK_DOWN or VK_UP
		//=====================================================================
		if ((pMsg->wParam == VK_DOWN) || (pMsg->wParam == VK_UP))
		{
			BOOL bDown = pMsg->wParam == VK_DOWN;

			HTREEITEM hItem = GetSelectedItem();
			
			if (hItem)
			{
				HTREEITEM hItemNew = bDown ? GetNextVisibleItem(hItem) : 
											 GetPrevVisibleItem(hItem);

				XHTMLTREEDATA *pXTCD = NULL;

				while (hItemNew)
				{
					pXTCD = GetItemDataStruct(hItemNew);
			
					if (pXTCD && pXTCD->bEnabled)
						break;

					// next item is not enabled, just skip it
					hItemNew = bDown ? GetNextVisibleItem(hItemNew) : 
									   GetPrevVisibleItem(hItemNew);
				}

				if (hItemNew)
				{
					SelectItem(hItemNew);
					return TRUE;
				}
			}
		}

		//=====================================================================
		// VK_MULTIPLY
		//=====================================================================
		if (pMsg->wParam == VK_MULTIPLY)
		{
			HTREEITEM hItem = GetSelectedItem();
			
			if (hItem)
			{
				ExpandBranch(hItem);
				EnsureVisible(hItem);
				SendMessage(WM_HSCROLL, SB_LEFT);
				return TRUE;
			}
		}

		//=====================================================================
		// VK_SUBTRACT  VK_ADD
		//=====================================================================
		UINT nCode = 0;
		switch (pMsg->wParam)
		{
			default:			break;
			case VK_SUBTRACT:	nCode = TVE_COLLAPSE; break;
			case VK_ADD:		nCode = TVE_EXPAND; break;
		}
		if (nCode)
		{
			HTREEITEM hItem = GetSelectedItem();
			if (hItem)
			{
				Expand(hItem, nCode);
				return TRUE;	// skip default processing
			}
		}

	}
	return CTreeCtrl::PreTranslateMessage(pMsg);
}

//=============================================================================
void CXHtmlTree::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
//=============================================================================
{
	NMTVCUSTOMDRAW* pCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);

	CDC* pDC = CDC::FromHandle(pCD->nmcd.hdc);

	HTREEITEM hItem = reinterpret_cast<HTREEITEM> (pCD->nmcd.dwItemSpec);

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	//=========================================================================
	if (pCD->nmcd.dwDrawStage == CDDS_PREPAINT)	// before the painting cycle begins
	//=========================================================================
	{
		*pResult = CDRF_NOTIFYITEMDRAW /*| CDRF_NOTIFYPOSTPAINT*/;
	}
	//=========================================================================
	else if (pCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)	// before an item is drawn
	//=========================================================================
	{
		pCD->clrText = pCD->clrTextBk;	// don't want default drawing -
										// set text color = background color
		if (hItem)
		{
			CRect rectItem1;
			GetItemRect(hItem, &rectItem1, FALSE);	// get rect for item
			if (!IsBadRect(rectItem1))
			{
				CBrush brush(m_crWindow);
				pDC->FillRect(&rectItem1, &brush);		// erase entire background
			}
		}
		*pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT;
	}
	//=========================================================================
	else if (pCD->nmcd.dwDrawStage == CDDS_ITEMPOSTPAINT)	// after an item has been drawn
	//=========================================================================
	{
		// by doing the drawing at this stage we avoid having to draw lines, etc.

		if (m_bFirstTime)
		{
			if (m_bToolTip)
				CreateToolTipsForTree();

			CImageList *pImageList = GetImageList(TVSIL_NORMAL);
			if (!pImageList)	//+++1.5
			{
				TRACE(_T("WARNING  no image list, setting m_bImages to FALSE\n"));
				m_bImages = FALSE;
			}
		}

		m_bFirstTime = FALSE;

		CRect rectItem;
		GetItemRect(hItem, &rectItem, FALSE);		// get rect for entire item
		CRect rectText;
		GetItemRect(hItem, &rectText, TRUE);		// get rect for text
		rectText.right = rectItem.right;

		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		// set up colors

		COLORREF crText = m_crWindowText;
		COLORREF crAnchorText = m_crAnchorText;
		COLORREF crBackground = m_crWindow;
		COLORREF crTextBackground = m_crWindow;

		BOOL bEnabled = TRUE;

		HTREEITEM hSelected = GetSelectedItem();

		if (pXTCD)
		{
			// try to use colors specified for this item
			pXTCD->ds.bIgnoreColorTag = FALSE;
			crText  = pXTCD->ds.crText;
			crTextBackground = pXTCD->ds.crTextBackground;
			crBackground = pXTCD->ds.crBackground;
			//TRACE(_T("crText=%08X  crBkgnd=%08X ~~~~~\n"), crText, crBackground);
			bEnabled = pXTCD->bEnabled;
			if ((hItem == hSelected) || 
				(GetItemState(hItem, TVIF_STATE) & TVIS_DROPHILITED))
			{
				crTextBackground = m_crHighlight;
			}
			else
			{
			 	//crTextBackground = COLOR_NONE;
			}

			if (!bEnabled)
			{
				crText = crAnchorText = m_crGrayText;
				pXTCD->ds.bIgnoreColorTag = TRUE;
			}
			else if ((hItem == hSelected) || 
				(GetItemState(hItem, TVIF_STATE) & TVIS_DROPHILITED))
			{
				crText = crAnchorText = m_crHighlightText;
				pXTCD->ds.bIgnoreColorTag = TRUE;
			}
			else
			{
			}
		}

		if (crBackground == COLOR_NONE)
			crBackground = m_crWindow;

		if (pXTCD && pXTCD->bSeparator)			//+++1.6
		{
			if (crText == COLOR_NONE)
				crText = m_crSeparator;

			if (hItem == hSelected)
				crBackground = m_crHighlight;

			DrawSeparator(pDC, hItem, crText, crBackground, rectText);
		}
		else
		{
			if (crText == COLOR_NONE)
				crText = m_crWindowText;

			CString strText = GetItemText(hItem);

			BOOL bContainsHtml = FALSE;

			// check for html tag and char entity
			if (strText.FindOneOf(_T("<&")) >= 0)
				bContainsHtml = TRUE;

			if (m_bStripHtml && bContainsHtml)
				strText = GetItemText(hItem, TRUE);

#ifdef XHTMLHTML
			if (m_bHtml && bContainsHtml)
				DrawItemTextHtml(pDC, hItem, strText, crText, crTextBackground,
									crBackground, crAnchorText, rectText);
			else
#endif // XHTMLHTML
				DrawItemText(pDC, hItem, strText, crText, crTextBackground, crBackground, rectText);
		}
	
		//*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.
	}
}

//=============================================================================
BOOL CXHtmlTree::SelectItem(HTREEITEM hItem)
//=============================================================================
{
	HTREEITEM hPrevItemSel = GetSelectedItem();

	if (hItem == hPrevItemSel)
		return TRUE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && pXTCD->bEnabled)
	{
		NMTREEVIEW nmtv = { 0 };
		
		nmtv.hdr.hwndFrom = m_hWnd;
		nmtv.hdr.idFrom = GetDlgCtrlID();
		nmtv.hdr.code = TVN_SELCHANGED;
		nmtv.itemNew.hItem = hItem;

		CWnd *pWnd = GetParent();
		if (!pWnd)
			pWnd = GetOwner();
		if (pWnd && ::IsWindow(pWnd->m_hWnd))
		{
			pWnd->SendMessage(WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&nmtv);
		}
	}
	else
	{
		if (hPrevItemSel)
			hItem = hPrevItemSel;
		else
			return TRUE;
	}

	return CTreeCtrl::SelectItem(hItem);
}

//=============================================================================
BOOL CXHtmlTree::IsSelected(HTREEITEM hItem)
//=============================================================================
{
	BOOL rc = FALSE;

	if (hItem == GetSelectedItem())
		rc = TRUE;

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::IsEnabled(HTREEITEM hItem)
//=============================================================================
{
	BOOL rc = FALSE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->bEnabled;
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::IsExpanded(HTREEITEM hItem)
//=============================================================================
{
	BOOL rc = FALSE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->bExpanded && ItemHasChildren(hItem);
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::IsSeparator(HTREEITEM hItem)			//+++1.6
//=============================================================================
{
	BOOL rc = FALSE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->bSeparator;
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::GetItemPath(HTREEITEM hItem, CStringArray& sa, CPtrArray& items)
//=============================================================================
{
	BOOL rc = FALSE;

	sa.RemoveAll();
	items.RemoveAll();

	if (hItem == NULL)
		hItem = GetRootItem();

	if (hItem)
	{
		CStringArray path;
		CPtrArray htreeitems;

		// get the path in reverse order
		while (hItem)
		{
			CString strText = GetItemText(hItem);

#ifdef XHTMLHTML
			// remove html tags
			CXHtmlDraw hd;
			TCHAR s[200];
			hd.GetPlainText(strText, s, sizeof(s)/sizeof(TCHAR)-1);
			strText = s;
#endif // XHTMLHTML
			path.Add(strText);
			htreeitems.Add(hItem);
			hItem = GetParentItem(hItem);
		}

		int n = (int) path.GetSize();
		if (n)
		{
			// return path in correct order
			for (int i = n-1; i >= 0 ; i--)
			{
				sa.Add(path[i]);
				items.Add(htreeitems[i]);
			}

			rc = TRUE;
		}
	}

	return rc;
}

//=============================================================================
int CXHtmlTree::GetDefaultTipWidth()
//=============================================================================
{
	int nWidth = 200;

	if (m_nDefaultTipWidth == 0)
	{
		// no default width specified, use a heuristic
		CWnd *pWnd = GetParent();
		if (!pWnd)
			pWnd = GetOwner();

		if (pWnd && ::IsWindow(pWnd->m_hWnd))
		{
			CRect rectParent;
			pWnd->GetWindowRect(&rectParent);
			CRect rectTree;
			GetWindowRect(&rectTree);
			int nWidthTree = (3 * rectTree.Width()) / 4;
			int nWidthParent = rectParent.Width() / 2;
			nWidth = (nWidthTree < 200) ? nWidthParent : nWidthTree;
		}
	}
	else
	{
		nWidth = m_nDefaultTipWidth;
	}

	return nWidth;
}

//=============================================================================
void CXHtmlTree::CreateToolTipsForTree()
//=============================================================================
{
	if ((m_pToolTip == 0) || (!IsWindow(m_pToolTip->m_hWnd)))
		return;

#ifdef XHTMLTOOLTIPS
	m_pToolTip->SetNotify(TRUE);
#endif // XHTMLTOOLTIPS

	m_pToolTip->SetMaxTipWidth(GetDefaultTipWidth());

	// first delete all existing tools
	int nCount = m_nToolCount; //m_pToolTip->GetToolCount();
	for (int j = 0; j < nCount; j++)
		m_pToolTip->DelTool(this, TOOLTIP_BASE_ID+j);
	m_nToolCount = 0;

	CRect rect; 
	GetClientRect(rect);

	CRect rectItem;
	GetItemRect(GetFirstVisibleItem(), &rectItem, FALSE);
	ASSERT(!IsBadRect(rectItem));

	rect.top = 0;
	rect.bottom = rect.top + rectItem.Height()-1;
	UINT n = GetVisibleCount();

	// loop to add a tool for each visible item
	UINT i = 0;
	for (i = 0; i < n; i++)
	{
#ifdef XHTMLTOOLTIPS
		PPTOOLTIP_INFO ti;
		ti.nBehaviour = PPTOOLTIP_MULTIPLE_SHOW;
		ti.nIDTool = 123;
		ti.rectBounds = rect;
		ti.sTooltip = "";
		ti.nMask = PPTOOLTIP_MASK_BEHAVIOUR;
		m_pToolTip->AddTool(this, ti);
#else
		m_pToolTip->AddTool(this, LPSTR_TEXTCALLBACK, rect, TOOLTIP_BASE_ID+i);
#endif // XHTMLTOOLTIPS
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + rectItem.Height()-1;
	}
	m_nToolCount = i;

	if (m_pToolTip)
	{
		// allow parent to perform custom initializatio of tooltip
		SendRegisteredMessage(WM_XHTMLTREE_INIT_TOOLTIP, 0, (LPARAM)m_pToolTip);
	}
}

//=============================================================================
// GetNormalImageWidth
// returns:  width - if image is specified
//          -width - TV_NOIMAGE is specified for this item
//               0 - no image list
int CXHtmlTree::GetNormalImageWidth(HTREEITEM hItem)
//=============================================================================
{
	int nWidth = 0;

	CImageList *pImageList = GetImageList(TVSIL_NORMAL);

	if (pImageList && hItem)
	{
		// there is an image list
		
		int nImage = TV_NOIMAGE;
		int nSelectedImage = TV_NOIMAGE;
		GetItemImage(hItem, nImage, nSelectedImage);

		IMAGEINFO ii = { 0 };
		if (pImageList->GetImageInfo(0, &ii))	// use first image width
		{
			nWidth = ii.rcImage.right - ii.rcImage.left;
		}

		if (nImage == TV_NOIMAGE)
			nWidth = -nWidth;
	}

	return nWidth;
}

//=============================================================================
BOOL CXHtmlTree::CreateCheckboxImages()
//=============================================================================
{
	CDC *pDC = GetDC();
	ASSERT(pDC);
	BOOL rc = HDCheckboxImageList::CreateCheckboxImageList(pDC, m_StateImage, 
				m_nImageHeight, m_crWindow);
	ReleaseDC(pDC);
	SetImageList(&m_StateImage, TVSIL_STATE);
	return rc;
}

//=============================================================================
int CXHtmlTree::DrawItemText(CDC *pDC, 
							 HTREEITEM hItem, 
							 LPCTSTR lpszText,
							 COLORREF crText, 
							 COLORREF crTextBackground, 
							 COLORREF crBackground, 
							 CRect& rect)
//=============================================================================
{
	ASSERT(pDC);
	ASSERT(hItem);

	if (!pDC || !hItem)
	{
		TRACE(_T("ERROR bad parameters\n"));
		return 0;
	}

	if (IsBadRect(rect))
	{
		return 0;
	}

	int nWidth = 0;

	CRect rectText(rect);

	pDC->FillSolidRect(&rectText, crBackground);

	CString str = lpszText;
	//TRACE(_T("CXHtmlTree::DrawItemText:  crText=%08X  crBkgnd=%08X  <%s> ++++++\n"), crText, crBackground, str);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && !str.IsEmpty())
	{
		UINT uFormat = DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_NOPREFIX;

		CFont *pOldFont = NULL;
		CFont font;

		CFont *pFont = pDC->GetCurrentFont();
		if (pFont)
		{
			LOGFONT lf;
			pFont->GetLogFont(&lf);

			lf.lfWeight    = pXTCD->ds.bBold ? FW_BOLD : FW_NORMAL;
			lf.lfUnderline = (BYTE) pXTCD->ds.bUnderline;
			lf.lfItalic    = (BYTE) pXTCD->ds.bItalic;
			lf.lfStrikeOut = (BYTE) pXTCD->ds.bStrikeThrough;

			font.CreateFontIndirect(&lf);
			pOldFont = pDC->SelectObject(&font);
		}

		pDC->SetTextColor(crText);
		if (crTextBackground == COLOR_NONE)
			pDC->SetBkColor(crBackground);
		else
			pDC->SetBkColor(crTextBackground);

		CRect rectOut(rectText);
		pDC->DrawText(str, &rectOut, uFormat | DT_CALCRECT);
		pDC->DrawText(str, &rectOut, uFormat);
		rectOut.InflateRect(m_nPadding, 0);
		nWidth = rectOut.right;

		pXTCD->ds.nRightX = rectOut.right;

		if (pOldFont)
			pDC->SelectObject(pOldFont);
	}

	return nWidth;
}

#ifdef XHTMLHTML
//=============================================================================
int CXHtmlTree::DrawItemTextHtml(CDC *pDC, 
								 HTREEITEM hItem, 
								 LPCTSTR lpszText,
								 COLORREF crText, 
								 COLORREF crTextBackground, 
								 COLORREF crBackground,
								 COLORREF crAnchorText, 
								 CRect& rect)
//=============================================================================
{
	ASSERT(pDC);
	ASSERT(hItem);

	if (!pDC || !hItem)
	{
		TRACE(_T("ERROR bad parameters\n"));
		return 0;
	}

	if (IsBadRect(rect))
	{
		return 0;
	}

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (!pXTCD)
	{
		TRACE(_T("ERROR no XHTMLTREEDATA\n"));
		return 0;
	}

	COLORREF crTextOld, crTextBackgroundOld, crBackgroundOld, crAnchorTextOld;

	crTextOld = pXTCD->ds.crText;
	crTextBackgroundOld = pXTCD->ds.crTextBackground;
	crBackgroundOld = pXTCD->ds.crBackground;
	crAnchorTextOld = pXTCD->ds.crAnchorText;

	pXTCD->ds.crText         = crText;
	pXTCD->ds.crTextBackground   = crTextBackground;
	pXTCD->ds.crBackground   = crBackground;
	pXTCD->ds.crAnchorText   = crAnchorText;
	pXTCD->ds.rect           = rect;
	pXTCD->ds.bUseEllipsis   = FALSE;

	if (m_bLogFont)
	{
		pXTCD->ds.bLogFont = TRUE;
		memcpy(&pXTCD->ds.lf, &m_lf, sizeof(LOGFONT));
	}

	CString strText = lpszText;//GetItemText(hItem);
	TRACE(_T("in CXHtmlTree::DrawItemTextHtml: <%s> crText=%06X  crBk=%06X\n"), strText, crText, crBackground);

	CXHtmlDraw htmldraw;

	int nWidth = htmldraw.Draw(pDC->m_hDC, strText, &pXTCD->ds, hItem == m_hAnchorItem);

	pXTCD->ds.crText = crTextOld;
	pXTCD->ds.crTextBackground = crTextBackgroundOld;
	pXTCD->ds.crBackground = crBackgroundOld;
	pXTCD->ds.crAnchorText = crAnchorTextOld;

	return nWidth;
}
#endif // XHTMLHTML

//=============================================================================
int CXHtmlTree::DrawSeparator(CDC *pDC,						//+++1.6
							  HTREEITEM hItem, 
							  COLORREF crText, 
							  COLORREF crBackground, 
							  CRect& rect)
//=============================================================================
{
	ASSERT(pDC);
	ASSERT(hItem);

	if (!pDC || !hItem)
	{
		TRACE(_T("ERROR bad parameters\n"));
		return 0;
	}

	if (IsBadRect(rect))
	{
		return 0;
	}

	int nWidth = 0;

	CRect rectSep(rect);
	pDC->FillSolidRect(&rectSep, crBackground);

	//TRACE(_T("CXHtmlTree::DrawItemText:  crText=%08X  crBkgnd=%08X  <%s> ++++++\n"), crText, crBackground, str);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		CPen pen(PS_SOLID, 1, crText);
		CPen * pOldPen = pDC->SelectObject(&pen);

		TRACE(_T("drawing separator\n"));

		rectSep.right -= 1;
		rectSep.left  -= 2;
		rectSep.top   += rectSep.Height()/2;

		pDC->MoveTo(rectSep.left, rectSep.top);
		pDC->LineTo(rectSep.right, rectSep.top);

		pDC->SelectObject(pOldPen);

		nWidth = rectSep.right;

		pXTCD->ds.nRightX = rectSep.right;
	}

	return nWidth;
}

//=============================================================================
void CXHtmlTree::OnDestroy()
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnDestroy\n"));

	DeleteMap();
	CTreeCtrl::OnDestroy();
}

//=============================================================================
void CXHtmlTree::DeleteMap()
//=============================================================================
{
	BOOL bOldDestroyingTree = m_bDestroyingTree;
	m_bDestroyingTree = TRUE;
	int n = (int)m_DataMap.GetCount();
	POSITION pos = m_DataMap.GetStartPosition();
	HTREEITEM hItem = 0;
	XHTMLTREEDATA *pXTCD = NULL;

	if (n > 0)
	{
		do
		{
			m_DataMap.GetNextAssoc(pos, hItem, pXTCD);

			if (hItem && pXTCD)
				delete pXTCD;

			n--;
		} while (pos != NULL);
	}

	ASSERT(n == 0);

	m_DataMap.RemoveAll();

	m_bDestroyingTree = bOldDestroyingTree;
}

//=============================================================================
// GetNextItem - Get next item in sequence (as if tree was completely expanded)
//   see http://www.codeguru.com/Cpp/controls/treeview/treetraversal/article.php/c645
//   hItem   - The reference item
//   Returns - The item immediately below the reference item
HTREEITEM CXHtmlTree::GetNextItem(HTREEITEM hItem)
//=============================================================================
{
	HTREEITEM hItemNext = NULL;

	ASSERT(hItem);

	if (hItem)
	{
		if (ItemHasChildren(hItem))
		{
			hItemNext = GetChildItem(hItem);	// first child
		}

		if (hItemNext == NULL)
		{
			// return next sibling item - go up the tree to find 
			// a parent's sibling if needed.
			while ((hItemNext = GetNextSiblingItem(hItem)) == NULL)
			{
				if ((hItem = GetParentItem(hItem)) == NULL)
					return NULL;
			}
		}
	}

	return hItemNext;
}

//=============================================================================
// GetNextItem  - Get previous item as if outline was completely expanded
// Returns      - The item immediately above the reference item
// hItem        - The reference item
HTREEITEM CXHtmlTree::GetPrevItem(HTREEITEM hItem)
//=============================================================================
{
	HTREEITEM hItemPrev;

	hItemPrev = GetPrevSiblingItem(hItem);
	if (hItemPrev == NULL)
		hItemPrev = GetParentItem(hItem);
	else
		hItemPrev = GetLastItem(hItemPrev);
	return hItemPrev;
}

//=============================================================================
// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine
HTREEITEM CXHtmlTree::GetLastItem(HTREEITEM hItem)
//=============================================================================
{
	// Last child of the last child of the last child ...
	HTREEITEM hItemNext;
	
	if (hItem == NULL)
	{
		// Get the last item at the top level
		hItemNext = GetRootItem();
		while (hItemNext)
		{
			hItem = hItemNext;
			hItemNext = GetNextSiblingItem(hItemNext);
		}
	}
	
	while (ItemHasChildren(hItem))
	{
		hItemNext = GetChildItem(hItem);
		while (hItemNext)
		{
			hItem = hItemNext;
			hItemNext = GetNextSiblingItem(hItemNext);
		}
	}
	
	return hItem;
}

//=============================================================================
// FindItem  - Finds an item that contains the search string
//
// http://www.codeguru.com/cpp/controls/treeview/treetraversal/article.php/c673/
//
// Returns        - Handle to the item or NULL
//
// str            - String to search for
// bCaseSensitive - Should the search be case sensitive
// bDownDir       - Search direction - TRUE for down
// bWholeWord     - True if search should match whole words
// hItem          - Item to start searching from. NULL for
//                  currently selected item
HTREEITEM CXHtmlTree::FindItem(CString &str, 
							   BOOL bCaseSensitive /*= FALSE*/, 
							   BOOL bDownDir /*= TRUE*/, 
							   BOOL bWholeWord /*= FALSE*/, 
							   BOOL bWrap /* = TRUE */,
							   HTREEITEM hItem /*= NULL*/)
//=============================================================================
{
	int lenSearchStr = str.GetLength();
	if (lenSearchStr == 0) 
		return NULL;

	HTREEITEM hItemSel = hItem ? hItem : GetSelectedItem();
	HTREEITEM hItemCur = bDownDir ? GetNextItem(hItemSel) : GetPrevItem(hItemSel);
	CString sSearch = str;

	if (hItemCur == NULL)
	{
		if (bDownDir)  
			hItemCur = GetRootItem();
		else 
			hItemCur = GetLastItem(NULL);
	}

	if (!bCaseSensitive)
		sSearch.MakeLower();

	while (hItemCur && (hItemCur != hItemSel))
	{
		CString sItemText = GetItemText(hItemCur);

#ifdef XHTMLHTML

		TCHAR s[200];

		// remove html tags
		CXHtmlDraw hd;
		hd.GetPlainText(sItemText, s, sizeof(s)/sizeof(TCHAR)-1);

		sItemText = s;

#endif // XHTMLHTML

		if (!bCaseSensitive)
			sItemText.MakeLower();

		int n = 0;
		while ((n = sItemText.Find(sSearch)) != -1)
		{
			// search string found
			if (bWholeWord)
			{
				// check preceding char
				if (n != 0)
				{
					if (isalpha(sItemText[n-1]) || 
						sItemText[n-1] == '_')
					{
						// Not whole word
						sItemText = sItemText.Right(sItemText.GetLength() - 
											n - lenSearchStr);
						continue;
					}
				}

				// check succeeding char
				if (sItemText.GetLength() > (n + lenSearchStr) &&
					(isalpha(sItemText[n+lenSearchStr]) ||
					sItemText[n+lenSearchStr] == '_' ))
				{
					// Not whole word
					sItemText = sItemText.Right(sItemText.GetLength() 
									- n - sSearch.GetLength());
					continue;
				}
			}

			if (IsFindValid( hItemCur))
				return hItemCur;
			else 
				break;
		}

		hItemCur = bDownDir ? GetNextItem(hItemCur) : GetPrevItem(hItemCur);

		if ((hItemCur == NULL) && !bWrap)
			break;

		if ((hItemCur == NULL) && (hItemSel != NULL))	// wrap only if there 
														// is a selected item
		{
			if (bDownDir)  
				hItemCur = GetRootItem();
			else 
				hItemCur = GetLastItem(NULL);
		}
	}
	return NULL;
}

//=============================================================================
// IsFindValid	- Virtual function used by FindItem to allow this
//		  function to filter the result of FindItem
// Returns	- True if item matches the criteria
// Arg		- Handle of the item
BOOL CXHtmlTree::IsFindValid(HTREEITEM)
//=============================================================================
{
	return TRUE;
}

//=============================================================================
void CXHtmlTree::RedrawItem(HTREEITEM hItem)
//=============================================================================
{
	if (hItem)
	{
		CRect rect;
		GetItemRect(hItem, &rect, FALSE);
		InvalidateRect(&rect, FALSE);
		UpdateWindow();
	}
}

//=============================================================================
// OnMouseMove - handle link underlining and checkbox hot state
void CXHtmlTree::OnMouseMove(UINT nFlags, CPoint point)
//=============================================================================
{
	// hItem will be non-zero if the cursor is anywhere over a valid item
	UINT flags = 0;
	HTREEITEM hItem = HitTest(point, &flags);

#ifdef XHTMLDRAGDROP

	if (!m_bDragging && !IsLeftButtonUp() && IsSeparator(hItem))
	{
		// we must send TVN_BEGINDRAG to ourself, since separator has no text
		NMTREEVIEW nmtv = { 0 };
	
		nmtv.hdr.hwndFrom = m_hWnd;
		nmtv.hdr.idFrom = GetDlgCtrlID();
		nmtv.hdr.code = TVN_BEGINDRAG;
		nmtv.itemNew.hItem = hItem;

		SendMessage(WM_NOTIFY, 0, (LPARAM)&nmtv);
	}
	else if (m_bDragging)
	{
		CPoint cursor_point(point);
		ClientToScreen(&cursor_point);

		LRESULT lResult = 0;				// allow drop if lResult is 0

		BOOL bCopyDrag = IsDragCopy();

		if (hItem)
		{
			// allow parent to decide whether to permit drag
			XHTMLTREEDRAGMSGDATA dragdata = { 0 };
			dragdata.hItem      = m_hItemButtonDown;
			dragdata.hAfter     = hItem;
			dragdata.bCopyDrag  = bCopyDrag;

			lResult = SendRegisteredMessage(WM_XHTMLTREE_DROP_HOVER, 
				m_hItemButtonDown, (LPARAM)&dragdata);
		}

		// Check to see if the drag is over an item in the tree
		if (hItem && !lResult)
		{
			if (m_hPreviousDropItem != hItem)
			{
				SetDragCursor();

				SetInsertMark(0, 0);	// remove previous insert mark
				TRACE(_T("Drag target item 0x%X\n"), hItem);

				m_hPreviousDropItem = hItem;
				m_dwDropHoverTime = GetTickCount();

				// check if Shift key down
				if (GetBit(m_dwDragOps, XHTMLTREE_DO_SHIFT_KEY) &&
					(GetAsyncKeyState(VK_SHIFT) < 0))
				{
					TRACE(_T("VK_SHIFT down\n"));
					if (IsSeparator(hItem))					//+++1.6
					{
						SelectDropTarget(NULL);
						SetInsertMark(hItem, TRUE);
					}
					else
					{
						SelectDropTarget(hItem);
					}
				}
				else
				{
					SetInsertMark(hItem, TRUE);
					SelectDropTarget(NULL);
				}
			}
		}
		else	// not over an item
		{
			SetInsertMark(0, 0);	// remove insert mark
			m_hPreviousDropItem = 0;
			if (m_hNoDropCursor)
				SetCursor(m_hNoDropCursor);			// set to no-drop cursor
			else
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));		// set to no-drop cursor
		}

		SetFocus();
	}
	else 
		
#endif // XHTMLDRAGDROP
		
	if (hItem)
	{
		// if mouse is on a different item, or has moved off state icon
		if ((m_hHotItem && (m_hHotItem != hItem)) || 
			(m_hHotItem && ((flags & TVHT_ONITEMSTATEICON) == 0)))
		{
			int nState = GetStateImage(m_hHotItem);

			// a hot item can only be UNCHECKED, CHECKED, or CHECKED_TRISTATE

			nState &= ~HDCheckboxImageList::HOT_INDEX;

			// remove hot from previous hot item
			SetItemState(m_hHotItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

			m_hHotItem = NULL;
		}

		if ((m_hHotItem == NULL) && (flags & TVHT_ONITEMSTATEICON))
		{
			TRACE(_T("cursor over state image\n"));
			int nState = GetStateImage(hItem);

			if ((nState & HDCheckboxImageList::DISABLED_INDEX) == 0)		// is it enabled?
			{
				// a hot item can only be UNCHECKED, CHECKED, or CHECKED_TRISTATE

				nState |= HDCheckboxImageList::HOT_INDEX;

				// remove hot from previous hot item
				SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

				m_hHotItem = hItem;
				SetTimer(HOT_TIMER, 100, NULL);		// timer in case mouse leaves window
			}
		}

		CRect rect;
		BOOL bOverAnchor = IsOverAnchor(hItem, point, &rect);
		//TRACE(_T("bOverAnchor=%d\n"), bOverAnchor);

#ifdef XHTMLHTML
		if (bOverAnchor)
			m_Links.SetLinkCursor();
#endif // XHTMLHTML

		if ((m_hAnchorItem && (m_hAnchorItem != hItem)) || 
			(m_hAnchorItem && !bOverAnchor))
		{
			TRACE(_T("removing anchor 0x%X-----\n"), m_hAnchorItem);
			GetItemRect(m_hAnchorItem, &rect, FALSE);	// note:  must get entire
														// rect, since text might
														// be shifted left
			m_hAnchorItem = NULL;
			InvalidateRect(&rect, FALSE);
		}
		else if ((m_hAnchorItem == NULL) && bOverAnchor)
		{
			TRACE(_T("adding anchor 0x%X-----\n"), hItem);

			m_hAnchorItem = hItem;
			TRACE(_T("mouse over anchor 0x%X-----\n"), hItem);
			GetItemRect(hItem, &rect, FALSE);	// note:  must get entire
												// rect, since text might
												// be shifted left
			InvalidateRect(&rect, FALSE);
			SetTimer(HOT_TIMER, 80, NULL);		// timer in case mouse leaves window
		}
	}
	
	CTreeCtrl::OnMouseMove(nFlags, point);
}

//=============================================================================
HTREEITEM CXHtmlTree::IsOverItem(LPPOINT lpPoint /*= NULL*/)
//=============================================================================
{
	CPoint point;
	if (lpPoint)
	{
		point = *lpPoint;
	}
	else
	{
		::GetCursorPos(&point);
		ScreenToClient(&point);
	}
	UINT flags = 0;
	HTREEITEM hItem = HitTest(point, &flags);

	return hItem;
}

//=============================================================================
BOOL CXHtmlTree::IsOverAnchor(HTREEITEM hItem, CPoint point, CRect *pRect /*= NULL*/)
//=============================================================================
{
	BOOL rc = FALSE;

	CRect rect(0,0,0,0);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);
	
	if (pXTCD && pXTCD->ds.bHasAnchor && pXTCD->bEnabled)
	{
		GetItemRect(hItem, &rect, TRUE);

		// set rect to anchor boundaries
		rect.left  = pXTCD->ds.rectAnchor.left;
		rect.right = pXTCD->ds.rectAnchor.right;

		if (rect.PtInRect(point))
		{
			rc = TRUE;
		}
	}

	if (pRect)
		*pRect = rect;

	return rc;
}

//=============================================================================
HCURSOR CXHtmlTree::SetCursor(HCURSOR hCursor)
//=============================================================================
{
	if (hCursor == m_hCurrentCursor)
		return m_hCurrentCursor;

	m_hCurrentCursor = hCursor;

	TRACE(_T("calling ::SetCursor %X\n"), hCursor);

	return ::SetCursor(hCursor);
}

//=============================================================================
BOOL CXHtmlTree::IsLeftButtonUp()
//=============================================================================
{
	BOOL rc = FALSE;

	SHORT state = 0;
	if (GetSystemMetrics(SM_SWAPBUTTON))		// check if buttons have been swapped
		state = GetAsyncKeyState(VK_RBUTTON);	// buttons swapped, get right button state
	else
		state = GetAsyncKeyState(VK_LBUTTON);

	// if the most significant bit is set, the button is down
	if (state >= 0)
		rc = TRUE;

	return rc;
}

//=============================================================================
// OnTimer - check if mouse has left, turn off underlining and hot state
void CXHtmlTree::OnTimer(UINT nIDEvent)
//=============================================================================
{
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	if (nIDEvent == HOT_TIMER)
	{
		// if mouse has left window, turn off hot and anchor highlighting

		CRect rectClient;
		GetClientRect(&rectClient);

		if (!rectClient.PtInRect(point))
		{
			KillTimer(nIDEvent);

			// mouse has left the window

			if (m_hHotItem)
			{
				int nState = GetStateImage(m_hHotItem);

				// a hot item can only be UNCHECKED, CHECKED, or CHECKED_TRISTATE

				nState &= ~HDCheckboxImageList::HOT_INDEX;

				// remove hot from previous hot item
				SetItemState(m_hHotItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

				m_hHotItem = NULL;
			}

			if (m_hAnchorItem)
			{
				// remove underline
				CRect rectAnchor;
				GetItemRect(m_hAnchorItem, &rectAnchor, FALSE);
				m_hAnchorItem = NULL;
				InvalidateRect(&rectAnchor, TRUE);
			}
		}
	}
	else if (nIDEvent == LBUTTONDOWN_TIMER)			// timer set by WM_LBUTTONDOWN
	{
		HTREEITEM hItem = IsOverItem(&point);

		if (IsLeftButtonUp())
		{
			TRACE(_T("mouse button is up >>>>>\n"));

			KillTimer(nIDEvent);

			HTREEITEM hItemSelected = GetSelectedItem();

#ifdef XHTMLDRAGDROP

			if (m_bDragging)				// case 1:  user is dragging
			{
				if (hItem && 
					(hItem != m_hItemButtonDown) && 
					(!IsChildNodeOf(hItem, m_hItemButtonDown)))
				{
					HTREEITEM hAfter = hItem;
					HTREEITEM hParent = GetParentItem(m_hItemButtonDown);
					HTREEITEM hNewParent = GetParentItem(hAfter);
					TRACE(_T("hParent=%X\n"), hParent);

					// check if Shift key down
					if ((m_dwDragOps & XHTMLTREE_DO_SHIFT_KEY) &&
						(GetAsyncKeyState(VK_SHIFT) < 0) &&
						!IsSeparator(hAfter))								//+++1.6
					{
						TRACE(_T("VK_SHIFT down, creating child item\n"));
						hNewParent = hAfter;
						hAfter = TVI_LAST;
					}
					else if (hParent == hAfter)
					{
						// dropping on parent
						hNewParent = hParent;
						hAfter = TVI_FIRST;
					}
					else if (ItemHasChildren(hAfter) && IsExpanded(hAfter))	//+++1.6
					{
						// dropping on node that is expanded
						hNewParent = hAfter;
						hAfter = TVI_FIRST;
					}
					else if (hNewParent == 0)								//+++1.6
					{
						// multiple roots
					}

					StartMoveBranch(m_hItemButtonDown, hNewParent, hAfter);
				}
				else
				{
					TRACE(_T("ERROR can't drop on %X\n"), hItem);
					SendRegisteredMessage(WM_XHTMLTREE_END_DRAG, 0, 0);
				}

				EndDragScroll();
			}
			else 

#endif // XHTMLDRAGDROP
				
			if (hItem && (hItem == hItemSelected)
				&& !IsSeparator(hItem))	// case 2:  user wants to edit a label
			{
				// clicking on a selected item
				CEdit *pEdit = GetEditControl();

				CRect rect;
				GetItemRect(hItem, &rect, TRUE);
				if (rect.PtInRect(point))
				{
					TRACE(_T("sending TVM_EDITLABEL\n"));
					// click on item text, begin edit
					SendMessage(TVM_EDITLABEL, 0, (LPARAM)hItem);
				}
				else if (pEdit && IsWindow(pEdit->m_hWnd))
				{
					TRACE(_T("sending WM_CLOSE to edit box\n"));
					// click outside item text, end edit
					pEdit->SendMessage(WM_CLOSE);
				}
			}
		}

#ifdef XHTMLDRAGDROP

		else		// left button is down
		{
			//TRACE(_T("mouse button is down >>>>>\n"));

			if (m_bDragging)
			{
				// check how long we've been hovering over same item

				if (hItem && (hItem == m_hPreviousDropItem))
				{
					if (GetBit(m_dwDragOps, XHTMLTREE_DO_AUTO_EXPAND))
					{
						// still over same item
						if ((GetTickCount() - m_dwDropHoverTime) > MIN_HOVER_TIME)
						{
							// min hover time has passed, expand node if it has children
							Expand(hItem, TVE_EXPAND);
						}
					}
				}

				if (m_bAutoScroll)
					AutoScroll(hItem);
			}
		}

#endif // XHTMLDRAGDROP

	}

#ifdef XHTMLDRAGDROP

	else if (nIDEvent == CTRL_UP_TIMER)
	{
		// check if Ctrl key down
		if (!IsCtrlDown())
		{
			TRACE(_T("VK_CONTROL up\n"));

			KillTimer(nIDEvent);

			if (IsOverItem() && m_bDragging)
			{
				SetDragCursor();
			}
		}
	}
	else if (nIDEvent == SHIFT_UP_TIMER)
	{
		if ((m_dwDragOps & XHTMLTREE_DO_SHIFT_KEY) &&
			(GetAsyncKeyState(VK_SHIFT) >= 0))
		{
			TRACE(_T("VK_SHIFT up\n"));
			KillTimer(nIDEvent);
			HTREEITEM hItem = IsOverItem();
			if (hItem)
				SetInsertMark(hItem, TRUE);
			SelectDropTarget(NULL);
		}
	}
	else if (nIDEvent == SELECT_TIMER)			// timer set by WM_LBUTTONDOWN
	{
		KillTimer(nIDEvent);
		HTREEITEM hItem = IsOverItem();
		if (hItem)
		{
			SelectItem(hItem);
		}
	}


#endif // XHTMLDRAGDROP

	CTreeCtrl::OnTimer(nIDEvent);
}

//=============================================================================
BOOL CXHtmlTree::OnEraseBkgnd(CDC* pDC)
//=============================================================================
{
	CRect rectClientx;
	GetClientRect(&rectClientx);
	pDC->FillSolidRect(rectClientx, m_crWindow);
	return TRUE;
}

//=============================================================================
CXHtmlTree& CXHtmlTree::SetCheck(HTREEITEM hItem, BOOL fCheck /*= TRUE*/)
//=============================================================================
{
	ASSERT(hItem);

	if (hItem && m_bCheckBoxes)
	{
		TRACE(_T("in CXHtmlTree::SetCheck: %d  <%s>\n"), fCheck, GetItemText(hItem));
		
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD && pXTCD->bEnabled && !pXTCD->bSeparator)		//+++1.6
		{
			BOOL bOldChecked = pXTCD->bChecked;
			pXTCD->bChecked = fCheck;

			UINT nState = GetStateImage(hItem);

			//TRACE(_T("nState=0x%X  nOldState=0x%X ~~~~~\n"), nState, nOldState);

			SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

			if (m_bSmartCheck && (bOldChecked != fCheck))
			{
				HTREEITEM hParent = hItem;
				int nCount = 0;
				if (fCheck)
					nCount = pXTCD->nChildren - pXTCD->nChecked + 1;//bOldCheck ? 1 : 0;
				else
					nCount = -(pXTCD->nChecked + 1);//bOldCheck ? 1 : 0);

				SetCheckChildren(hItem, fCheck);

				// find all parents, adjust their checked counts
				TRACE(_T("starting nCount=%d\n"), nCount);
				while ((hParent = GetParentItem(hParent)) != NULL)
				{
					nCount = SetCheckParent(hParent, nCount);
				}
			}

			SendRegisteredMessage(WM_XHTMLTREE_CHECKBOX_CLICKED, hItem, fCheck);
		}
	}

	return *this;
}

//=============================================================================
void CXHtmlTree::SetHotItem(HTREEITEM hItem, UINT nFlags)
//=============================================================================
{
	if (m_hHotItem && (m_hHotItem != hItem))
	{
		int nState = GetStateImage(m_hHotItem);

		// a hot item can only be UNCHECKED, CHECKED, or CHECKED_TRISTATE

		nState &= ~HDCheckboxImageList::HOT_INDEX;

		// remove hot from previous hot item
		SetItemState(m_hHotItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

		m_hHotItem = NULL;
	}

	if (hItem && (m_hHotItem == NULL) && (nFlags & TVHT_ONITEMSTATEICON))
	{
		TRACE(_T("cursor over state image\n"));
		int nState = GetStateImage(hItem);

		// a hot item can only be UNCHECKED, CHECKED, or CHECKED_TRISTATE

		nState |= HDCheckboxImageList::HOT_INDEX;

		// remove hot from previous hot item
		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

		m_hHotItem = hItem;
	}
}

//=============================================================================
LRESULT CXHtmlTree::SendRegisteredMessage(UINT nMessage, 
									   HTREEITEM hItem, 
									   LPARAM lParam /*= 0*/)
//=============================================================================
{
	LRESULT lResult = 0;

	CWnd *pWnd = GetParent();
	if (!pWnd)
		pWnd = GetOwner();

	if (pWnd && ::IsWindow(pWnd->m_hWnd))
	{
		XHTMLTREEMSGDATA msgdata = { 0 };
		msgdata.hCtrl    = m_hWnd;
		msgdata.nCtrlId  = GetDlgCtrlID();
		msgdata.hItem    = hItem;

		lResult = pWnd->SendMessage(nMessage, (WPARAM)&msgdata, lParam);
	}

	return lResult;
}

//=============================================================================
int CXHtmlTree::GetStateImage(HTREEITEM hItem)
//=============================================================================
{
	int nState = 0;

	ASSERT(hItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		if (m_bSmartCheck && (pXTCD->nChildren != 0))
		{
			if (pXTCD->nChecked == 0)
				nState = UNCHECKED;
			else if (pXTCD->nChecked == (pXTCD->nChildren - pXTCD->nSeparators))	//+++1.6
				nState = CHECKED;
			else
				nState = TRISTATE;
		}
		else
		{
			if (pXTCD->bChecked)
				nState = CHECKED;
			else
				nState = UNCHECKED;
		}
		if (!pXTCD->bEnabled)
			nState |= HDCheckboxImageList::DISABLED_INDEX;
	}

	TRACE(_T("GetStateImage returning %d ~~~~~\n"), nState);

	return nState;
}

//=============================================================================
int CXHtmlTree::SetCheckParent(HTREEITEM hItem, int nCount)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::SetCheckParent:  nCount=%d  <%s>\n"), nCount, GetItemText(hItem));
	ASSERT(hItem);

	int nState = 0;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		TRACE(_T("pXTCD->nChecked=%d  pXTCD->nChildren=%d \n"), pXTCD->nChecked, pXTCD->nChildren);
		pXTCD->nChecked += nCount;
		if (pXTCD->nChecked < 0)
			pXTCD->nChecked = 0;

		BOOL bOldCheck = pXTCD->bChecked;
		if (pXTCD->nChecked == (pXTCD->nChildren - pXTCD->nSeparators))	//+++1.6
			pXTCD->bChecked = TRUE;
		else
			pXTCD->bChecked = FALSE;

		if (pXTCD->bChecked != bOldCheck)
			nCount += pXTCD->bChecked ? 1 : -1;

		nState = GetStateImage(hItem);

		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

		TRACE(_T("nState=%d\n"), nState);
	}

	return nCount;
}

//=============================================================================
CXHtmlTree& CXHtmlTree::SetCheckChildren(HTREEITEM hItem, BOOL fCheck)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::SetCheckChildren\n"));

	// first set item state for this item
	SetItemStateChildren(hItem, fCheck);

	HTREEITEM hNext = GetChildItem(hItem);
	
	// loop to set item state for children
	while (hNext)
	{
		TRACE(_T("SetCheckChildren: %d  <%s>\n"), fCheck, GetItemText(hNext));

		// recurse into children
		if (ItemHasChildren(hNext))
			SetCheckChildren(hNext, fCheck);

		SetItemStateChildren(hNext, fCheck);

		hNext = GetNextItem(hNext, TVGN_NEXT);
	}

	return *this;
}

//=============================================================================
CXHtmlTree& CXHtmlTree::SetItemStateChildren(HTREEITEM hItem, BOOL fCheck)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::SetItemStateChildren\n"));

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && pXTCD->bEnabled)
	{
		int nState = GetStateImage(hItem);
		if (pXTCD->bSeparator)				//+++1.6
		{
			nState = 0;
		}
		else
		{
			int nStateHot = nState & HDCheckboxImageList::HOT_INDEX;			// save hot
			int nStateDisabled = nState & HDCheckboxImageList::DISABLED_INDEX;	// save disabled
			nState &= ~(HDCheckboxImageList::HOT_INDEX | 
						HDCheckboxImageList::DISABLED_INDEX);	// remove hot & disabled

			pXTCD->bChecked = fCheck;

			if (fCheck)
			{
				pXTCD->nChecked = pXTCD->nChildren - pXTCD->nSeparators;	//+++1.6
				if (pXTCD->nChecked < 0)
					pXTCD->nChecked = 0;
				nState = CHECKED;
			}
			else
			{
				pXTCD->nChecked = 0;
				nState = UNCHECKED;
			}

			nState |= nStateHot;		// restore hot
			nState |= nStateDisabled;	// restore disabled
			TRACE(_T("setting state to %d\n"), nState);
		}
		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);
	}

	return *this;
}

//=============================================================================
BOOL CXHtmlTree::EnableItem(HTREEITEM hItem, BOOL bEnabled)
//=============================================================================
{
	BOOL rc = TRUE;

	ASSERT(hItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->bEnabled;

		pXTCD->bEnabled = bEnabled;

		int nState = GetStateImage(hItem);

		if (bEnabled)
			nState &= ~HDCheckboxImageList::DISABLED_INDEX;
		else
			nState |= HDCheckboxImageList::DISABLED_INDEX;

		// set enabled state
		SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::EnableBranch(HTREEITEM hItem, BOOL bEnabled)
//=============================================================================
{
	BOOL rc = TRUE;

	if (hItem && !IsSeparator(hItem))	//+++1.6
	{
		rc = EnableItem(hItem, bEnabled);

		hItem = GetChildItem(hItem);

		if (hItem)
		{
			do
			{
				EnableBranch(hItem, bEnabled);

			} while ((hItem = GetNextSiblingItem(hItem)) != NULL);
		}
	}

	return rc;	// return state of first item
}

//=============================================================================
BOOL CXHtmlTree::GetCheck(HTREEITEM hItem)
//=============================================================================
{
	BOOL rc = FALSE;

	ASSERT(hItem);

	if (m_bCheckBoxes && hItem)
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			if (m_bSmartCheck)
			{
				if (pXTCD->nChildren == 0)
				{
					rc = pXTCD->bChecked;
				}
				else
				{
					if (pXTCD->nChecked == 0)
						rc = FALSE;		// no children are checked
					else if (pXTCD->nChecked == (pXTCD->nChildren - pXTCD->nSeparators))	//+++1.6
						rc = TRUE;		// all children are checked
					else
						rc = FALSE;		// not all children are checked
				}
			}
			else
			{
				rc = pXTCD->bChecked;
			}
		}
	}

	return rc;
}

//=============================================================================
HTREEITEM CXHtmlTree::GetFirstCheckedItem()
//=============================================================================
{
	if (m_bCheckBoxes)
	{
		for (HTREEITEM hItem = GetRootItem(); 
			 hItem != NULL; 
			 hItem = GetNextItem(hItem))
		{
			if (GetCheck(hItem))
				return hItem;
		}
	}

	return NULL;
}

//=============================================================================
HTREEITEM CXHtmlTree::GetNextCheckedItem(HTREEITEM hItem)
//=============================================================================
{
	if (m_bCheckBoxes)
	{
		for (hItem = GetNextItem(hItem); 
			 hItem != NULL; 
			 hItem = GetNextItem(hItem))
		{
			if (GetCheck(hItem))
				return hItem;
		}
	}

	return NULL;
}

//=============================================================================
HTREEITEM CXHtmlTree::GetPrevCheckedItem(HTREEITEM hItem)
//=============================================================================
{
	if (m_bCheckBoxes)
	{
		for (hItem = GetPrevItem(hItem); 
			 hItem != NULL; 
			 hItem = GetPrevItem(hItem))
		{
			if (GetCheck(hItem))
				return hItem;
		}
	}

	return NULL;
}

//=============================================================================
BOOL CXHtmlTree::DeleteItem(HTREEITEM hItem)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::DeleteItem\n"));
	BOOL bOldDestroyingTree = m_bDestroyingTree;

	if (hItem && ItemHasChildren(hItem))
	{
		DeleteBranch(hItem);
	}
	else if (hItem)
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			if (pXTCD->bChecked)
				m_nDeletedChecked++;

			HTREEITEM hParent = hItem;

			// find all parents, decrement their children counts,
			// adjust their checked counts and separator counts
			while ((hParent = GetParentItem(hParent)) != NULL)
			{
				IncrementChildren(hParent, -1);
				if (pXTCD->bChecked)
					SetCheckParent(hParent, -1);
				if (pXTCD->bSeparator)					//+++1.6
					IncrementSeparators(hParent, -1);
			}

			m_bDestroyingTree = TRUE;
			m_DataMap.RemoveKey(hItem);
			delete pXTCD;
		}
	}

	m_bDestroyingTree = bOldDestroyingTree;

	m_nDeleted++;

	return CTreeCtrl::DeleteItem(hItem);
}

//=============================================================================
void CXHtmlTree::DeleteBranch(HTREEITEM hItem)
//=============================================================================
{
	if (hItem)
	{
		HTREEITEM hChild = GetChildItem(hItem);
		while (hChild)
		{
			// recursively delete all the items
			HTREEITEM hNext = GetNextSiblingItem(hChild);
			DeleteBranch(hChild);
			hChild = hNext;
		}
		DeleteItem(hItem);
	}
}

//=============================================================================
CString CXHtmlTree::GetItemNote(HTREEITEM hItem, BOOL bStripHtml /*= FALSE*/)
//=============================================================================
{
	CString strNote = _T("");

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && pXTCD->pszNote)
	{
		strNote = pXTCD->pszNote;

		if (bStripHtml)
		{
#ifdef XHTMLHTML
			// remove html tags
			CXHtmlDraw hd;
			int n = strNote.GetLength();
			if (n > 3)		// minimum html string
			{
				TCHAR *s = new TCHAR [n + 16];
				hd.GetPlainText(strNote, s, n+4);
				strNote = s;
				delete [] s;
			}
#endif // XHTMLHTML
		}
	}

	return strNote;
}

//=============================================================================
int CXHtmlTree::GetItemNoteWidth(HTREEITEM hItem)
//=============================================================================
{
	int nWidth = 0;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && pXTCD->pszNote)
	{
		nWidth = pXTCD->nTipWidth;
	}

	return nWidth;
}

//=============================================================================
CXHtmlTree& CXHtmlTree::SetItemNote(HTREEITEM hItem, 
									LPCTSTR lpszNote, 
									int nTipWidth /*= 0*/)
//=============================================================================
{
	ASSERT(hItem);
	ASSERT(lpszNote);

	if (hItem && lpszNote)
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			if (pXTCD->pszNote)
				delete [] pXTCD->pszNote;
			pXTCD->pszNote = NULL;

			size_t len = _tcslen(lpszNote);
			pXTCD->pszNote = new TCHAR [len + 4];
			if (pXTCD->pszNote)
			{
				memset(pXTCD->pszNote, 0, len+4);
				_tcsncpy(pXTCD->pszNote, lpszNote, len+1);
				pXTCD->nTipWidth = nTipWidth;
			}
		}
	}

	return *this;
}

//=============================================================================
HTREEITEM CXHtmlTree::InsertItem(LPTVINSERTSTRUCT lpInsertStruct, 
								 XHTMLTREEDATA * pData /*= NULL*/)
//=============================================================================
{
	XHTMLTREEDATA *pXTCD = new XHTMLTREEDATA;
	ASSERT(pXTCD);
	if (!pXTCD)
	{
		ASSERT(FALSE);
		return 0;
	}

	if (pData)
	{
		// copy user items for XHTMLTREEDATA
		pXTCD->bChecked   = pData->bChecked;
		pXTCD->bEnabled   = pData->bEnabled;
		pXTCD->bSeparator = pData->bSeparator;	//+++1.6
	
		// copy user items for XHTMLDRAWSTRUCT
		pXTCD->ds.crText           = pData->ds.crText;
		pXTCD->ds.crAnchorText     = pData->ds.crAnchorText;
		pXTCD->ds.crBackground     = pData->ds.crBackground;
		pXTCD->ds.crTextBackground = pData->ds.crTextBackground;
		pXTCD->ds.bIgnoreColorTag  = pData->ds.bIgnoreColorTag;
		pXTCD->ds.bTransparent     = pData->ds.bTransparent;
		pXTCD->ds.bBold            = pData->ds.bBold;
		pXTCD->ds.bItalic          = pData->ds.bItalic;
		pXTCD->ds.bUnderline       = pData->ds.bUnderline;
		pXTCD->ds.bStrikeThrough   = pData->ds.bStrikeThrough;
		pXTCD->ds.bUseEllipsis     = pData->ds.bUseEllipsis;
		pXTCD->ds.bLogFont         = pData->ds.bLogFont;
		pXTCD->ds.uFormat          = pData->ds.uFormat;
		pXTCD->ds.lf               = pData->ds.lf;
	}

	pXTCD->hTreeCtrl = m_hWnd;

	TVINSERTSTRUCT tvis;
	memcpy(&tvis, lpInsertStruct, sizeof(TVINSERTSTRUCT));

	if (!m_bImages)
	{
		tvis.item.iImage = TV_NOIMAGE;
		tvis.item.iSelectedImage = TV_NOIMAGE;	//+++1.5
	}

	tvis.item.mask |= TVIF_STATE;
	int nState = UNCHECKED;
	if (pXTCD->bChecked && m_bCheckBoxes)
		nState = CHECKED;
	if (!pXTCD->bEnabled)
		nState |= HDCheckboxImageList::DISABLED_INDEX;
	tvis.item.state = INDEXTOSTATEIMAGEMASK(nState);
	tvis.item.stateMask = TVIS_STATEIMAGEMASK;

	CString strText = tvis.item.pszText;

	if (m_bStripHtml)
	{
#ifdef XHTMLHTML
		// remove html tags
		CXHtmlDraw hd;
		int n = strText.GetLength();
		if (n > 3)		// minimum html string
		{
			TCHAR *s = new TCHAR [n + 16];
			hd.GetPlainText(strText, s, n+4);
			strText = s;
			delete [] s;
		}
#endif // XHTMLHTML
	}

	TRACE(_T("inserting <%s>\n"), strText);

	tvis.item.pszText = strText.LockBuffer();

	HTREEITEM hItem = CTreeCtrl::InsertItem(&tvis);
	ASSERT(hItem);

	strText.UnlockBuffer();

	if (hItem)
	{
		m_DataMap.SetAt(hItem, pXTCD);
		TRACE(_T("count=%d\n"), m_DataMap.GetCount());

		if (m_bSmartCheck)
		{
			HTREEITEM hParent = hItem;

			// find all parents, increment their children counts,
			// adjust their checked counts
			int nCount = pXTCD->bChecked ? 1 : 0;
			while ((hParent = GetParentItem(hParent)) != NULL)
			{
				IncrementChildren(hParent);
				nCount = SetCheckParent(hParent, nCount);
			}
		}
	}

	return hItem;
}

//=============================================================================
HTREEITEM CXHtmlTree::InsertItem(UINT nMask, 
								 LPCTSTR lpszItem, 
								 int nImage, 
								 int nSelectedImage, 
								 UINT nState, 
								 UINT nStateMask, 
								 LPARAM lParam, 
								 HTREEITEM hParent, 
								 HTREEITEM hInsertAfter)
//=============================================================================
{
	TVINSERTSTRUCT tvis = { 0 };

	tvis.item.mask = nMask;
	tvis.item.pszText = (LPTSTR)lpszItem;
	tvis.item.iImage = nImage;
	tvis.item.iSelectedImage = nSelectedImage;
	tvis.item.state = nState;
	tvis.item.stateMask = nStateMask;
	tvis.item.lParam = lParam;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;

	return InsertItem(&tvis);
}

//=============================================================================
HTREEITEM CXHtmlTree::InsertItem(LPCTSTR lpszItem, 
								 HTREEITEM hParent /*= TVI_ROOT*/, 
								 HTREEITEM hInsertAfter /*= TVI_LAST*/)
//=============================================================================
{
	TVINSERTSTRUCT tvis = { 0 };

	tvis.item.mask = TVIF_TEXT;
	tvis.item.pszText = (LPTSTR)lpszItem;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;

	return InsertItem(&tvis);
}

//=============================================================================
HTREEITEM CXHtmlTree::InsertItem(LPCTSTR lpszItem, 
								 int nImage, 
								 int nSelectedImage, 
								 HTREEITEM hParent /*= TVI_ROOT*/, 
								 HTREEITEM hInsertAfter /*= TVI_LAST*/)
//=============================================================================
{
	TVINSERTSTRUCT tvis = { 0 };

	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvis.item.pszText = (LPTSTR)lpszItem;
	tvis.item.iImage = nImage;
	tvis.item.iSelectedImage = nSelectedImage;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;

	return InsertItem(&tvis);
}

//=============================================================================
HTREEITEM CXHtmlTree::InsertSeparator(HTREEITEM hItem)	//+++1.6
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::InsertSeparator\n"));

	HTREEITEM hAfter = hItem;
	HTREEITEM hParent = GetParentItem(hItem);
	HTREEITEM hNewParent = GetParentItem(hItem);
	TRACE(_T("hParent=%X\n"), hParent);

	if (hParent == hAfter)
	{
		// dropping on parent
		hNewParent = hParent;
		hAfter = TVI_FIRST;
	}
	else if (ItemHasChildren(hAfter) && IsExpanded(hAfter))
	{
		// dropping on node that is expanded
		hNewParent = hAfter;
		hAfter = TVI_FIRST;
	}

	TVINSERTSTRUCT tvis = { 0 };
	tvis.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvis.item.pszText = _T("");
	tvis.item.iImage = TV_NOIMAGE;
	tvis.item.iSelectedImage = TV_NOIMAGE;
	tvis.hParent = hNewParent;
	tvis.hInsertAfter = hAfter;

	HTREEITEM hSep = InsertItem(&tvis);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hSep);

	if (pXTCD)
	{
		pXTCD->bSeparator = TRUE;
		//SetItemTextColor(hSep, RGB(255,0,0));
	}

	SetItemState(hSep, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);

	// increment separator count in parents
	hParent = hSep;
	while ((hParent = GetParentItem(hParent)) != NULL)
	{
		IncrementSeparators(hParent, 1);
	}

	return hSep;
}

//=============================================================================
int CXHtmlTree::IncrementChildren(HTREEITEM hItem, int n /*= 1*/)
//=============================================================================
{
	int nChildren = 0;

	ASSERT(hItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		pXTCD->nChildren += n;
		if (pXTCD->nChildren < 0)
			pXTCD->nChildren = 0;
		nChildren = pXTCD->nChildren;
	}

	return nChildren;
}

//=============================================================================
int CXHtmlTree::IncrementSeparators(HTREEITEM hItem, int n /*= 1*/)		//+++1.6
//=============================================================================
{
	int nSeparators = 0;

	ASSERT(hItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		pXTCD->nSeparators += n;
		if (pXTCD->nSeparators < 0)
			pXTCD->nSeparators = 0;
		nSeparators = pXTCD->nSeparators;
	}

	return nSeparators;
}

//=============================================================================
XHTMLTREEDATA * CXHtmlTree::GetItemDataStruct(HTREEITEM hItem)
//=============================================================================
{
	XHTMLTREEDATA *pXTCD = NULL;

	if (hItem && !m_bDestroyingTree)
	{
		m_DataMap.Lookup(hItem, pXTCD);
	}

	return pXTCD;
}

#ifdef XHTMLTOOLTIPS

//=============================================================================
// OnDisplayTooltip - display CPPToolTip
void CXHtmlTree::OnDisplayTooltip(NMHDR * pNMHDR, LRESULT * pResult)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnDisplayTooltip\n"));
	*pResult = 0;

	NM_PPTOOLTIP_DISPLAY * pNotify = (NM_PPTOOLTIP_DISPLAY*)pNMHDR;

	CString strToolTip = _T("");

	if (PreDisplayToolTip(FALSE, strToolTip))
	{
		// no limitation on text length
		
		TRACE(_T("setting tooltip to <%s>\n"), strToolTip);

		// change the tooltip's text
		pNotify->ti->sTooltip = strToolTip;
	}
}

#else


//=============================================================================
BOOL CXHtmlTree::OnToolTipText(UINT /*id*/, NMHDR * pNMHDR, LRESULT * pResult)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnToolTipText\n"));

	UINT nID = (UINT)pNMHDR->idFrom;
	
	// check if this is the automatic tooltip of the control
	if (nID == 0) 
		return TRUE;	// do not allow display of automatic tooltip,
						// or our tooltip will disappear
	
	// handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
	*pResult = 0;
	
	CString strToolTip = _T("");

	if (PreDisplayToolTip(TRUE, strToolTip))
	{
		// copy item text (up to 80 characters worth, limitation 
		// of the TOOLTIPTEXT structure) into the TOOLTIPTEXT 
		// structure's szText member
		
		strToolTip = strToolTip.Mid(0, sizeof(pTTTA->szText)-2);

#ifndef _UNICODE
		if (pNMHDR->code == TTN_NEEDTEXTA)
			lstrcpyn(pTTTA->szText, strToolTip, sizeof(pTTTA->szText));
		else
			_mbstowcsz(pTTTW->szText, strToolTip, sizeof(pTTTW->szText)/sizeof(TCHAR));
#else
		if (pNMHDR->code == TTN_NEEDTEXTA)
			_wcstombsz(pTTTA->szText, strToolTip, sizeof(pTTTA->szText));
		else
			lstrcpyn(pTTTW->szText, strToolTip, sizeof(pTTTW->szText)/sizeof(TCHAR));
#endif // _UNICODE
	}

	return FALSE;	// we didn't handle the message, let the 
					// framework continue propagating the message
}

#endif  // XHTMLTOOLTIPS

//=============================================================================
// PreDisplayToolTip - returns TRUE if tooltip should be displayed
BOOL CXHtmlTree::PreDisplayToolTip(BOOL bAlwaysRemoveHtml, CString& strToolTip)
//=============================================================================
{
	BOOL rc = FALSE;

	if (m_bDragging)
		return rc;

	strToolTip = _T("");

	// get the mouse position
	const MSG* pMessage;
	pMessage = GetCurrentMessage();
	ASSERT(pMessage);
	CPoint point;
	point = pMessage->pt;		// get the point from the message
	ScreenToClient(&point);		// convert the point's coords to be relative 
								// to this control
	
	// see if the point falls on a tree item
	
	UINT flags = 0;
	HTREEITEM hItem = HitTest(point, &flags);

	if (IsSeparator(hItem))		//+++1.6
		return FALSE;			// no tooltip for separator
		
	if (hItem && (flags & TVHT_ONITEM))
	{
		// it did fall on an item

		TRACE(_T("in PreDisplayToolTip:  mouse on item %X\n"), hItem);

		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			// get rect for item text
			CRect rectClient;
			GetClientRect(&rectClient);
			CRect rectText;
			GetItemRect(hItem, &rectText, TRUE);	// get rect for text
			rectText.right = pXTCD->ds.nRightX;

			//TRACE(_T("nRightX = %d\n"), pXTCD->ds.nRightX);
			//TRACERECT(rectText);
			//TRACERECT(rectClient);

			strToolTip = GetItemNote(hItem);
			BOOL bNote = !strToolTip.IsEmpty();

			// check if text rect falls entirely inside client rect of control
			if (bNote || (rectText.right > (rectClient.right - 3)))
			{
				TRACE(_T("note or overflow\n"));

				// check if parent wants to display this tooltip --
				// if lResult is not zero, don't display 
				LRESULT lResult = 0;
				if (m_pToolTip)
				{
					lResult = SendRegisteredMessage(WM_XHTMLTREE_DISPLAY_TOOLTIP, 
									hItem, (LPARAM)m_pToolTip);
				}

				if (!lResult)
				{
					// get note again - this allows parent to modify note 
					// before it is displayed
					BOOL bStripHtml = bAlwaysRemoveHtml || !bNote;
					strToolTip = GetItemNote(hItem, bStripHtml);
					if (strToolTip.IsEmpty())
						strToolTip = GetItemText(hItem, bStripHtml);

					rc = TRUE;

					// set tip width regardless of whether there is a note
					int nTipWidth = GetItemNoteWidth(hItem);

					if (nTipWidth == 0)
					{
						// no note width specified, use a heuristic
						nTipWidth = GetDefaultTipWidth();
					}

					if (nTipWidth && m_pToolTip && IsWindow(m_pToolTip->m_hWnd))
						m_pToolTip->SetMaxTipWidth(nTipWidth);
				}
			}
		}
	}

	return rc;
}

//=============================================================================
void CXHtmlTree::OnSysColorChange() 
//=============================================================================
{
	CTreeCtrl::OnSysColorChange();
	SetColors();	
}

//=============================================================================
COLORREF CXHtmlTree::GetItemTextBkColor(HTREEITEM hItem)
//=============================================================================
{
	COLORREF rc = 0;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
		rc = pXTCD->ds.crTextBackground;

	return rc;
}

//=============================================================================
COLORREF CXHtmlTree::GetItemTextColor(HTREEITEM hItem)
//=============================================================================
{
	COLORREF rc = 0;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
		rc = pXTCD->ds.crText;

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::SetItemText(HTREEITEM hItem, LPCTSTR lpszItem)		//+++1.6
//=============================================================================
{
	if (IsSeparator(hItem))
		return FALSE;

	return CTreeCtrl::SetItemText(hItem, lpszItem);
}

//=============================================================================
COLORREF CXHtmlTree::SetItemTextBkColor(HTREEITEM hItem, COLORREF rgb)
//=============================================================================
{
	COLORREF rc = 0;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->ds.crTextBackground;
		pXTCD->ds.crTextBackground = rgb;
	}

	return rc;
}

//=============================================================================
COLORREF CXHtmlTree::SetItemTextColor(HTREEITEM hItem, COLORREF rgb)
//=============================================================================
{
	COLORREF rc = 0;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->ds.crText;
		pXTCD->ds.crText = rgb;
	}

	return rc;
}

//=============================================================================
COLORREF CXHtmlTree::SetBkColor(COLORREF rgb) 
//=============================================================================
{
	COLORREF old = m_crWindow; 
	if (rgb == COLOR_NONE)
		rgb = GetSysColor(COLOR_WINDOW);
	m_crCustomWindow = m_crWindow = rgb; 
	return old; 
}

//=============================================================================
COLORREF CXHtmlTree::SetTextColor(COLORREF rgb) 
//=============================================================================
{
	COLORREF old = m_crWindowText; 
	if (rgb == COLOR_NONE)
		rgb = GetSysColor(COLOR_WINDOWTEXT);
	m_crCustomWindowText = m_crWindowText = rgb; 
	return old; 
}

//=============================================================================
COLORREF CXHtmlTree::SetInsertMarkColor(COLORREF rgb)
//=============================================================================
{
	if (rgb == COLOR_NONE)
		rgb = GetSysColor(COLOR_HIGHLIGHT);
	m_crInsertMark = rgb; 
	return CTreeCtrl::SetInsertMarkColor(rgb);
}

//=============================================================================
CXHtmlTree& CXHtmlTree::SetSeparatorColor(COLORREF rgb)	//+++1.6
//=============================================================================
{
	if (rgb == COLOR_NONE)
		rgb = GetSysColor(COLOR_GRAYTEXT);
	m_crSeparator = rgb; 
	return *this;
}

//=============================================================================
void CXHtmlTree::SetColors()
//=============================================================================
{
	m_crWindow        = GetSysColor(COLOR_WINDOW);
	m_crWindowText    = GetSysColor(COLOR_WINDOWTEXT);
	m_crAnchorText    = RGB(0,0,255);
	m_crGrayText      = GetSysColor(COLOR_GRAYTEXT);
	m_crHighlight     = GetSysColor(COLOR_HIGHLIGHT);
	m_crHighlightText = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_crInsertMark    = GetSysColor(COLOR_HIGHLIGHT);
	m_crSeparator     = GetSysColor(COLOR_GRAYTEXT);		//+++1.6

	if (m_crCustomWindow != COLOR_NONE)
		m_crWindow = m_crCustomWindow;

	if (m_crCustomWindowText != COLOR_NONE)
		m_crWindowText = m_crCustomWindowText;
}

//=============================================================================
BOOL CXHtmlTree::EnableWindow(BOOL bEnable /*= TRUE*/)
//=============================================================================
{
	BOOL rc = CTreeCtrl::EnableWindow(bEnable);

	if (bEnable)
	{
		if (m_crCustomWindow != COLOR_NONE)
			m_crWindow = m_crCustomWindow;
		else
			m_crWindow = GetSysColor(COLOR_WINDOW);

		if (m_crCustomWindowText != COLOR_NONE)
			m_crWindowText = m_crCustomWindowText;
		else
			m_crWindowText = GetSysColor(COLOR_WINDOWTEXT);
	}
	else
	{
		m_crWindow = GetDisabledColor(GetSysColor(COLOR_WINDOW));
		m_crWindowText = GetSysColor(COLOR_GRAYTEXT);
	}

	return rc;
}

//=============================================================================
COLORREF CXHtmlTree::GetDisabledColor(COLORREF color)
//=============================================================================
{
	BYTE r = GetRValue(color);
	BYTE g = GetGValue(color);
	BYTE b = GetBValue(color);
	const BYTE disabled_value = 10;

	r = (r >= disabled_value) ? (BYTE)(r - disabled_value) : r;
	g = (g >= disabled_value) ? (BYTE)(g - disabled_value) : g;
	b = (b >= disabled_value) ? (BYTE)(b - disabled_value) : b;

	return RGB(r, g, b);
}

//=============================================================================
CXHtmlTree& CXHtmlTree::SetLogfont(LOGFONT * pLogFont)
//=============================================================================
{
	ASSERT(pLogFont);

	if (pLogFont)
		m_lf = *pLogFont;

	return *this;
}

//=============================================================================
BOOL CXHtmlTree::GetItemBold(HTREEITEM hItem)
//=============================================================================
{
	BOOL rc = FALSE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
		rc = pXTCD->ds.bBold;

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::SetItemBold(HTREEITEM hItem, BOOL bBold)
//=============================================================================
{
	BOOL rc = FALSE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->ds.bBold;
		pXTCD->ds.bBold = bBold;
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::DeleteAllItems()
//=============================================================================
{
	// avoid unneeded selchange notifications
	SelectItem(NULL);

	CollapseAll();
	BOOL bOldDestroyingTree = m_bDestroyingTree;
	m_bDestroyingTree = TRUE;
	BOOL rc = CTreeCtrl::DeleteAllItems();
	DeleteMap();
	m_bDestroyingTree = bOldDestroyingTree;
	return rc;
}

//=============================================================================
void CXHtmlTree::CollapseAll()
//=============================================================================
{
	HTREEITEM hItemRoot = GetRootItem();

	HTREEITEM hItem = hItemRoot;

	if (hItem)
	{
		do 
		{
			CollapseBranch(hItem);

		} while ((hItem = GetNextSiblingItem(hItem)) != NULL);

		SelectItem(hItemRoot);

		SendMessage(WM_HSCROLL, SB_LEFT);
		UpdateWindow();
	}
}

//=============================================================================
void CXHtmlTree::ExpandAll()
//=============================================================================
{
	HTREEITEM hItemSel = GetSelectedItem();
	if (!hItemSel)
		hItemSel = GetRootItem();

	if (hItemSel)
	{
		HTREEITEM hItem = GetRootItem();	// must start with root for best performance

		SetRedraw(FALSE);

		do 
		{
			ExpandBranch(hItem);

		} while ((hItem = GetNextSiblingItem(hItem)) != NULL);

		SelectItem(hItemSel);
		SetScrollPos(SB_VERT, 0);
		EnsureVisible(hItemSel);
		SendMessage(WM_HSCROLL, SB_LEFT);

		SetRedraw(TRUE);
	}
}

//=============================================================================
void CXHtmlTree::ExpandBranch(HTREEITEM hItem)
//=============================================================================
{
	if (hItem && ItemHasChildren(hItem))
	{
		Expand(hItem, TVE_EXPAND);

		hItem = GetChildItem(hItem);

		if (hItem)
		{
			do
			{
				ExpandBranch(hItem);

			} while ((hItem = GetNextSiblingItem(hItem)) != NULL);
		}
	}
}

//=============================================================================
void CXHtmlTree::CollapseBranch(HTREEITEM hItem)
//=============================================================================
{
	if (hItem && ItemHasChildren(hItem))
	{
		Expand(hItem, TVE_COLLAPSE);

		hItem = GetChildItem(hItem);

		if (hItem && ItemHasChildren(hItem))
		{
			do 
			{
				CollapseBranch(hItem);

			} while ((hItem = GetNextSiblingItem(hItem)) != NULL);
		}
	}
}

//=============================================================================
BOOL CXHtmlTree::Expand(HTREEITEM hItem, UINT nCode)
//=============================================================================
{
	if (hItem && ItemHasChildren(hItem))
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD && pXTCD->bEnabled)
		{
			BOOL bOldExpanded = pXTCD->bExpanded;

			if (nCode == TVE_COLLAPSE || nCode == TVE_COLLAPSERESET)
			{
				pXTCD->bExpanded = FALSE;
			}
			else if (nCode == TVE_EXPAND)
			{
				pXTCD->bExpanded = TRUE;
			}
			else if (nCode == TVE_TOGGLE)
			{
				if (bOldExpanded)
					pXTCD->bExpanded = FALSE;
				else
					pXTCD->bExpanded = TRUE;
			}
			else
			{
				TRACE(_T("ERROR bad nCode=%u\n"), nCode);
			}

			if (pXTCD->bExpanded)
				pXTCD->bHasBeenExpanded = TRUE;

			if (pXTCD->bExpanded != bOldExpanded)
				SendRegisteredMessage(WM_XHTMLTREE_ITEM_EXPANDED, hItem, 
					pXTCD->bExpanded);
		}
	}

	TRACE(_T("calling CTreeCtrl::Expand()\n"));
	BOOL rc = CTreeCtrl::Expand(hItem, nCode);

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::GetHasBeenExpanded(HTREEITEM hItem)
//=============================================================================
{
	BOOL rc = FALSE;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->bHasBeenExpanded;
	}

	return rc;
}

//=============================================================================
void CXHtmlTree::CheckAll(BOOL bCheck)
//=============================================================================
{
	if (m_bCheckBoxes)
	{
		if (m_bSmartCheck)
		{
			// check all root-level items
			HTREEITEM hRoot = GetRootItem();

			while (hRoot)
			{
				SetCheck(hRoot, bCheck);
				hRoot = GetNextItem(hRoot, TVGN_NEXT);	// get next root item
			}
		}
		else
		{
			// check all items
			HTREEITEM hItem = GetRootItem();

			while (hItem)
			{
				SetCheck(hItem, bCheck);
				hItem = GetNextItem(hItem);		// get next sequential item
			}
		}
	}
}

//=============================================================================
int CXHtmlTree::GetCheckedCount()
//=============================================================================
{
	int rc = 0;

	if (!m_bCheckBoxes)
		return 0;

	for (HTREEITEM hItem = GetRootItem();
		 hItem != NULL; 
		 hItem = GetNextItem(hItem))
	{
		if (GetCheck(hItem))
			rc++;
	}

	return rc;
}

//=============================================================================
int CXHtmlTree::GetChildrenCheckedCount(HTREEITEM hItem)
//=============================================================================
{
	int rc = 0;

	if (!m_bCheckBoxes)
		return 0;

	if (!hItem)
		hItem = GetRootItem();

	if (hItem && m_bSmartCheck)
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			rc = pXTCD->nChecked;
		}
	}
	else if (hItem && ItemHasChildren(hItem))
	{
		HTREEITEM hChild = GetChildItem(hItem);
		if (hChild)
		{
			do
			{
				if (GetCheck(hChild))
					rc++;

				rc += GetChildrenCheckedCount(hChild);

			} while ((hChild = GetNextSiblingItem(hChild)) != NULL);
		}
	}

	return rc;
}

//=============================================================================
int CXHtmlTree::GetChildrenDisabledCount(HTREEITEM hItem)
//=============================================================================
{
	int rc = 0;

	if (!hItem)
		hItem = GetRootItem();

	if (hItem && ItemHasChildren(hItem))
	{
		HTREEITEM hChild = GetChildItem(hItem);
		if (hChild)
		{
			do
			{
				if (!IsEnabled(hChild))
					rc++;

				rc += GetChildrenDisabledCount(hChild);

			} while ((hChild = GetNextSiblingItem(hChild)) != NULL);
		}
	}

	return rc;
}

//=============================================================================
int CXHtmlTree::GetChildrenCount(HTREEITEM hItem)
//=============================================================================
{
	int rc = 0;

	if (!hItem)
		hItem = GetRootItem();

	if (hItem && m_bSmartCheck)
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			rc = pXTCD->nChildren;
		}
	}
	else if (hItem && ItemHasChildren(hItem))
	{
		HTREEITEM hChild = GetChildItem(hItem);
		if (hChild)
		{
			do
			{
				rc++;
				rc += GetChildrenCount(hChild);

			} while ((hChild = GetNextSiblingItem(hChild)) != NULL);
		}
	}

	return rc;
}

//=============================================================================
int CXHtmlTree::GetSeparatorCount(HTREEITEM hItem)			//+++1.6
//=============================================================================
{
	int rc = 0;

	if (!hItem)
		hItem = GetRootItem();

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		rc = pXTCD->nSeparators;
	}

	return rc;
}

//=============================================================================
CString CXHtmlTree::GetItemText(HTREEITEM hItem, BOOL bStripHtml /*= FALSE*/) const
//=============================================================================
{
	CString strText = _T("");

	if (hItem)
	{
		strText = CTreeCtrl::GetItemText(hItem);

		if (bStripHtml)
		{
#ifdef XHTMLHTML
			// remove html tags
			CXHtmlDraw hd;
			int n = strText.GetLength();
			if (n > 3)		// minimum html string
			{
				TCHAR *s = new TCHAR [n + 16];
				hd.GetPlainText(strText, s, n+4);
				strText = s;
				delete [] s;
			}
#endif // XHTMLHTML
		}
	}

	return strText;
}

//=============================================================================
void CXHtmlTree::OnLButtonDown(UINT nFlags, CPoint point)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnLButtonDown\n"));

	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point, &uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();
	CEdit *pEdit = GetEditControl();

	if (hItem && (TVHT_ONITEMBUTTON & uFlags))
	{
		TRACE(_T("TVHT_ONITEMBUTTON\n"));
		if (pEdit && IsWindow(pEdit->m_hWnd))
		{
			TRACE(_T("sending WM_CLOSE to edit box\n"));
			pEdit->SendMessage(WM_CLOSE);
		}

		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD && !pXTCD->bEnabled)
			return;

		if (pXTCD && pXTCD->bEnabled && ItemHasChildren(hItem))
		{
			BOOL bExpanded = !pXTCD->bExpanded;
			Expand(hItem, bExpanded ? TVE_EXPAND : TVE_COLLAPSE);
			return;
		}
	}
	else if (hItem && (TVHT_ONITEMSTATEICON & uFlags))
	{
		TRACE(_T("TVHT_ONITEMSTATEICON\n"));
		// click on checkbox
	}
	else if (hItem && IsSeparator(hItem))		//+++1.6
	{
		if (hItem != hItemSelected)
			SelectItem(hItem);

		m_hItemButtonDown = hItem;
		TRACE(_T("setting LBUTTONDOWN_TIMER >>>>>\n"));
		SetTimer(LBUTTONDOWN_TIMER, 100, NULL);
		return;
	}
	else if (hItem && (hItem == hItemSelected))
	{
		// item was already selected, so catch the button up state -
		// this will be start of edit. We don't need to check if disabled, 
		// because disabled items can't be selected
		//
		// NOTE: we use timer because we don't always get WM_LBUTTONUP message.
		//
		m_hItemButtonDown = hItem;
		TRACE(_T("setting LBUTTONDOWN_TIMER >>>>>\n"));
		SetTimer(LBUTTONDOWN_TIMER, 100, NULL);

#ifndef XHTMLDRAGDROP
		// We disable the return to prevent edit box opening on button down -
		// it should open only on button up.
		// For drag & drop, we need to call base function to allow 
		// OnBegindrag() to be called.
		return;
#endif // XHTMLDRAGDROP

	}
#ifdef XHTMLDRAGDROP
	else if (hItem && (hItem != hItemSelected))
	{
		SetTimer(SELECT_TIMER, 50, NULL);
	}
#endif // XHTMLDRAGDROP

	TRACE(_T("calling CTreeCtrl::OnLButtonDown\n"));

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

//=============================================================================
void CXHtmlTree::OnRButtonDown(UINT nFlags, CPoint point) 
//=============================================================================
{
#ifdef XHTMLDRAGDROP
	EndDragScroll();
	SendRegisteredMessage(WM_XHTMLTREE_END_DRAG, 0, 0);
#endif // XHTMLDRAGDROP
	CTreeCtrl::OnRButtonDown(nFlags, point);
}

//=============================================================================
// OnClick - handle clicking on checkbox and link
BOOL CXHtmlTree::OnClick(NMHDR* /*pNMHDR*/, LRESULT* pResult)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnClick\n"));

	BOOL rc = FALSE;	// allow parent to handle

	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	UINT flags = 0;
	HTREEITEM hItem = HitTest(point, &flags);
	TRACE(_T("in CXHtmlTree::OnClick:  hItem=%X\n"), hItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)		// will not be NULL if hItem is valid
	{
		if (pXTCD->bSeparator)			//+++1.6
		{
			return TRUE;	// can't set checkbox if separator
		}
		else if (flags & TVHT_ONITEMSTATEICON)
		{
			TRACE(_T("click on checkbox\n"));

			if (pXTCD->bEnabled && !m_bReadOnly)
			{
				SetCheck(hItem, !pXTCD->bChecked);

				//BOOL bCheck = GetCheck(hItem);
				//TRACE(_T("item %s checked\n"), bCheck ? _T("is") : _T("is not"));

				if (m_bSelectFollowsCheck)
					SelectItem(hItem);

				int nState = GetStateImage(hItem);
				nState |= HDCheckboxImageList::HOT_INDEX;

				SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK);

				m_hHotItem = hItem;
			}
			else
			{
				rc = TRUE;
			}
		}
		else
		{
			TRACE(_T("not on checkbox\n"));
			// can't use TVHT_ONITEMLABEL because text might be shifted left
			if (pXTCD->ds.bHasAnchor && pXTCD->bEnabled)
			{
				if (IsOverAnchor(hItem, point))
				{
#ifdef XHTMLHTML
					TRACE(_T("click on link\n"));
					m_Links.GotoURL(pXTCD->ds.pszAnchor, SW_SHOW, (LPARAM)(UINT_PTR)hItem);
#endif // XHTMLHTML
				}
				else
				{
					TRACE(_T("not in link rect\n"));
				}
			}
			else if (!pXTCD->bEnabled)
			{
				TRACE(_T("click on disabled item\n"));
				rc = TRUE;
			}
		}
	}

	*pResult = 0;
	return rc;
}

//=============================================================================
BOOL CXHtmlTree::OnDblclk(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnDblclk\n"));
	BOOL rc = FALSE;	// allow parent to handle

	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	UINT flags = 0;
	HTREEITEM hItem = HitTest(point, &flags);
	TRACE(_T("in CXHtmlTree::OnDblclk:  hItem=%X\n"), hItem);

	if (hItem && (flags & (TVHT_ONITEM | TVHT_ONITEMBUTTON | TVHT_ONITEMSTATEICON)))
	{
		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD && !pXTCD->bEnabled)
		{
			TRACE(_T("double click on disabled item\n"));
			rc = TRUE;		// don't allow default processing
		}
		else if (pXTCD && pXTCD->bEnabled && ItemHasChildren(hItem))
		{
			pXTCD->bExpanded = !pXTCD->bExpanded;
			pXTCD->bHasBeenExpanded = TRUE;
			SendRegisteredMessage(WM_XHTMLTREE_ITEM_EXPANDED, hItem, 
				pXTCD->bExpanded);
		}
	}

	*pResult = rc;
	return rc;
}

//=============================================================================
BOOL CXHtmlTree::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
//=============================================================================
{
	BOOL rc = FALSE;	// allow parent to handle

	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;
	
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	HTREEITEM hOldItem = pNMTreeView->itemOld.hItem;

	CString strItem = GetItemText(hItem);
	TRACE(_T("in CXHtmlTree::OnSelchanged:  <%s>\n"), strItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && !pXTCD->bEnabled)
	{
		if (hOldItem)
		{
			SelectItem(hOldItem);
		}
		rc = TRUE;
	}
	else
	{
		if (hItem == m_hPreviousItem)
			rc = TRUE;
	}
	
	if (!rc)
		m_hPreviousItem = hItem;

	*pResult = rc;
	return rc;
}

//=============================================================================
BOOL CXHtmlTree::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
//=============================================================================
{
	BOOL rc = FALSE;	// allow parent to handle

	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;
	
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;

	CString strItem = GetItemText(hItem);
	TRACE(_T("in CXHtmlTree::OnSelchanging:  <%s>\n"), strItem);

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	if (pXTCD && !pXTCD->bEnabled)
	{
		rc = TRUE;
	}

	*pResult = rc;
	return rc;
}

//=============================================================================
void CXHtmlTree::OnSize(UINT nType, int cx, int cy) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnSize\n"));

	CTreeCtrl::OnSize(nType, cx, cy);

	m_bFirstTime = TRUE;	// this will cause tooltips to be re-created
}

//=============================================================================
int CXHtmlTree::GetIndentLevel(HTREEITEM hItem)
//=============================================================================
{
	int nIndent = 0;

	while ((hItem = GetParentItem(hItem)) != NULL)
		nIndent++;

	return nIndent;
}

#ifdef XHTMLXML

//=============================================================================
BOOL CXHtmlTree::ConvertBuffer(const BYTE * inbuf, 
							   DWORD inlen,				// in bytes
							   BYTE ** outbuf,
							   DWORD& outlen,			// in bytes
							   ConvertAction eConvertAction /*= NoConvertAction*/)
//=============================================================================
{
	BOOL rc = FALSE;

	ASSERT(inbuf);
	ASSERT(inlen != 0);

	outlen = 0;

	if (inbuf && (inlen != 0))
	{
		TRACE(_T("eConvertAction=%d\n"), eConvertAction);

		// copy buffer to ensure it's null terminated
		BYTE * buf = new BYTE [inlen+16];
		memset(buf, 0, inlen+16);
		memcpy(buf, inbuf, inlen);

		if (eConvertAction == ConvertToUnicode)
		{
			TRACE(_T("converting to unicode\n"));
			int wlen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, NULL, 0);
			TRACE(_T("wlen=%d\n"), wlen);
			WCHAR *pszText = new WCHAR [wlen+16];
			memset(pszText, 0, (wlen+16) * sizeof(WCHAR));
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, pszText, wlen+2);
			outlen = (DWORD)wcslen(pszText) * sizeof(WCHAR);	// bytes
			*outbuf = (BYTE*) pszText;
			delete [] buf;
		}
		else if (eConvertAction == ConvertToAnsi)
		{
			TRACE(_T("converting to ansi\n"));
			LPCWSTR wp = (LPCWSTR) buf;
			int alen = WideCharToMultiByte(CP_ACP, 0, wp, -1, NULL, 0, NULL, NULL);
			TRACE(_T("alen=%d\n"), alen);
			char *pszText = new char [alen+16];
			memset(pszText, 0, alen+16);
			WideCharToMultiByte(CP_ACP, 0, wp, -1, pszText, alen+2, NULL, NULL);
			outlen = (DWORD)strlen(pszText);	// bytes
			*outbuf = (BYTE*) pszText;
			delete [] buf;
		}
		else
		{
			// no conversion
			outlen = inlen;						// bytes
			*outbuf = buf;
		}

		TRACE(_T("outlen=%d\n"), outlen);

		rc = TRUE;
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::LoadXmlFromBuffer(const BYTE * pBuf, 
								   DWORD len,	// bytes
								   ConvertAction eConvertAction)
//=============================================================================
{
	BOOL rc = FALSE;

	ASSERT(pBuf);

	if (pBuf)
	{
		DWORD outlen = 0;
		BYTE * outbuf = 0;

		rc = ConvertBuffer(pBuf, len, &outbuf, outlen, 
				eConvertAction);

		if (rc)
		{
			CString strXML = (TCHAR *) outbuf;

			delete [] outbuf;

			// remove endofline and tabs
			strXML.Remove(_T('\n'));
			strXML.Remove(_T('\r'));
			strXML.Remove(_T('\t'));

			m_nXmlCount = 0;

			CXmlDocument xml;
			BOOL ret = xml.Parse(strXML);
			TRACE(_T("Parse returned %d\n"), ret);

			if (ret)		// useless, always returns TRUE
			{
				TRACE(_T("loading root +++++\n"));
				HTREEITEM hRoot = InsertXmlItem(xml.GetRootElement(), 0);
				if (hRoot)
					m_nXmlCount++;

				TRACE(_T("loading children +++++\n"));
				LoadXml(xml, xml.GetRootElement(), hRoot, m_nXmlCount);

				rc = TRUE;
			}
			else
			{
				TRACE(_T("ERROR - Parse failed\n"));
			}
		}
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::LoadXmlFromResource(HINSTANCE hInstance, 
									 LPCTSTR lpszResId, 
									 LPCTSTR lpszResType,
									 ConvertAction eConvertAction)
//=============================================================================
{
	BOOL rc = FALSE;

	ASSERT(lpszResId);
	ASSERT(lpszResType);

	if (lpszResId && lpszResType)
	{
		TCHAR *pszRes = NULL;

		// is this a resource name string or an id?
		if (HIWORD(lpszResId) == 0)
		{
			// id
			pszRes = MAKEINTRESOURCE(LOWORD((UINT)(UINT_PTR)lpszResId));
		}
		else
		{
			// string
			pszRes = (TCHAR *)lpszResId;
			TRACE(_T("pszRes=%s\n"), pszRes);
		}

		HRSRC hrsrc = FindResource(hInstance, pszRes, lpszResType);
		_ASSERTE(hrsrc);

		if (hrsrc)
		{
			DWORD dwSize = SizeofResource(hInstance, hrsrc);	// in bytes
			TRACE(_T("dwSize=%d\n"), dwSize);

			HGLOBAL hglob = LoadResource(hInstance, hrsrc);
			_ASSERTE(hglob);

			if (hglob)
			{
				LPVOID lplock = LockResource(hglob);
				_ASSERTE(lplock);

				if (lplock)
				{
					BYTE *pBuf = new BYTE [dwSize+16];
					ASSERT(pBuf);

					if (pBuf)
					{
						memcpy(pBuf, lplock, dwSize);

						pBuf[dwSize] = 0;
						pBuf[dwSize+1] = 0;
						pBuf[dwSize+2] = 0;

						LoadXmlFromBuffer(pBuf, dwSize, eConvertAction);
							
						delete [] pBuf;

						rc = TRUE;
					}
				}
			}
		}
	}

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::LoadXmlFromFile(LPCTSTR lpszFile, ConvertAction eConvertAction)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::LoadXmlFromFile: %s\n"), lpszFile);

	BOOL rc = FALSE;

	DWORD dwFileSize = 0;
	HANDLE hFile = NULL;

	ASSERT(lpszFile);

	if (lpszFile)
	{
		hFile = CreateFile(lpszFile,
						   GENERIC_READ,
						   FILE_SHARE_READ | FILE_SHARE_WRITE,
						   NULL,
						   OPEN_EXISTING,
						   FILE_ATTRIBUTE_NORMAL,
						   NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			TRACE(_T("ERROR - CreateFile failed\n"));
			hFile = 0;
		}
		else
		{
			dwFileSize = GetFileSize(hFile, NULL);

			if ((dwFileSize != INVALID_FILE_SIZE))
			{
				BYTE * pBuf = new BYTE [dwFileSize+16];
				ASSERT(pBuf);

				if (pBuf)
				{
					DWORD dwBytesRead = 0;
					BOOL bRet = ReadFile(hFile, 
										 (LPVOID) pBuf, 
										 dwFileSize, 
										 &dwBytesRead, 
										 NULL);

					if (bRet)
					{
						pBuf[dwFileSize] = 0;
						pBuf[dwFileSize+1] = 0;
						pBuf[dwFileSize+2] = 0;

						LoadXmlFromBuffer(pBuf, dwFileSize, 
							eConvertAction);

						rc = TRUE;
					}
					else
					{
						TRACE(_T("ERROR - ReadFile failed\n"));
						dwFileSize = 0;
					}

					delete [] pBuf;
				}
				else
				{
					TRACE(_T("ERROR - failed to allocate memory\n"));
					dwFileSize = 0;
				}
			}
			else
			{
				TRACE(_T("ERROR - GetFileSize failed\n"));
				dwFileSize = 0;
			}
		}
	}
	else
	{
		TRACE(_T("ERROR - bad parameter\n"));
	}

	if (hFile)
		CloseHandle(hFile);

	return rc;
}

//=============================================================================
HTREEITEM CXHtmlTree::InsertXmlItem(CXmlElement *pElement, HTREEITEM hParent)
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::InsertXmlItem\n"));

	HTREEITEM hItem = 0;

	ASSERT(pElement);
	if (pElement)
	{
		CString strName = pElement->GetValue(_T("name"));
		TRACE(_T("InsertXmlItem: <%s>\n"), strName);

		// hack to stop display
		if (/*!strName.IsEmpty() &&*/ strName.Compare(_T("...")) != 0)
		{
			strName.TrimLeft();
			strName.TrimRight();

#if 0  // -----------------------------------------------------------
			if (strName.GetLength() <= 0)
			{
				TRACE(_T("ERROR - name is empty\n"));
				ASSERT(FALSE);
			}
#endif // -----------------------------------------------------------

			XHTMLTREEDATA xhtd;

			CString strSeparator = pElement->GetValue(_T("separator"));		//+++1.6
			if (!strSeparator.IsEmpty())
				xhtd.bSeparator = _ttoi(strSeparator);
			CString strChecked = pElement->GetValue(_T("checked"));
			if (!strChecked.IsEmpty() && !xhtd.bSeparator)
				xhtd.bChecked = _ttoi(strChecked);
			CString strEnabled = pElement->GetValue(_T("enabled"));
			if (!strEnabled.IsEmpty() && !xhtd.bSeparator)
				xhtd.bEnabled = _ttoi(strEnabled);
			TRACE(_T("name=<%s>, <%s>, <%s> \n"), strName, strChecked, strEnabled);
			TRACE(_T("bChecked=%d  bEnabled=%d  bSeparator=%d\n"), xhtd.bChecked, xhtd.bEnabled, xhtd.bSeparator);

			// get colors - must be named colors, e.g. "red"
			CString strTextColor = pElement->GetValue(_T("text-color"));
			CString strBackgroundColor = pElement->GetValue(_T("text-background-color"));

			if (!strTextColor.IsEmpty())
			{
				CXNamedColors crText(strTextColor);
				xhtd.ds.crText = crText.GetRGB();
			}

			if (!strBackgroundColor.IsEmpty())
			{
				CXNamedColors crBackground(strBackgroundColor);
				xhtd.ds.crTextBackground = crBackground.GetRGB();
			}

			int nImage = -1;
			CString strImage = pElement->GetValue(_T("image"));
			if (!strImage.IsEmpty() && !xhtd.bSeparator)
			{
				nImage = _ttoi(strImage);
				CImageList *pImageList = GetImageList(TVSIL_NORMAL);
				if (pImageList)		//+++1.5
				{
					int nCount = pImageList->GetImageCount();
					if (nImage >= nCount)
					{
						TRACE(_T("ERROR - invalid image\n"));
						ASSERT(FALSE);
						nImage = -1;
					}
				}
				else
				{
					TRACE(_T("WARNING  no image list, setting m_bImages to FALSE\n"));
					m_bImages = FALSE;
				}
			}

			//static int nItem = 1;

			// line not empty - add item
			TVINSERTSTRUCT tvis      = { 0 };
			if (!xhtd.bSeparator)
			{
				tvis.item.mask       = TVIF_TEXT;
				tvis.item.cchTextMax = strName.GetLength();
				tvis.item.pszText    = strName.LockBuffer();
			}
			tvis.hParent             = hParent;
			tvis.item.iImage         = TV_NOIMAGE;
			tvis.item.iSelectedImage = TV_NOIMAGE;
			tvis.item.mask          |= TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			//tvis.item.mask          |= TVIF_PARAM;
			//tvis.item.lParam         = nItem++;		// for debugging

			if (m_bImages && (nImage != -1) && !xhtd.bSeparator)		//+++1.5
			{
				tvis.item.iImage = tvis.item.iSelectedImage = nImage;
			}

			hItem = InsertItem(&tvis, &xhtd);
			ASSERT(hItem);

			if (!xhtd.bSeparator)
				strName.UnlockBuffer();

			if (hItem)
			{
				if (xhtd.bSeparator)
				{
					SetItemState(hItem, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);

					// increment separator count in parents
					HTREEITEM hParentSep = hItem;
					while ((hParentSep = GetParentItem(hParentSep)) != NULL)
					{
						IncrementSeparators(hParentSep, 1);
					}
				}
				else
				{
					CString strNote = pElement->GetValue(_T("note"));
					int nNoteWidth = 0;
					CString strNoteWidth = pElement->GetValue(_T("note-width"));
					if (!strNoteWidth.IsEmpty())
						nNoteWidth = _ttoi(strNoteWidth);
					if (!strNote.IsEmpty())
						SetItemNote(hItem, strNote, nNoteWidth);
				}
			}
		}
	}

	return hItem;
}

//=============================================================================
BOOL CXHtmlTree::LoadXml(CXmlDocument& xml, 
						 CXmlElement *pElement, 
						 HTREEITEM hParent,
						 int& nCount)
//=============================================================================
{
	BOOL rc = TRUE;

	ASSERT(pElement);
	if (pElement)
	{
		CXmlElement *pChild = xml.GetFirstChild(pElement);

		while (pChild != NULL)
		{
			HTREEITEM hItem = InsertXmlItem(pChild, hParent);

			if (!hItem)
			{
				// found '...'
				rc = FALSE;
				break;
			}

			nCount++;

			rc = LoadXml(xml, pChild, hItem, nCount);
			if (!rc)
				break;
			
			pChild = xml.GetNextSibling(pElement);
		}
	}

	return rc;
}

//=============================================================================
CString CXHtmlTree::GetXmlText(HTREEITEM hItem, LPCTSTR lpszElem)
//=============================================================================
{
	ASSERT(lpszElem);

	CString strElem = lpszElem;

	XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

	CString s = _T("");

	s = GetItemText(hItem);
	s.Replace(_T("&"), _T("&amp;"));
	s.Replace(_T("<"), _T("&lt;"));
	s.Replace(_T(">"), _T("&gt;"));
	s.Replace(_T("\""), _T("&quot;"));

	CString strXml = _T("");
	strXml.Format(_T("<%s name=\"%s\""), strElem, s);

	if (pXTCD)
	{
		s.Format(_T(" separator=\"%s\""), pXTCD->bSeparator ? _T("1") : _T("0"));
		strXml += s;

		s.Format(_T(" checked=\"%s\""), pXTCD->bChecked ? _T("1") : _T("0"));
		strXml += s;

		s.Format(_T(" enabled=\"%s\""), pXTCD->bEnabled ? _T("1") : _T("0"));
		strXml += s;

		if (pXTCD->ds.crText != COLOR_NONE)
		{
			TCHAR szColor[50];
			szColor[0] = _T('\0');
			CXNamedColors nc(pXTCD->ds.crText);
			if (nc.IsKnownColor())
				nc.GetName(szColor, sizeof(szColor)/sizeof(TCHAR)-1);
			else
				nc.GetHex(szColor, sizeof(szColor)/sizeof(TCHAR)-1);
			if (szColor[0] != _T('\0'))
			{
				s.Format(_T(" text-color=\"%s\""), szColor);
				strXml += s;
			}
		}

		if (pXTCD->ds.crTextBackground != COLOR_NONE)
		{
			TCHAR szColor[50];
			szColor[0] = _T('\0');
			CXNamedColors nc(pXTCD->ds.crTextBackground);
			if (nc.IsKnownColor())
				nc.GetName(szColor, sizeof(szColor)/sizeof(TCHAR)-1);
			else
				nc.GetHex(szColor, sizeof(szColor)/sizeof(TCHAR)-1);
			if (szColor[0] != _T('\0'))
			{
				s.Format(_T(" text-background-color=\"%s\""), szColor);
				strXml += s;
			}
		}
	}

	int nImage, nSelectedImage;
	GetItemImage(hItem, nImage, nSelectedImage);

	if (nImage != TV_NOIMAGE)
	{
		s.Format(_T(" image=\"%d\""), nImage);
		strXml += s;
	}

	s = GetItemNote(hItem);
	if (!s.IsEmpty())
	{
		s.Replace(_T("&"), _T("&amp;"));
		s.Replace(_T("<"), _T("&lt;"));
		s.Replace(_T(">"), _T("&gt;"));
		s.Replace(_T("\""), _T("&quot;"));

		strXml += _T(" note=\"");
		strXml += s;
		strXml += _T("\"");

		int nNoteWidth = 0;
		if (pXTCD)
			nNoteWidth = pXTCD->nTipWidth;
		if (nNoteWidth)
		{
			s.Format(_T(" note-width=\"%d\""), nNoteWidth);
			strXml += s;
		}
	}

	return strXml;
}

//=============================================================================
BOOL CXHtmlTree::SaveXml(HTREEITEM hItem, 
						 LPCTSTR lpszFile, 
						 BOOL bSaveAsUTF16)	// useful only on VS2005
//=============================================================================
{
	BOOL rc = FALSE;

	ASSERT(lpszFile);

	if (lpszFile)
	{
		FILE *f = NULL;

#if _MSC_VER >= 1400
		if (bSaveAsUTF16)
			f = _tfopen(lpszFile, _T("w, ccs=UTF-16LE"));
		else
#else
		UNUSED_ALWAYS(bSaveAsUTF16);
#endif
			f = _tfopen(lpszFile, _T("w"));

		if (f && hItem)
		{
			_ftprintf(f, _T("<?xml version=\"1.0\" encoding=\"ISO-8859-15\"?>\n"));

			int nPrevIndent = -1;
			int nIndent = 0;
			int nLevel = 1;
			BOOL bInItem = FALSE;
			CString ws = _T("");
			CString strText = _T("");

			HTREEITEM hNext = hItem;
			TCHAR *elem = _T("root");

			while (hNext)
			{
				strText = GetXmlText(hNext, elem);
				elem = _T("item");

				nIndent = GetIndentLevel(hNext);
				if (nIndent > nPrevIndent)
				{
					if (bInItem)
						_ftprintf(f, _T(">\n"));
					ws = _T("");
					for (int i = 0; i < nIndent; i++)
						ws += _T('\t');
					_ftprintf(f, _T("%s%s"), ws, strText);
					bInItem = TRUE;
					nLevel++;
				}
				else if (nIndent < nPrevIndent)
				{
					_ftprintf(f, _T("/>\n"), ws);
					ws = _T("");
					while (nPrevIndent > nIndent)
					{
						nPrevIndent--;
						ws = _T("");
						for (int i = 0; i < nPrevIndent; i++)
							ws += _T('\t');
						_ftprintf(f, _T("%s</item>\n"), ws);
					}
					_ftprintf(f, _T("%s%s"), ws, strText);
					bInItem = TRUE;
				}
				else
				{
					ws = _T("");
					for (int i = 0; i < nIndent; i++)
						ws += _T('\t');
					if (bInItem)
						//_ftprintf(f, _T("%s</item>\n"), ws);
						_ftprintf(f, _T("/>\n"));
					_ftprintf(f, _T("%s%s"), ws, strText);
					bInItem = TRUE;
				}
				nPrevIndent = nIndent;
				hNext = GetNextItem(hNext);			
			}

			_ftprintf(f, _T("/>\n"));
			nIndent--;
			while (nIndent > 0)
			{
				ws = _T("");
				for (int i = 0; i < nIndent; i++)
					ws += _T('\t');
				_ftprintf(f, _T("%s</item>\n"), ws);
				nIndent--;
			}

			_ftprintf(f, _T("</root>\n"));
			fflush(f);
			fclose(f);
			rc = TRUE;
		}
	}

	return rc;
}

#endif	// XHTMLXML


//=============================================================================
LRESULT CXHtmlTree::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
//=============================================================================
{
	LRESULT rc = CTreeCtrl::WindowProc(message, wParam, lParam);
	return rc;
}

//=============================================================================
// This function does special processing for bTextOnly=TRUE, since
// the text rect is shifted left when there is no image.
//
BOOL CXHtmlTree::GetItemRect(HTREEITEM hItem, LPRECT lpRect, BOOL bTextOnly)
//=============================================================================
{
	BOOL rc = CTreeCtrl::GetItemRect(hItem, lpRect, bTextOnly);

	if (bTextOnly)
	{
		int width = GetNormalImageWidth(hItem);		// get width of normal image

		if (width < 0)
		{
			// TV_NOIMAGE specified, shift text to the left
			lpRect->left += width;
			lpRect->right += width;
		}

		XHTMLTREEDATA *pXTCD = GetItemDataStruct(hItem);

		if (pXTCD)
		{
			lpRect->right = pXTCD->ds.nRightX;
		}

		//TRACERECT(*lpRect);
	}
	return rc;
}

//=============================================================================
BOOL CXHtmlTree::OnBeginlabeledit(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
//=============================================================================
{
	*pResult = 0;

	HTREEITEM hItem = IsOverItem();

	TRACE(_T("in CXHtmlTree::OnBeginlabeledit: %X\n"), hItem);

	if (hItem && IsSeparator(hItem))	//+++1.6
	{
		*pResult =  1;		// separator item, don't allow edit
	}
	else if (m_bReadOnly)
	{
		*pResult =  1;		// tree is read-only, don't allow edit
	}
	else
	{
		m_nHorzPos = GetScrollPos(SB_HORZ);	// save initial scroll position
	}
	return (BOOL)*pResult;	// 0 = allow parent to handle
}

//=============================================================================
BOOL CXHtmlTree::OnEndlabeledit(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
//=============================================================================
{
	TRACE(_T("in CXHtmlTree::OnEndlabeledit\n"));
	
	*pResult = 0;
	if ((m_nHorzPos == 0) && (GetScrollPos(SB_HORZ) != 0))
		SendMessage(WM_HSCROLL, SB_LEFT);	// editing caused tree to be 
											// scrolled, so scroll it back
	return 0;								// 0 = allow parent to handle
}

//=============================================================================
// following code contributed by David McMinn
BOOL CXHtmlTree::OnCommand(WPARAM wParam, LPARAM lParam)
//=============================================================================
{
	CEdit *pEdit = GetEditControl();
	if (((HIWORD(wParam) == EN_SETFOCUS) || (HIWORD(wParam) == EN_CHANGE))  && 
		pEdit && 
		(pEdit->GetSafeHwnd() == (HWND)lParam))
	{
		AdjustEditRect();
	}
	return CTreeCtrl::OnCommand(wParam, lParam);
}

//=============================================================================
// AdjustEditRect() moves the in-place edit box to line up with item text
//
void CXHtmlTree::AdjustEditRect()
//=============================================================================
{
	CEdit *pEdit = GetEditControl();

	if (pEdit && IsWindow(pEdit->m_hWnd))
	{
		HTREEITEM hItemEdit = GetSelectedItem();
		if (hItemEdit)
		{
			// adjust position of edit box for all items, even
			// those with image
			CRect rectClient;
			GetClientRect(&rectClient);
			CRect rectEdit;
			GetItemRect(hItemEdit, &rectEdit, TRUE);
			rectEdit.InflateRect(1, 1);				// allow for border
			rectEdit.OffsetRect(-1, -1);			// overlay existing text
			if (rectEdit.left < 0)
				rectEdit.left = 0;
			rectEdit.right = rectClient.right - 1;	// extend edit box full width
													// of tree control
			pEdit->MoveWindow(&rectEdit);
		}
	}
}

#ifdef XHTMLDRAGDROP

//=============================================================================
BOOL CXHtmlTree::IsCtrlDown()
//=============================================================================
{
	BOOL rc = FALSE;

	// always return FALSE if XHTMLTREE_DO_CTRL_KEY is not set
	if (m_dwDragOps & XHTMLTREE_DO_CTRL_KEY)
		if (GetAsyncKeyState(VK_CONTROL) < 0)
			rc = TRUE;

	return rc;
}

//=============================================================================
BOOL CXHtmlTree::IsDragCopy()
//
// returns TRUE if copy, FALSE if move
//
//  Ctrl key    COPY_DRAG flag    Action
// ----------+------------------+--------
//     up    |      false       |  move
//    down   |      false       |  copy
//     up    |      true        |  copy
//    down   |      true        |  move
//=============================================================================
{
	BOOL rc = FALSE;

	BOOL bCopyDrag = GetBit(m_dwDragOps, XHTMLTREE_DO_COPY_DRAG);
	BOOL bCtrlDown = IsCtrlDown();

	if (bCtrlDown && !bCopyDrag)		// Ctrl down, !bCopyDrag: copy
		rc = TRUE;
	else if (!bCtrlDown && bCopyDrag)	// Ctrl up, bCopyDrag: copy
		rc = TRUE;

	return rc;
}

//=============================================================================
HCURSOR CXHtmlTree::GetDragCursor()
//=============================================================================
{
	BOOL bCopyDrag = IsDragCopy();

	HCURSOR hCursor = bCopyDrag ? m_hDropCopyCursor : m_hDropMoveCursor;

	return hCursor;
}

//=============================================================================
void CXHtmlTree::SetDragCursor()
//=============================================================================
{
	HCURSOR hCursor = GetDragCursor();

	if (hCursor)
		SetCursor(hCursor);
	else
		SetCursor(m_hPreviousCursor);
}

//=============================================================================
void CXHtmlTree::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
//=============================================================================
{
	ASSERT(!m_bDragging);

	NMTREEVIEW* pNMTreeView = (NMTREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	ASSERT(hItem);

	if (!hItem)
		return;

	BOOL bCopyDrag = IsDragCopy();

#ifdef _DEBUG
	CString strText = GetItemText(hItem);
	TRACE(_T("in CXHtmlTree::OnBegindrag: %s  bCopyDrag=%d\n"), strText, bCopyDrag);
#endif

	// allow parent to decide whether to permit drag
	XHTMLTREEDRAGMSGDATA dragdata = { 0 };
	dragdata.hItem = hItem;
	dragdata.bCopyDrag = bCopyDrag;

	LRESULT lResult = SendRegisteredMessage(WM_XHTMLTREE_BEGIN_DRAG, hItem, 
		(LPARAM)&dragdata);

	if (lResult)
	{
		return;
	}

	m_hItemButtonDown = hItem;
	TRACE(_T("setting LBUTTONDOWN_TIMER >>>>>\n"));
	SetTimer(LBUTTONDOWN_TIMER, 100, NULL);

	m_bDragging = TRUE;

	if (m_nNoDropCursor && (m_hNoDropCursor == NULL))
		m_hNoDropCursor = AfxGetApp()->LoadCursor(m_nNoDropCursor);
	if (m_nDropCopyCursor && (m_hDropCopyCursor == NULL))
		m_hDropCopyCursor = AfxGetApp()->LoadCursor(m_nDropCopyCursor);
	if (m_nDropMoveCursor && (m_hDropMoveCursor == NULL))
		m_hDropMoveCursor = AfxGetApp()->LoadCursor(m_nDropMoveCursor);

	SetDragCursor();

	m_dwDropHoverTime = GetTickCount();
	SetInsertMarkColor(m_crInsertMark);
	m_hPreviousDropItem = NULL;
	
	SetCapture();
	SetFocus();
	
	*pResult = 0;
}

//=============================================================================
// Determines if hItem is a child of hitemSuspectedParent
// Called in OnTimer to prevent the case where an item is attempted
// to be made a child of its own child.
//
BOOL CXHtmlTree::IsChildNodeOf(HTREEITEM hItem, HTREEITEM hitemSuspectedParent)
//=============================================================================
{
	do
	{
		if (hItem == hitemSuspectedParent)
			break;
	}
	while ((hItem = GetParentItem(hItem)) != NULL);

	return (hItem != NULL);
}

//=============================================================================
// CopyItem   - Copies an item to a new location
// Returns    - Handle of the new item
// hItem      - Item to be copied
// hNewParent - Handle of the parent for new item
// hAfter     - Item after which the new item should be created
HTREEITEM CXHtmlTree::MoveItem(HTREEITEM hItem, 
							   HTREEITEM hNewParent, 
							   HTREEITEM hAfter /*= TVI_LAST*/)
//=============================================================================
{
	HTREEITEM hNewItem = NULL;
	XHTMLTREEDATA *pXTCD = NULL;

	if (hItem)
		pXTCD = GetItemDataStruct(hItem);

	if (pXTCD)
	{
		TVINSERTSTRUCT tvis;
		CString strText = _T("");
		
		// get information of the source item
		tvis.item.hItem = hItem;
		tvis.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_PARAM |
			TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		GetItem(&tvis.item);  
		strText = GetItemText(hItem);
		
		tvis.item.cchTextMax = strText.GetLength();
		tvis.item.pszText = strText.LockBuffer();
		
		// insert the item at proper location
		tvis.hParent = hNewParent;
		tvis.hInsertAfter = hAfter;
		tvis.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;

		hNewItem = InsertItem(&tvis, pXTCD);

		strText.UnlockBuffer();

		if (pXTCD->bSeparator)			//+++1.6
		{
			SetItemState(hNewItem, INDEXTOSTATEIMAGEMASK(0), TVIS_STATEIMAGEMASK);

			// increment separator count
			HTREEITEM hParent = hNewItem;
			while ((hParent = GetParentItem(hParent)) != NULL)
			{
				IncrementSeparators(hParent, 1);
			}
		}

#if 0  // -----------------------------------------------------------
		SetItemState(hNewItem, GetItemState(hItem, TVIS_STATEIMAGEMASK), 
			TVIS_STATEIMAGEMASK);
#endif // -----------------------------------------------------------
		
	}

	return hNewItem;
}

//=============================================================================
// MoveBranch - Moves all items in a branch to a new location
// Returns    - The new branch node
// hBranch    - The node that starts the branch
// hNewParent - Handle of the parent for new branch
// hAfter     - Item after which the new branch should be created
HTREEITEM CXHtmlTree::MoveBranch(HTREEITEM hBranch, 
								 HTREEITEM hNewParent, 
								 HTREEITEM hAfter /*= TVI_LAST*/)
//=============================================================================
{
	HTREEITEM hChild;
	
	HTREEITEM hNewItem = MoveItem(hBranch, hNewParent, hAfter);
	HTREEITEM hNext = GetChildItem(hBranch);
	hChild = hNext;
	while (hChild)
	{
		// recursively transfer all the items
		MoveBranch(hChild, hNewItem);
		hNext = GetNextSiblingItem(hChild);
		hChild = hNext;
	}
	return hNewItem;
}

//=============================================================================
BOOL CXHtmlTree::StartMoveBranch(HTREEITEM hItem, 
								 HTREEITEM hNewParent, 
								 HTREEITEM hAfter /*= TVI_LAST*/)
//=============================================================================
{
	BOOL bCopyDrag = IsDragCopy();

	TRACE(_T("in CXHtmlTree::StartMoveBranch: %s %X:  new parent=%X  after=%X\n"), 
		bCopyDrag ? _T("copying") : _T("moving"), hItem, hNewParent, hAfter);

	BOOL rc = FALSE;

	ASSERT(hItem);

	if (hItem)
	{
		// allow parent to decide whether to permit drag
		XHTMLTREEDRAGMSGDATA dragdata = { 0 };
		dragdata.hItem      = hItem;
		dragdata.hNewParent = hNewParent;
		dragdata.hAfter     = hAfter;
		dragdata.bCopyDrag  = bCopyDrag;

		LRESULT lResult = SendRegisteredMessage(WM_XHTMLTREE_END_DRAG, hItem, 
			(LPARAM)&dragdata);

		rc = lResult == 0;				// allow drop if lResult is 0

		if (rc)
		{
			MoveBranch(hItem, hNewParent, hAfter);

			if (!bCopyDrag)
			{
				// moving, so delete original item
				m_nDeleted = 0;
				m_nDeletedChecked = 0;
				DeleteBranch(hItem);	// this was a move, not a copy
				TRACE(_T("m_nDeleted=%d  m_nDeletedChecked=%d\n"), m_nDeleted, m_nDeletedChecked);
			}
		}
	}

	return rc;
}

//=============================================================================
void CXHtmlTree::AutoScroll(HTREEITEM hItem)
//=============================================================================
{
	DWORD dwSpeedFlags = XHTMLTREE_DO_SCROLL_NORMAL | XHTMLTREE_DO_SCROLL_FAST;

#ifdef _DEBUG
	if ((m_dwDragOps & dwSpeedFlags) == dwSpeedFlags)
	{
		TRACE(_T("ERROR - only one speed flag should be set\n"));
		ASSERT(FALSE);
	}
#endif // _DEBUG

	if ((m_dwDragOps & dwSpeedFlags) == 0)
	{
		// no speed flags, don't scroll
		return;
	}
		
	if (m_dwDragOps & XHTMLTREE_DO_SCROLL_NORMAL)
	{
		// scroll every other time, about 5 times a second
		if ((++m_nScrollTime & 1) == 0)
			return;
	}

	int n = 0;

	if (hItem)
	{
		int nScrollZone = GetItemHeight() + 5;

		CPoint point;
		GetCursorPos(&point);	// screen coords
		CRect rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);	// screen coords

		int nDistance = 0;
		BOOL bUp = TRUE;

		if (point.y < (rect.top + nScrollZone))
		{
			nDistance = point.y - rect.top;
			bUp = TRUE;		// up
		}
		else if (point.y > (rect.bottom - nScrollZone))
		{
			nDistance = rect.bottom - point.y;
			bUp = FALSE;	// down
		}

		if (nDistance > 0)
		{
			SetInsertMark(0, 0);	// remove previous insert mark

			if (nDistance > ((nScrollZone/3)*2))
			{
				// in region farthest from border, scroll slow
				SendMessage(WM_VSCROLL, bUp ? SB_LINEUP : SB_LINEDOWN);
				n = 1;
			}
			else if (nDistance > (nScrollZone/3))
			{
				// in middle region, scroll faster
				SendMessage(WM_VSCROLL, bUp ? SB_LINEUP : SB_LINEDOWN);
				SendMessage(WM_VSCROLL, bUp ? SB_LINEUP : SB_LINEDOWN);
				n = 2;
			}
			else
			{
				// in region closest to border, scroll very fast
				SendMessage(WM_VSCROLL, bUp ? SB_PAGEUP : SB_PAGEDOWN);
				n = 3;
			}

			ScreenToClient(&point);

			HTREEITEM hItem = IsOverItem(&point);

			if (hItem)
			{
				if ((m_dwDragOps & XHTMLTREE_DO_SHIFT_KEY) &&
					(GetAsyncKeyState(VK_SHIFT) < 0))
				{
					TRACE(_T("VK_SHIFT down\n"));
					if (IsSeparator(hItem))					//+++1.6
					{
						SelectDropTarget(NULL);
						SetInsertMark(hItem, TRUE);
					}
					else
					{
						SelectDropTarget(hItem);
					}
				}
				else
				{
					SetInsertMark(hItem, TRUE);
					SelectDropTarget(NULL);
				}
			}
		}
	}

#ifdef XHTMLTREE_DEMO
	CWnd *pWnd = GetParent();
	if (!pWnd)
		pWnd = GetOwner();
	if (pWnd && ::IsWindow(pWnd->m_hWnd))
		pWnd->SendMessage(WM_XHTMLTREE_SCROLL_SPEED, n, 0);
#endif // XHTMLTREE_DEMO
}
#endif // XHTMLDRAGDROP

//=============================================================================
void CXHtmlTree::EndDragScroll()
//=============================================================================
{
#ifdef XHTMLDRAGDROP

	TRACE(_T("in CXHtmlTree::EndDragScroll\n"));

	KillTimer(LBUTTONDOWN_TIMER);
	KillTimer(SHIFT_UP_TIMER);
	SetInsertMark(0, 0);
	m_nScrollTime = 0;
	if (m_bAutoScroll)
		AutoScroll(NULL);
	SelectDropTarget(NULL);
	ReleaseCapture();
	m_bDragging = FALSE;
	SetCursor(m_hPreviousCursor);

#endif // XHTMLDRAGDROP
}
