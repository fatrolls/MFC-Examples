// OutlookView.cpp : implementation of the COutlookView class
//

#include "stdafx.h"
#include "Outlook.h"

#include "OutlookDoc.h"
#include "OutlookView.h"

#include "SHBPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_START			(100)
#define IDC_OUTLOOKBAR		(IDC_START + 1)
#define IDC_TREE			(IDC_START + 2)

#define	SHB_IDMPROPERTIES	(SHB_IDMUSER + 1)

/////////////////////////////////////////////////////////////////////////////
// COutlookView

IMPLEMENT_DYNCREATE(COutlookView, CView)

BEGIN_MESSAGE_MAP(COutlookView, CView)
	//{{AFX_MSG_MAP(COutlookView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(SHBN_CONTEXTMENU, IDC_OUTLOOKBAR, OnSHBContextMenu)
	ON_COMMAND(SHB_IDMPROPERTIES, OnProperties)
	ON_COMMAND(ID_SKIN_CLASSIC, OnSkinClassic)
	ON_COMMAND(ID_SKIN_OFFICEXP, OnSkinOfficexp)
	ON_COMMAND(ID_SKIN_OFFICE2003, OnSkinOffice2003)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookView construction/destruction

COutlookView::COutlookView()
{
	// TODO: add construction code here

}

COutlookView::~COutlookView()
{
}

BOOL COutlookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutlookView drawing

void COutlookView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	COutlookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COutlookView diagnostics

#ifdef _DEBUG
void COutlookView::AssertValid() const
{
	CView::AssertValid();
}

void COutlookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COutlookDoc* COutlookView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutlookDoc)));
	return (COutlookDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookView message handlers

int COutlookView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	const COLORREF rgb = RGB(255, 0, 255);

	m_shb.Create(this, CRect(0,0,0,0),
		SHBS_EDITHEADERS | SHBS_EDITITEMS | SHBS_DRAWHEADERDRAGIMAGE | SHBS_BOLDEXPANDEDGROUP | SHBS_SHOWACTIVEALWAYS | SHBS_DRAWITEMDRAGIMAGE | SHBS_ANIMATEEXPAND | SHBS_FLATGROUPBUTTON,
		IDC_OUTLOOKBAR,
		WS_CHILD | WS_VISIBLE,
		NULL);

	// create tree control 
	m_tree.Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS, CRect(0,0,0,0), &m_shb, IDC_TREE);

	TV_INSERTSTRUCT	tvstruct;
	TCHAR rgszItems[][20] = { _T("Mail Box"), _T("Calendar"), _T("Deleted Items"), _T("Inbox"), _T("Journal"), _T("Notes"), _T("Outbox"), _T("Sent Items") };
	VERIFY(m_ilTree.Create(IDB_BITMAP3, 16, 8, rgb));
	m_tree.SetImageList(&m_ilTree, TVSIL_NORMAL);

	HTREEITEM hParent = NULL;
	int nIndex = 0;
	for (nIndex = 0; nIndex < (sizeof(rgszItems) / sizeof(rgszItems[0])); nIndex++)
	{
		tvstruct.hParent = nIndex == 0 ? NULL : hParent;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = nIndex;
		tvstruct.item.iSelectedImage = nIndex;
		tvstruct.item.pszText = rgszItems[nIndex];
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		HTREEITEM hItem = m_tree.InsertItem(&tvstruct);
		hParent = hParent == NULL ? hItem : hParent;
	}

	{

//		VERIFY(m_ilTree2003.Create(25, 22, ILC_COLOR24 | ILC_MASK, 0, 10));

		CBitmap bm;
		bm.LoadBitmap(IDB_BITMAP5);

		BITMAP b;
		bm.GetBitmap(&b);

		const int imageCount = 5;

		VERIFY(m_ilTree2003.Create(25, 22, ILC_COLOR32 | ILC_MASK, imageCount, imageCount) > 0);

		CDC dc;
		dc.CreateCompatibleDC(NULL);

		CDC srcDC;
		srcDC.CreateCompatibleDC(&dc);
		CBitmap * pOldSrcBmp = srcDC.SelectObject(&bm);

		for(int i=0;i<=imageCount; ++i)
		{
			CBitmap bitmap;
			bitmap.CreateBitmap(25, b.bmHeight, 1, 32, NULL);
			CBitmap * pOldDestBmp = dc.SelectObject(&bitmap);

			dc.BitBlt(0, 0, 25, b.bmHeight, &srcDC, 25 * i, 0, SRCCOPY);
			
			dc.SelectObject(pOldDestBmp);
		 	
			m_ilTree2003.Add(&bitmap, RGB(255, 0, 255));
		}

		srcDC.SelectObject(pOldSrcBmp);
	}

	//	populate shortcut bar
	m_shb.SetImageList(&m_ilTree2003);

	SHB_GROUPINFO shbGroup;
	CString sText;

	// create image lists
	VERIFY(m_ilLarge.Create(IDB_BITMAP1, 32, 11, rgb));
	VERIFY(m_ilSmall.Create(IDB_BITMAP2, 16, 11, rgb));

	// outlook group
	sText = _T("Outlook");
	shbGroup.nMask = SHBIF_TEXT;
	shbGroup.nTextMax = sText.GetLength();
	shbGroup.pszText = sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	HSHBGROUP group = m_shb.InsertGroup(&shbGroup);
	m_shb.SetGroupImage(group, 0);

	// mail group
	sText = _T("Mail");
	shbGroup.nMask = SHBIF_TEXT;
	shbGroup.nTextMax = sText.GetLength();
	shbGroup.pszText = sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	group = m_shb.InsertGroup(&shbGroup);
	m_shb.SetGroupImage(group, 1);

	// group with tree control child window
	sText = _T("Other");
	shbGroup.nMask = SHBIF_TEXT | SHBIF_CHILDWND;
	shbGroup.nTextMax = sText.GetLength();
	shbGroup.pszText = sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	shbGroup.hwndChild = m_tree.GetSafeHwnd();
	group = m_shb.InsertGroup(&shbGroup);
	m_shb.SetGroupImage(group, 2);
	HSHBGROUP hGroup = m_shb.FindGroup(&shbGroup);
	m_shb.SetGroupBkColor(hGroup, ::GetSysColor(COLOR_WINDOW));

	// fill standard list controls
	TCHAR shbszItems[][20]= { _T("Inbox"), _T("Calendar"), _T("Contacts"), _T("Tasks"), _T("Journal"), _T("Notes"), _T("Deleted Items"), _T("Inbox"), _T("Sent Items"), _T("Outbox"), _T("Deleted Items") };

	// find outlook group and populate it
	sText = _T("Outlook");
	shbGroup.nMask = SHBIF_TEXT;
	shbGroup.nTextMax = sText.GetLength();
	shbGroup.pszText = sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	hGroup = m_shb.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_shb.SetLCImageList(hGroup, &m_ilLarge, LVSIL_NORMAL);
	m_shb.SetLCImageList(hGroup, &m_ilSmall, LVSIL_SMALL);

	for(nIndex = 0; nIndex < 7 ; nIndex++)
	{
		CString sText = shbszItems[nIndex];
		LV_ITEM lvi;
		lvi.iItem = nIndex;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT|LVIF_IMAGE;
		lvi.iImage = nIndex;
		lvi.cchTextMax = sText.GetLength();
		lvi.pszText = sText.GetBuffer(lvi.cchTextMax);
		sText.ReleaseBuffer();
		m_shb.InsertLCItem(hGroup, &lvi);
	}
	m_shb.ExpandGroup(hGroup);
	
	// find mail group and populate it
	sText = _T("Mail");
	shbGroup.nMask = SHBIF_TEXT;
	shbGroup.nTextMax = sText.GetLength();
	shbGroup.pszText = sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	hGroup = m_shb.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_shb.SetLCImageList(hGroup, &m_ilLarge, LVSIL_NORMAL);
	m_shb.SetLCImageList(hGroup, &m_ilSmall, LVSIL_SMALL);

	for (nIndex = 7; nIndex < (sizeof(shbszItems) / sizeof(shbszItems[0])); nIndex++)
	{
		CString sText = shbszItems[nIndex];
		LV_ITEM lvi;
		lvi.iItem = nIndex - 7;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		lvi.iImage = nIndex;
		lvi.cchTextMax = sText.GetLength();
		lvi.pszText = sText.GetBuffer(lvi.cchTextMax);
		sText.ReleaseBuffer();
		m_shb.InsertLCItem(hGroup, &lvi);
	}
	
	return 0;
}

void COutlookView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CRect rect(0, 0, cx, cy);
	
	if (::IsWindow(m_shb.GetSafeHwnd()))
		m_shb.MoveWindow(&rect);
}

void COutlookView::OnSHBContextMenu(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	LPSHBCONTEXTMENU pSHBCM = (LPSHBCONTEXTMENU)((LPNMSHORTCUTBAR) pNotifyStruct)->lParam;
	if (pSHBCM->pShortcutBar->GetSafeHwnd() == m_shb.GetSafeHwnd() && m_shb.GetExpandedGroup() != NULL)
	{
		CMenu* pMenu = pSHBCM->pMenu;
		if (pMenu->GetMenuItemCount() > 0)
			pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING, SHB_IDMPROPERTIES, _T("Properties..."));
	}

	*pResult = 0;
}

void COutlookView::OnProperties()
{
	CSHBPropertiesDlg propertiesDlg(&m_shb);
	propertiesDlg.DoModal();
}
void COutlookView::OnSkinClassic()
{
	m_shb.SetImageList(&m_ilTree);

	COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
	if (pSkinnedApp != NULL)
		pSkinnedApp->SetCurrentSkin(OXSkinClassic);
}


void COutlookView::OnSkinOfficexp()
{
	m_shb.SetImageList(&m_ilTree);

	COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
	if (pSkinnedApp != NULL)
		pSkinnedApp->SetCurrentSkin(OXSkinOfficeXP);
}

void COutlookView::OnSkinOffice2003()
{
	m_shb.SetImageList(&m_ilTree2003);

	COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
	if (pSkinnedApp != NULL)
		pSkinnedApp->SetCurrentSkin(OXSkinOffice2003);
}
