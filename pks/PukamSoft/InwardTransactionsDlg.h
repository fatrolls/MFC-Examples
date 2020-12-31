#if !defined(AFX_INWARDTRANSACTIONSDLG_H__47CA41AB_A07A_42FB_ADE8_6C49934B50A4__INCLUDED_)
#define AFX_INWARDTRANSACTIONSDLG_H__47CA41AB_A07A_42FB_ADE8_6C49934B50A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InwardTransactionsDlg.h : header file
//
#include "..\Common\UIClasses\SkinnedStatic.h"
#include "..\Common\UIClasses\SkinnedComboBox.h"
#include "..\Common\UIClasses\SkinnedEdit.h"
#include "..\Common\UIClasses\SkinnedButton.h"

#define IDC_SKINNEDSTATIC				2000
#define IDC_CUSTOMERID_COMBO			2001
#define IDC_SERIALNUMBER_EDIT			2002
#define IDC_DATE_DAY_COMBO				2003
#define IDC_DATE_MONTH_COMBO			2004
#define IDC_DATE_YEAR_COMBO				2005
#define IDC_CATEGORY_COMBO				2006
#define IDC_SIZE_EDIT					2009
#define IDC_WEIGHT_EDIT					2008
#define IDC_QUANTITY_EDIT				2007
#define IDC_STORAGELOCATION_COMBO		2010
#define IDC_CATEGORY_EDIT				2011
#define IDC_STORAGELOCATION_EDIT		2012
#define IDC_SAVEDETAILS_BUTTON			3000
/////////////////////////////////////////////////////////////////////////////
// CInwardTransactionsDlg dialog

class CInwardTransactionsDlg : public CDialog
{
// Construction
public:
	void PaintMemoryDC();
	CSkinnedComboBox* GetComboBoxPtr(int nIndex);
	CInwardTransactionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInwardTransactionsDlg)
	enum { IDD = IDD_INWARDTRANSACTIONS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInwardTransactionsDlg)
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
	virtual void OnOK();
	CSkinnedEdit* m_pStorageLocationEdit;
	CSkinnedEdit* m_pCategoryEdit;
	CSkinnedComboBox* m_pStorageLocationCombo;
	CSkinnedEdit* m_pQuantityEdit;
	CSkinnedEdit* m_pWeightEdit;
	CSkinnedEdit* m_pSizeEdit;
	CSkinnedComboBox* m_pCategoryCombo;
	CSkinnedComboBox* m_pDateYearCombo;
	CSkinnedComboBox* m_pDateMonthCombo;
	CSkinnedComboBox* m_pDateDayCombo;
	CSkinnedEdit* m_pSerialNumberEdit;
	CSkinnedComboBox* m_pCustomerIDCombo;
	CSkinnedStatic* m_pStorageLocationStatic;
	CSkinnedStatic* m_pQuantityStatic;
	CSkinnedStatic* m_pWeightStatic;
	CSkinnedStatic* m_pSizeStatic;
	CSkinnedStatic* m_pCategoryStatic;
	CSkinnedStatic* m_pDateStatic;
	CSkinnedStatic* m_pSerialNumberStatic;
	CSkinnedStatic* m_pCustomerIDStatic;

	// Generated message map functions
	//{{AFX_MSG(CInwardTransactionsDlg)
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
	BOOL ValidateEntries();
	BOOL SaveInwardTransaction();
	void OnSaveDetails();
	void PopulateStorageLocationCombo(CSkinnedComboBox* pStorageLocationCombo);
	void PopulateCategoryCombo(CSkinnedComboBox* pCategoryCombo);
	void PopulateDateYearCombo(CSkinnedComboBox* pDateYearCombo);
	void PopulateDateMonthCombo(CSkinnedComboBox* pDateMonthCombo);
	void PopulateCustomerIDCombo(CSkinnedComboBox* pCustomerIDCombo);
	void PopulateDateDayCombo(CSkinnedComboBox* pDateDayCombo);
	void InitializeControls();
	void DestroyControls();
	void CreateControls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INWARDTRANSACTIONSDLG_H__47CA41AB_A07A_42FB_ADE8_6C49934B50A4__INCLUDED_)
