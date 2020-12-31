// ShapeWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoteWnd window

#define CXWIDTH		250
#define CYHEIGHT	200
#define CXCORNER	20
#define CYCORNER	20

#include "oxshape.h"

class CNoteWnd : public CWnd, public COXShape
{
private:
	CRgn m_rgnWnd;
	BOOL m_bTrackMove;
	CPoint m_ptMouse, m_ptLast;
	POINT m_aPoints[10];
	int m_nPoints;
	CFont m_fontText;

private:
	void InvertTracker(CPoint point);
	HWND GetHWND() { return m_hWnd; }

// Construction
public:
	CNoteWnd(CWnd *pParentWnd=NULL);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNoteWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNoteWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
