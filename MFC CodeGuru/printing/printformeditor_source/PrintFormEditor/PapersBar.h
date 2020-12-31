#if !defined(AFX_PAPERSBAR_H__08DDE511_0B44_11D2_8413_0000B43382FE__INCLUDED_)
#define AFX_PAPERSBAR_H__08DDE511_0B44_11D2_8413_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PapersBar.h : header file
//
#include "PagePage1.h"

/////////////////////////////////////////////////////////////////////////////
// CPapersBar window
class Doc;

class CPapersBar : public SECControlBar
{
// Construction
public:
	CPapersBar();

// Attributes
public:
	CListCtrl	wndList;
	CImageList  lima;
	Doc * pDoc;

	CPagePage1	pPage1;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPapersBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPapersBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPapersBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAPERSBAR_H__08DDE511_0B44_11D2_8413_0000B43382FE__INCLUDED_)
