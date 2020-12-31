// Cell.cpp: implementation of the CCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\PukamSoft\PukamSoft.h"
#include "Cell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCell::CCell()
{

}

CCell::~CCell()
{
	m_listOfCellLines.RemoveAll();
}

void CCell::AddItem(int nLine, SCellLine* pSCellLine)
{
	m_listOfCellLines.AddTail(*pSCellLine);
	if(nLine == 0)
	{
		SetCellBackColor(pSCellLine->crBackColor);
	}
}

int CCell::GetLineCount() const
{
	return m_listOfCellLines.GetCount();
}

SCellLine* CCell::GetCellLine(int nIndex)
{
	SCellLine* pSCellLine = NULL;
	int nIdx = 0;
	POSITION pos = m_listOfCellLines.GetHeadPosition();
	while(pos != NULL)
	{
		pSCellLine = &m_listOfCellLines.GetNext(pos);
		if(nIdx == nIndex)
		{
			break;	
		}
		nIdx++;
	}
	return pSCellLine;
}

void CCell::SetCellBackColor(COLORREF crBackColor)
{
	m_crBackColor = crBackColor;
}

COLORREF CCell::GetCellBackColor() const
{
	return m_crBackColor;
}

void CCell::ModifyItem(int nCellLine, SCellLine *pSCellLine)
{
	if(nCellLine >= m_listOfCellLines.GetCount())
	{
		return;
	}

	if(!m_listOfCellLines.IsEmpty()) 
	{
		POSITION pos = m_listOfCellLines.FindIndex(nCellLine);

		if (pos != NULL)
		{
			m_listOfCellLines.SetAt(pos,*pSCellLine);
		}
	}
}

void CCell::RemoveItem(int nCellLine)
{
	if(nCellLine >= m_listOfCellLines.GetCount())
	{
		return;
	}

	if(!m_listOfCellLines.IsEmpty()) 
	{
		POSITION pos = m_listOfCellLines.FindIndex(nCellLine);

		if (pos != NULL)
		{
			m_listOfCellLines.RemoveAt(pos);
		}
	}
}

SCellLine CCell::GetItem(int nCellLine)
{
	SCellLine sCellLine;
	memset(&sCellLine,0,sizeof(SCellLine));

	if(nCellLine >= m_listOfCellLines.GetCount())
	{
		return sCellLine;
	}

	if(!m_listOfCellLines.IsEmpty()) 
	{
		POSITION pos;
		int nCellLineCount = -1;

		for(pos = m_listOfCellLines.GetHeadPosition();pos != NULL;)
		{
			nCellLineCount++;
			sCellLine = m_listOfCellLines.GetNext(pos);

			if (nCellLineCount == nCellLine)
			{
				return sCellLine;
				break;
			}
		}
	}

	return sCellLine;
}