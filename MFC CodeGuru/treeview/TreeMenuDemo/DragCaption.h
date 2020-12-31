
#ifndef _DRAGCAPTION_H
#define _DRAGCAPTION_H


class CDragCaption : public CStatic {
public:
	DECLARE_DYNAMIC(CDragCaption)
	CDragCaption(LPCTSTR lpText = NULL, BOOL bDeleteOnDestroy=FALSE);
	~CDragCaption() { }

	
	BOOL SubclassDlgItem(UINT nID, CWnd* pParent) {
		return CStatic::SubclassDlgItem(nID, pParent);
	}

	COLORREF		m_color;

	// Default colors you can change
	// These are global, so they're the same for all links.
	static COLORREF g_colorUnvisited;
	static COLORREF g_colorVisited;

	

protected:
	CFont			m_font;			
	BOOL			m_bDeleteOnDestroy;	// delete object when window destroyed?

	virtual void PostNcDestroy();

	// message handlers
	DECLARE_MESSAGE_MAP()
	afx_msg UINT	OnNcHitTest(CPoint point);
	afx_msg HBRUSH 	CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
};

#endif _DRAGCAPTION_H
