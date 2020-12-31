#ifndef __LINA_BOT_GIF_CONTROL_H__

#include <vector>

//The Control
class CGIFControl : public CStatic
{
public:
	//CTOR & DTOR
	CGIFControl();
	virtual ~CGIFControl();

	//
	BOOL Create(CRect& rc,CWnd* parent ,UINT nID);

	//Load gif image
	void Load(LPCTSTR sFileName);

	//Start play
	void Play();

	//Stop play
	void Stop();

	//Set border prop
	void SetBorderRound(Color& c,int iLineWidth = 1);

	//Set if show border
	void EnableBorder(BOOL bEnable = TRUE);

	//Url going when click
	void SetURL(LPCTSTR sURL);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
	void DrawBorder(Graphics& g);


protected:
	Image* m_pImage;
	GUID* m_pDimensionIDs;
	UINT m_FrameCount;
	PropertyItem* m_pItem;
	UINT m_iCurrentFrame;

	CString m_URL;

	Color m_cBorder;
	int m_iBorderLineWidth;
	BOOL m_bBorderEnable;

	HCURSOR m_hHandCursor;
	HCURSOR m_hOldCursor;
	BOOL m_bTrackOnce;

	//
	BOOL m_bIsPlaying;

protected:
	DECLARE_MESSAGE_MAP()
};

#endif
