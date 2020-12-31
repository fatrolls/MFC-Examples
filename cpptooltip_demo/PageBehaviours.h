#if !defined(AFX_PAGEBEHAVIOURS_H__5A4FE9A1_B1E6_11D7_84BD_00C026A7402A__INCLUDED_)
#define AFX_PAGEBEHAVIOURS_H__5A4FE9A1_B1E6_11D7_84BD_00C026A7402A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageBehaviours.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageBehaviours dialog

class CPageBehaviours : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageBehaviours)

// Construction
public:
	CPageBehaviours();
	~CPageBehaviours();

// Dialog Data
	//{{AFX_DATA(CPageBehaviours)
	enum { IDD = IDD_PAGE_BEHAVIOUR };
	BOOL	m_multiple_show;
	BOOL	m_hide_by_left;
	BOOL	m_nohide_over;
	BOOL	m_nohide_by_timer;
	BOOL	m_tracking_mouse;
	UINT	m_show_time;
	UINT	m_hide_time;
	UINT	m_fade_in;
	UINT	m_fade_out;
	BOOL	m_debug_mode;
	DWORD	m_animation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageBehaviours)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageBehaviours)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeBehaviour();
	afx_msg void OnChangeTimers();
	afx_msg void OnDebugMode();
	afx_msg void OnChangeAniStep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEBEHAVIOURS_H__5A4FE9A1_B1E6_11D7_84BD_00C026A7402A__INCLUDED_)
