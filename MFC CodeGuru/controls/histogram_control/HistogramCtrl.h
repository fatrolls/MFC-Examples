// HistogramCtrl.h : header file
//

#ifndef __HISTOGRAMCTRL_H__
#define __HISTOGRAMCTRL_H__

/////////////////////////////////////////////////////////////////////////////
// CHistogramCtrl window

class CHistogramCtrl : public CWnd
{
// Construction
public:
	CHistogramCtrl();
  UINT m_nVertical;

// Attributes
public:
	UINT SetPos(UINT nPos);
	void SetRange(UINT nLower, UINT nUpper);
	void InvalidateCtrl();
	void DrawSpike();

	// Operations
public:
	void StepIt();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHistogramCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHistogramCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	UINT     m_nLower;		// lower bounds
	UINT     m_nUpper;		// upper bounds
	UINT     m_nPos;		// current position within bounds

	CDC      m_MemDC;
	CBitmap  m_Bitmap;
};

/////////////////////////////////////////////////////////////////////////////
#endif
