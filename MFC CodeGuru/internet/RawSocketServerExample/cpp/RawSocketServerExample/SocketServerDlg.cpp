// SocketServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SocketServer.h"
#include "SocketServerDlg.h"
#include "ClosingDialog.h"
#include "names.h"
#include <winnls.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocketServerDlg dialog

CSocketServerDlg::CSocketServerDlg(Worker& rWorker, 
			CWizThreadDispatcher& rDispatcher,
			CWnd* pParent /*=NULL*/)
	: CDialog(CSocketServerDlg::IDD, pParent),
	  m_rWorker (rWorker),
	  m_rDispatcher (rDispatcher)
{
	//{{AFX_DATA_INIT(CSocketServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSocketServerDlg)
	DDX_Control(pDX, IDC_EDIT3, m_nRequests);
	DDX_Control(pDX, IDC_EDIT2, m_nMaximum);
	DDX_Control(pDX, IDC_EDIT1, m_cCurrent);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSocketServerDlg, CDialog)
	//{{AFX_MSG_MAP(CSocketServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocketServerDlg message handlers

BOOL CSocketServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(1,100,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSocketServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSocketServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSocketServerDlg::OnTimer(UINT nIDEvent) 
{
	static int i1 = 0, i2 = 0, i3 = 0;
	CWizCritSect cs (m_rWorker.cs);
	if (i1 != m_rWorker.m_nCurrThreads)
		{ 
		i1 = m_rWorker.m_nCurrThreads; 
		SetDlgItemInt(IDC_EDIT1, i1); 
		}
	if (i2 != m_rWorker.m_nMaxThreads)
		{ 
		i2 = m_rWorker.m_nMaxThreads; 
		SetDlgItemInt(IDC_EDIT2, i2); 
		}
	if (i3 != m_rWorker.m_nRequests)
		{ 
		i3 = m_rWorker.m_nRequests; 
		SetDlgItemInt(IDC_EDIT3, i3); 
		}
}


void CSocketServerDlg::OnOK() 
{
	CDialog::OnOK();

	CClosingDialog closing;
	m_rDispatcher.MsgStop(&closing, FINISHClosingDialog);
	closing.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
Worker::Worker()
		: m_nCurrThreads (0), m_nMaxThreads (0) , m_nRequests(0) ,
		  CWizRawSocketListener (1966)
{
}


BOOL Worker::TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent)
{
	{
	CWizCritSect wcs (cs);
	if(++m_nCurrThreads > m_nMaxThreads)
		m_nMaxThreads = m_nCurrThreads;
	}
	if (!CWizRawSocketListener::TreatData (hShutDownEvent, hDataTakenEvent))
		return FALSE;
	{
	CWizCritSect wcs (cs);
	--m_nCurrThreads;
	++m_nRequests;
	}
	return TRUE;
}


BOOL Worker::ReadWrite (CWizReadWriteSocket& socket)
{
	LPCTSTR	out = _T("Unknown");
	TCHAR buff[500];
	int  Len = socket.ReadString(buff, 500);
	if (Len == 0)
		return FALSE;
	for (INDEX i = 0; i < nNames; i++)
		{
		for (INDEX j = 0; j < Len; j++)
			if (buff [j] != Names[i][0][j])
				break;
		if (j == Len && Names[i][0][Len] == 0)
			{
			out = Names[i][1];
			break;
			}
		}
	return socket.WriteString(out);
}



