// Dialog2.cpp : implementation file
//

#include "stdafx.h"
#include "dlgmgrtest.h"
#include "Dialog2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialog2 dialog

IMPLEMENT_LAYOUT(Dialog2)


Dialog2::Dialog2(CWnd* pParent /*=NULL*/)
	: CDialogMgr(Dialog2::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dialog2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogMgr::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dialog2)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dialog2, CDialogMgr)
	//{{AFX_MSG_MAP(Dialog2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dialog2 message handlers

BOOL Dialog2::OnInitDialog() 
{
	CDialogMgr::OnInitDialog();

	// Add some Item
	TC_ITEM tItem;
	tItem.mask = TCIF_TEXT;
	tItem.pszText = "TEST";
	m_tab.InsertItem(0,&tItem);
	
	// define the layout
	////////////////////

	// the bottom pane
	CPane*	paneBottom = new CPane(CPane::HORIZONTAL);
	paneBottom->addItem( new CPaneItem( NULL, CPaneBase::GREEDY));			// Greedy
	paneBottom->addItem( new CPaneItem( IDOK, this, CPaneBase::NORESIZE));
	paneBottom->addItem( new CPaneItem( IDCANCEL, this, CPaneBase::NORESIZE));


	// (green) holding a spacer and the ListCtrl
	CPane*	paneList = new CPane(CPane::VERTICAL);
	paneList->addItem( new CPaneItem( &m_list, CPaneBase::GREEDY));

	// (blue) the pane with the tab attached with an ExtraBorder
	CPane* paneTab  = new CPaneTab(&m_tab, CPane::HORIZONTAL);
	paneTab->addItem( paneList );

	// (red) the root pane 
	m_pRootPane = new CPane(CPane::VERTICAL);
	m_pRootPane->addItem( paneTab );
	m_pRootPane->addItem( paneBottom, CPaneBase::ABSOLUTE_VERT );

	UpdateLayout();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
