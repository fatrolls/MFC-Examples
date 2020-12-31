/***************************************************************************/
/*                        类名：CAdvEdit		                           */
/*				 	   (C)CopyRight www.cguage.com		     			   */
/***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
//基类：CEdit
//功能：实现了3D圆角编辑框，可自定义字体大小、颜色，边框圆角大小、边框颜色等，可以
//自定义光标，设置多种鼠标滑过效果
//作者：C瓜哥
//		(Email: tangcraig@gmail.com  QQ: 1019714877 blog: www.cguage.com)
//版本：V0.9(2010年7月12日15:32:41)

//主要方法：
// - 设置光标
// void SetCursor(UINT nIDCursor);
// void SetCursor(LPCTSTR lpszCur);
// - 设置鼠标滑过效果
// void SetHoverStyle(int nHoverStyle = FOCUS_DEFAULT, int nHoverFontSize = 0,
// 				   COLORREF clrHoverBkgnd = 0, int nHoverBorderThick = 0);
// 
// void SetGrayTipString(CString strTipStr);	//灰色文字提示
// void SetBorderCorner(CPoint ptBorderCorner);	//设置圆角圆度
// void SetTextColor(COLORREF clrText);			//设置文字颜色
// void SetBkgndColor(COLORREF clrBkgnd);		//设置背景颜色
// - 设置边框颜色
// void SetBorderColor(COLORREF clrBorderNormal, COLORREF clrBorderHover);
// - 设置阴影颜色
// void SetShadowColor(COLORREF clrInnerShadow, COLORREF clrOutterShadow);
// - 设置字体及大小
// 	void SetFont(int nPointSize, LPCTSTR lpszFaceName);

/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ADVEDIT_H__9BC7B9B8_C54A_4B57_B105_A6C5F1745B4B__INCLUDED_)
#define AFX_ADVEDIT_H__9BC7B9B8_C54A_4B57_B105_A6C5F1745B4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdvEdit window
//鼠标滑过时的效果
enum
{
	FOCUS_DEFAULT,			//默认效果：只有边框颜色变化
	FOCUS_ENLARGE,			//文本框变大		
	FOCUS_BKCOLOR,			//背景色变化
	FOCUS_BORDERTHICK = 4	//边框厚度变化
};

class CAdvEdit : public CEdit
{
// Construction
public:
	CAdvEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvEdit)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCursor(UINT nIDCursor);
	void SetCursor(LPCTSTR lpszCur);
	void SetHoverStyle(int nHoverStyle = FOCUS_DEFAULT, int nHoverFontSize = 0,
		COLORREF clrHoverBkgnd = 0, int nHoverBorderThick = 0);
	void SetGrayTipString(CString strTipStr);
	void SetBorderCorner(CPoint ptBorderCorner);
	void SetTextColor(COLORREF clrText);
	void SetBkgndColor(COLORREF clrBkgnd);
	void SetBorderColor(COLORREF clrBorderNormal, COLORREF clrBorderHover);
	void SetShadowColor(COLORREF clrInnerShadow, COLORREF clrOutterShadow);
	void SetFont(int nPointSize, LPCTSTR lpszFaceName);
	virtual ~CAdvEdit();

	// Generated message map functions
protected:
	void ResizeWnd();
	//{{AFX_MSG(CAdvEdit)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	afx_msg void OnNcPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	HCURSOR m_hCursor;

	int m_nHoverStyle;
	COLORREF m_nHoverBorderThick;
	CString m_strTipStr;
	CPoint m_ptBorderCorner;
	COLORREF m_clrOutterShadow;
	COLORREF m_clrInnerShadow;
	COLORREF m_clrBorderHover;
	COLORREF m_clrBorderNormal;
	COLORREF m_clrBkgnd;
	COLORREF m_clrHoverBkgnd;
	COLORREF m_clrText;
	LPCTSTR m_lpszFaceName;
	int m_nFontSize;
	int m_nHoverFontSize;
	BOOL m_bIsEmpty;
	BOOL m_bModByUsr;
	BOOL m_bHover;
	BOOL m_bAllowTrack;
	CFont m_font;
	CBrush m_brhNull;
	CRect m_rcClient;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVEDIT_H__9BC7B9B8_C54A_4B57_B105_A6C5F1745B4B__INCLUDED_)
