// TreeBar.cpp : implementation file
//

#include "stdafx.h"
#include "dockdemo.h"
#include "TreeBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define IDC_TREEBAR_TAB     100

/////////////////////////////////////////////////////////////////////////////
// CTreeBar

CTreeBar::CTreeBar()
{
}

CTreeBar::~CTreeBar()
{
}


BEGIN_MESSAGE_MAP(CTreeBar, CMRCSizeControlBar)
	//{{AFX_MSG_MAP(CTreeBar)
	ON_WM_CREATE()
    ON_NOTIFY(TCN_SELCHANGE,   IDC_TREEBAR_TAB, OnTabChanged)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreeBar message handlers

int CTreeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMRCSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    CRect rect(0,0,0,0);
    // create a tab control with tree controls inside it....
    if (!m_TabCtrl.Create(WS_CHILD | WS_VISIBLE | TCS_BOTTOM | TCS_MULTILINE,
                        rect, this, IDC_TREEBAR_TAB))
    {
        TRACE("Failed to create Tab control\n");
        return -1;
    }

    m_ImgList.Create( IDB_TREEBAR, 16, 1, RGB(192, 192, 192));
    
    m_TabCtrl.SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))); 
    m_TabCtrl.SetImageList(&m_ImgList);


    // populate the tab control ....
    LPCTSTR szTabName[] = { _T("Classes"), _T("Resources"), _T("Files"), _T("Info") };
    
    for (int i = 0; i < sizeof(szTabName) / sizeof(LPCTSTR); i++)
    {
        CTreeCtrl * pTreeCtrl = new CTreeCtrl;
        DWORD dwStyle = WS_BORDER | WS_CHILD | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT;
        if (!pTreeCtrl->Create(dwStyle, rect, this, i))
            return -1;      // failed to create tree control
        pTreeCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);

        TC_ITEM TCI;
        TCI.mask = TCIF_TEXT | TCIF_PARAM | TCIF_IMAGE;
        TCI.pszText = (char *)szTabName[i];
        TCI.lParam = (LPARAM)pTreeCtrl;
        TCI.iImage = i;
        VERIFY(m_TabCtrl.InsertItem(0, &TCI) != -1);
    
        // insert some items into the tree control.
        HTREEITEM hRoot = pTreeCtrl->InsertItem(szTabName[i]);
        for (int j = 0; j < 4; j++)
        {
            CString strText;
            strText.Format("item %d", j);
            pTreeCtrl->InsertItem(strText , hRoot);
        }
    }
    ShowSelTabWindow();
    
	return 0;
}


CWnd * CTreeBar::GetTabWindow(int nTab)
{
    TC_ITEM TCI;
    TCI.mask = TCIF_PARAM; 
    m_TabCtrl.GetItem(nTab, &TCI);
    CWnd * pWnd = (CWnd *)TCI.lParam;
    ASSERT(pWnd != NULL && pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
    return pWnd;
}


void CTreeBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
    CRect rect(0, 0, cx, cy);
    if (IsProbablyFloating())
        rect.InflateRect(-2, -2);       // give space around controls.
    else
        rect.InflateRect(-4, -4);       // give space around controls.

    // reposition the tab control.
    m_TabCtrl.MoveWindow(&rect);
    m_TabCtrl.AdjustRect(FALSE, &rect);

    for (int i = 0; i < m_TabCtrl.GetItemCount(); i++)
    {
        GetTabWindow(i)->MoveWindow(&rect);
    }
}


afx_msg void CTreeBar::OnTabChanged( NMHDR * pNM, LRESULT * pResult )
// hide all the windows - except the one with the currently selected tab
{
    ShowSelTabWindow();
    *pResult = TRUE;
}


void CTreeBar::ShowSelTabWindow()
{    
    m_TabCtrl.GetCurSel();        
    int nSel = m_TabCtrl.GetCurSel();   
    ASSERT(nSel != -1);
    
    for (int i = 0; i < m_TabCtrl.GetItemCount(); i++)
    {
        GetTabWindow(i)->ShowWindow(i == nSel ? SW_SHOW : SW_HIDE);
    }
}

void CTreeBar::OnDestroy() 
{
    // delete the CWnd object belonging to the child window
    for (int i = 0; i < m_TabCtrl.GetItemCount(); i++)
    {
        delete GetTabWindow(i);
    }
    
    CMRCSizeControlBar::OnDestroy();
}
