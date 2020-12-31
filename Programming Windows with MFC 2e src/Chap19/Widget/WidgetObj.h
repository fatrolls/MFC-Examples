#if !defined(AFX_WIDGETOBJ_H__02909A57_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
#define AFX_WIDGETOBJ_H__02909A57_3F5C_11D2_AC89_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WidgetObj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWidget command target

class CWidget : public CObject
{
	DECLARE_SERIAL(CWidget)

// Attributes
public:

// Operations
public:
	CWidget();
	CWidget (int x, int y, COLORREF color);
	virtual ~CWidget();
	void DrawSelected (CDC* pDC);
	BOOL PtInWidget (POINT point);
	virtual void DrawDragImage (CDC* pDC, POINT point);
	virtual void Draw (CDC* pDC);
	COLORREF GetColor ();
	CRect GetRect ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWidget)
	//}}AFX_VIRTUAL
	virtual void Serialize (CArchive& ar);

// Implementation
protected:
	COLORREF m_color;
	CRect m_rect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDGETOBJ_H__02909A57_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
