
#ifndef _CLOCKSTATUSBAR_H_
#define _CLOCKSTATUSBAR_H_

//CClockStatusBar.h:
//==============
class CClockStatusBar : public CStatusBar {
     DECLARE_DYNCREATE(CClockStatusBar)
public:
     CClockStatusBar();
     ~CClockStatusBar();
private:
     CString m_strClockFormat;
public:
     void SetClockFormat(LPCTSTR strClockFormat);
     // Overrides
     // ClassWizard generated virtual function overrides
     //{{AFX_VIRTUAL(CClockStatusBar)
     //}}AFX_VIRTUAL
     // Generated message map functions
     //{{AFX_MSG(CClockStatusBar)
     afx_msg void OnDestroy();
     afx_msg void OnUpdateIndicatorTime(CCmdUI* pCmdUI);
     afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
     //}}AFX_MSG
     DECLARE_MESSAGE_MAP()
};
#endif