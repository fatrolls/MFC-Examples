#if !defined(AFX_CUSTOMIZETOOLTIP_H__8E588403_A7AF_11D7_84BD_00C026A7402A__INCLUDED_)
#define AFX_CUSTOMIZETOOLTIP_H__8E588403_A7AF_11D7_84BD_00C026A7402A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomizeTooltip.h : header file
//

#include "PPTooltip.h"

#include "PageColors.h"
#include "PageBehaviours.h"
#include "PageSizes.h"
#include "PageStyles.h"
#include "PageCssStyles.h"
#include "PageShadow.h"

#include "TestPageGeneral.h"
#include "PageTestHyperlinks.h"
#include "PageTestImages.h"
#include "PageTestTable.h"
#include "PageTestListTree.h"
#include "PageTestMisc.h"

#define GetTooltipWnd (CCustomizeTooltip*)(GetParent()->GetParent())

/////////////////////////////////////////////////////////////////////////////
// CCustomizeTooltip dialog

class CCustomizeTooltip : public CDialog
{
	DECLARE_DYNCREATE(CCustomizeTooltip)

// Construction
public:
	CPropertySheet m_examples;
	CTestPageGeneral m_general;
	CPageTestHyperlinks m_hyperlinks;
	CPageTestImages m_images;
	CPageTestTable m_tables;
	CPageTestListTree m_list_tree;
	CPageTestMisc m_misc;
	CPageShadow m_shadow;
	
	CPPToolTip m_tooltip;
	CCustomizeTooltip(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CCustomizeTooltip)
	enum { IDD = IDD_PPTOOLTIP_OPTIONS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeTooltip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPropertySheet m_sheet;
	CPageColors m_page_colors;
	CPageBehaviours m_page_behaviours;
	CPageStyles m_styles;
	CPageSizes m_page_sizes;
	CPageCssStyles m_page_css_style;

	

	// Generated message map functions
	//{{AFX_MSG(CCustomizeTooltip)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZETOOLTIP_H__8E588403_A7AF_11D7_84BD_00C026A7402A__INCLUDED_)
