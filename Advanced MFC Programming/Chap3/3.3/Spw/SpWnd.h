#if !defined(__SPWND_H__)
#define __SPWND_H__

class MCSplitterWnd : public CSplitterWnd
{
public:
	void DeleteRow(int);
	void DeleteColumn(int);
};

#endif
