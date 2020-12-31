// Row.cpp: implementation of the CRow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\PukamSoft\PukamSoft.h"
#include "Row.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_CELLS_PER_ROW		12
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRow::CRow()
{
	m_nNumCells = m_obListOfCells.GetCount();
}

CRow::~CRow()
{
	CCell* pCell;
	POSITION pos;

   for(pos = m_obListOfCells.GetHeadPosition();pos != NULL;)
   {
		pCell = (CCell*)m_obListOfCells.GetNext(pos);
		delete pCell; 
   }

	m_obListOfCells.RemoveAll();
}

void CRow::AddItem(int nCol, SCellLine* pSCellLine)
{
	if(nCol >= MAX_CELLS_PER_ROW)
	{
		return;
	}

	if(m_obListOfCells.IsEmpty() || nCol > (m_obListOfCells.GetCount()-1))
	{
		CCell* pCell = new CCell;
 		m_obListOfCells.AddTail((CObject*)pCell);
		pCell->AddItem(0,pSCellLine);
	}
	else
	{
		CCell* pCell = 0;//&m_oCell;
		pCell = (CCell*)m_obListOfCells.GetTail();
		pCell->AddItem(1,pSCellLine);
	}	
}

int CRow::GetCellCount() const
{	
	return m_obListOfCells.GetCount();
}

CCell* CRow::GetCell(int nIndex)
{
	CCell* pCell = NULL;
	int nIdx = 0;
	POSITION pos = m_obListOfCells.GetHeadPosition();
	while(pos != NULL)
	{
		pCell = (CCell*)m_obListOfCells.GetNext(pos);
		if(nIdx == nIndex)
		{
			break;	
		}
		nIdx++;
	}
	return pCell;
}

int CRow::GetNoOfLineCount()
{
	CCell* pCell = NULL;
	int nNoOfLines = 0;

	POSITION pos = m_obListOfCells.GetHeadPosition();
	while(pos != NULL)
	{
		pCell = (CCell*)m_obListOfCells.GetNext(pos);

		if(nNoOfLines < pCell->GetLineCount())
		{
			nNoOfLines = pCell->GetLineCount(); 
		}
	}

	return nNoOfLines;
}

void CRow::ModifyItem(int nCol, int nCellLine, SCellLine *pSCellLine)
{
	if(nCol >= MAX_CELLS_PER_ROW)
	{
		return;
	}

	if(!m_obListOfCells.IsEmpty()) 
	{
		CCell* pCell;
		POSITION pos;
		int nCellCount = -1;

	   for(pos = m_obListOfCells.GetHeadPosition();pos != NULL;)
	   {
			nCellCount++;
			pCell = (CCell*)m_obListOfCells.GetNext(pos);

			if (nCellCount == nCol)
			{
				pCell->ModifyItem(nCellLine,pSCellLine);
				break;
			}
	   }
	}
}

void CRow::RemoveItem(int nCol, int nCellLine)
{
	if(nCol >= MAX_CELLS_PER_ROW)
	{
		return;
	}

	if(!m_obListOfCells.IsEmpty()) 
	{
		CCell* pCell;
		POSITION pos;
		int nCellCount = -1;

	   for(pos = m_obListOfCells.GetHeadPosition();pos != NULL;)
	   {
			nCellCount++;
			pCell = (CCell*)m_obListOfCells.GetNext(pos);

			if (nCellCount == nCol)
			{
				pCell->RemoveItem(nCellLine);
				break;
			}
	   }
	}
}

SCellLine CRow::GetItem(int nCol, int nCellLine)
{
	SCellLine sCellLine;
	memset(&sCellLine,0,sizeof(SCellLine));

	if(nCol >= MAX_CELLS_PER_ROW)
	{
		return sCellLine;
	}

	if(!m_obListOfCells.IsEmpty()) 
	{
		CCell* pCell;
		POSITION pos;
		int nCellCount = -1;

	   for(pos = m_obListOfCells.GetHeadPosition();pos != NULL;)
	   {
			nCellCount++;
			pCell = (CCell*)m_obListOfCells.GetNext(pos);

			if (nCellCount == nCol)
			{
				sCellLine = pCell->GetItem(nCellLine);
				return sCellLine;
				break;
			}
	   }
	}

	return sCellLine;
}