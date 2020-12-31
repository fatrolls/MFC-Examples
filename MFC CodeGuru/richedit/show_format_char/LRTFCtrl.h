#if !defined(AFX_LRTFCTRL_H__9674279E_94A4_11D1_B661_204C4F4F5020__INCLUDED_)
#define AFX_LRTFCTRL_H__9674279E_94A4_11D1_B661_204C4F4F5020__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LRTFCtrl.h : header file
//

#define BM_DRAW_FORMAT_CHAR WM_USER + 100

/////////////////////////////////////////////////////////////////////////////
// LRichEditCtrl window

class LRichEditCtrl : public CRichEditCtrl
{
// Construction
public:
	LRichEditCtrl();

// Attributes
public:

// Operations
public:
	void GetRTFText(CString& strText);
	void SetRTFText(const CString& strText);
	void DrawFormatChars(BOOL bDrawFormatChars = TRUE);
	void ToggleFormatChars();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LRichEditCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~LRichEditCtrl();

	// Generated message map functions
protected:
	CFont m_foFormatChar;
	BOOL m_bDrawFormatChars;

	//{{AFX_MSG(LRichEditCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg LRESULT OnDrawFormatChars(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LRTFCTRL_H__9674279E_94A4_11D1_B661_204C4F4F5020__INCLUDED_)
