#if !defined(AFX_LEFTNAVDLG_H__2E6C64AE_BBC6_4AE9_BBA5_58454C03B175__INCLUDED_)
#define AFX_LEFTNAVDLG_H__2E6C64AE_BBC6_4AE9_BBA5_58454C03B175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftNavDlg.h : header file
//

#include "..\Common\UIClasses\SkinnedStatic.h"
#include "..\Common\UIClasses\SkinnedButton.h"

#define IDC_SKINNEDSTATIC					2000
#define IDC_CUSTOMERINFO_BUTTON				2001
#define IDC_INWARDTRANSACTIONS_BUTTON		2002
#define IDC_OUTWARDTRANSACTIONS_BUTTON		2003
#define IDC_BILLINGINFO_BUTTON				2004
#define IDC_REPORTS_BUTTON					2005

/////////////////////////////////////////////////////////////////////////////
// CLeftNavDlg dialog

class CLeftNavDlg : public CDialog
{
// Construction
public:
	void ResetLeftNavState();
	void SetLeftNavState(UINT nID);
	void PaintMemoryDC();
	CLeftNavDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLeftNavDlg)
	enum { IDD = IDD_LEFTNAV_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftNavDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSkinnedStatic* m_pBGStatic;
	virtual void OnCancel();
	virtual void OnOK();
	CSkinnedButton* m_pReportsButton;
	CSkinnedButton* m_pBillingInfoButton;
	CSkinnedButton* m_pOutwardTransactionsButton;
	CSkinnedButton* m_pInwardTransactionsButton;
	CSkinnedButton* m_pCustomerInfoButton;

	CBitmap m_memBmp;
	CDC m_memDC;
	HBITMAP m_hBackBmp;

	// Generated message map functions
	//{{AFX_MSG(CLeftNavDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnClickNotifyParentHandler(int nID);
	void InitializeControls();
	void DestroyControls();
	void CreateControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTNAVDLG_H__2E6C64AE_BBC6_4AE9_BBA5_58454C03B175__INCLUDED_)
