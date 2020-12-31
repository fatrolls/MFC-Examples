#if !defined(AFX_TOPBANDDLG_H__AED7E402_8420_45CC_B575_DF3267E9CAB1__INCLUDED_)
#define AFX_TOPBANDDLG_H__AED7E402_8420_45CC_B575_DF3267E9CAB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TopBandDlg.h : header file
//

#include "..\Common\UIClasses\SkinnedStatic.h"

#define IDC_SKINNEDSTATIC				2000
#define IDC_CLOSE_BUTTON				4000
#define IDC_HOME_BUTTON					4001
/////////////////////////////////////////////////////////////////////////////
// CTopBandDlg dialog

class CTopBandDlg : public CDialog
{
// Construction
public:
	void ShowAppropriateSubTitle(UINT nSubTitleID);
	void PaintMemoryDC();
	CTopBandDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTopBandDlg)
	enum { IDD = IDD_TOPBAND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopBandDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnCancel();
	virtual void OnOK();
	CSkinnedButton* m_pHomeButton;
	CSkinnedButton* m_pCloseButton;
	CSkinnedStatic* m_pPipeStatic;
	CSkinnedStatic* m_pTitleREStatic;
	CSkinnedStatic* m_pTitleBIStatic;
	CSkinnedStatic* m_pTitleOTStatic;
	CSkinnedStatic* m_pTitleITStatic;
	CSkinnedStatic* m_pTitleCIStatic;
	CSkinnedStatic* m_pTitleMainStatic;
	CBitmap m_memBmp;
	CDC m_memDC;
	HBITMAP m_hBackBmp;

	// Generated message map functions
	//{{AFX_MSG(CTopBandDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitializeControls();
	void DestroyControls();
	void CreateControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPBANDDLG_H__AED7E402_8420_45CC_B575_DF3267E9CAB1__INCLUDED_)
