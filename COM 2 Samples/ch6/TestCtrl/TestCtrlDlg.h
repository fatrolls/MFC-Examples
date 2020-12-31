// TestCtrlDlg.h : header file
//

#if !defined(AFX_TESTCTRLDLG_H__36D8C3FC_56EA_11CF_B355_00104B08CC22__INCLUDED_)
#define AFX_TESTCTRLDLG_H__36D8C3FC_56EA_11CF_B355_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestCtrlDlg dialog

class CTestCtrlDlg : public CDialog
{
// Construction
public:
	CTestCtrlDlg(CWnd* pParent = NULL);	// standard constructor
	~CTestCtrlDlg();	// standard deconstructor

// Dialog Data
	//{{AFX_DATA(CTestCtrlDlg)
	enum { IDD = IDD_TESTCTRL_DIALOG };
	long	m_Property;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	int Connection();
	int Disconnection();
	// Generated message map functions
	//{{AFX_MSG(CTestCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnection();
	afx_msg void OnDisconnection();
	afx_msg void OnSetproperty();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BEGIN_INTERFACE_PART(EventSink, IDispatch)
		INIT_INTERFACE_PART(CTestCtrlDlg, EventSink)
		STDMETHOD(GetTypeInfoCount)(unsigned int*);
		STDMETHOD(GetTypeInfo)(unsigned int, LCID, ITypeInfo**);
		STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR*, unsigned int, LCID, DISPID*);
		STDMETHOD(Invoke)(DISPID, REFIID, LCID, unsigned short, DISPPARAMS*,
						  VARIANT*, EXCEPINFO*, unsigned int*);
	END_INTERFACE_PART(EventSink)

private:
	DWORD m_dwCookie;
	LPDISPATCH m_pDispatch;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCTRLDLG_H__36D8C3FC_56EA_11CF_B355_00104B08CC22__INCLUDED_)
