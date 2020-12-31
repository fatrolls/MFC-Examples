// SheetConfig.cpp : implementation file
// contains code for the property sheet and its three property pages

#include "stdafx.h"
#include "ex30a.h"
#include "SheetConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageClient property page

IMPLEMENT_DYNCREATE(CPageClient, CPropertyPage)

CPageClient::CPageClient() : CPropertyPage(CPageClient::IDD)
{
	//{{AFX_DATA_INIT(CPageClient)
	m_strProxy = _T("");
	m_strServerIP = _T("");
	m_strServerName = _T("");
	m_bUseProxy = FALSE;
	m_strFile = _T("");
	m_nPort = 0;
	//}}AFX_DATA_INIT
}

CPageClient::~CPageClient()
{
}

void CPageClient::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageClient)
	DDX_Text(pDX, IDC_PROXY, m_strProxy);
	DDX_Text(pDX, IDC_IPADDR, m_strServerIP);
	DDX_Text(pDX, IDC_SERVER, m_strServerName);
	DDX_Check(pDX, IDC_USEPROXY, m_bUseProxy);
	DDX_Text(pDX, IDC_FILE, m_strFile);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageClient, CPropertyPage)
	//{{AFX_MSG_MAP(CPageClient)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CPageServer property page

IMPLEMENT_DYNCREATE(CPageServer, CPropertyPage)

CPageServer::CPageServer() : CPropertyPage(CPageServer::IDD)
{
	//{{AFX_DATA_INIT(CPageServer)
	m_strDirect = _T("");
	m_nPortServer = 0;
	m_strDefault = _T("");
	//}}AFX_DATA_INIT
}

CPageServer::~CPageServer()
{
}

void CPageServer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageServer)
	DDX_Text(pDX, IDC_DIRECT, m_strDirect);
	DDX_Text(pDX, IDC_PORTSERVER, m_nPortServer);
	DDX_Text(pDX, IDC_DEFAULT, m_strDefault);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageServer, CPropertyPage)
	//{{AFX_MSG_MAP(CPageServer)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageClient message handlers
/////////////////////////////////////////////////////////////////////////////
// CPageAdv property page

IMPLEMENT_DYNCREATE(CPageAdv, CPropertyPage)

CPageAdv::CPageAdv() : CPropertyPage(CPageAdv::IDD)
{
	//{{AFX_DATA_INIT(CPageAdv)
	m_strIPServer = _T("");
	m_strIPClient = _T("");
	//}}AFX_DATA_INIT
}

CPageAdv::~CPageAdv()
{
}

void CPageAdv::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAdv)
	DDX_Text(pDX, IDC_IPSERVER, m_strIPServer);
	DDX_Text(pDX, IDC_IPCLIENT, m_strIPClient);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageAdv, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAdv)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSheetConfig

IMPLEMENT_DYNAMIC(CSheetConfig, CPropertySheet)

CSheetConfig::CSheetConfig(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSheetConfig::CSheetConfig(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_pageClient);
	AddPage(&m_pageServer);
	AddPage(&m_pageAdv);
}

CSheetConfig::~CSheetConfig()
{
}


BEGIN_MESSAGE_MAP(CSheetConfig, CPropertySheet)
	//{{AFX_MSG_MAP(CSheetConfig)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// message handlers
