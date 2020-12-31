#if !defined(AFX_SKINNEDSTATIC_H__98F66FA2_929E_44C0_96BD_0B84190A0C82__INCLUDED_)
#define AFX_SKINNEDSTATIC_H__98F66FA2_929E_44C0_96BD_0B84190A0C82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinnedStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinnedStatic window

#include "Skincontrol.h"
#include "..\Tools\GlobalFunctions.h"

class CSkinnedStatic : public CWnd, public CSkinControl
{
// Construction
public:
	CSkinnedStatic();

// Attributes
public:

// Operations
public:
	BOOL CreateSkinControl(LPCTSTR lpszWindowName, 
						LPRECT lpRect, 
						CWnd *pParentWnd, 
						UINT nControlID, 
						long lFlags=DRAW_STYLE_NORMAL);
	void BltEx();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinnedStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Redraw();
	CSize GetTextExtentEng();
	long GetTextAlignment();
	void SetTextAlignment(int nAlignment);
	void SetEnabled(BOOL bEnabled);
	void MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags=0);
	void MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags=0);
	void SetImageResource(INT nUnPressedID=-1, INT nHoverID=-1, INT nPressedID=-1, INT nDisabledID=-1);
	virtual ~CSkinnedStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSkinnedStatic)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bFindEdges;
	int UpdateMemoryDC();
	long m_lStaticType;
	HBITMAP m_hBitmap;
	HRGN m_hRgn;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINNEDSTATIC_H__98F66FA2_929E_44C0_96BD_0B84190A0C82__INCLUDED_)
