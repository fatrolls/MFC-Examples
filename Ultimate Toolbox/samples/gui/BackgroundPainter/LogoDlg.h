#if !defined(AFX_LOGODLG_H__24987B30_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
#define AFX_LOGODLG_H__24987B30_8DEB_11D2_A792_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogoDlg.h : header file
//

#include "OXBackgroundPainter.h"
#include "OXStaticHyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg dialog

class CLogoDlg : public CDialog
{
// Construction
public:
	CLogoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogoDlg)
	enum { IDD = IDD_LOGO_DIALOG };
	COXStaticHyperLink	m_ctlWebLink;
	//}}AFX_DATA

protected:
	// background painter organizer
	COXBackgroundPainterOrganizer m_backPainterOrganizer;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGODLG_H__24987B30_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
