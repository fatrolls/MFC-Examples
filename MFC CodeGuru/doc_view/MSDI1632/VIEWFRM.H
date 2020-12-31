/////////////////////////////////////////////////////////////////////////////
// CViewFrame

class CViewFrame : public CMDIChildWnd
{
  DECLARE_DYNCREATE(CViewFrame)
protected:
  CViewFrame();     // protected constructor used by dynamic creation
// Implementation
protected:
  BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual ~CViewFrame();
  virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
  // Generated message map functions
  //{{AFX_MSG(CViewFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
