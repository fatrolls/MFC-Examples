/////////////////////////////////////////////////////////////////////////////
//
// SocketServerDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CSocketServerDlg___H___
#define CSocketServerDlg___H___

#include "ThreadDispatcher.h"
#include "critsect.h"
#include "RawSocketServerWorker.h"

class Worker : public CWizRawSocketListener
{
public:
	Worker();
	virtual BOOL TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent);
	virtual BOOL ReadWrite   (CWizReadWriteSocket& socket);
	int m_nCurrThreads;
	int m_nMaxThreads;
	int	m_nRequests;
	CWizCriticalSection cs;
};

/////////////////////////////////////////////////////////////////////////////
// CSocketServerDlg dialog

class CSocketServerDlg : public CDialog
{
// Construction
public:
	CSocketServerDlg(Worker& rWorker, 
				CWizThreadDispatcher& rDispatcher,
				CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSocketServerDlg)
	enum { IDD = IDD_SOCKETSERVER_DIALOG };
	CEdit	m_nRequests;
	CEdit	m_nMaximum;
	CEdit	m_cCurrent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	Worker& m_rWorker;
	CWizThreadDispatcher& m_rDispatcher;
	// Generated message map functions
	//{{AFX_MSG(CSocketServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif // CSocketServerDlg___H___

