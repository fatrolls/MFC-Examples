// LogoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "docktest.h"
#include "LogoDlg.h"
#include "OxFrameWndDock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg dialog


CLogoDlg::CLogoDlg(CWnd* pParent /*=NULL*/)
	: COXSizeDialogBar()
{
	//{{AFX_DATA_INIT(CLogoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	UNREFERENCED_PARAMETER(pParent);
}


void CLogoDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogoDlg)
	DDX_Control(pDX, IDC_OXBUTTON, m_LogoButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogoDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CLogoDlg)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_OXBUTTON, OnOxbutton)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg message handlers

BOOL CLogoDlg::Create(CWnd* pParentWnd, UINT nIDTemplate,
					  UINT nStyle, UINT nID)
	{
	if (!COXSizeDialogBar::Create(pParentWnd, MAKEINTRESOURCE(nIDTemplate), nStyle, nID))
		return FALSE;

	return TRUE;  
	}

int CLogoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

BOOL CLogoDlg::OnInitDialog() 
{
	COXSizeDialogBar::OnInitDialog();
	
	UpdateData(FALSE);

	m_LogoButton.LoadBitmap(IDB_BITMAP2);
	m_LogoButton.SetTrackLook();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CLogoDlg::OnOxbutton() 
{
	// TODO: Add your control notification handler code here
	CPtrArray arrViewBars;
	CWnd* pWnd=AfxGetMainWnd()->GetWindow(GW_CHILD);
	while (pWnd != NULL)
	{
		if(pWnd->IsKindOf(RUNTIME_CLASS(COXSizeViewBar)) && 
			!((COXSizeViewBar*)pWnd)->IsFloating())
		{
			arrViewBars.Add(pWnd->GetSafeHwnd());
			((COXSizeViewBar*)pWnd)->m_pDockContext->ToggleDocking();
		}
		pWnd=pWnd->GetNextWindow();
	}
	((CMDIFrameWnd*)AfxGetMainWnd())->RecalcLayout();
}

void CLogoDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
