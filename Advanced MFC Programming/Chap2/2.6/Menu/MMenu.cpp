#include "stdafx.h"
#include "MMenu.h"
#include "resource.h"

MCMenu::MCMenu() : CMenu()
{
	m_bmpQuestion.LoadBitmap(IDB_BITMAP_QUESTION);
	m_bmpQuestionSel.LoadBitmap(IDB_BITMAP_QUESTIONSEL);
	m_bmpSmile.LoadBitmap(IDB_BITMAP_SMILE);
	m_bmpSmileSel.LoadBitmap(IDB_BITMAP_SMILESEL);
}

MCMenu::~MCMenu()
{
	Detach();
}

void MCMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	BITMAP bm;

	switch(lpMeasureItemStruct->itemData)
	{
		case MENUTYPE_SMILE:
		{
			m_bmpSmile.GetBitmap(&bm);
			break;
		}
		case MENUTYPE_QUESTION:
		{
			m_bmpQuestion.GetBitmap(&bm);
			break;
		}
	}
	lpMeasureItemStruct->itemWidth=bm.bmWidth;
	lpMeasureItemStruct->itemHeight=bm.bmHeight;
}

void MCMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *ptrDC;
	CDC dcMem;
	CBitmap *ptrBmpOld;
	CBitmap *ptrBmp;
	CRect rect;

	if(!(lpDrawItemStruct->CtlType & ODT_MENU))
	{
		CMenu::DrawItem(lpDrawItemStruct);
		return;
	}

	ptrDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	dcMem.CreateCompatibleDC(ptrDC);

	if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		switch(lpDrawItemStruct->itemData)
		{
			case MENUTYPE_SMILE:
			{
				ptrBmp=&m_bmpSmileSel;
				break;
			}
			case MENUTYPE_QUESTION:
			{
				ptrBmp=&m_bmpQuestionSel;
				break;
			}
		}
	}
	else
	{
		switch(lpDrawItemStruct->itemData)
		{
			case MENUTYPE_SMILE:
			{
				ptrBmp=&m_bmpSmile;
				break;
			}
			case MENUTYPE_QUESTION:
			{
				ptrBmp=&m_bmpQuestion;
				break;
			}
		}
	}	
	
	ptrBmpOld=dcMem.SelectObject(ptrBmp);
	rect=lpDrawItemStruct->rcItem;
	ptrDC->BitBlt
	(
		rect.left,
		rect.top,
		rect.Width(),
		rect.Height(),
		&dcMem,
		0,
		0,
		SRCCOPY
	);
	dcMem.SelectObject(ptrBmpOld);
}
