// ResizingPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ResizingPropPage.h"

#include "OXLayoutManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define OX_OFFSET (7)

IMPLEMENT_DYNCREATE(CResizingPropPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CResizingPropPage2, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CResizingPropPage1 property page

CResizingPropPage1::CResizingPropPage1() : CPropertyPage(CResizingPropPage1::IDD)
{
	//{{AFX_DATA_INIT(CResizingPropPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pLayoutManager = NULL;
}

CResizingPropPage1::~CResizingPropPage1()
{
	if (m_pLayoutManager != NULL)
		delete m_pLayoutManager;
}

void CResizingPropPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizingPropPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizingPropPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CResizingPropPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CResizingPropPage1::OnSetActive() 
{
	if (m_pLayoutManager == NULL)
	{
		if ((m_pLayoutManager = new COXLayoutManager(this)) != NULL)
		{
			ASSERT_VALID(m_pLayoutManager);

			//
			// Setup constraints
			m_pLayoutManager->SetConstraint(IDC_FRAME, OX_LMS_TOP | OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_FRAME, OX_LMS_BOTTOM | OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
			
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);

			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_EDIT);
			m_pLayoutManager->SetConstraint(IDC_LIST, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);
		}

		//
		// Insert some data into the listbox control
		TCHAR szBuffer[10];
		int i = 0;
		for (; i < 100; i++)
		{
			wsprintf(szBuffer, _T("Item #%d"), i);
			GetDlgItem(IDC_LIST)->SendMessage(LB_INSERTSTRING, i, (LPARAM)(LPCTSTR) szBuffer);
		}

		m_pLayoutManager->RedrawLayout();
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// CResizingPropPage2 property page

CResizingPropPage2::CResizingPropPage2() : CPropertyPage(CResizingPropPage2::IDD)
{
	//{{AFX_DATA_INIT(CResizingPropPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pLayoutManager = NULL;
}

CResizingPropPage2::~CResizingPropPage2()
{
	if (m_pLayoutManager != NULL)
		delete m_pLayoutManager;
}

void CResizingPropPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizingPropPage2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResizingPropPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CResizingPropPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CResizingPropPage2::OnSetActive() 
{
	if (m_pLayoutManager == NULL)
	{
		if ((m_pLayoutManager = new COXLayoutManager(this)) != NULL)
		{
			ASSERT_VALID(m_pLayoutManager);

			//
			// Setup constraints
			m_pLayoutManager->SetConstraint(IDC_FRAME, OX_LMS_TOP | OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
			m_pLayoutManager->SetConstraint(IDC_FRAME, OX_LMS_BOTTOM | OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
			
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_EDIT, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);

			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_EDIT);
			m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_BOTTOM, OX_LMT_SAME, -OX_OFFSET, IDC_FRAME);
		}

		//
		// Insert some data into the CTreeCtrl
		//
		CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
		if (pTree != NULL)
		{
			HTREEITEM hItem = pTree->InsertItem(_T("Root"));
			TCHAR szBuffer[10];
			
			for (int i = 0; i < 100; i++)
			{
				wsprintf(szBuffer, _T("Item #%d"), i);
				pTree->InsertItem(szBuffer, hItem);
			}

			pTree->ModifyStyle(NULL, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
			pTree->Expand(hItem, TVE_EXPAND);
		}

		m_pLayoutManager->RedrawLayout();
	}
	
	return CPropertyPage::OnSetActive();
}



BOOL CResizingPropPage1::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_LAYOUTTYPE));
	ASSERT(cs.lpszClass);

	return CPropertyPage::PreCreateWindow(cs);
}

BOOL CResizingPropPage2::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_LAYOUTTYPE));
	ASSERT(cs.lpszClass);

	return CPropertyPage::PreCreateWindow(cs);
}
