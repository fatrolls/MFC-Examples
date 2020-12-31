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