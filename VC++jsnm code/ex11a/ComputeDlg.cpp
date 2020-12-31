// ComputeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex11a.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComputeDlg dialog


CComputeDlg::CComputeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComputeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComputeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nCount = 0;
}


void CComputeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComputeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComputeDlg, CDialog)
	//{{AFX_MSG_MAP(CComputeDlg)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComputeDlg message handlers

void CComputeDlg::OnStart() 
{
	MSG message;

	m_nTimer = SetTimer(1, 100, NULL); // 1/10 second
	ASSERT(m_nTimer != 0);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	volatile int nTemp;
	for (m_nCount = 0; m_nCount < nMaxCount; m_nCount++) {
		for (nTemp = 0; nTemp < 10000; nTemp++) {
			// uses up CPU cycles
		}
		if (::PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	}
	CDialog::OnOK();
}

void CComputeDlg::OnCancel() 
{
	TRACE("entering CComputeDlg::OnCancel\n");
	if (m_nCount == 0) {      // prior to Start button
		CDialog::OnCancel();
	}
	else {                    // computation in progress
		m_nCount = nMaxCount; // Force exit from OnStart
	}
}

void CComputeDlg::OnTimer(UINT nIDEvent) 
{
	CProgressCtrl* pBar = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
	pBar->SetPos(m_nCount * 100 / nMaxCount);
}
