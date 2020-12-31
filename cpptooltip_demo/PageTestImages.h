#if !defined(AFX_PAGETESTIMAGES_H__E57F95C9_D7FC_4492_9B12_1C2C3188A658__INCLUDED_)
#define AFX_PAGETESTIMAGES_H__E57F95C9_D7FC_4492_9B12_1C2C3188A658__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTestImages.h : header file
//
#include "PPTooltip.h"

/////////////////////////////////////////////////////////////////////////////
// CPageTestImages dialog

class CPageTestImages : public CPropertyPage
{
// Construction
public:
	CPPToolTip m_tooltip;
	CPageTestImages();
	~CPageTestImages();

// Dialog Data
	//{{AFX_DATA(CPageTestImages)
	enum { IDD = IDD_PAGETEST_IMAGES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageTestImages)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageTestImages)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETESTIMAGES_H__E57F95C9_D7FC_4492_9B12_1C2C3188A658__INCLUDED_)
