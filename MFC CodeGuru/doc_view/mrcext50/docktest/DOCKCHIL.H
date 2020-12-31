// dockchil.h : header file
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:28  $

/////////////////////////////////////////////////////////////////////////////
// CDockChildWnd frame

class CDockChildWnd : public CMRCMDIChildWndSizeDock
{
	DECLARE_DYNCREATE(CDockChildWnd)
protected:
	CDockChildWnd();           // protected constructor used by dynamic creation

// Attributes
public:
	CMRCSizeToolBar	m_wndToolBar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockChildWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDockChildWnd();

	// Generated message map functions
	//{{AFX_MSG(CDockChildWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
