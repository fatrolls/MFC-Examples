// MenuSpawn.h: interface for the CMenuSpawn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUSPAWN_H__BB6F2F01_91FA_11D1_8B78_0000B43382FE__INCLUDED_)
#define AFX_MENUSPAWN_H__BB6F2F01_91FA_11D1_8B78_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMenuSpawn  
{
public:
	struct ToolBarData	
	{ // struct for toolbar resource; guess you already know it ;)
		WORD wVersion;
		WORD wWidth;			
		WORD wHeight;			
		WORD wItemCount;		
	};
	struct SpawnItem
	{
		int		iImageIdx;
		int		iCmd;
		char	cText[128];
	};
	struct ImageItem
	{
		int		iImageIdx;
		int		iCmd;
	};
public:
	bool IsSpawnMenu(CMenu * pMenu, const int iItem, const bool bByPos);
	bool GetMenuItemText(CString &csText, CMenu * pMenu, const int cmd, bool bByPos);
	void TransparentBlt(CDC * pDestDc, int x, int y, int w, int h, CBitmap * pBmp, int sx, int sy, COLORREF crTransparent);
	void SetBackBitmap(const int iRes, COLORREF crBackColor);
	void SetBackBitmap(const int iRes);
	void SetTextColor(const COLORREF crNormal, const COLORREF crSelected);
	bool FindKeyboardShortcut(UINT nChar, UINT nFlags, CMenu * pMenu, LRESULT &lRes);
	bool SetFont(LOGFONT * lf);
	
	HFONT	hMenuFont, hGuiFont;
	CSize szImage;
	bool MeasureItem(LPMEASUREITEMSTRUCT lpm);
	bool DrawItem(LPDRAWITEMSTRUCT lp);
	int FindImageItem(const int cmd);
	SpawnItem * AddSpawnItem(const char * txt, const int cmd);
	void RemapMenu(CMenu * pMenu);
	void AddImageItem(const int idx, WORD cmd);

	CImageList ilList;
	CImageList ilOther;

	COLORREF crMenuText, crMenuTextSel;
	COLORREF cr3dFace, crMenu, crHighlight, cr3dHilight, cr3dShadow, crGrayText;
	COLORREF m_clrBtnFace, m_clrBtnHilight, m_clrBtnShadow;

	int iSpawnItem;
	SpawnItem ** pSpawnItem;

	int iImageItem;
	ImageItem * pImageItem;

	bool bIsPopup;
	bool bBackBitmap;
	CBitmap	bmpBack;

	bool LoadToolBarResource(unsigned int resId);
	bool AddToolBarResource(unsigned int resId);
	void EnableMenuItems(CMenu * pMenu, CWnd * pParent);
	CMenuSpawn();
	CMenuSpawn(const bool _IsPopup);
	virtual ~CMenuSpawn();

protected:
	void Init();
};

#endif // !defined(AFX_MENUSPAWN_H__BB6F2F01_91FA_11D1_8B78_0000B43382FE__INCLUDED_)
