// sidepane.cpp : implementation file
//

#include "stdafx.h"
#include "treemenudemo.h"
#include "sidepane.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//_____________________________________
//                                     |
//           CSidePane                 |
//_____________________________________|
//
// 
//
//

#define BORDER		 2
#define IDC_COOLTREECTRL	1111


#define NUM_ITEMS	9
#define NUM_SUB		3

static _TCHAR *_gszItem[NUM_ITEMS] = 
{
	_T("Fifi"),		_T("Babs Bunny"),	_T("Buster Bunny"),
	_T("Concorde"), _T("Cyote"),		_T("Dizzy Devil"), 
	_T("Elmyra"),	_T("Hampton"),		_T("Plucky Duck")
};


/////////////////////////////////////////////////////////////////////////////
// CSidePane

CSidePane::CSidePane()
{
	m_clrBtnHilight = ::GetSysColor(COLOR_BTNHILIGHT);
	m_clrBtnShadow	= ::GetSysColor(COLOR_BTNSHADOW);
	m_iPaneCaptionY = ::GetSystemMetrics(SM_CYCAPTION);

	m_pControl = NULL;
}

CSidePane::~CSidePane()
{

}


BEGIN_MESSAGE_MAP(CSidePane, CSizingControlBar)
    //{{AFX_MSG_MAP(CSidePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
    //}}AFX_MSG_MAP
	ON_MESSAGE(TMFN_HIDE, OnHide)
	ON_MESSAGE(TMFN_CAPTIONDRAG, OnCaptionDrag)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSidePane message handlers


int CSidePane::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CSizingControlBar::OnCreate(lpCreateStruct) == -1)
        return -1;

	m_TreeFrame.Create(CRect(0,0,0,0), this, 100);
	m_TreeFrame.CalcLayout();
	
	m_pControl = &m_TreeFrame;
	m_pControl->SubclassDlgItem(IDC_COOLTREECTRL, this);

	m_pControl->GetTreeMenuCtrl()->SetItemHeight(35);
	m_pControl->GetTreeMenuCtrl()->SetBorder(TVSBF_XBORDER|TVSBF_YBORDER, 2, 0);
	m_pControl->GetTreeMenuCtrl()->SetBkColor(GetSysColor (COLOR_3DFACE));
	m_pControl->ShowSideBevels();

	// ImageList
	m_ImageList.Create(IDB_TINYTOON, 32, 1, RGB(255,0,255));
    
    // Attach ImageList to TreeView
    if (m_ImageList)
        m_pControl->GetTreeMenuCtrl()->SetImageList((HIMAGELIST)m_ImageList,TVSIL_NORMAL);


	TVITEM tvi, tvi1;
	TVINSERTSTRUCT tvis;
	HTREEITEM hPrev;
	
	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
	tvi.hItem = NULL;
	tvi.cchTextMax = 64;     
	tvi.pszText = _T("Tiny Toons");
	tvi.iImage = 0;
	tvi.iSelectedImage = 0;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item = tvi;

	hPrev = m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);
	
	int i;
	for(i = 0; i < NUM_SUB; i++)
	{
		tvi1.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi1.cchTextMax = 64; 
		tvi1.pszText = _gszItem[i];
		tvi1.iImage = i+1;
		tvi1.iSelectedImage = i+1;
	
		tvis.hParent = hPrev;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi1;
		m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);
	}

	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
	tvi.hItem = NULL;
	tvi.pszText = _T("Tiny Toons 2");
	tvi.iImage = 0;
	tvi.iSelectedImage = 0;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item = tvi;

	hPrev = m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);
	

	for(i = 0; i < NUM_SUB; i++)
	{
		tvi1.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi1.pszText = _gszItem[3+i];
		tvi1.iImage = i+4;
		tvi1.iSelectedImage = i+4;
	
		tvis.hParent = hPrev;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi1;
		m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);
	}

	tvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_CHILDREN;
	tvi.hItem = NULL;
	tvi.pszText = _T("Tiny Toons 3");
	tvi.iImage = 0;
	tvi.iSelectedImage = 0;

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item = tvi;

	hPrev = m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);
	

	for(i = 0; i < NUM_SUB; i++)
	{
		tvi1.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi1.pszText = _gszItem[6+i];
		tvi1.iImage = i+7;
		tvi1.iSelectedImage = i+7;
	
		tvis.hParent = hPrev;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi1;
		m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);
	}


	CString s;
	for(i = 0; i < NUM_SUB*2; i++)
	{
		s.Format("Bookmark No: %i", i+1);

		tvi1.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
		tvi1.pszText = s.GetBuffer(64);
		tvi.hItem = NULL;
		tvi1.iImage = i+1;
		tvi1.iSelectedImage = i+4;
	
		tvis.hParent = TVI_ROOT;
		tvis.hInsertAfter = TVI_LAST;
		tvis.item = tvi1;
		m_pControl->GetTreeMenuCtrl()->InsertItem(&tvis);

		s.ReleaseBuffer();
	}

    return 0;
}

void CSidePane::OnNcPaint() 
{
	CControlBar::EraseNonClient();
}

void CSidePane::OnPaint() 
{
	CPaintDC dc(this);
	CControlBar::OnPaint();
}



void CSidePane::OnSize(UINT nType, int cx, int cy) 
{
    CSizingControlBar::OnSize(nType, cx, cy);

    if (IsWindow(m_pControl->GetSafeHwnd()))
		PositionControls() ;
}

void CSidePane::PositionControls() 
{
	CRect rc;
    GetClientRect(rc);
	
	if (m_pControl)  
	{
   		m_pControl->MoveWindow(rc.left, rc.top, rc.right, rc.bottom);
		m_pControl->CalcLayout(TRUE);
	}	
}

void CSidePane::OnHide() 
{
	ShowPane(FALSE);
}

void CSidePane::OnCaptionDrag(UINT nFlags, CPoint point) 
{
	CPoint pt; 
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	CSizingControlBar::OnLButtonDown(nFlags, pt);
}

