// CBCGToolbarCustomize.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "resource.h"
#include "CBCGToolbarCustomize.h"
#include "BCGToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CBCGToolbarCustomize*	g_pWndCustomize = NULL;

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarCustomize

IMPLEMENT_DYNAMIC(CBCGToolbarCustomize, CPropertySheet)

CBCGToolbarCustomize::CBCGToolbarCustomize(CWnd* pWndParent, 
								CBCGToolBarImages* pImages)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	ASSERT (pWndParent != NULL);
	m_pParentWnd = pWndParent;

	AddPage (&m_CustomizePage);
	AddPage (&m_ToolbarsPage);

	m_CustomizePage.SetImages (pImages);
}
//**************************************************************************************
CBCGToolbarCustomize::~CBCGToolbarCustomize()
{
}

BEGIN_MESSAGE_MAP(CBCGToolbarCustomize, CPropertySheet)
	//{{AFX_MSG_MAP(CBCGToolbarCustomize)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarCustomize message handlers

int CBCGToolbarCustomize::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	g_pWndCustomize = this;
	SetFrameCustMode (TRUE);
	return 0;
}
//**************************************************************************************
void CBCGToolbarCustomize::PostNcDestroy()
{
	g_pWndCustomize = NULL;
	SetFrameCustMode (FALSE);

	CPropertySheet::PostNcDestroy();
	delete this;
}
//**************************************************************************************
void CBCGToolbarCustomize::AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button)
{
	m_CustomizePage.AddButton (lpszCategory, button);
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::SetUserCategory (LPCTSTR lpszCategory)
{
	return m_CustomizePage.SetUserCategory (lpszCategory);
}
//**************************************************************************************
void CBCGToolbarCustomize::SetFrameCustMode (BOOL bCustMode)
{
	ASSERT_VALID (m_pParentWnd);

	//-------------------------------------------------------------------
	// Enable/disable all parent frame child windows (except docking bars
	// and our toolbars):
	//-------------------------------------------------------------------
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

	//-----------------------------------------------
	// Set/reset costumize mode for ALL our toolbars:
	//-----------------------------------------------
	CBCGToolBar::SetCustomizeMode (bCustMode);

	//-------------------------------------------------------------
	// Inform the parent frame about mode (for additional actions):
	//-------------------------------------------------------------
	m_pParentWnd->SendMessage (BCGM_CUSTOMIZETOOLBAR, (WPARAM) bCustMode);
}
//**************************************************************************************
BOOL CBCGToolbarCustomize::Create () 
{
	return CPropertySheet::Create (m_pParentWnd);
}
//*************************************************************************************
void CBCGToolbarCustomize::ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow)
{
	m_ToolbarsPage.ShowToolBar (pToolBar, bShow);
}
//*************************************************************************************
BOOL CBCGToolbarCustomize::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	//----------------------
	// Show "Cancel" button:
	//----------------------
	CWnd *pWndCancel = GetDlgItem (IDCANCEL);
	if (pWndCancel == NULL)
	{
		return bResult;
	}

	pWndCancel->ShowWindow (SW_SHOW);
	pWndCancel->EnableWindow ();

	CRect rectClientCancel;
	pWndCancel->GetClientRect (&rectClientCancel);
	pWndCancel->MapWindowPoints (this, &rectClientCancel);

	//-------------------------------
	// Enlarge property sheet window:
	//-------------------------------
	CRect rectWnd;
	GetWindowRect(rectWnd);	

	SetWindowPos(NULL, 0, 0,
		rectWnd.Width (),
		rectWnd.Height () + rectClientCancel.Height () + 10,
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	//-------------------------------------------------
	// Move "Cancel" button to the right bottom corner:
	//-------------------------------------------------
	pWndCancel->SetWindowPos (NULL, 
		rectClient.right - rectClientCancel.Width () - 10,
		rectClientCancel.top,
		0, 0,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

	//---------------------------------------------------
	// Change "Cancel" button's style to "DEFPUSHBUTTON":
	//---------------------------------------------------
	CWnd *pWndOk = GetDlgItem (IDOK);
	if (pWndOk != NULL)
	{
		pWndOk->ModifyStyle (BS_DEFPUSHBUTTON, 0);
	}

	pWndCancel->ModifyStyle (0, BS_DEFPUSHBUTTON);

	//--------------------------------------------------------
	// Replace "Cancel" text to "Close" 
	// (CPropertyPage::CancelToClose method does nothing in a 
	// modeless property sheet):
	//--------------------------------------------------------
	CString strCloseText;
	strCloseText.LoadString (IDS_CLOSE);

	pWndCancel->SetWindowText (strCloseText);

	return bResult;
}
//************************************************************************************
BOOL CBCGToolbarCustomize::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (LOWORD (wParam) == IDCANCEL)
	{
		DestroyWindow ();
		return TRUE;
	}
	
	return CPropertySheet::OnCommand(wParam, lParam);
}
