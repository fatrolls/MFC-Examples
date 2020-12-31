// DlgCalcDlg.h : header file
//

#if !defined(AFX_DLGCALCDLG_H__F42970C6_9047_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_DLGCALCDLG_H__F42970C6_9047_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcDlg dialog

class CDlgCalcDlg : public CDialog
{
// Construction
public:
	void UpdateDisplay (LPCTSTR pszDisplay);
	CDlgCalcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalcDlg)
	enum { IDD = IDD_DLGCALC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DropStack();
	void LiftStack();
	void DisplayXRegister();

    double m_dblStack[4];
    double m_dblMemory;
    CString m_strDisplay;
    CString m_strFormat;
    CRect m_rect;
    int m_cxChar;
    int m_cyChar;

    BOOL m_bFixPending;
    BOOL m_bErrorFlag;
    BOOL m_bDecimalInString;
    BOOL m_bStackLiftEnabled;
    BOOL m_bNewX;

	HICON m_hIcon;
	HACCEL m_hAccel;

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnAdd();
	afx_msg void OnSubtract();
	afx_msg void OnMultiply();
	afx_msg void OnDivide();
	afx_msg void OnEnter();
	afx_msg void OnChangeSign();
	afx_msg void OnExponent();
	afx_msg void OnStore();
	afx_msg void OnRecall();
	afx_msg void OnFix();
	afx_msg void OnClear();
	afx_msg void OnDecimal();
	afx_msg void OnDelete();
	//}}AFX_MSG
	afx_msg void OnDigit(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALCDLG_H__F42970C6_9047_11D2_8E53_006008A82731__INCLUDED_)
