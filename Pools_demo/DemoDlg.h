// DemoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__C77D5BA1_B9E2_4C03_B79D_BA54D2E894EF__INCLUDED_)
#define AFX_DEMODLG_H__C77D5BA1_B9E2_4C03_B79D_BA54D2E894EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferPool.h"
#include "ObjectPool.h"

class SomeType
{
public:
	SomeType(){i = 1;f = 0.2F;d[0] = f;}
    virtual ~SomeType(){}
	virtual int DoSomethingOrRather(){memset(NameOfSomethingOrRather,0,MAX_PATH); return i;}
	virtual float  GetTheFlaot(){return f;}
	static int OneMoreMethod(){return 1;}
private:
	TCHAR NameOfSomethingOrRather[MAX_PATH];
	int   i;
	float f;
	double d[10];

};

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
{
// Construction
public:

	CObjectPool<SomeType> SomeTypeObjectPool;

	CBufferPool m_BuffPoolObj;

	UINT	m_BPFreeCount;
	UINT	m_RegFreeCount;
	UINT	m_BPAllocateCount;
	UINT	m_RegAllocateCount;

	__int64		m_nBPTotalTime;

	__int64		m_nRegTotalTime;


	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

	virtual ~CDemoDlg();

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
	CProgressCtrl	m_RegularAllocationProgress;
	CProgressCtrl	m_BuffPollProgress;
	CString	m_BPFreeStatic;
	CString	m_RegFreeStatic;
	CString	m_BPAllocateStatic;
	CString	m_RegAllocateStatic;
	CString	m_BPAvTime;
	CString	m_RegAvTime;
	CString	m_BPTotalTime;
	CString	m_RegTotalTime;
	DWORD	m_nBufferSize;
	DWORD	m_nMaximumBuffers;
	DWORD	m_nNumberOfOperations;
	DWORD	m_nNumberOfThreads;
	UINT	m_nMinNumberOfSegments;
	UINT	m_nMaxNumberOfSegments;
	UINT	m_nInitialNumberOfSegments;
	float	m_nFreeBuffersPrecentForSegmentDeletion;
	UINT	m_nBuffersPerSegment;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTestButton();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTestBpButton();
	afx_msg void OnTestGlobalButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__C77D5BA1_B9E2_4C03_B79D_BA54D2E894EF__INCLUDED_)





















