#if !defined(AFX_PAGECOLORS_H__B0864553_48E3_4A19_835E_B425E914BF4B__INCLUDED_)
#define AFX_PAGECOLORS_H__B0864553_48E3_4A19_835E_B425E914BF4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageColors.h : header file
//

#include "ColourPicker.h"

/////////////////////////////////////////////////////////////////////////////
// CPageColors dialog

class CPageColors : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageColors)

// Construction
public:
	CPageColors();
	~CPageColors();

// Dialog Data
	//{{AFX_DATA(CPageColors)
	enum { IDD = IDD_PAGE_COLORS };
	CColourPicker	m_border_color;
	CColourPicker	m_end_bk;
	CColourPicker	m_mid_bk;
	CColourPicker	m_start_bk;
	int		m_theme;
	int		m_effect_bk;
	BYTE	m_granularity;
	BOOL	m_border;
	int		m_custom_border;
	BYTE	m_border_width;
	BYTE	m_border_height;
	BYTE    m_transparency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageColors)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageColors)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeColorTheme();
	afx_msg void OnChangeEffect();
	afx_msg void OnShowBorder();
	afx_msg void OnSetBorder();
	afx_msg void OnChangeTransparency();
	//}}AFX_MSG
	afx_msg LONG OnChangeColorBk(UINT lParam = 0, LONG wParam = 0);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECOLORS_H__B0864553_48E3_4A19_835E_B425E914BF4B__INCLUDED_)
