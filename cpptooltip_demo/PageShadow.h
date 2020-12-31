#if !defined(AFX_PAGESHADOW_H__2AD4B9E2_4248_4143_880C_FB70C6BD3CC9__INCLUDED_)
#define AFX_PAGESHADOW_H__2AD4B9E2_4248_4143_880C_FB70C6BD3CC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageShadow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageShadow dialog

class CPageShadow : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageShadow)

// Construction
public:
	CPageShadow();
	~CPageShadow();

// Dialog Data
	//{{AFX_DATA(CPageShadow)
	enum { IDD = IDD_PAGE_SHADOW };
	BYTE	m_darken;
	BYTE	m_offset_x;
	BYTE	m_offset_y;
	BYTE	m_depth_x;
	BYTE	m_depth_y;
	BOOL	m_gradient;
	BYTE	m_img_darken;
	BYTE	m_img_offset_x;
	BYTE	m_img_offset_y;
	BYTE	m_img_depth_x;
	BYTE	m_img_depth_y;
	BOOL	m_img_gradient;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageShadow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageShadow)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeGradient();
	afx_msg void OnChangeTooltip();
	afx_msg void OnImgGradient();
	afx_msg void OnImgChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESHADOW_H__2AD4B9E2_4248_4143_880C_FB70C6BD3CC9__INCLUDED_)
