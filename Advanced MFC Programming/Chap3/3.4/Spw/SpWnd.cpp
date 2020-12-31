#include "StdAfx.h"
#include "SpWnd.h"

#define ONE_STEP_MOVE	6

void MCSplitterWnd::DeleteRow(int rowDelete)
{
	int nNumRows;

	nNumRows=GetRowCount();
	if(nNumRows < 2)
	{
		CSplitterWnd::DeleteRow(rowDelete);
	}
	else
	{
		int nCyCur, nCyMin;
		
		GetRowInfo(0, nCyCur, nCyMin);
		nCyCur+=ONE_STEP_MOVE;
		SetRowInfo(0, nCyCur, nCyMin);
		
		GetRowInfo(1, nCyCur, nCyMin);
		nCyCur-=ONE_STEP_MOVE;
		if(nCyCur < nCyMin)
		{
			CSplitterWnd::DeleteRow(rowDelete);
		}
		else
		{
			SetRowInfo(1, nCyCur, nCyMin);
			RecalcLayout();
		}
	}
}

void MCSplitterWnd::DeleteColumn(int colDelete)
{
	int nNumColumns;

	nNumColumns=GetColumnCount();
	if(nNumColumns < 2)
	{
		CSplitterWnd::DeleteColumn(colDelete);
	}
	else
	{
		int nCxCur, nCxMin;
		
		GetColumnInfo(0, nCxCur, nCxMin);
		nCxCur+=ONE_STEP_MOVE;
		SetColumnInfo(0, nCxCur, nCxMin);
		
		GetColumnInfo(1, nCxCur, nCxMin);
		nCxCur-=ONE_STEP_MOVE;
		if(nCxCur < nCxMin)
		{
			CSplitterWnd::DeleteColumn(colDelete);
		}
		else
		{
			SetColumnInfo(1, nCxCur, nCxMin);
			RecalcLayout();
		}
	}
}

void MCSplitterWnd::OnDrawSplitter
(
	CDC* pDC,
	ESplitType nType,
	const CRect& rect
)
{
	CBrush brush;
	CBrush *ptrBrushOld;

	if(pDC == NULL)
	{
		CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
		return;
	}
	switch(nType)
	{
		case CSplitterWnd::splitBox:
		{
			VERIFY(brush.CreateSolidBrush(RGB(255, 0, 0)));
			break;
		}
		case CSplitterWnd::splitBar:
		{
			VERIFY(brush.CreateSolidBrush(RGB(0, 255, 0)));
			break;
		}
		case CSplitterWnd::splitIntersection:
		case CSplitterWnd::splitBorder:
		{
			CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
			return;
		}
	}
	ptrBrushOld=pDC->SelectObject(&brush);
	pDC->Rectangle(rect);
	pDC->SelectObject(ptrBrushOld);
	brush.DeleteObject();
}

void MCSplitterWnd::OnInvertTracker(const CRect& rect)
{
	CDC* pDC;
	CBrush brush;
	CBrush *ptrBrushOld;

	ASSERT_VALID(this);
	ASSERT(!rect.IsRectEmpty());
	ASSERT((GetStyle() & WS_CLIPCHILDREN) == 0);

	pDC=GetDC();
	brush.CreateSolidBrush(RGB(255, 0, 0));
	ptrBrushOld=pDC->SelectObject(&brush);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATINVERT);
	pDC->SelectObject(ptrBrushOld);
	brush.DeleteObject();
	ReleaseDC(pDC);
}