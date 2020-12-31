// SieveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sieve.h"
#include "SieveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSieveDlg dialog

CSieveDlg::CSieveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSieveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSieveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSieveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSieveDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSieveDlg, CDialog)
	//{{AFX_MSG_MAP(CSieveDlg)
	ON_BN_CLICKED(IDC_START, OnStart)
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_USER_THREAD_FINISHED, OnThreadFinished)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSieveDlg message handlers

BOOL CSieveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	return TRUE;
}

void CSieveDlg::OnStart() 
{
	int nMax = GetDlgItemInt (IDC_MAX);
	if (nMax < 10) {
		MessageBox (_T ("The number you enter must be 10 or higher"));
		GetDlgItem (IDC_MAX)->SetFocus ();
		return;
	}

    SetDlgItemText (IDC_RESULT, _T (""));
    GetDlgItem (IDC_START)->EnableWindow (FALSE);

	THREADPARMS* ptp = new THREADPARMS;
	ptp->nMax = nMax;
	ptp->hWnd = m_hWnd;
	AfxBeginThread (ThreadFunc, ptp);
}

LONG CSieveDlg::OnThreadFinished (WPARAM wParam, LPARAM lParam)
{
    SetDlgItemInt (IDC_RESULT, (int) wParam);
    GetDlgItem (IDC_START)->EnableWindow (TRUE);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Global functions

UINT ThreadFunc (LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*) pParam;
	int nMax = ptp->nMax;
	HWND hWnd = ptp->hWnd;
	delete ptp;

    int nCount = Sieve (nMax);
    ::PostMessage (hWnd, WM_USER_THREAD_FINISHED, (WPARAM) nCount, 0);
    return 0;
}

int Sieve(int nMax)
{
    PBYTE pBuffer = new BYTE[nMax + 1];
    ::FillMemory (pBuffer, nMax + 1, 1);

    int nLimit = 2;
    while (nLimit * nLimit < nMax)
        nLimit++;

    for (int i=2; i<=nLimit; i++) {
        if (pBuffer[i]) {
            for (int k=i + i; k<=nMax; k+=i)
                pBuffer[k] = 0;
        }
    }

    int nCount = 0;
    for (i=2; i<=nMax; i++)
        if (pBuffer[i])
            nCount++;

    delete[] pBuffer;
    return nCount;
}
