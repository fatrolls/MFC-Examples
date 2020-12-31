// PapersBar.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PapersBar.h"
#include "Doc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPapersBar

CPapersBar::CPapersBar()
{
	lima.Create(32,32,ILC_MASK|ILC_COLOR8, 0, 2);
	lima.Add((HICON) AfxGetApp()->LoadIcon(IDR_PRINTFTYPE));
	lima.Add((HICON) AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	pDoc = NULL;
}

CPapersBar::~CPapersBar()
{
}


BEGIN_MESSAGE_MAP(CPapersBar, SECControlBar)
	//{{AFX_MSG_MAP(CPapersBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(LVN_ITEMCHANGED, 1020, OnItemchangedList1)
	ON_NOTIFY(LVN_ENDLABELEDIT, 1020, OnEndlabeleditList1)
	ON_NOTIFY(NM_SETFOCUS, 1020, OnSetfocusList1)
	ON_NOTIFY(NM_KILLFOCUS, 1020, OnKillfocusList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPapersBar message handlers

void CPapersBar::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState & LVIS_SELECTED || pNMListView->uNewState & LVIS_FOCUSED)
	{
		int idx = wndList.GetNextItem(-1, LVNI_SELECTED);
		if (idx >= 0)
		{
			if (pDoc)
			{
				pDoc->SelectPage(idx);

				if (GfxIsProp2())
				{
					CGfxProperty * pg = GfxGetProp2();
					if (!(pg->pDocument == pDoc && pg->pWnd == this))
					{
						pg->ClearTabArray();
						pPage1.pDoc = pDoc;

						pg->pDocument = pDoc;
						pg->pWnd = this;

						pPage1.Create(CPagePage1::IDD, pg);
						pg->AddPage(&pPage1, "Page");
						pg->SetCurSel(0);
					}
					else pPage1.UpdateData(false);
				}
				
			}
		}
	}
	*pResult = 0;
}


int CPapersBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (SECControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rc;
	GetInsideRect(rc);
	wndList.Create(WS_CHILD|WS_VISIBLE|LVS_ICON|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_EDITLABELS,rc,this,1020);
	wndList.SetImageList(&lima, LVSIL_NORMAL);
	wndList.ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);

	return 0;
}

void CPapersBar::OnSize(UINT nType, int cx, int cy) 
{
	CRect rectInside;
	GetInsideRect(rectInside);
	if (wndList.GetSafeHwnd())
		wndList.SetWindowPos(0, rectInside.left, rectInside.top, rectInside.Width(), rectInside.Height(), SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREDRAW);

	SECControlBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

BOOL CPapersBar::OnEraseBkgnd(CDC* pDC) 
{
	ASSERT_VALID(pDC);

	// Fill background with APPWORKSPACE
	CBrush backBrush(GetSysColor(COLOR_BTNFACE));
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed

	CRect rectInside;
	GetInsideRect(rectInside);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rectInside.top - rect.top, PATCOPY);
	pDC->PatBlt(rect.left, rectInside.bottom, rect.Width(), rect.bottom - rectInside.bottom, PATCOPY);
	pDC->PatBlt(rect.left, rect.top, rectInside.left - rect.left, rect.Height(), PATCOPY);
	pDC->PatBlt(rectInside.right, rect.top, rect.right - rectInside.right, rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;	
	
//	return SECControlBar::OnEraseBkgnd(pDC);
}


void CPapersBar::OnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;

	if (pDoc)
	{
		pDoc->RenamePage(pDispInfo->item.iItem, CString(pDispInfo->item.pszText));
		*pResult = 1;
	}
	
}

void CPapersBar::OnSetfocusList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pDoc && GfxIsProp2())
	{
		CGfxProperty * pg = GfxGetProp2();
		if (pg->pDocument != pDoc || pg->pWnd != this)
		{
			pg->ClearTabArray();
			pPage1.pDoc = pDoc;

			pg->pDocument = pDoc;
			pg->pWnd = this;

			pPage1.Create(CPagePage1::IDD, pg);
			pg->AddPage(&pPage1, "Page");
			pg->SetCurSel(0);
		}		
	}
	
	*pResult = 0;
}

void CPapersBar::OnKillfocusList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
/*	if (pDoc && GfxIsProp2())
	{
		CGfxProperty * pg = GfxGetProp2();
		if (pg->pDocument == pDoc && pg->pWnd == this)
		{
			pg->ClearTabArray();
		}		
	}
*/	
	*pResult = 0;
}
