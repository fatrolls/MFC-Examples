#pragma once
#include ".\..\Dialog\WndPopup.h"
#include <vector>
using namespace std;

struct MeunExItem
{
	BOOL bSeparator;
	UINT uMenuID;
	Image *pImage;
	CSize sizeImage;
	CString strText;
	CRect rcItem;
};

class CMenuEx :  public CWndPopup
{
	vector<MeunExItem> m_vecItem;
	int					 m_nHoverItem;

public:
	CMenuEx(void);
	~CMenuEx(void);


	virtual void DrawWindow(CDC &dc, CRect rcClient);
	virtual void DrawWindowEx(CDC &dc, CRect rcClient);
	virtual void InitUI();
	int AddMenu(CString strText, int nResourceID, UINT uMenuID);
	int AddSeparator();

	virtual bool OnMouseMove(CPoint point);
	virtual bool OnLButtonDown(CPoint point);
	virtual bool OnLButtonUp(CPoint point);

private:
	void SetItemPoint();
	
};
