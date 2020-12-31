#if !defined(MYBAR_H_INCLUDED)
#define MYBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// mybar.h : header file
//

#include "sizecbar.h"
/////////////////////////////////////////////////////////////////////////////
// CMyBar window

class CMyBar : public CSizingControlBar
{
// Construction
public:
    CMyBar();

// Attributes
public:
protected:
    CButton m_wndButton;
    CFont   m_font;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMyBar)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CMyBar();

    // Generated message map functions
protected:
    //{{AFX_MSG(CMyBar)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBAR_H__3FE34D81_820A_11D1_88BD_AE3AF0BB8026__INCLUDED_)
