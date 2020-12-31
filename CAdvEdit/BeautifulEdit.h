/***************************************************************************/
/*                        类名：CBeautifulEdit                             */
/*				 	   (C)CopyRight www.cguage.com		     			   */
/***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
//基类：CEdit
//功能：使Edit控件有背景图像，和内容为空时显示指定的灰色消息文字，及设置对应
//		的颜色的功能
//作者：C瓜哥(admin@cguage.com)
//版本：V1.0(2010年4月14日2:31:20)
//		V1.1(    年 月  日        )
//主要方法：
//	void AddTipString(CString strTip);	/*设置……的文字*/
//	void AddBitmap(UINT nIDBitmap);		/*设置背景图像*/
//										/*设置文字和提示色:*/
//	void SetColors(COLORREF clrText = RGB(0, 0, 0),		
//						COLORREF clrTip = RGB(180, 180, 180));
//			
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEAUTIFULEDIT_H__CA359AF1_C2BC_4DA0_BE11_11802673AE54__INCLUDED_)
#define AFX_BEAUTIFULEDIT_H__CA359AF1_C2BC_4DA0_BE11_11802673AE54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BeautifulEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBeautifulEdit window

class CBeautifulEdit : public CEdit
{
// Construction
public:
	CBeautifulEdit(CString strTip = _T(""), UINT nIDBitmap = NULL);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeautifulEdit)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void AddTipString(CString strTip);	/*设置……的文字*/
	void AddBitmap(UINT nIDBitmap);		/*设置背景图像*/
										/*设置文字和提示色:*/
	void SetColors(COLORREF clrText = RGB(0, 0, 0),		
					COLORREF clrTip = RGB(180, 180, 180));
	virtual ~CBeautifulEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBeautifulEdit)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bIsTxtChangeByUsr;
	COLORREF m_clrTip;		//Tip文字的RGB颜色
	COLORREF m_clrText;		//Text(文本)的RGB颜色
	CBrush m_brhWhite;		//白色画刷
	CBrush m_brhNull;		//空画刷
	BOOL m_bIsEmpty;		//(用户编辑的)Text是否为空
	int m_bBkImg;			//是否有背景图像
	BOOL m_bIsFocus;		//是否获得焦点
	CString m_strTip;		//Tip文字内容(比如：请点击以编辑控件)
	CBitmap m_bitmap;		//背景图像
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAUTIFULEDIT_H__CA359AF1_C2BC_4DA0_BE11_11802673AE54__INCLUDED_)
