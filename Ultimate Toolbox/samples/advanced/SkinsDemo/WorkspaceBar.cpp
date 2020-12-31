// WorkspaceBar.cpp : implementation file
//

#include "stdafx.h"
#include "skinsdemo.h"
#include "WorkspaceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar

#define IDC_SHORTCUT_BAR 7565

CWorkspaceBar::CWorkspaceBar()
{
}

CWorkspaceBar::~CWorkspaceBar()
{
}


BEGIN_MESSAGE_MAP(CWorkspaceBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(CWorkspaceBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(SHBN_SELECTITEM, IDC_SHORTCUT_BAR, OnShortcutBarSelectItem)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CWorkspaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetClientBorder(TRUE);

	// Create the shortcut bar
	m_ShortcutBar.Create(this, CRect(0, 0, 0, 0), SHBS_EDITHEADERS | SHBS_EDITITEMS | SHBS_DISABLEDRAGDROPITEM |
		SHBS_DISABLEDRAGDROPHEADER | SHBS_FLATGROUPBUTTON | SHBS_SHOWACTIVEALWAYS, IDC_SHORTCUT_BAR);
	InitShortcutBar();

	return 0;
}

void CWorkspaceBar::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeControlBar::OnSize(nType, cx, cy);
	
	// Size the tabs container accordingly
	CRect rectClient;
	GetClientRect(rectClient);
	m_ShortcutBar.MoveWindow(rectClient);
}

void CWorkspaceBar::InitShortcutBar()
{
	//	Populate shortcut bar
	m_ShortcutBar.SetImageList(&m_ilTree);

	SHB_GROUPINFO shbGroup;
	CString sText;

	// create image lists
	VERIFY(m_ilLarge.Create(IDB_LARGE,32,11,RGB(255, 0, 0)));
	VERIFY(m_ilSmall.Create(IDB_SMALL,16,11,RGB(255, 0, 0)));

	// Skins group
	sText=_T("Skins");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	m_ShortcutBar.InsertGroup(&shbGroup);

	// outlook group
	sText=_T("Outlook");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	m_ShortcutBar.InsertGroup(&shbGroup);

	// mail group
	sText=_T("Mail");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	m_ShortcutBar.InsertGroup(&shbGroup);

	// find the skins group and populate it
	sText=_T("Skins");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	HSHBGROUP hGroup=m_ShortcutBar.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_ShortcutBar.SetLCImageList(hGroup,&m_ilLarge,LVSIL_NORMAL);
	m_ShortcutBar.SetLCImageList(hGroup,&m_ilSmall,LVSIL_SMALL);

	m_ShortcutBar.InsertLCItem(hGroup, 0, _T("Classic"), 0);
	m_ShortcutBar.InsertLCItem(hGroup, 1, _T("Office XP"), 1);
	m_ShortcutBar.InsertLCItem(hGroup, 2, _T("Office 2003"), 2);
	m_ShortcutBar.ExpandGroup(hGroup);
	m_ShortcutBar.GetGroupListCtrl(hGroup)->ActivateItem(2);

	// fill standard list controls
	TCHAR shbszItems[][20]={_T("Inbox"),_T("Calendar"),_T("Contracts"), 
		_T("Tasks"),_T("Journal"),_T("Notes"),_T("Deleted Items"),_T("Inbox"),
		_T("Sent Items"),_T("Outbox"),_T("Deleted Items")};

	// find outlook group and populate it
	sText=_T("Outlook");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	hGroup=m_ShortcutBar.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_ShortcutBar.SetLCImageList(hGroup,&m_ilLarge,LVSIL_NORMAL);
	m_ShortcutBar.SetLCImageList(hGroup,&m_ilSmall,LVSIL_SMALL);

	for(int i=0 ; i<10; i++)
	for(int nIndex=0; nIndex<7 ; nIndex++)
	{
		CString sText=shbszItems[nIndex];
		m_ShortcutBar.InsertLCItem(hGroup,nIndex+7*i,sText,nIndex);
	}
	
	// find mail group and populate it
	sText=_T("Mail");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	hGroup=m_ShortcutBar.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_ShortcutBar.SetLCImageList(hGroup,&m_ilLarge,LVSIL_NORMAL);
	m_ShortcutBar.SetLCImageList(hGroup,&m_ilSmall,LVSIL_SMALL);

	for(int nIndex=7; nIndex<(sizeof(shbszItems)/sizeof(shbszItems[0])); nIndex++)
	{
		CString sText=shbszItems[nIndex];
		LV_ITEM lvi;
		lvi.iItem=nIndex-7;
		lvi.iSubItem=0;
		lvi.mask=LVIF_TEXT|LVIF_IMAGE;
		lvi.iImage=nIndex;
		lvi.cchTextMax=sText.GetLength();
		lvi.pszText=sText.GetBuffer(lvi.cchTextMax);
		sText.ReleaseBuffer();
		m_ShortcutBar.InsertLCItem(hGroup,&lvi);
	}

	DWORD dwBarStyle=m_ShortcutBar.GetBarStyle();
	dwBarStyle&=~(SHBS_DISABLEDRAGDROPHEADER|SHBS_DISABLEDRAGDROPITEM);
	dwBarStyle|=SHBS_DRAWITEMDRAGIMAGE|SHBS_DRAWHEADERDRAGIMAGE|SHBS_INFOTIP|
		SHBS_AUTOEXPAND|SHBS_ANIMATEEXPAND;
	m_ShortcutBar.SetBarStyle(dwBarStyle);
}

void CWorkspaceBar::OnShortcutBarSelectItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMSHORTCUTBAR pNMSHB = (LPNMSHORTCUTBAR) pNotifyStruct;
	ASSERT(pNMSHB != NULL);

	if (pNMSHB->nItem != -1)
	{
		// Change the skin
		if (m_ShortcutBar.GetGroupText(pNMSHB->hGroup) == _T("Skins"))
		{
			CString strSkinName = m_ShortcutBar.GetGroupListCtrl(pNMSHB->hGroup)->GetItemText(pNMSHB->nItem, 0);
			COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
			if (pSkinnedApp != NULL)
				pSkinnedApp->SetCurrentSkin(strSkinName);
		}
	}

	*result=0;
}