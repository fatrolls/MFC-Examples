// mainfrm.h : interface of the CMainFrame class
// Docktest demo of Dockable Views functionality
//
/////////////////////////////////////////////////////////////////////////////

#include "mysizeba.h"
#include "TabViewBar.h"
#include "OXFrameWndDock.h"
#include "OXSizeToolBar.h"
#include "OXSizeDlgBar.h"
#include "OXSizeDockBar.h"
#include "logodlg.h"
#include "OXTabClientWnd.h"
#include "OXMenuBar.h"

#define MainFrameParent COXMDIFrameWndSizeDock

class CMainFrame : public COXMenuBarFrame<MainFrameParent,COXSizeDockBar>
//class CMainFrame : public MainFrameParent
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
					    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	virtual void OnHandleButton();

protected:  // control bar embedded members
	CStatusBar  		m_wndStatusBar;
	COXSizeDialogBar	m_DlgBar;
	COXSizeDialogBar	m_SizeDlgBar;
	CLogoDlg			m_LogoBar;
	CMyListBoxBar		m_SizeListBar;
	CTabViewBar			m_TabViewBar;

	int 				m_BarCount;

	// MTI client window
	COXTabClientWnd m_MTIClientWnd;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewTiledockbars();
	afx_msg void OnArrangeBottomLeft();
	afx_msg void OnArrangeBottomRight();
	afx_msg void OnArrangeTopLeft();
	afx_msg void OnArrangeTopRight();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
