#if !defined(AFX_OUTWARDTRANSACTIONSDLG_H__BE8BF19C_DCAB_4BB5_8086_C66D94D73D2A__INCLUDED_)
#define AFX_OUTWARDTRANSACTIONSDLG_H__BE8BF19C_DCAB_4BB5_8086_C66D94D73D2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutwardTransactionsDlg.h : header file
//

#include "..\Common\UIClasses\SkinnedStatic.h"
#include "..\Common\UIClasses\SkinnedComboBox.h"
#include "..\Common\UIClasses\SkinnedEdit.h"
#include "..\Common\UIClasses\SkinnedButton.h"

#define IDC_SKINNEDSTATIC					2000
#define IDC_CUSTOMERID_COMBO				2001
#define IDC_SERIALNUMBER_COMBO				2002
#define IDC_DATE_DAY_COMBO					2003
#define IDC_DATE_MONTH_COMBO				2004
#define IDC_DATE_YEAR_COMBO					2005
#define IDC_GATEPASSNUMBER_EDIT				2006
#define IDC_QUANTITY_EDIT					2007
#define IDC_SAVEDETAILS_BUTTON				3000
/////////////////////////////////////////////////////////////////////////////
// COutwardTransactionsDlg dialog

class COutwardTransactionsDlg : public CDialog
{
// Construction
public:
	void PaintMemoryDC();
	CSkinnedComboBox* GetComboBoxPtr(int nIndex);
	COutwardTransactionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COutwardTransactionsDlg)
	enum { IDD = IDD_OUTWARDTRANSACTIONS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutwardTransactionsDlg)
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
//	CSkinnedStatic* m_pBottomBandStatic;
//	CSkinnedStatic* m_pTopBandStatic;
	virtual void OnOK();
	CSkinnedButton* m_pSaveDetailsButton;
	CSkinnedEdit* m_pQuantityEdit;
	CSkinnedEdit* m_pGatePassNumberEdit;
	CSkinnedComboBox* m_pDateYearCombo;
	CSkinnedComboBox* m_pDateMonthCombo;
	CSkinnedComboBox* m_pDateDayCombo;
	CSkinnedComboBox* m_pSerialNumberCombo;
	CSkinnedComboBox* m_pCustomerIDCombo;
	CSkinnedStatic* m_pQuantityStatic;
	CSkinnedStatic* m_pGatePassNumberStatic;
	CSkinnedStatic* m_pDateStatic;
	CSkinnedStatic* m_pSerialNumberStatic;
	CSkinnedStatic* m_pCustomerIDStatic;

	// Generated message map functions
	//{{AFX_MSG(COutwardTransactionsDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsQuantityValid(CCustomDB* pdbWrapper);
	void ClearAllControls();
	void RetrieveAndDisplayCompanyName();
	void CreateFontCompany();
	void SetCompanyName(LPCTSTR lpszCompanyName);
	BOOL SaveOutwardTransaction();
	BOOL ValidateEntries();
	void OnSaveDetails();
	void PopulateSerialNumberCombo(CSkinnedComboBox *pSerialNumberCombo);
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

#endif // !defined(AFX_OUTWARDTRANSACTIONSDLG_H__BE8BF19C_DCAB_4BB5_8086_C66D94D73D2A__INCLUDED_)
