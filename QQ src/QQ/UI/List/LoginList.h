#pragma once
#include ".\..\Dialog\WndPopup.h"
#include <vector>
using namespace std;

// ÏûÏ¢
#define				SELECT_ITEM					1
#define				DELETE_ITEM					2

struct EditListItem
{
	UINT nResourceID;
	CString strImagrFile;
	Image *pImage;
	CSize sizeImage;
	CString strName;
	CString strNumber;
	CRect rcItem;
};

class CLoginList :  public CWndPopup
{
	Image*			m_pHeadImage;
	Image*			m_pCloseImage;
	CSize			m_sizeHeadImage;
	CSize			m_sizeCloseImage;
	CRect			m_rcClose;
	enumButtonState   m_buttonState;
	vector<EditListItem> m_vecItem;
	int					 m_nHoverItem;

public:
	CLoginList(void);
	~CLoginList(void);

	void SetHeadBitmap(UINT nResourceID);
	void SetHeadBitmap(CString strImage);
	void SetDeleteBitmap(UINT nResourceID);
	void SetDeleteBitmap(CString strImage);

	bool GetItemNumber(UINT nItem, CString &strNumber);
	bool GetItemName(UINT nItem, CString &strName);
	bool GetItemImage(UINT nItem, UINT &nResourceID, CString &strImageFile);
	bool DeleteItem(UINT nItem);

	virtual void DrawWindow(CDC &dc, CRect rcClient);
	virtual void DrawWindowEx(CDC &dc, CRect rcClient);

	virtual void InitUI();
	int AddItem(CString strName, CString strNumber, int nResourceID, CString strImageFile = "");

	virtual bool OnMouseMove(CPoint point);
	virtual bool OnLButtonDown(CPoint point);
	virtual bool OnLButtonUp(CPoint point);

private:
	void SetItemPoint();
	
};
