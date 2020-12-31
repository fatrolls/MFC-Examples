#if !defined(AFX_CDisplayOptionsPage_H__F309F003_9BAA_11D1_A2AB_000000000000__INCLUDED_)
#define AFX_CDisplayOptionsPage_H__F309F003_9BAA_11D1_A2AB_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDisplayOptionsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayOptionsPage dialog

class CDisplayOptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CDisplayOptionsPage)

// Construction
public:
	CDisplayOptionsPage();
	~CDisplayOptionsPage();

protected:
	HPALETTE			m_hPal;           // Our DIB's palette
	HBITMAP				m_hBitmap;
	LONG				m_width;
	LONG				m_height;

//	SECWellButton		m_btnBackgroundColor;

public:
// Dialog Data
	//{{AFX_DATA(CDisplayOptionsPage)
	enum { IDD = IDD_PROPPAGE_DISPLAYOPTIONS };
	CButton	m_btnFilePath;
	CEdit	m_edtBackgroundFile;
	CButton	m_btnUseBackgroundFile;
	CStatic	m_preview;
	CListBox	m_lbBackground;
	CString	m_backgroundFile;
	BOOL	m_useBackgroundFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDisplayOptionsPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDisplayOptionsPage)
	afx_msg void OnSelchangeDoBkgnd();
	virtual BOOL OnInitDialog();
	afx_msg void OnDoFilepath();
	afx_msg void OnDoUsefile();
	afx_msg void OnPaint();
	afx_msg void OnModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL SetBitmap(UINT nID);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDisplayOptionsPage_H__F309F003_9BAA_11D1_A2AB_000000000000__INCLUDED_)
