// ComputeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex11b.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int g_nCount = 0;

UINT ComputeThreadProc(LPVOID pParam)
{
	volatile int nTemp; // volatile else compiler optimizes too much

	for (g_nCount = 0; g_nCount < CComputeDlg::nMaxCount;
	                   ::InterlockedIncrement((long*) &g_nCount)) {
		for (nTemp = 0; nTemp < 10000; nTemp++) {
			// uses up CPU cycles
		}
	}
	// WM_THREADFINISHED is user-defined message
	::PostMessage((HWND) pParam, WM_THREADFINISHED, 0, 0);
	g_nCount = 0;
	return 0; // ends the thread
}


/////////////////////////////////////////////////////////////////////////////
// CComputeDlg dialog


CComputeDlg::CComputeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComputeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComputeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComputeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComputeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComputeDlg, CDialog)
	ON_MESSAGE(WM_THREADFINISHED, OnThreadFinished)
	//{{AFX_MSG_MAP(CComputeDlg)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputeDlg message handlers

void CComputeDlg::OnStart() 
{
	m_nTimer = SetTimer(1, 100, NULL); // 1/10 second
	ASSERT(m_nTimer != 0);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	AfxBeginThread(ComputeThreadProc, GetSafeHwnd(),
	               THREAD_PRIORITY_NORMAL);
}

void CComputeDlg::OnCancel() 
{
	if (g_nCount == 0) { // prior to Start button
		CDialog::OnCancel();
	}
	else { // computation in progress
		g_nCount = nMaxCount; // Force thread to exit
	}
}

void CComputeDlg::OnTimer(UINT nIDEvent) 
{
	CProgressCtrl* pBar = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
	pBar->SetPos(g_nCount * 100 / nMaxCount);
}

LRESULT CComputeDlg::OnThreadFinished(WPARAM wParam, LPARAM lParam)
{
	CDialog::OnOK();
	return 0;
}