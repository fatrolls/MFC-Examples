// IOCPSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iocp.h"
#include "IOCPSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IOCPSettingsDlg dialog


IOCPSettingsDlg::IOCPSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IOCPSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(IOCPSettingsDlg)
	m_iMaxNumberOfConnections = 1201;
	m_iMaxNrOfFreeBuff = 0;
	m_iMaxNrOfFreeContext = 0;
	m_iNrOfIOWorkers = 1;
	m_iNrOfLogicalWorkers = 0;
	m_iPortNr = 999;
	m_bReadInOrder = TRUE;
	m_iSendInOrder = TRUE;
	m_iNrOfPendlingReads = 4;
	//}}AFX_DATA_INIT

}


void IOCPSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IOCPSettingsDlg)
	DDX_Text(pDX, IDC_MAXNUMOFCONNECTION, m_iMaxNumberOfConnections);
	DDX_Text(pDX, IDC_NROFFREEBUFF, m_iMaxNrOfFreeBuff);
	DDX_Text(pDX, IDC_NROFFREECONTEXT, m_iMaxNrOfFreeContext);
	DDX_Text(pDX, IDC_NROFIOWORKERS, m_iNrOfIOWorkers);
	DDX_Text(pDX, IDC_NROFLOGICWORKERS, m_iNrOfLogicalWorkers);
	DDX_Text(pDX, IDC_PORTNR, m_iPortNr);
	DDX_Check(pDX, IDC_RECEIVEDORDERED, m_bReadInOrder);
	DDX_Check(pDX, IDC_SENDORDERED, m_iSendInOrder);
	DDX_Text(pDX, IDC_NRPENDLINGREAD, m_iNrOfPendlingReads);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IOCPSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(IOCPSettingsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IOCPSettingsDlg message handlers
