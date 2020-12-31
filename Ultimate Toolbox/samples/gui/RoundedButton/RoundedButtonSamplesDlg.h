#if !defined(AFX_ROUNDEDBUTTONSAMPLESDLG_H__9B0A9184_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_)
#define AFX_ROUNDEDBUTTONSAMPLESDLG_H__9B0A9184_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXRoundedButton.h"
#include "OXSeparator.h"

// RoundedButtonSamplesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonSamplesDlg dialog

class CRoundedButtonSamplesDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CRoundedButtonSamplesDlg)

// Construction
public:
	CRoundedButtonSamplesDlg();
	~CRoundedButtonSamplesDlg();

// Dialog Data
	//{{AFX_DATA(CRoundedButtonSamplesDlg)
	enum { IDD = IDD_ROUNDEDBUTTON_SAMPLES_DIALOG };
	COXSeparator	m_sepToggleButtons;
	COXRoundedButton	m_btnToggle4;
	COXRoundedButton	m_btnToggle3;
	COXRoundedButton	m_btnToggle2;
	COXRoundedButton	m_btnToggle1;
	COXRoundedButton	m_btnWithImage7;
	COXRoundedButton	m_btnWithImage6;
	COXRoundedButton	m_btnWithImage5;
	COXRoundedButton	m_btnWithImage4;
	COXRoundedButton	m_btnWithImage3;
	COXRoundedButton	m_btnWithImage2;
	COXRoundedButton	m_btnWithImage1;
	COXSeparator	m_sepButtonsWithImages;
	COXRoundedButton	m_btnWithTextMultilineCustom;
	COXSeparator	m_sepButtonsWithText;
	COXRoundedButton	m_btnWithText3;
	COXRoundedButton	m_btnWithText2;
	COXRoundedButton	m_btnWithText1;
	COXRoundedButton	m_btnRound5;
	COXRoundedButton	m_btnRound4;
	COXRoundedButton	m_btnRound3;
	COXRoundedButton	m_btnRound2;
	COXRoundedButton	m_btnRound1;
	COXSeparator	m_sepRoundButtons;
	//}}AFX_DATA
	BOOL m_bOption1;
	BOOL m_bOption2;
	BOOL m_bOption3;
	BOOL m_bOption4;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRoundedButtonSamplesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	void SetupRoundButton(COXRoundedButton* pButton, COLORREF clr);
	void SetupImageButton(COXRoundedButton* pButton, UINT nIconID);
	void SetupToggleButton(COXRoundedButton* pButton);
	void ResetImages(BOOL bSet);

	// Generated message map functions
	//{{AFX_MSG(CRoundedButtonSamplesDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnToggle(UINT id, NMHDR* pNotifyStruct, LRESULT* result);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDEDBUTTONSAMPLESDLG_H__9B0A9184_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_)
