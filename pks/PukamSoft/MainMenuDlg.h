#if !defined(AFX_MAINMENUDLG_H__12DDF2CD_3CB3_47FD_90A4_51A5DD910028__INCLUDED_)
#define AFX_MAINMENUDLG_H__12DDF2CD_3CB3_47FD_90A4_51A5DD910028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainMenuDlg.h : header file
//

#include "..\Common\UIClasses\SkinnedButton.h"
#include "..\Common\UIClasses\SkinnedStatic.h"

#define IDC_SKINNEDSTATIC					2000
#define IDC_CUSTOMERINFO_BUTTON				2001
#define IDC_INWARDTRANSACTIONS_BUTTON		2002
#define IDC_OUTWARDTRANSACTIONS_BUTTON		2003
#define IDC_BILLINGINFO_BUTTON				2004
#define IDC_REPORTS_BUTTON					2005
/////////////////////////////////////////////////////////////////////////////
// CMainMenuDlg dialog

class CMainMenuDlg : public CDialog
{
// Construction
public:
	void PaintMemoryDC();
	CMainMenuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainMenuDlg)
	enum { IDD = IDD_MAINMENU_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainMenuDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CSkinnedStatic* m_pBottomBandStatic;
//	CSkinnedStatic* m_pTopBandStatic;
	CSkinnedStatic* m_pBackgroundStatic;
	CSkinnedButton* m_pReportsButton;
	CSkinnedButton* m_pBillingInfoButton;
	CSkinnedButton* m_pOutwardTransactionsButton;
	CSkinnedButton* m_pInwardTransactionsButton;
	CSkinnedButton* m_pCustomerInfoButton;
	CDC m_memDC;
	CBitmap m_memBmp;
	HBITMAP m_hBackBmp;

	// Generated message map functions
	//{{AFX_MSG(CMainMenuDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnClickNotifyParentHandler(int nID);
	void InitializeControls();
	void CreateControls();
	void DestroyControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINMENUDLG_H__12DDF2CD_3CB3_47FD_90A4_51A5DD910028__INCLUDED_)
