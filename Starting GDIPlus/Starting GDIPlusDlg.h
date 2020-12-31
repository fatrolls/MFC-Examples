// Starting GDIPlusDlg.h : header file
//

#if !defined(AFX_STARTINGGDIPLUSDLG_H__4CC93546_46D9_11D5_AE4A_0080ADB4DF70__INCLUDED_)
#define AFX_STARTINGGDIPLUSDLG_H__4CC93546_46D9_11D5_AE4A_0080ADB4DF70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStartingGDIPlusDlg dialog

class CStartingGDIPlusDlg : public CDialog
{
// Construction
public:
	CStartingGDIPlusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStartingGDIPlusDlg)
	enum { IDD = IDD_STARTINGGDIPLUS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartingGDIPlusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStartingGDIPlusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTINGGDIPLUSDLG_H__4CC93546_46D9_11D5_AE4A_0080ADB4DF70__INCLUDED_)
