#if !defined(AFX_REPORTSDLG_H__3592C8B1_8E60_4CD5_AA88_CCFFAA11B61B__INCLUDED_)
#define AFX_REPORTSDLG_H__3592C8B1_8E60_4CD5_AA88_CCFFAA11B61B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportsDlg.h : header file
//
#include "..\Common\Tools\TableContainer.h"
#include "..\Common\UIClasses\SkinnedButton.h"

#define IDC_TABLECONTAINER				6000
#define IDC_VIEWIT_BUTTON				6001
#define IDC_VIEWOT_BUTTON				6002
#define IDC_VIEWCI_BUTTON				6003
#define IDC_DELETE_BUTTON				6004
#define IDC_MODIFY_BUTTON				6005
/////////////////////////////////////////////////////////////////////////////
// CReportsDlg dialog

class CReportsDlg : public CDialog
{
// Construction
public:
	void PaintMemoryDC();
	CReportsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportsDlg)
	enum { IDD = IDD_REPORTS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nCurrentTableID;
	CSkinnedButton* m_pDeleteButton;
	CSkinnedButton* m_pModifyButton;
	CSkinnedButton* m_pViewCIButton;
	CSkinnedButton* m_pViewOTButton;
	CSkinnedButton* m_pViewITButton;
	CFont m_fontPageTitle;
	CString m_csPageTitle;
	CBitmap m_memBmp;
	CDC m_memDC;
	HBITMAP m_hBackBmp;
	CTableContainer* m_pTableContainerWnd;

	// Generated message map functions
	//{{AFX_MSG(CReportsDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DisplayAppropriateButtons();
	void InitializeControls();
	void DestroyControls();
	void CreateControls();
	void DisplayPageTitle();
	void CreateFontPageTitle();
	void SetPageTitle(LPCTSTR lpszPageTitle);
	void CreateTableContainer();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTSDLG_H__3592C8B1_8E60_4CD5_AA88_CCFFAA11B61B__INCLUDED_)
