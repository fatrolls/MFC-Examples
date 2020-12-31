#if !defined(AFX_PAGESIZES_H__5A4FE9A2_B1E6_11D7_84BD_00C026A7402A__INCLUDED_)
#define AFX_PAGESIZES_H__5A4FE9A2_B1E6_11D7_84BD_00C026A7402A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSizes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSizes dialog

class CPageSizes : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageSizes)

// Construction
public:
	CPageSizes();
	~CPageSizes();

// Dialog Data
	//{{AFX_DATA(CPageSizes)
	enum { IDD = IDD_PAGE_SIZES };
#if _MSC_VER < 1300
	BYTE	m_margin_cx;
	BYTE	m_margin_cy;
	BYTE	m_rounded_cx;
	BYTE	m_rounded_cy;
	BYTE	m_anchor_width;
	BYTE	m_anchor_height;
	BYTE	m_anchor_offset;
	BYTE	m_offset_cx;
	BYTE	m_offset_cy;
#else
    DWORD	m_margin_cx;
    DWORD	m_margin_cy;
    DWORD	m_rounded_cx;
    DWORD	m_rounded_cy;
    DWORD	m_anchor_width;
    DWORD	m_anchor_height;
    DWORD	m_anchor_offset;
    DWORD	m_shadow_cx;
    DWORD	m_shadow_cy;
    DWORD	m_offset_cx;
    DWORD	m_offset_cy;
#endif
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSizes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageSizes)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESIZES_H__5A4FE9A2_B1E6_11D7_84BD_00C026A7402A__INCLUDED_)
