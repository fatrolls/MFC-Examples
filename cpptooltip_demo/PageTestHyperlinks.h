#if !defined(AFX_PAGETESTHYPERLINKS_H__A0580732_1606_4FB1_9B5B_CA4138246D4F__INCLUDED_)
#define AFX_PAGETESTHYPERLINKS_H__A0580732_1606_4FB1_9B5B_CA4138246D4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTestHyperlinks.h : header file
//
#define UNM_HYPERLINK_CLICKED	(WM_APP + 0x100)
#include "PPTooltip.h"

/////////////////////////////////////////////////////////////////////////////
// CPageTestHyperlinks dialog

class CPageTestHyperlinks : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageTestHyperlinks)

// Construction
public:
	CPPToolTip m_tooltip;
	CPageTestHyperlinks();
	~CPageTestHyperlinks();

// Dialog Data
	//{{AFX_DATA(CPageTestHyperlinks)
	enum { IDD = IDD_PAGETEST_HYPERLINKS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageTestHyperlinks)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageTestHyperlinks)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
    afx_msg LRESULT NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETESTHYPERLINKS_H__A0580732_1606_4FB1_9B5B_CA4138246D4F__INCLUDED_)
