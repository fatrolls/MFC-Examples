#if !defined(AFX_PROPERTYPAGEIMAGE_H__E32DDA24_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PROPERTYPAGEIMAGE_H__E32DDA24_805A_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertyPageImage.h : header file
//

#include "OXContextHelpPropertyPage.h"
#include "OXSpinCtrl.h"
#include "OXLayoutManager.h"


/////////////////////////////////////////////////////////////////////////////
// CPropertyPageImage dialog

class CPropertyPageImage : public COXContextHelpPropertyPage
{
//	DECLARE_DYNCREATE(CPropertyPageImage)

// Construction
public:
	CPropertyPageImage();
	~CPropertyPageImage();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CPropertyPageImage)
	enum { IDD = IDD_PROPPAGE_IMAGE };
	CStatic	m_ctlStaticWidth;
	CStatic	m_ctlStaticHeight;
	COXSpinCtrl	m_ctlSpinWidth;
	COXSpinCtrl	m_ctlSpinHeight;
	CEdit	m_ctlEditWidth;
	CEdit	m_ctlEditHeight;
	CButton	m_ctlCheckResize;
	CButton	m_ctlCheckMaintainRatio;
	BOOL	m_bMaintainRatio;
	BOOL	m_bResize;
	UINT	m_nHeight;
	UINT	m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void CheckVars();
	void ShowControls();

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	COXLayoutManager m_LayoutManager;

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageImage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckResize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEIMAGE_H__E32DDA24_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
