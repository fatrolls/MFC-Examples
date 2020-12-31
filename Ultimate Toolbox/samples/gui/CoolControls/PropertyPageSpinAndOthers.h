#if !defined(AFX_PROPERTYPAGESPINANDOTHERS_H__3696ECE9_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_PROPERTYPAGESPINANDOTHERS_H__3696ECE9_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "OXCoolCtrl.h"

// PropertyPageSpinAndOthers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageSpinAndOthers dialog

class CPropertyPageSpinAndOthers : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageSpinAndOthers)

// Construction
public:
	CPropertyPageSpinAndOthers();
	~CPropertyPageSpinAndOthers();

// Dialog Data
	//{{AFX_DATA(CPropertyPageSpinAndOthers)
	enum { IDD = IDD_DIALOG_SPINSCROLLHOTKEYPROGRESSSLIDER };
	COXCoolSpinButtonCtrl	m_spinVert2;
	COXCoolSpinButtonCtrl	m_spinVert1;
	COXCoolSpinButtonCtrl	m_spinHorz;
	COXCoolSliderCtrl	m_sliderVertRight;
	COXCoolSliderCtrl	m_sliderVertLeft;
	COXCoolSliderCtrl	m_sliderVertBoth;
	COXCoolSliderCtrl	m_sliderHorzTop;
	COXCoolSliderCtrl	m_sliderHorzBottom;
	COXCoolSliderCtrl	m_sliderHorzBoth;
	COXCoolScrollBar	m_scrollVert;
	COXCoolScrollBar	m_scrollHorz;
	COXCoolCtrl<CProgressCtrl>	m_progressHorz;
	COXCoolButton	m_btnDisable;
	BOOL	m_bDisable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageSpinAndOthers)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageSpinAndOthers)
	afx_msg void OnCheckDisableAll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGESPINANDOTHERS_H__3696ECE9_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
