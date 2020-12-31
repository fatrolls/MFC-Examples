#if !defined(AFX_CUSTOMERINFODLG_H__0E8F7C77_B132_4A92_9F23_97E5FDDF1E8D__INCLUDED_)
#define AFX_CUSTOMERINFODLG_H__0E8F7C77_B132_4A92_9F23_97E5FDDF1E8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomerInfoDlg.h : header file
//
#include "..\Common\UIClasses\SkinnedStatic.h"
#include "..\Common\UIClasses\SkinnedEdit.h"
#include "..\Common\UIClasses\SkinnedButton.h"

#define IDC_SKINNEDSTATIC			2000
#define IDC_CUSTOMERID_EDIT			2001
#define IDC_COMPANYNAME_EDIT		2002
#define IDC_CONTACTPERSON_EDIT		2003
#define IDC_ADDRESS1_EDIT			2004
#define IDC_ADDRESS2_EDIT			2005
#define IDC_PHONER_EDIT				2006
#define IDC_PHONEO_EDIT				2007
#define IDC_CELL_EDIT				2008
#define IDC_FAX_EDIT				2009
#define IDC_EMAIL_EDIT				2010
#define IDC_SAVEDETAILS_BUTTON		3000
/////////////////////////////////////////////////////////////////////////////
// CCustomerInfoDlg dialog

class CCustomerInfoDlg : public CDialog
{
// Construction
public:
	void PaintMemoryDC();
	CCustomerInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomerInfoDlg)
	enum { IDD = IDD_CUSTOMERINFO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomerInfoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnCancel();
	
	CFont m_fontStatic;
	CBitmap m_memBmp;
	CDC m_memDC;
	HBITMAP m_hBackBmp;
//	CSkinnedStatic* m_pBottomBandStatic;
//	CSkinnedStatic* m_pTopBandStatic;
	CSkinnedButton* m_pSaveDetailsButton;
	virtual void OnOK();
	CSkinnedEdit* m_pEmailEdit;
	CSkinnedEdit* m_pFaxEdit;
	CSkinnedEdit* m_pCellEdit;
	CSkinnedEdit* m_pPhoneOEdit;
	CSkinnedEdit* m_pPhoneREdit;
	CSkinnedEdit* m_pAddress2Edit;
	CSkinnedEdit* m_pAddress1Edit;
	CSkinnedEdit* m_pContactPersonEdit;
	CSkinnedEdit* m_pCompanyNameEdit;
	CSkinnedEdit* m_pCustomerIDEdit;
	CSkinnedStatic* m_pEmailStatic;
	CSkinnedStatic* m_pFaxStatic;
	CSkinnedStatic* m_pCellStatic;
	CSkinnedStatic* m_pPhoneOStatic;
	CSkinnedStatic* m_pPhoneRStatic;
	CSkinnedStatic* m_pAddress2Static;
	CSkinnedStatic* m_pAddress1Static;
	CSkinnedStatic* m_pContactPersonStatic;
	CSkinnedStatic* m_pCompanyNameStatic;
	CSkinnedStatic* m_pCustomerIDStatic;

	// Generated message map functions
	//{{AFX_MSG(CCustomerInfoDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ClearAllControls();
	void CreateFontStatic();
	void OnSaveDetails();
	BOOL ValidateEntries();
	BOOL SaveCustomerInfo();
	void InitializeControls();
	void DestroyControls();
	void CreateControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERINFODLG_H__0E8F7C77_B132_4A92_9F23_97E5FDDF1E8D__INCLUDED_)
