// PaletteDlg.h : header file
//

#if !defined(AFX_PALETTEDLG_H__6893A4E7_6F23_11D1_9A8D_444553540000__INCLUDED_)
#define AFX_PALETTEDLG_H__6893A4E7_6F23_11D1_9A8D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPaletteDlg dialog

class CPaletteDlg : public CDialog
{
// Construction
public:
	CPaletteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPaletteDlg)
	enum { IDD = IDD_PALETTE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaletteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPaletteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PALETTEDLG_H__6893A4E7_6F23_11D1_9A8D_444553540000__INCLUDED_)
