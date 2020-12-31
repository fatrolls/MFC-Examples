/////////////////////////////////////////////////////////////////////////////
// CViewFrame

class CMSDIViewFrame : public CMDIChildWnd
{
  DECLARE_DYNCREATE(CMSDIViewFrame)
protected:
  CMSDIViewFrame();	// protected constructor used by dynamic creation
// Implementation
protected:
  BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
  virtual ~CMSDIViewFrame();
  virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
  // Generated message map functions
  //{{AFX_MSG(CMSDIViewFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
