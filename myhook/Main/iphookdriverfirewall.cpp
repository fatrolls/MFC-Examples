// IPHookDriverFirewall.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "MainDlg.h"
#include "IPHookDriverFirewall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvDlg dialog
IMPLEMENT_DYNCREATE(CIpHookDrvDlg, CRootDlg)

CIpHookDrvDlg::CIpHookDrvDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CIpHookDrvDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIpHookDrvDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pFrame = NULL;
}


void CIpHookDrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIpHookDrvDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIpHookDrvDlg, CRootDlg)
	//{{AFX_MSG_MAP(CIpHookDrvDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvDlg message handlers


/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverView

IMPLEMENT_DYNCREATE(CIPHookDriverView, CFormView)

CIPHookDriverView::CIPHookDriverView()
	: CFormView(CIPHookDriverView::IDD)
{
	//{{AFX_DATA_INIT(CIPHookDriverView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CIPHookDriverView::~CIPHookDriverView()
{
}

void CIPHookDriverView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPHookDriverView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPHookDriverView, CFormView)
	//{{AFX_MSG_MAP(CIPHookDriverView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverView diagnostics

#ifdef _DEBUG
void CIPHookDriverView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIPHookDriverView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverView message handlers
/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverDoc

IMPLEMENT_DYNCREATE(CIPHookDriverDoc, CDocument)

CIPHookDriverDoc::CIPHookDriverDoc()
{
}

BOOL CIPHookDriverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CIPHookDriverDoc::~CIPHookDriverDoc()
{
}


BEGIN_MESSAGE_MAP(CIPHookDriverDoc, CDocument)
	//{{AFX_MSG_MAP(CIPHookDriverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverDoc diagnostics

#ifdef _DEBUG
void CIPHookDriverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIPHookDriverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverDoc serialization

void CIPHookDriverDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverDoc commands
/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvFrame

IMPLEMENT_DYNCREATE(CIpHookDrvFrame, CFrameWnd)

CIpHookDrvFrame::CIpHookDrvFrame()
{
	m_sizeofFrame = CSize(0, 0);
}

CIpHookDrvFrame::~CIpHookDrvFrame()
{
}


BEGIN_MESSAGE_MAP(CIpHookDrvFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CIpHookDrvFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_FILE_CONSERVE, OnFileConserve)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONSERVE, OnUpdateFileConserve)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvFrame message handlers

BOOL CIpHookDrvDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();	
	CMainApp* pApp = (CMainApp*)AfxGetApp();
	//pApp->LoadStdProfileSettings(); 
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CIPHookDrvDocTemplate();
	pApp->AddDocTemplate(pDocTemplate);
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	ASSERT(pos != NULL);
	CSingleDocTemplate* pTemplate = (CSingleDocTemplate*)pApp->GetNextDocTemplate(pos);
	ASSERT(pTemplate != NULL);
	while(!pTemplate->IsKindOf(RUNTIME_CLASS(CIPHookDrvDocTemplate)))
		pTemplate = (CSingleDocTemplate*)pApp->GetNextDocTemplate(pos);
    ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CIPHookDrvDocTemplate)));
	pApp->m_pMainWnd = NULL;
	pTemplate->OpenDocumentFile(NULL, TRUE);
	m_pFrame = (CIpHookDrvFrame*)pApp->m_pMainWnd;
	CMainDlg* pParent = (CMainDlg*)GetParent();
	pApp->m_pMainWnd = pParent;
    m_pFrame->SetParent(this);
	m_pFrame->ModifyStyle(WS_BORDER, 0);
	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right += 22;
	m_pFrame->MoveWindow(rcClient);
	return TRUE; 
}

IMPLEMENT_DYNAMIC(CIPHookDrvDocTemplate, CSingleDocTemplate)

CIPHookDrvDocTemplate::CIPHookDrvDocTemplate()
		:CSingleDocTemplate(IDR_IPHOOKDRV, 
		                    RUNTIME_CLASS(CIPHookDriverDoc),
		                    RUNTIME_CLASS(CIpHookDrvFrame),       // main SDI frame window
		                    RUNTIME_CLASS(CIPHookDriverView))
{
}

void CIpHookDrvDlg::OnSize(UINT nType, int cx, int cy) 
{
	static iTimes = 0;
	CRootDlg::OnSize(nType, cx, cy);
	if (m_pFrame == NULL || !IsWindow(m_pFrame->m_hWnd))
		return;
	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right += 22;
	m_pFrame->MoveWindow(rcClient);	
	iTimes ++;
	if (iTimes == 2)
	{
		CRect rc;
		m_pFrame->GetWindowRect(&rc);
		m_pFrame->m_sizeofFrame = CSize(rc.Width(), rc.Height());
	}
}

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CIpHookDrvFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| /*CBRS_GRIPPER | */ CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_IPHOOKDRV))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

void CIpHookDrvFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
	if (m_sizeofFrame != CSize(0, 0))
	{
       lpMMI->ptMinTrackSize.x = m_sizeofFrame.cx;
	   lpMMI->ptMinTrackSize.y = m_sizeofFrame.cy;
	   lpMMI->ptMaxTrackSize.x = m_sizeofFrame.cx;
	   lpMMI->ptMaxTrackSize.y = m_sizeofFrame.cy;
	}
}

void CIpHookDrvFrame::OnFileConserve() 
{
	CIPHookDriverDoc* pDoc = (CIPHookDriverDoc*)GetActiveDocument();
	// 弹出保存对话框
	CFileDialog dlg(FALSE, "rul", NULL, 
		OFN_HIDEREADONLY | OFN_CREATEPROMPT, "Rule Files(*.rul)|*.rul||", NULL);
	if(dlg.DoModal() == IDCANCEL)
		return;

	// 写入文件
	CFile file;
	if(file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
	{
		for(int i=0; i<pDoc->m_aRules.size(); i++)
		{
			file.Write(&pDoc->m_aRules[i], sizeof(IPFilterRule));
		}
	}
	else
	{
		AfxMessageBox("保存文件出错！");
	}	
}

void CIpHookDrvFrame::OnUpdateFileConserve(CCmdUI* pCmdUI) 
{
	CIPHookDriverDoc* pDoc = (CIPHookDriverDoc*)GetActiveDocument();
	pCmdUI->Enable(pDoc->m_aRules.size() > 0);
}

void CIPHookDriverDoc::AddRule(UINT srcIp, UINT srcMask, USHORT srcPort,
		UINT dstIp, UINT dstMask, USHORT dstPort, UINT protocol, BOOL bDrop)
{
	// 添加到m_rules数组
	IPFilterRule rule;
	rule.sourceIP	  = srcIp;
	rule.sourceMask	  = srcMask;
	rule.sourcePort	  = srcPort;
	rule.destIP   = dstIp;
	rule.destMask = dstMask;
	rule.destPort = dstPort;
	rule.protocol	  = protocol;
	rule.bDrop 	  = bDrop;
	m_aRules.push_back(rule);
}

void CIPHookDriverDoc::ClearRules()
{
	m_aRules.clear();
}

void CIPHookDriverDoc::DeleteRules(int nPos)
{
	if(nPos >= m_aRules.size() || nPos < 0)
		return;
	m_aRules.erase(m_aRules.begin() + nPos);
}
