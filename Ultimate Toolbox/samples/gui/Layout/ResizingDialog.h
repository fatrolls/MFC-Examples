#if !defined(AFX_RESIZINGDIALOG_H__7D955F3B_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
#define AFX_RESIZINGDIALOG_H__7D955F3B_0A9F_11D2_88B8_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ResizingDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResizingDialog dialog
class COXLayoutManager;

class CResizingDialog : public CDialog
{
// Construction
public:
	CResizingDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CResizingDialog();

// Dialog Data
	//{{AFX_DATA(CResizingDialog)
	enum { IDD = IDD_RESIZING_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXLayoutManager* m_pLayoutManager;

	// Generated message map functions
	//{{AFX_MSG(CResizingDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESIZINGDIALOG_H__7D955F3B_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
