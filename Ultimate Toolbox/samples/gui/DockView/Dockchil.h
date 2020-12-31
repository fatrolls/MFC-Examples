// dockchil.h : header file
//
// Docktest demo of Dockable Views functionality

/////////////////////////////////////////////////////////////////////////////
// CDockChildWnd frame

#include "OXFrameWndDock.h"
//#include "OXSizeToolBar.h"
#include "OXCoolToolBar.h"

class CDockChildWnd : public COXMDIChildWndSizeDock
{
	DECLARE_DYNCREATE(CDockChildWnd)
protected:
	CDockChildWnd();           // protected constructor used by dynamic creation

// Attributes
public:
//	CToolBar	m_wndToolBar;
//	COXSizeToolBar	m_wndToolBar;
	COXCoolToolBar	m_wndToolBar;
	CStatusBar  	m_wndChildStatusBar;
	CMyListBoxBar	m_SizeListBar;
	CMyListBoxBar	m_SizeListBarAdd1;
	CMyListBoxBar	m_SizeListBarAdd2;
	CMyListBoxBar	m_SizeListBarAdd3;
	CMyListBoxBar	m_SizeListBarAdd4;

protected:
	int nListBarID;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockChildWnd)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDockChildWnd();

	BOOL CreateListBar(CMyListBoxBar* pBar);

	// Generated message map functions
	//{{AFX_MSG(CDockChildWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

