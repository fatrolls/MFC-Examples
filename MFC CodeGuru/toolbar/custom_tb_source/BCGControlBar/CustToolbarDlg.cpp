// CustToolbarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "resource.h"
#include "CustToolbarDlg.h"
#include "BCGtoolbar.h"
#include "BCGToolbarButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustToolbarDlg dialog


CCustToolbarDlg::CCustToolbarDlg(CWnd* pParent, CBCGToolBarImages* pImages)
	: CDialog (IDD_CUST_TOOLBAR, pParent)
{
	ASSERT (pParent != NULL);
	ASSERT (pImages != NULL);

	//{{AFX_DATA_INIT(CCustToolbarDlg)
	m_strButtonDescription = _T("");
	//}}AFX_DATA_INIT

	m_pParentWnd = pParent;

	m_pImages = pImages;
	m_pSelButton = NULL;
	m_pUserCategory = NULL;
}

CCustToolbarDlg::~CCustToolbarDlg ()
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

void CCustToolbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustToolbarDlg)
	DDX_Control(pDX, IDC_USER_TOOLS, m_wndUserTools);
	DDX_Control(pDX, IDC_BUTTONS_LIST, m_wndButtons);
	DDX_Control(pDX, IDC_CATEGORY, m_wndCategory);
	DDX_Text(pDX, IDC_BUTTON_DESCR, m_strButtonDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustToolbarDlg, CDialog)
	//{{AFX_MSG_MAP(CCustToolbarDlg)
	ON_WM_NCDESTROY()
	ON_WM_ACTIVATEAPP()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_CATEGORY, OnSelchangeCategory)
	ON_LBN_SELCHANGE(IDC_USER_TOOLS, OnSelchangeUserTools)
	ON_BN_CLICKED(IDC_BUTTONS_LIST, OnButtonsList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustToolbarDlg message handlers

BOOL CCustToolbarDlg::Create()
{
	return CDialog::Create (IDD_CUST_TOOLBAR, m_pParentWnd);
}
//**********************************************************************************************
BOOL CCustToolbarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_pParentWnd->SendMessage (BCGM_CUSTOMIZETOOLBAR, (WPARAM) TRUE))
	{
		SetFrameCustMode (TRUE);
	}

	m_wndButtons.SetImages (m_pImages);
	
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
void CCustToolbarDlg::OnNcDestroy() 
{
	if (m_pParentWnd->SendMessage (BCGM_CUSTOMIZETOOLBAR, (WPARAM) FALSE))
	{
		SetFrameCustMode (FALSE);
	}

	CDialog::OnNcDestroy();
	delete this;
}
//**********************************************************************************************
void CCustToolbarDlg::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CDialog::OnActivateApp(bActive, hTask);

	if (bActive)
	{
		SetFocus ();
	}
}
//**********************************************************************************************
int CCustToolbarDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CenterWindow ();
	return 0;
}
//**********************************************************************************************
void CCustToolbarDlg::OnCancel() 
{
	DestroyWindow ();
}
//**********************************************************************************************
void CCustToolbarDlg::OnChangeSelButton (CBCGToolbarButton* pSelButton)
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
//******************************************************************
void CCustToolbarDlg::AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button)
{
	CBCGToolbarButton* pButton = new CBCGToolbarButton (button);
	ASSERT_VALID(pButton);

	CObList* pCategoryButtonsList;
	if (!m_Buttons.Lookup (lpszCategory, pCategoryButtonsList))
	{
		pCategoryButtonsList = new CObList;
		m_Buttons.SetAt (lpszCategory, pCategoryButtonsList);

		m_Categories.AddTail (lpszCategory);
	}

	pCategoryButtonsList->AddTail (pButton);
}
//******************************************************************
void CCustToolbarDlg::AddButton (LPCTSTR lpszCategory, UINT uiID, int iImage, LPCTSTR lpszText)
{
	CBCGToolbarButton button;

	button.m_nID = uiID;
	button.m_iImage = iImage;
	button.m_bDragFromCollection = TRUE;

	if (lpszText != NULL)
	{
		button.m_strText = lpszText;
	}

	AddButton (lpszCategory, button);
}
//****************************************************************
BOOL CCustToolbarDlg::SetUserCategory (LPCTSTR lpszCategory)
{
	CObList* pCategoryButtonsList;

	if (!m_Buttons.Lookup (lpszCategory, pCategoryButtonsList))
	{
		return FALSE;
	}

	m_pUserCategory = pCategoryButtonsList;
	return TRUE;
}
//****************************************************************
void CCustToolbarDlg::OnSelchangeCategory() 
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
//*********************************************************************
void CCustToolbarDlg::OnSelchangeUserTools() 
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
//*********************************************************************
void CCustToolbarDlg::OnButtonsList() 
{
	OnChangeSelButton (m_wndButtons.GetSelectedButton ());
}
//*********************************************************************
void CCustToolbarDlg::SetFrameCustMode (BOOL bCustMode)
{
	CWnd* pWndChild = m_pParentWnd->GetWindow (GW_CHILD);
	while (pWndChild != NULL)
	{
		CRuntimeClass* pChildClass = pWndChild->GetRuntimeClass ();
		if (pChildClass == NULL ||
			(!pChildClass->IsDerivedFrom (RUNTIME_CLASS (CDockBar)) &&
			!pChildClass->IsDerivedFrom (RUNTIME_CLASS (CBCGToolBar))))
		{
			pWndChild->EnableWindow (!bCustMode);
		}

		pWndChild = pWndChild->GetNextWindow ();
	}

	CBCGToolBar::SetCustomizeMode (bCustMode);
}
