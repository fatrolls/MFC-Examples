// RanDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRanDialog dialog
#include "stdafx.h"
#include "SecureChat.h"
#include "MyCryptLib.h"
#define _POOL_SIZE_ 624*4
#ifndef _RANDOMDIALOG_21343434SLDKLSSDDUYGD6783676323jdjsdj
#define _RANDOMDIALOG_21343434SLDKLSSDDUYGD6783676323jdjsdj



class CRanDialog : public CDialog
{
// Construction
public:
	BYTE m_raw_pool[_POOL_SIZE_];
public:

	CRanDialog(CWnd* pParent = NULL);   // standard constructor

	void stir_it(unsigned int);

// Dialog Data
	//{{AFX_DATA(CRanDialog)
	enum { IDD = IDD_RANDOM };
	CProgressCtrl	m_cProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRanDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_times_around;
	int m_max_times_around;
	int m_raw_pool_ptr;
	// Generated message map functions
	//{{AFX_MSG(CRanDialog)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
