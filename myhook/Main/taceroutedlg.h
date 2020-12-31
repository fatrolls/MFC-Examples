#if !defined(AFX_TACEROUTEDLG_H__A3E6C718_1ACF_4D42_A71F_35C740B27B07__INCLUDED_)
#define AFX_TACEROUTEDLG_H__A3E6C718_1ACF_4D42_A71F_35C740B27B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaceRouteDlg.h : header file
//
#include "RootDlg.h"
#include <winsock2.h>
/////////////////////////////////////////////////////////////////////////////
// CTaceRouteDlg dialog

#define WM_TRACE_END WM_USER+100
#define WM_TRACE_ADD_GROUD WM_USER+101
#define WM_TRACE_Add_CHILD WM_USER+102

struct ChildProp
{
	CString strName;
	CString strValue;
};
class CTaceRouteDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CTaceRouteDlg)
// Construction
public:
	CTaceRouteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTaceRouteDlg)
	enum { IDD = IDD_TRACEROUTE_DLG };
	CButton	m_wndPlace;
	CIPAddressCtrl	m_IpAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaceRouteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTaceRouteDlg)
	afx_msg void OnBtnTrace();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnTraceEnd(WPARAM, LPARAM);
	afx_msg LRESULT OnTraceAddGroup(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTraceAddChild(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	CBCGPPropList m_wndPropList;

	CBCGPProp* AddGroupProp(CString strName, CBCGPProp* pParent = NULL);
	void AddChildProp(CString strName, CString strValue, CBCGPProp* pParent = NULL);
};



/////////////////////////////////////////////////////////////////////////////
// CTraceRouteThread thread

class CTraceRouteThread : public CWinThread
{
	DECLARE_DYNCREATE(CTraceRouteThread)
protected:
	CTraceRouteThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void StartTrace(CTaceRouteDlg* pDlg, DWORD dwIP);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTraceRouteThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTraceRouteThread();

	// Generated message map functions
	//{{AFX_MSG(CTraceRouteThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CTaceRouteDlg* m_pDlg;
	CEvent m_event;
	DWORD m_dwIP;
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TACEROUTEDLG_H__A3E6C718_1ACF_4D42_A71F_35C740B27B07__INCLUDED_)
