// NewWizPage.cpp : implementation file
//

#include "stdafx.h"
#include "NewWizPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewWizPage dialog



CNewWizPage::CNewWizPage(LPCTSTR lpszTemplateName, CWnd* pParent)
                   :CDialog(lpszTemplateName,pParent)
{
  m_bCreated = FALSE;
  m_bActive = FALSE;
  m_nDialogID = 0;
  m_pParent = NULL; 
}


CNewWizPage::CNewWizPage(UINT nIDTemplate, CWnd* pParent)
                   :CDialog(nIDTemplate,pParent)
{
  m_bCreated = FALSE;
  m_bActive = FALSE;
  m_nDialogID = nIDTemplate;
  m_pParent = NULL; 
}

CNewWizPage::~CNewWizPage()
{
}



void CNewWizPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewWizPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewWizPage, CDialog)
	//{{AFX_MSG_MAP(CNewWizPage)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewWizPage message handlers


BOOL CNewWizPage::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// create the large font
	m_LargeFont.CreateFont(-16, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

  DWORD style = GetStyle();
  ASSERT((style & WS_CHILD) != 0);
  ASSERT((style & WS_BORDER) == 0);
  ASSERT((style & WS_DISABLED) != 0);

	m_Brush.CreateSolidBrush(RGB(255, 255, 255));


  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CNewWizPage::OnCreatePage()
{
	return TRUE;
}

void CNewWizPage::OnDestroyPage()
{
}


HBRUSH CNewWizPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	switch (nCtlColor)
	{	   
		case CTLCOLOR_STATIC:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255,255,255));
		case CTLCOLOR_EDIT:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255,255,255));
		case CTLCOLOR_LISTBOX:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255,255,255));
		case CTLCOLOR_SCROLLBAR:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255,255,255));
		case CTLCOLOR_BTN:
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkColor(RGB(255,255,255));
		case CTLCOLOR_DLG:	    
			return m_Brush;
	}	
	
	// TODO: Return a different brush if the default is not desired
	return m_Brush;
}


// refer to CPropertyPage class members for a description of this function
void CNewWizPage::OnCancel()
{
}


// refer to CPropertyPage class members for a description of this function
BOOL CNewWizPage::OnKillActive()
{
	return TRUE;
}



// called when the page is set active
void CNewWizPage::OnSetActive()
{
}



// refer to CPropertyPage class members for a description of this function
BOOL CNewWizPage::OnQueryCancel()
{
	return TRUE;
}


// refer to CPropertyPage class members for a description of this function
// return -1 to prevent changing pages
// to move to a page other than the previous one, return the 
// Dialog resource ID of the page to display
LRESULT CNewWizPage::OnWizardBack()
{
	return 0;
}


// refer to CPropertyPage class members for a description of this function
// return -1 to prevent changing pages
// to move to a page other than the next one, return the 
// Dialog resource ID of the page to display
LRESULT CNewWizPage::OnWizardNext()
{
	return 0;
}



// refer to CPropertyPage class members for a description of this function
BOOL CNewWizPage::OnWizardFinish()
{
	return TRUE;
}
