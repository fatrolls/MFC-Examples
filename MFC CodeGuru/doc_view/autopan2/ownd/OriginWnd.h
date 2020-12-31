///////////////////////////////////////////////////////////////////
//	Written by Russ Freeman (russf@dircon.co.uk or russf@digita.com)
//	Copyright (c) 1998.
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is 
//	not sold for profit without the authors written consent, and 
//	providing that this notice and the authors name is included. If 
//	the source code in this file is used in any commercial application 
//	then acknowledgement must be made to the author of this file 
//	(in whatever form you wish).
//
//	This file is provided "as is" with no expressed or implied warranty.
//
//	Easy to use, simply call StartPanning(...)
//	See sample CScrollView derived view class in the associated sample program.

class COriginWnd : public CWnd
{
// Construction
public:
	COriginWnd( BOOL bHorz, BOOL bVert, CPoint ptOrigin );

// Attributes
public:

// Operations
public:

	//
	//	Call this to actually create the window having dynamically created an instance.
	//lint -e1411
	BOOL Create( CWnd *pParent );
	//lint +e1411

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COriginWnd)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COriginWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(COriginWnd)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	COriginWnd();																		//	Not implemented
	COriginWnd( const COriginWnd & );								//	Not implemented
	COriginWnd& operator =( const COriginWnd & );		//	Not implemented
	static LRESULT CALLBACK HookProc(int code, WPARAM wParam ,LPARAM lParam);
	typedef const UINT (*CursorArray)[3][3];
	static CursorArray GetCursorArray( BOOL bHorz, BOOL bVert );

	HCURSOR GetNewCursorAndDistance( CPoint pt );

	//
	//	The bitmap we use for the origin, plus the bitmap description structure
	CBitmap m_bitmap;
	CSize m_sizeBitmap;

	//
	//	The directions we can scroll in
	const BOOL m_bScrollVert, m_bScrollHorz;
	
	//
	//	The origin point, used to calculate the current mouse distance, this is then used
	//	to pass on to determine how fast we scroll and in what directions
	const CPoint m_ptOrigin;
	CSize m_sizeDistance;
	CRect m_rcCursorMargin;

	//
	//	An optimisation to allow us to not calculate the cursor and the distance if the
	//	mouse has not been moved.
	CPoint m_ptCursorPrevious;

	const CursorArray m_parrnIDs;
	CWnd *m_pParent;

	//
	//	Whether we have issued any scroll messages yet, used to process the middle button up event
	//	so that we can properly simulate IE behaviour
	BOOL m_bScrolledAlready;
};

/////////////////////////////////////////////////////////////////////////////
