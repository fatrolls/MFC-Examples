#if !defined(__SPWND_H__)
#define __SPWND_H__

class MCSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNCREATE(MCSplitterWnd)
public:
	MCSplitterWnd();
	void SetResizable(BOOL bResizable){m_bResizable=bResizable;}
	virtual void DeleteRow(int);
	virtual void DeleteColumn(int);

protected:
	BOOL m_bResizable;

	virtual void OnDrawSplitter(CDC*, CSplitterWnd::ESplitType,	const CRect&);
	virtual void OnInvertTracker(const CRect& rect);
	afx_msg void OnLButtonDown(UINT, CPoint);
	DECLARE_MESSAGE_MAP()
};

#endif
