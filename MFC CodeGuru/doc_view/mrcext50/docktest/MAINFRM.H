// mainfrm.h : interface of the CMainFrame class
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:36  $
//
/////////////////////////////////////////////////////////////////////////////
#include "mysizeba.h"


#define MainFrameParent CMRCMDIFrameWndSizeDock

class CMainFrame : public MainFrameParent
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

protected:  // control bar embedded members
	CStatusBar  		m_wndStatusBar;
	CMRCSizeToolBar		m_wndToolBar;
	CMRCSizeDialogBar	m_DlgBar;
	CMRCSizeDialogBar	m_SizeDlgBar;
	CMyListBoxBar		m_SizeListBar;

	CToolBar			m_wndFixedToolBar;
	int 			m_BarCount;

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
