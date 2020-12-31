// DialogBitmapDlg.h : header file
//

#if !defined(AFX_DIALOGBITMAPDLG_H__2839F6C7_7788_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_DIALOGBITMAPDLG_H__2839F6C7_7788_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BitmapPicture.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapDlg dialog

class CDialogBitmapDlg : public CDialog
{
// Construction
public:
	CDialogBitmapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogBitmapDlg)
	enum { IDD = IDD_DIALOGBITMAP_DIALOG };
	//}}AFX_DATA
	CBitmapPicture m_Picture;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBitmapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogBitmapDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBITMAPDLG_H__2839F6C7_7788_11D1_ABBA_00A0243D1382__INCLUDED_)
