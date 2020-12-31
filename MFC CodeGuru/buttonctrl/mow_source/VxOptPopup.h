/////////////////////////////////////////////////////////////////////////=
// VxOptPopup.h : header file


#ifndef _VxOptPopup_H
#define _VxOptPopup_H

// forward declaration
class CVxOptPicker;

/////////////////////////////////////////////////////////////
// CVxOptPopup window

class CVxOptPopup : public CWnd
{
// Construction
public:
    CVxOptPopup(CPoint p, CVxOptPicker* pParentWnd, UINT nID);

// Operations
public:
    BOOL Create(CPoint p, CVxOptPicker* pParentWnd, UINT nID);
    void SetWindowSize();
    void CreateToolTips();

// Implementation
public:
    virtual ~CVxOptPopup();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVxOptPopup)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL


// protected attributes
protected:
    CRect          m_WindowRect;
    //CToolTipCtrl   m_ToolTip;

public:
    CVxOptPicker* m_pParent;

    // Generated message map functions
protected:
    //{{AFX_MSG(CVxOptPopup)
    afx_msg void OnNcDestroy();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


#endif
