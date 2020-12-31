// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include "logomdi.h"
#include "TwainCpp.h" //<<<TWAIN>>>
class CMainFrame : public CMDIFrameWnd, public CTwain
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
	void SetImage(HANDLE hBitmap,TW_IMAGEINFO& info); //<<<TWAIN>>>
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	inline CStatusBar&	  GetStatusBar() { return m_wndStatusBar; }
	inline CProgressCtrl& GetProgressBar() { return m_wndProgressBar; }

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CLogoMdi m_LogoMdiClientWnd;
	CProgressCtrl m_wndProgressBar;
 
// Generated message map functions
protected:
	protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnFileSelectsource();
	afx_msg void OnFileAcquire();
	afx_msg void OnClose();
	afx_msg void OnFileCapture();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
