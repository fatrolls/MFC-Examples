// proctestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "proctest.h"
#include "proctestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProctestDlg dialog

CProctestDlg::CProctestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProctestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProctestDlg)
	m_strOs = _T("");
	m_strProcessToCheck = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProctestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProctestDlg)
	DDX_Control(pDX, IDC_PROCESSLIST, m_ctrlProcLB);
	DDX_Text(pDX, IDC_OSMESSAGE, m_strOs);
	DDX_Text(pDX, IDC_PROCESS_NAME, m_strProcessToCheck);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProctestDlg, CDialog)
	//{{AFX_MSG_MAP(CProctestDlg)
	ON_BN_CLICKED(IDC_GETALLPROCS, OnGetallprocs)
	ON_BN_CLICKED(IDC_CHECKIFACTIVE, OnCheckifactive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProctestDlg message handlers

BOOL CProctestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if(!m_win32proc.Init())
		AfxMessageBox(m_win32proc.GetLastError());
	m_strOs=m_win32proc.IsWinNT() ? "Using Win NT config" : "Using Win 95 config";

	UpdateData (FALSE);

	return TRUE;  
}


void CProctestDlg::OnGetallprocs() 
{
	//clear the list box...
	m_ctrlProcLB.ResetContent();
	CWaitCursor wait;
	if (!m_win32proc.EnumAllProcesses())
	{
		AfxMessageBox(m_win32proc.GetLastError());
		return;
	}
	//populate the list box
	int size=m_win32proc.GetAllProcessesNames()->GetSize();
	for (int i=0;i<size;i++)
		m_ctrlProcLB.AddString(m_win32proc.GetAllProcessesNames()->GetAt(i));

}



void CProctestDlg::OnCheckifactive() 
{
	CWaitCursor wait;
	UpdateData(TRUE);
	if (m_strProcessToCheck=="")
	{
		AfxMessageBox("You must supply a process name to check for!");
		return;
	}
	
	bool bStatus;
	
	if (!m_win32proc.GetProcessStatus(&m_strProcessToCheck,&bStatus))
	{
		AfxMessageBox(m_win32proc.GetLastError());
		return;
	}
	if (bStatus)
		AfxMessageBox(m_strProcessToCheck+" is running!");
	else		
		AfxMessageBox(m_strProcessToCheck+" is NOT running!");


	
}

