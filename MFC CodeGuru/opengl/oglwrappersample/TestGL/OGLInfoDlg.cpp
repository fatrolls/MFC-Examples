// OGLInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGL.h"
#include "OGLInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COGLInfoDlg dialog


COGLInfoDlg::COGLInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COGLInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COGLInfoDlg)
	m_accel = _T("");
	m_extensions = _T("");
	m_rend = _T("");
	m_vendor = _T("");
	m_version = _T("");
	//}}AFX_DATA_INIT
}


void COGLInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COGLInfoDlg)
	DDX_Text(pDX, IDC_STATIC_ACCELERATION, m_accel);
	DDX_Text(pDX, IDC_STATIC_EXTENSIONS, m_extensions);
	DDX_Text(pDX, IDC_STATIC_RENDERER, m_rend);
	DDX_Text(pDX, IDC_STATIC_VENDOR, m_vendor);
	DDX_Text(pDX, IDC_STATIC_VERSION, m_version);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COGLInfoDlg, CDialog)
	//{{AFX_MSG_MAP(COGLInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGLInfoDlg message handlers
