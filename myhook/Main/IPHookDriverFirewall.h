#if !defined(AFX_IPHOOKDRIVERFIREWALL_H__B0573721_812C_483F_B467_B43FD9F1FB27__INCLUDED_)
#define AFX_IPHOOKDRIVERFIREWALL_H__B0573721_812C_483F_B467_B43FD9F1FB27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPHookDriverFirewall.h : header file
//
#include "Protocoltypes.h"
/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "RootDlg.h"
class CIpHookDrvFrame;

class CIpHookDrvDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CIpHookDrvDlg)
// Construction
public:
	CIpHookDrvDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIpHookDrvDlg)
	enum { IDD = IDD_IPHOOKDRV_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIpHookDrvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIpHookDrvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CIpHookDrvFrame* m_pFrame;
};

class CIPHookDriverView : public CFormView
{
protected:
	CIPHookDriverView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIPHookDriverView)

// Form Data
public:
	//{{AFX_DATA(CIPHookDriverView)
	enum { IDD = IDD_IPHOOKDRV_VIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPHookDriverView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIPHookDriverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIPHookDriverView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CIPHookDriverDoc document

class CIPHookDriverDoc : public CDocument
{
protected:
	CIPHookDriverDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIPHookDriverDoc)

	void AddRule(UINT srcIp, UINT srcMask, USHORT srcPort,
		UINT dstIp, UINT dstMask, USHORT dstPort, UINT protocol, BOOL bDrop);
	void ClearRules();
	void DeleteRules(int nPos);

// Attributes
public:
    vector<IPFilterRule> m_aRules;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPHookDriverDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIPHookDriverDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CIPHookDriverDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CIpHookDrvFrame frame

class CIpHookDrvFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CIpHookDrvFrame)
protected:
	CIpHookDrvFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIpHookDrvFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIpHookDrvFrame();

	// Generated message map functions
	//{{AFX_MSG(CIpHookDrvFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnFileConserve();
	afx_msg void OnUpdateFileConserve(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
public:
    CSize       m_sizeofFrame;
};

class CIPHookDrvDocTemplate : public CSingleDocTemplate
{
	DECLARE_DYNAMIC(CIPHookDrvDocTemplate)
public:
	CIPHookDrvDocTemplate();
};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPHOOKDRIVERFIREWALL_H__B0573721_812C_483F_B467_B43FD9F1FB27__INCLUDED_)
