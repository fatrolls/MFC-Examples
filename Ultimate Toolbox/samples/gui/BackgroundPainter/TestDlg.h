#if !defined(AFX_TESTDLG_H__24987B29_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
#define AFX_TESTDLG_H__24987B29_8DEB_11D2_A792_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//

#include "OXSeparator.h"
#include "OXColorPickerButton.h"
#include "OXHistoryCombo.h"
#include "OXBackgroundPainter.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	COXHistoryCombo	m_cmbFilename;
	COXColorPickerButton	m_btnBackColor;
	COXSeparator	m_ctlSeparator;
	int		m_nAlign;
	CString	m_sFilename;
	//}}AFX_DATA
	COLORREF m_clrBack;

protected:
	// background painter organizer
	COXBackgroundPainterOrganizer m_backPainterOrganizer;

	// window to display image
	CWnd m_pictureWnd;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAlign();
	afx_msg void OnBackclr();
	afx_msg void OnSelchangeFilename();
	afx_msg void OnEditchangeFilename();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__24987B29_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
