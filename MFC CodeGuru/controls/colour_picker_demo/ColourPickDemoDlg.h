// ColourPickDemoDlg.h : header file
//

#if !defined(AFX_COLOURPICKDEMODLG_H__D0B758F6_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
#define AFX_COLOURPICKDEMODLG_H__D0B758F6_9830_11D1_9C0F_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CColourPickDemoDlg dialog

#include "ColourPicker.h"

class CColourPickDemoDlg : public CDialog
{
// Construction
public:
    CColourPickDemoDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CColourPickDemoDlg)
	enum { IDD = IDD_COLOURPICKDEMO_DIALOG };
    CColourPicker    m_ColourBox;
	int		m_nMode;
	BOOL	m_bTrack;
	BOOL	m_bDisable;
	CString	m_strDefaultText;
	CString	m_strCustomText;
	//}}AFX_DATA
    COLORREF m_crColour;

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColourPickDemoDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CColourPickDemoDlg)
    virtual BOOL OnInitDialog();
	afx_msg void OnModeChange();
	afx_msg void OnTrackColour();
	afx_msg void OnDisable();
	afx_msg void OnChangeEdit();
	//}}AFX_MSG

    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelEndCancel(UINT lParam, LONG wParam);
    afx_msg LONG OnSelChange(UINT lParam, LONG wParam);
    afx_msg LONG OnCloseUp(UINT lParam, LONG wParam);
    afx_msg LONG OnDropDown(UINT lParam, LONG wParam);

    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURPICKDEMODLG_H__D0B758F6_9830_11D1_9C0F_00A0243D1382__INCLUDED_)
