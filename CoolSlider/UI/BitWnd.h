#if !defined(AFX_BITWND_H__177953D4_86F7_4FBD_AC1D_6B9C165AACD6__INCLUDED_)
#define AFX_BITWND_H__177953D4_86F7_4FBD_AC1D_6B9C165AACD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Author	:	Jackey
//	Date	:	2004.02.19
//	File	:	BitWnd.h
//	Home	:	http://www.kuihua.net/
//	Contains:	Define the CBitWnd class...
//	History	:
//		1.0	:	2004.02.19 - First Version...
//	Mailto	:	Omega@Kuihua.net (Bug Report or Comments)
////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBitItem;

class CBitWnd : public CWnd
{
public:
	CBitWnd();
	virtual ~CBitWnd();
public:
	//{{AFX_VIRTUAL(CBitWnd)
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CBitWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg	LRESULT	OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	BOOL		GetMuteFlag()					{ return m_bMute; }
	void		SetMuteFlag(BOOL bMute)			{ m_bMute = bMute; m_nState = m_bMute ? kActiveBit : kNormalBit; }
	void		SetCanMute(BOOL bCanMute)		{ m_bCanMute= bCanMute; }
	void		SetNotifyParent(BOOL bNotify)	{ m_bNotify = bNotify; }
	void		SetFlipCursor(HCURSOR hCursor)	{ m_hCursor = hCursor; }
	void		SetLDownNotify(BOOL bDownFlag)	{ m_bLDownNotify = bDownFlag; }

	void		SetBitItem(CBitItem * lpBit);
	void		ReLoadBitItem(UINT nResID, int cx, int cy);
	BOOL		Create(UINT wStyle, CWnd * pParentWnd, UINT nID);
private:
	enum BIT_STATE
	{
		kNormalBit		= 0,
		kHoverBit		= 1,
		kActiveBit		= 2,
	};
	BIT_STATE		m_nState;
	CBitItem	*	m_lpBit;
	HCURSOR			m_hCursor;
	BOOL			m_bMute;
	BOOL			m_bCanMute;
	BOOL			m_bNotify;
	BOOL			m_bTracking;
	BOOL			m_bAllocFlag;
	BOOL			m_bLDownNotify;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITWND_H__177953D4_86F7_4FBD_AC1D_6B9C165AACD6__INCLUDED_)
