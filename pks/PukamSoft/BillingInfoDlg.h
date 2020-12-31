#if !defined(AFX_BILLINGINFODLG_H__0FD2CEE1_E88A_49F6_8E26_3C140A92FF98__INCLUDED_)
#define AFX_BILLINGINFODLG_H__0FD2CEE1_E88A_49F6_8E26_3C140A92FF98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BillingInfoDlg.h : header file
//

#include "..\Common\UIClasses\SkinnedStatic.h"
#include "..\Common\UIClasses\SkinnedComboBox.h"
#include "..\Common\UIClasses\SkinnedEdit.h"
#include "..\Common\UIClasses\SkinnedButton.h"

#define IDC_SKINNEDSTATIC				2000
#define IDC_CUSTOMERID_COMBO			2001
#define IDC_SERIALNUMBER_COMBO			2002
#define IDC_BILLNUMBER_EDIT				2003
#define IDC_RATE_EDIT					2004
#define IDC_FREQUENCY_COMBO				2005
#define IDC_DATEDAY_COMBO				2006
#define IDC_DATEMONTH_COMBO				2007
#define IDC_DATEYEAR_COMBO				2008
#define IDC_PAYMENTMODE_COMBO			2009
#define IDC_SAVEDETAILS_BUTTON			3000


/////////////////////////////////////////////////////////////////////////////
// CBillingInfoDlg dialog

class CBillingInfoDlg : public CDialog
{
// Construction
public:
	void PaintMemoryDC();
	CSkinnedComboBox* GetComboBoxPtr(int nIndex);
	CBillingInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBillingInfoDlg)
	enum { IDD = IDD_BILLINGINFO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBillingInfoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_fontCompany;
	CString m_csCompanyName;
	CBitmap m_memBmp;
	CDC m_memDC;
	HBITMAP m_hBackBmp;
	CSkinnedButton* m_pSaveDetailsButton;
//	CSkinnedStatic* m_pBottomBandStatic;
//	CSkinnedStatic* m_pTopBandStatic;
	CSkinnedComboBox* m_pPaymentModeCombo;
	CSkinnedComboBox* m_pDateYearCombo;
	CSkinnedComboBox* m_pDateMonthCombo;
	CSkinnedComboBox* m_pDateDayCombo;
	CSkinnedComboBox* m_pFrequencyCombo;
	CSkinnedEdit* m_pRateEdit;
	CSkinnedEdit* m_pBillNumberEdit;
	CSkinnedComboBox* m_pSerialNumberCombo;
	CSkinnedComboBox* m_pCustomerIDCombo;
	CSkinnedStatic* m_pPaymentModeStatic;
	CSkinnedStatic* m_pDateStatic;
	CSkinnedStatic* m_pFrequencyStatic;
	CSkinnedStatic* m_pRateStatic;
	CSkinnedStatic* m_pBillNumberStatic;
	CSkinnedStatic* m_pSerialNumberStatic;
	CSkinnedStatic* m_pCustomerIDStatic;

	// Generated message map functions
	//{{AFX_MSG(CBillingInfoDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ClearAllControls();
	void RetrieveAndDisplayCompanyName();
	void CreateFontCompany();
	void SetCompanyName(LPCTSTR lpszCompanyName);
	BOOL SaveBillingInfo();
	BOOL ValidateEntries();
	void OnSaveDetails();
	void PopulateCustomerIDCombo(CSkinnedComboBox* pCustomerIDCombo);
	void PopulateSerialNumberCombo(CSkinnedComboBox* pSerialNumberCombo);
	void PopulateFrequencyCombo(CSkinnedComboBox* pFrequencyCombo);
	void PopulateDateDayCombo(CSkinnedComboBox* pDateDayCombo);
	void PopulateDateMonthCombo(CSkinnedComboBox* pDateMonthCombo);
	void PopulateDateYearCombo(CSkinnedComboBox* pDateYearCombo);
	void PopulatePaymentModeCombo(CSkinnedComboBox* pPaymentModeCombo);
	void InitializeControls();
	void DestroyControls();
	void CreateControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BILLINGINFODLG_H__0FD2CEE1_E88A_49F6_8E26_3C140A92FF98__INCLUDED_)
