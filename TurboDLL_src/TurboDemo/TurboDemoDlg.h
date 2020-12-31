// TurboDemoDlg.h : header file
//

#if !defined(AFX_TURBODEMODLG_H__69D8D45F_DA9F_4A4E_AC41_34CC71C4D818__INCLUDED_)
#define AFX_TURBODEMODLG_H__69D8D45F_DA9F_4A4E_AC41_34CC71C4D818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTurboDemoDlg dialog

class CTurboDemoDlg : public CDialog
{
// Construction
public:
	CTurboDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTurboDemoDlg)
	enum { IDD = IDD_TURBODEMO_DIALOG };
	CTreeListCtrl m_ctrlTreeList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTurboDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList	m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CTurboDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonDd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TURBODEMODLG_H__69D8D45F_DA9F_4A4E_AC41_34CC71C4D818__INCLUDED_)
