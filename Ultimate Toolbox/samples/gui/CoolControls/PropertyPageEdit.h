#if !defined(AFX_PROPERTYPAGEEDIT_H__3696ECE4_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_PROPERTYPAGEEDIT_H__3696ECE4_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "OXCoolCtrl.h"
#include "OXEdit.h"
#include "OXMaskedEdit.h"

// PropertyPageEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageEdit dialog

class CPropertyPageEdit : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageEdit)

// Construction
public:
	CPropertyPageEdit();
	~CPropertyPageEdit();

// Dialog Data
	//{{AFX_DATA(CPropertyPageEdit)
	enum { IDD = IDD_DIALOG_EDIT };
	COXCoolCtrl<CHotKeyCtrl>	m_hotKey;
	COXCoolSpinButtonCtrl	m_spinUnattached;
	COXCoolSpinButtonCtrl	m_spinRight;
	COXCoolSpinButtonCtrl	m_spinLeft;
	COXCoolCtrl<CRichEditCtrl>	m_richeditMultiline;
	COXCoolCtrl<CEdit>	m_editSpinUnattached;
	COXCoolCtrl<CEdit>	m_editSpinRight;
	COXCoolCtrl<CEdit>	m_editSpinLeft;
	COXCoolCtrl<CEdit>	m_editPlain;
	COXCoolCtrl<COXEdit>	m_editExtended;
	COXCoolCtrl<COXNumericEdit>	m_editNumeric;
	COXCoolCtrl<CEdit>	m_editMultiline;
	COXCoolCtrl<COXMaskedEdit>	m_editMasked;
	COXCoolCtrl<COXCurrencyEdit>	m_editCurrency;
	COXCoolButton	m_btnDisable;
	BOOL	m_bDisable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageEdit)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckDisableAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEEDIT_H__3696ECE4_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
