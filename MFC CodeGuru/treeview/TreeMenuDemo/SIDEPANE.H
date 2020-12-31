#if !defined(SIDEPANE_H_INCLUDED)
#define SIDEPANE_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// sidepane.h : header file
//

#include "flatbmpbtn.h"
#include "sizecbar.h"
//#include "treemenuframe.h"




/////////////////////////////////////////////////////////////////////////////
// CSidePane window
class CSidePane : public CSizingControlBar
{
// Construction
public:
    CSidePane();
	void PositionControls();

// Attributes
public:

protected:
	CTreeMenuFrame		m_TreeFrame;
	CImageList			m_ImageList;
    CFont				m_font;
	CFont				m_fontHeader;

	COLORREF m_clrBtnHilight;
	COLORREF m_clrBtnShadow;
	int		m_iPaneCaptionY;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSidePane)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CSidePane();

    // Generated message map functions
protected:
    //{{AFX_MSG(CSidePane)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnHide();
	afx_msg void OnCaptionDrag(UINT nFlags, CPoint point);
	
    DECLARE_MESSAGE_MAP()

 private:
	CTreeMenuFrame *m_pControl;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIDEPANE_H__3FE34D81_820A_11D1_88BD_AE3AF0BB8026__INCLUDED_)
