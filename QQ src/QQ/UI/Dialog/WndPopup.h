#pragma once

#include "..\Base\ControlBase.h"

#define					WM_POPUP_CLOSE					(WM_USER + 1)

// CWndPopup

class CWndPopup : public CWnd
{
	bool m_bTracking;
	bool m_bLButtonDown;
	bool m_bIsSetCapture;

protected:
	Image*			m_pImage;
	CSize			m_sizeBKImage;
	CFont			m_font;
	CPoint			m_point;
	UINT			m_uMessageID;
	DECLARE_DYNAMIC(CWndPopup)

public:
	CWndPopup();
	virtual ~CWndPopup();

	void SetBackBitmap(UINT nResourceID);
	void SetBackBitmap(CString strImage);
	BOOL Create(CWnd *pParent, CRect rc, UINT uMessageID);
	void CloseWindow();

	void DrawWindow();	
	virtual void DrawWindow(CDC &dc, CRect rcClient){};
	virtual void DrawWindowEx(CDC &dc, CRect rcClient){};
	virtual void InitUI(){};
	virtual bool OnMouseMove(CPoint point){ return false;};
	virtual bool OnLButtonDown(CPoint point){ return false;};
	virtual bool OnLButtonUp(CPoint point){ return false;};

	// 发送通知消息
	bool SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);


protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg BOOL OnEraseBkgnd (CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();()
public:
	afx_msg void OnClose();
};


