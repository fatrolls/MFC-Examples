// ResizingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "layout.h"
#include "ResizingDialog.h"

#include "OXLayoutManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OX_OFFSET (7)	// This is the default padding in the Visual C++ Dialog editor
						// so we use it here too. This number must be >= 0

/////////////////////////////////////////////////////////////////////////////
// CResizingDialog dialog


CResizingDialog::CResizingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CResizingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResizingDialog)
	//}}AFX_DATA_INIT

	m_pLayoutManager = NULL;
}

CResizingDialog::~CResizingDialog()
{
	if (m_pLayoutManager != NULL)
	{
		delete m_pLayoutManager;
		m_pLayoutManager = NULL;
	}
}

void CResizingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResizingDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CResizingDialog, CDialog)
	//{{AFX_MSG_MAP(CResizingDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizingDialog message handlers

BOOL CResizingDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ((m_pLayoutManager = new COXLayoutManager(this)) != NULL)
	{
		//
		// Create the layout for this window; See CLayoutView::OnInitialUpdate
		// for more detailed informaton.
		//

		// Size the OK button with right edge of the window
		// Size the CANCEL button with right edge of the window
		m_pLayoutManager->SetConstraint(IDOK, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
		m_pLayoutManager->SetConstraint(IDCANCEL, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);

		// Size the TEXT control with the left side of the picture control
		// and size it on the right side with the OK button (you could have used the
		// the cancel button since both buttons have the same dimensions)
		m_pLayoutManager->SetConstraint(IDC_TEXT, OX_LMS_LEFT, OX_LMT_OPPOSITE, OX_OFFSET, IDC_PICTURE);
		m_pLayoutManager->SetConstraint(IDC_TEXT, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -OX_OFFSET, IDOK);
		
		// Size the combobox with the right and left sides of the window
		m_pLayoutManager->SetConstraint(IDC_COMBO, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
		m_pLayoutManager->SetConstraint(IDC_COMBO, OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);

		// Size the tree with the left and right side of the window and on the top
		// with the combobox and on the bottom with bottom of the Window.
		m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_LEFT, OX_LMT_SAME, OX_OFFSET);
		m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_BOTTOM | OX_LMS_RIGHT, OX_LMT_SAME, -OX_OFFSET);
		m_pLayoutManager->SetConstraint(IDC_TREE, OX_LMS_TOP, OX_LMT_OPPOSITE, OX_OFFSET, IDC_COMBO);
			
		
		// Set the minimum and maximum sizes of the CTreeCtrl and CEdit controls
		//
		m_pLayoutManager->SetMinMax(IDC_TEXT, CSize(30, 0));
		m_pLayoutManager->SetMinMax(IDC_TREE, CSize(20, 40));
		
		
		/////////////////////////////////////////////////////////////
		// Insert some data into the controls
		//
		
		CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
		if (pTree != NULL)
		{
			TCHAR szBuffer[10];
			HTREEITEM hRoot = pTree->InsertItem(_T("Root"));
			for (int i = 0; i < 100; i++)
			{
				wsprintf(szBuffer, _T("Item #%d"), i);
				pTree->InsertItem(szBuffer, hRoot);
			}
			pTree->ModifyStyle(NULL, TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS);
			pTree->Expand(hRoot, TVE_EXPAND);
		}

		m_pLayoutManager->RedrawLayout();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

