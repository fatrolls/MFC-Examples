// CBCGToolbarCustomize.h : header file
//
// CBCGToolbarCustomize is a modeless property sheet that is 
// created once and not destroyed until the application
// closes.  It is initialized and controlled from
// CPropertyFrame.
 
#ifndef __CBCGTOOLBARCUSTOMIZE_H__
#define __CBCGTOOLBARCUSTOMIZE_H__

#include "CBCGToolbarCustomizePages.h"

class CBCGToolBarImages;
class CBCGToolbarButton;
class CBCGToolBar;

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarCustomize

class AFX_EXT_CLASS CBCGToolbarCustomize : public CPropertySheet
{
	friend class CBCGToolBar;

	DECLARE_DYNAMIC(CBCGToolbarCustomize)

// Construction
public:
	CBCGToolbarCustomize(CWnd* pWndParent, CBCGToolBarImages* pImages);

// Attributes
public:
	CCustomizePage	m_CustomizePage;
	CToolbarsPage	m_ToolbarsPage;

// Operations
public:
	void AddButton (LPCTSTR lpszCategory, const CBCGToolbarButton& button);
	BOOL SetUserCategory (LPCTSTR lpszCategory);

protected:
	void SetFrameCustMode (BOOL bCustMode);
	void ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGToolbarCustomize)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	virtual BOOL Create();

// Implementation
public:
	 virtual ~CBCGToolbarCustomize();
	 virtual void PostNcDestroy();

// Generated message map functions
protected:
	//{{AFX_MSG(CBCGToolbarCustomize)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:
	CWnd*	m_pParentWnd;
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __CBCGTOOLBARCUSTOMIZE_H__
