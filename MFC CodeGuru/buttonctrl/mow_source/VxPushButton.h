/////////////////////////////////////////////////////////////////////////=
// VxPushButton.h : header file


#ifndef _VxPushButton_H
#define _VxPushButton_H



class CVxPushButton : public CButton
{

// Construction

	public:
	BOOL m_bLBtnDown;
	CBrush m_brBackground;
	COLORREF m_crText;
	CVxPushButton();
	void SetBkgndColor (COLORREF rgb);
	void SetTextColor (COLORREF rgb);
	void SetBitmap2 (UINT);
	UINT GetBitmap2();

	// Operations

	public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVxPushButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

	// Implementation

	protected:
		COLORREF	m_clrBack;
		COLORREF	m_clrText;
		UINT		m_idBitmap;
		CFont		m_font;
		int			m_uniqueID;


	public:
		UINT		m_idCursor;
		void		SetCursor (UINT idCursor);
		
		virtual		~CVxPushButton();
		
		// This function will associate a unique ID to the
		// button object. 
		// This function was written primarily to keep the 
		// code structure similarity between MOTIF and NT
		void		AddCallbackID(int Idx);

	// Generated message map functions

	protected:
	//{{AFX_MSG(CVxPushButton)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void uiPushBtnCB();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};




#endif //_VxPushButton_H
