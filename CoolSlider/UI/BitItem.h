////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Author	:	Jackey
//	Date	:	2004.02.19
//	File	:	BitItem.h
//	Home	:	http://www.kuihua.net/
//	Contains:	Define the CBitItem class...
//	History	:
//		1.0	:	2004.02.19 - First Version...
//	Mailto	:	Omega@Kuihua.net (Bug Report or Comments)
////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __BIT_ITEM_H__
#define __BIT_ITEM_H__

class CBitItem
{
public:
	enum
	{
		kBitReadMode	= 0,			// This item can be read only...
		kBitWriteMode	= 1				// This item can be read and write...
	};
	enum
	{
		kBitHorizon		= 0,			// Sub-Icon is Horizon direction...
		kBitVertical	= 1				// Sub-Icon is Vertical direction...
	};
public:
	CBitItem(UINT nResID, int cx, int cy, int nMode = CBitItem::kBitReadMode);
	~CBitItem();
	
	CDC		*	GetWriteDC()		{ return ((m_nMode == kBitWriteMode) ? &m_WriteDC : NULL); }
	CDC		*	GetReadDC()			{ return &m_ReadDC; }

	int			GetBitDir()			{ return m_nDir; }
	int			GetBitMode()		{ return m_nMode; }

	UINT		GetItemNums()		{ return m_nItemNums; }
	UINT		GetItemWidth()		{ return m_nItemWidth; }
	UINT		GetItemHeight()		{ return m_nItemHeight; }
	UINT		GetImageWidth()		{ return m_Bitmap.bmWidth; }
	UINT		GetImageHeight()	{ return m_Bitmap.bmHeight; }
	void		SetOffset(POINT pt) { m_Offset.x = pt.x; m_Offset.y = pt.y; }

	BOOL		RecoverDirtyDC();
	BOOL		WriteItemIndex(CBitItem * lpSrcBit, int nSrcIndex);

	BOOL		IsInBitItem(CPoint & pt, POINT * lpOff = NULL);
	void		GetRectPos(LPRECT lpRect, POINT * lpOff = NULL);
	
	BOOL		GetRectByIndex(LPRECT lpRect, int nIndex, BOOL bSrc = TRUE, POINT * lpOff = NULL);
	BOOL		CopyItemIndex(CDC * lpDesDC, int nIndex, BOOL bSrc = TRUE, POINT * lpOff = NULL);

	BOOL		CopyHoleDC( CDC * lpDesDC, int x, int y, int cx, int cy, int xSrc = 0, int ySrc = 0,
							BOOL bStretch = FALSE, BOOL bMiddle = FALSE);
	BOOL		CopyHoleDC( CDC * lpDesDC, LPRECT lpRect, int xSrc = 0, int ySrc = 0,
							BOOL bStretch = FALSE, BOOL bMiddle = FALSE);
private:
	int			m_nItemNums;			// This object has how many sub-item...
	UINT		m_nItemWidth;			// Every sum-item's width...(Zero Means background)
	UINT		m_nItemHeight;			// Every sum-item's height...(Zero Means background)

	int			m_nMode;				// This item's mode...
	int			m_nDir;					// This item's direction...

	CPoint		m_Offset;
	BITMAP		m_Bitmap;				// This item's bitmap information...
	CBitmap		m_ReadBit;				// The read bitmap object...
	CBitmap		m_WriteBit;				// The write bitmap object...

	CDC			m_ReadDC;				// This item's read DC...
	CDC			m_WriteDC;				// This item's write DC...
};

#endif	// __BIT_ITEM_H__