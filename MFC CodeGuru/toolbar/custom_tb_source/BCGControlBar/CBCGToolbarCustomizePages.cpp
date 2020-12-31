// CBCGToolbarCustomizePages.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CBCGToolbarCustomizePages.h"
#include "BCGtoolbar.h"
#include "BCGToolbarButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCustomizePage, CPropertyPage)
IMPLEMENT_DYNCREATE(CToolbarsPage, CPropertyPage)

extern CObList	gAllToolbars;

/////////////////////////////////////////////////////////////////////////////
// CCustomizePage property page

CCustomizePage::CCustomizePage() : CPropertyPage(CCustomizePage::IDD)
{
	//{{AFX_DATA_INIT(CCustomizePage)
	m_strButtonDescription = _T("");
	//}}AFX_DATA_INIT

	m_pImages = NULL;
}

CCustomizePage::~CCustomizePage()
{
	POSITION pos = m_Buttons.GetStartPosition();
	while (pos != NULL)
	{
		CObList* pCategoryButtonsList;
		CString string;
		
		m_Buttons.GetNextAssoc (pos, string, pCategoryButtonsList);
		ASSERT_VALID(pCategoryButtonsList);

		while (!pCategoryButtonsList->IsEmpty ())
		{
			delete pCategoryButtonsList->RemoveHead ();
		}

		delete pCategoryButtonsList;
	}

	m_Buttons.RemoveAll();
}

void CCustomizePage::SetImages (CBCGToolBarImages* pImages)
{
	m_pImages = pImages;
}

void CCustomizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizePage)
	DDX_Control(pDX, IDC_USER_TOOLS, m_wndUserTools);
	DDX_Control(pDX, IDC_CATEGORY, m_wndCategory);
	DDX_Control(pDX, IDC_BUTTONS_LIST, m_wndButtons);
	DDX_Text(pDX, IDC_BUTTON_DESCR, m_strButtonDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizePage, CPropertyPage)
	//{{AFX_MSG_MAP(CCustomizePage)
	ON_BN_CLICKED(IDC_BUTTONS_LIST, OnButtonsList)
	ON_CBN_SELCHANGE(IDC_CATEGORY, OnSelchangeCategory)
	ON_LBN_SELCHANGE(IDC_USER_TOOLS, OnSelchangeUserTools)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCustomizePage::OnButtonsList() 
{
	OnChangeSelButton (m_wndButtons.GetSelectedButton ());
}
//**************************************************************************************
void CCustomizePage::OnSelchangeCategory() 
{
	m_wndButtons.RemoveButtons ();
	m_wndUserTools.ResetContent ();

	int iIndex = m_wndCategory.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		m_wndButtons.Invalidate ();
		return;
	}

	CObList* pCategoryButtonsList = 
		(CObList*) m_wndCategory.GetItemData (iIndex);
	ASSERT_VALID (pCategoryButtonsList);

	if (pCategoryButtonsList == m_pUserCategory)
	{
		for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
			ASSERT (pButton != NULL);

			pButton->m_bUserButton = TRUE;

			int iIndex = m_wndUserTools.AddString (pButton->m_strText);
			m_wndUserTools.SetItemData (iIndex, (DWORD) pButton);
		}

		m_wndUserTools.EnableWindow ();
		m_wndUserTools.ShowWindow (SW_SHOW);

		m_wndButtons.EnableWindow (FALSE);
		m_wndButtons.ShowWindow (SW_HIDE);
	}
	else
	{
		for (POSITION pos = pCategoryButtonsList->GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pCategoryButtonsList->GetNext (pos);
			ASSERT (pButton != NULL);

			pButton->m_bUserButton = FALSE;

			m_wndButtons.AddButton (pButton);
		}

		m_wndUserTools.EnableWindow (FALSE);
		m_wndUserTools.ShowWindow (SW_HIDE);

		m_wndButtons.EnableWindow ();
		m_wndButtons.ShowWindow (SW_SHOW);

		m_wndButtons.Invalidate ();
	}
}
//**************************************************************************************
void CCustomizePage::OnSelchangeUserTools() 
{
	int iIndex = m_wndUserTools.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		OnChangeSelButton (NULL);
	}
	else
	{
		OnChangeSelButton ((CBCGToolbarButton*) m_wndUserTools.GetItemData (iIndex));
	}
}
//**************************************************************************************
BOOL CCustomizePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_wndButtons.SetImages (m_pImages);
	m_wndButtons.EnableDragFromList ();
	
	for (POSITION pos = m_Categories.GetHeadPosition(); pos != NULL;)
	{
		CString strCategory = m_Categories.GetNext (pos);

		CObList* pCategoryButtonsList;
		if (!m_Buttons.Lookup (strCategory, pCategoryButtonsList))
		{
			ASSERT (FALSE);
		}
		else
		{
			ASSERT_VALID(pCategoryButtonsList);

			int iIndex = m_wndCategory.AddString (strCategory);
			m_wndCategory.SetItemData (iIndex, (DWORD) pCategoryButtonsList);
		}
	}

	m_wndCategory.SetCurSel (0);
	OnSelchangeCategory ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//**********************************************************************************************
void CCustomizePage::OnChangeSelButton (CBCGToolbarButton* pSelButton)
{
	m_strButtonDescription = _T("");

	if (pSelButton != NULL)
	{
		if (pSelButton->m_nID == 0)
		{
			m_strButtonDescription = pSelButton->m_strText;
		}
		else
		{
			CFrameWnd* pParent = GetParentFrame ();
			if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
			{
				pParent->GetMessageString (pSelButton->m_nID,
							m_strButtonDescription);
			}
		}
	}

	m_pSelButton = pSelButton;
	UpdateData (FALSE);
}
//**************************************************************************************
void CCustomizePage::AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button)
{
	//-------------------------------------------------------------------
	// Create a new CBCGToolbarButton object (MFC class factory is used):
	//-------------------------------------------------------------------
	CRuntimeClass* pClass = button.GetRuntimeClass ();
	ASSERT (pClass != NULL);

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) pClass->CreateObject ();
	ASSERT_VALID (pButton);

	pButton->CopyFrom (button);

	//-------------------------------------------
	// Add a new button to the specific category:
	//-------------------------------------------
	CObList* pCategoryButtonsList;
	if (!m_Buttons.Lookup (lpszCategory, pCategoryButtonsList))
	{
		//--------------------------------
		// Category not found! Create new:
		//--------------------------------
		pCategoryButtonsList = new CObList;
		m_Buttons.SetAt (lpszCategory, pCategoryButtonsList);

		m_Categories.AddTail (lpszCategory);
	}

	pCategoryButtonsList->AddTail (pButton);

	pButton->OnAddToCustomizePage ();
}
//*************************************************************************************
BOOL CCustomizePage::SetUserCategory (LPCTSTR lpszCategory)
{
	CObList* pCategoryButtonsList;

	if (!m_Buttons.Lookup (lpszCategory, pCategoryButtonsList))
	{
		return FALSE;
	}

	m_pUserCategory = pCategoryButtonsList;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarsPage property page

CToolbarsPage::CToolbarsPage() : CPropertyPage(CToolbarsPage::IDD)
{
	//{{AFX_DATA_INIT(CToolbarsPage)
	m_bShowTooltips = CBCGToolBar::m_bShowTooltips;
	//}}AFX_DATA_INIT
}

CToolbarsPage::~CToolbarsPage()
{
}

void CToolbarsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolbarsPage)
	DDX_Control(pDX, IDC_TOOLBAR_LIST, m_wndToobarList);
	DDX_Check(pDX, IDC_SHOW_TOOLTIPS, m_bShowTooltips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolbarsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CToolbarsPage)
	ON_LBN_SELCHANGE(IDC_TOOLBAR_LIST, OnSelchangeToolbarList)
	ON_LBN_DBLCLK(IDC_TOOLBAR_LIST, OnDblclkToolbarList)
	ON_BN_CLICKED(IDC_SHOW_TOOLTIPS, OnShowTooltips)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CToolbarsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	for (POSITION pos = gAllToolbars.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (pos);
		ASSERT_VALID(pToolBar);

		CString strName;
		pToolBar->GetWindowText (strName);

		if (strName.IsEmpty ())
		{
			strName.LoadString (IDS_UNTITLED_TOOLBAR);
		}

		int iIndex = m_wndToobarList.AddString (strName);
		m_wndToobarList.SetItemData (iIndex, (DWORD) pToolBar);

		if (pToolBar->GetStyle () & WS_VISIBLE)
		{
			m_wndToobarList.SetCheck (iIndex, 1);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//*************************************************************************************
void CToolbarsPage::OnSelchangeToolbarList() 
{
	int iIndex = m_wndToobarList.GetCurSel ();
	if (iIndex == LB_ERR)
	{
		return;
	}

	CBCGToolBar* pToolBar = (CBCGToolBar*) m_wndToobarList.GetItemData (iIndex);
	ASSERT_VALID(pToolBar);

	CFrameWnd* pParentFrame = (pToolBar->m_pDockSite == NULL) ?
		pToolBar->GetDockingFrame() : pToolBar->m_pDockSite;
	ASSERT_VALID(pParentFrame);

	pParentFrame->ShowControlBar (pToolBar,
		m_wndToobarList.GetCheck (iIndex), FALSE);
}
//*************************************************************************************
void CToolbarsPage::OnDblclkToolbarList() 
{
	OnSelchangeToolbarList ();
}
//*************************************************************************************
void CToolbarsPage::ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow)
{
	if (m_wndToobarList.GetSafeHwnd () == NULL)
	{
		return;
	}

	for (int i = 0; i < m_wndToobarList.GetCount (); i ++)
	{
		CBCGToolBar* pListToolBar = (CBCGToolBar*) m_wndToobarList.GetItemData (i);
		ASSERT_VALID(pListToolBar);

		if (pListToolBar == pToolBar)
		{
			m_wndToobarList.SetCheck (i, bShow);
			break;
		}
	}
}
//**************************************************************************************
void CToolbarsPage::OnShowTooltips() 
{
	UpdateData ();
	CBCGToolBar::m_bShowTooltips = m_bShowTooltips;
}
