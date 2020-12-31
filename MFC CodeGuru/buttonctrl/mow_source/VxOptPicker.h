/////////////////////////////////////////////////////////////////////////=
// VxOptPicker.h : header file


#ifndef _VxOptPicker_H
#define _VxOptPicker_H

#include "VxOptPopup.h"

/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker window

/////////////////////////////////////////////////////////////////////////////
// CVxOptPicker window

class CVxOptPicker : public CButton
{
// Construction
public:
	CVxOptPicker(int width, int height, int rows, int columns);
    virtual ~CVxOptPicker();

protected:
    void SetWindowSize();


// Attributes
public:
	CString			m_CurText;
	UINT			m_CurBitmap;
	CWnd *			m_CurButton;

	CVxOptPopup	*	m_PopupWnd;
	int				m_PopupWndVisible ;

// protected attributes
public:
    CRect    m_ArrowRect;
	int		 m_Width;
	int		 m_Height;
	int		 m_Rows;
	int		 m_Columns;

// Operations
public:

// Overrides
// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CVxOptPicker)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

// Generated message map functions
protected:
    //{{AFX_MSG(CVxOptPicker)
    afx_msg BOOL OnClicked();
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};


#endif 