#if !defined(__SPWND_H__)
#define __SPWND_H__

class MCSplitterWnd : public CSplitterWnd
{
public:
	virtual void DeleteRow(int);
	virtual void DeleteColumn(int);

protected:
	virtual void OnDrawSplitter(CDC*, CSplitterWnd::ESplitType,	const CRect&);
	virtual void OnInvertTracker(const CRect& rect);
};

#endif
