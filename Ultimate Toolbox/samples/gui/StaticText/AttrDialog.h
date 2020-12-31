#if !defined(AFX_ATTRDIALOG_H__48BCEDC6_5699_11D1_A990_0000929B340A__INCLUDED_)
#define AFX_ATTRDIALOG_H__48BCEDC6_5699_11D1_A990_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AttrDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttrDialog dialog

#include "OXSpinCtrl.h"
#include "OXStaticText.h"

class CAttrDialog : public CDialog
{
// Construction
public:
	int m_nEllipseMode;
	CAttrDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAttrDialog)
	enum { IDD = IDD_ATTR_DIALOG };
	COXStaticText	m_TestStatic;
	COXSpinCtrl	m_OffsetSpin;
	CEdit	m_OffsetEdit;
	COXSpinCtrl	m_HeightSpin;
	CEdit	m_HeightEdit;
	COXSpinCtrl	m_bkRedSpin;
	CEdit	m_bkRedEdit;
	COXSpinCtrl	m_bkGreenSpin;
	CEdit	m_bkGreenEdit;
	COXSpinCtrl	m_bkBlueSpin;
	CEdit	m_bkBlueEdit;
	COXSpinCtrl	m_RedSpin;
	COXSpinCtrl	m_GreenSpin;
	COXSpinCtrl	m_BlueSpin;
	CEdit	m_RedEdit;
	CEdit	m_GreenEdit;
	CEdit	m_BlueEdit;
	CString	m_sCaption;
	CString	m_sFont;
	int		m_BlueVal;
	int		m_GreenVal;
	int		m_RedVal;
	int		m_bkBlueVal;
	int		m_bkGreenVal;
	int		m_bkRedVal;
	int		m_Height;
	BOOL	m_Bold;
	BOOL	m_Italic;
	BOOL	m_Under;
	BOOL	m_Striked;
	DWORD	m_OffsetVal;
	BOOL	m_bEmboss;
	BOOL	m_bRaised;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttrDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAttrDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnBegrepRadio();
	afx_msg void OnMidrepRadio();
	afx_msg void OnEndrepRadio();
	afx_msg void OnNorepRadio();
	afx_msg void OnApplyButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRDIALOG_H__48BCEDC6_5699_11D1_A990_0000929B340A__INCLUDED_)
