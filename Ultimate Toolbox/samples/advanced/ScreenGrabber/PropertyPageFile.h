#if !defined(AFX_PROPERTYPAGEFILE_H__E32DDA25_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_PROPERTYPAGEFILE_H__E32DDA25_805A_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertyPageFile.h : header file
//

#include "OXContextHelpPropertyPage.h"
#include "OXHistoryCombo.h"
#include "OXLayoutManager.h"


/////////////////////////////////////////////////////////////////////////////
// CPropertyPageFile dialog

class CPropertyPageFile : public COXContextHelpPropertyPage
{
//	DECLARE_DYNCREATE(CPropertyPageFile)

// Construction
public:
	CPropertyPageFile();
	~CPropertyPageFile();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CPropertyPageFile)
	enum { IDD = IDD_PROPPAGE_FILE };
	CStatic	m_ctlStaticFileType;
	CStatic	m_ctlStaticFileName;
	CStatic	m_ctlStaticCaptureDir;
	CComboBox	m_ctlComboFileType;
	COXHistoryCombo	m_ctlComboFileName;
	CButton	m_ctlCheckAutomaticNaming;
	CButton	m_ctlButtonDir;
	BOOL	m_bAutomaticNaming;
	CString	m_sFileName;
	CString	m_sFileType;
	CString	m_sCaptureDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void CheckVars();
	void ShowControls();

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	BOOL m_bInitialized;
	COXLayoutManager m_LayoutManager;

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCaptureDir();
	afx_msg void OnCheckAutomaticNaming();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGEFILE_H__E32DDA25_805A_11D1_A3D5_0080C83F712F__INCLUDED_)
