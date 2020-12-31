/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame frame

class CMSDIFrame : public CMDIChildWnd
{
  DECLARE_DYNCREATE(CMSDIFrame)
protected:
  CMSDIFrame();  // protected constructor used by dynamic creation
// Implementation
protected:
  virtual ~CMSDIFrame();
  // Generated message map functions
  //{{AFX_MSG(CMSDIFrame)
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
