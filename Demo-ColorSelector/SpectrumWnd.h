#if !defined(AFX_SPECTRUMWND_H__F8FAFDC3_CC0B_4F4A_97B2_264DAFE1DE34__INCLUDED_)
#define AFX_SPECTRUMWND_H__F8FAFDC3_CC0B_4F4A_97B2_264DAFE1DE34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpectrumWnd window

class CSpectrumWnd : public CWnd
{
// Construction
public:
	CSpectrumWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetNameOfClosestColor( COLORREF cr, COLORREF* crNamed = NULL );
	CPoint GetCellCoordinatesFromPoint( CPoint point );
	BOOL m_bIsDragging;
	COLORREF* m_crArray;
	COLORREF m_crCurrentFocusColor;
	CRect m_rcFocusOutline;
	static const int m_cbCells;
	COLORREF m_crTargetColor;
	void SetLum( int iLum );
	int m_iLum;
	virtual ~CSpectrumWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpectrumWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMWND_H__F8FAFDC3_CC0B_4F4A_97B2_264DAFE1DE34__INCLUDED_)
