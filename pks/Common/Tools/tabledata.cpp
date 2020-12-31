// TableData.cpp: implementation of the CTableData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\PukamSoft\PukamSoft.h"
#include "TableData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableData::CTableData()
{

}

CTableData::~CTableData()
{
	CRow* pRow;
	POSITION pos;

   for(pos = m_obListOfRows.GetHeadPosition();pos != NULL;)
   {
		pRow = (CRow*)m_obListOfRows.GetNext(pos);
		delete pRow; 
   }

	m_obListOfRows.RemoveAll();
	m_listOfColumnTitles.RemoveAll();
}

void CTableData::SetDimensions(int nRows, int nCols)
{
	m_nNumRows = nRows;
	m_nNumCols = nCols;
}

void CTableData::AddItem(int nRow, int nCol, SCellLine* pSCellLine)
{
	if(nRow >= m_nNumRows || nCol >= m_nNumCols)
	{
		return;
	}

	if(m_obListOfRows.IsEmpty() || nRow > (m_obListOfRows.GetCount()-1))
	{
		CRow* pRow = new CRow;
 		m_obListOfRows.AddTail((CObject*)pRow);
		pRow->AddItem(nCol,pSCellLine);
	}
	else
	{
		CRow* pRow = 0;
		pRow = (CRow*)m_obListOfRows.GetTail();
		pRow->AddItem(nCol,pSCellLine);
	}
}

void CTableData::AddColumnTitle(SColumnTitle* psColumnTitle)
{
	if(m_listOfColumnTitles.GetCount() > m_nNumCols)
	{
		return;
	}
	else
	{
 		m_listOfColumnTitles.AddTail(*psColumnTitle);
	}
}

void CTableData::ModifyItem(int nRow, int nCol, int nCellLine, SCellLine* pSCellLine)
{
	if(nRow >= m_nNumRows || nCol >= m_nNumCols)
	{
		return;
	}

	if(!m_obListOfRows.IsEmpty()) 
	{
		CRow* pRow;
		POSITION pos;
		int nRowCount = -1;

	   for(pos = m_obListOfRows.GetHeadPosition();pos != NULL;)
	   {
			nRowCount++;
			pRow = (CRow*)m_obListOfRows.GetNext(pos);

			if (nRowCount == nRow)
			{
				pRow->ModifyItem(nCol,nCellLine,pSCellLine);
			}
	   }
	}
}

void CTableData::RemoveItem(int nRow)
{
	if(!m_obListOfRows.IsEmpty()) 
	{
		CRow* pRow;
		POSITION pos;
		int nRowCount = -1;

	   for(pos = m_obListOfRows.GetHeadPosition();pos != NULL;)
	   {
			nRowCount++;
			if(nRowCount == nRow)
			{
				pRow = (CRow*)m_obListOfRows.GetAt(pos);
				m_obListOfRows.RemoveAt(pos);
				delete pRow;
				break;
			}
			else
			{
				pRow = (CRow*)m_obListOfRows.GetNext(pos);
			}
	   }
	}
}

void CTableData::SetColumnWidth(int nWidth, int nIndex/*=-1*/)
{
	m_nColWidth[nIndex] = nWidth;
}

int CTableData::GetColumnWidth(int nIndex/*=-1*/) const
{
	int nRet = -1;

	nRet = m_nColWidth[nIndex];

	return nRet;
}

const CTableData& CTableData::operator =(const CTableData& oTableData)
{
	return oTableData;
}

CRow* CTableData::GetRow(int nIndex)
{
	CRow* pRow = NULL;
	int nIdx = 0;
	POSITION pos = m_obListOfRows.GetHeadPosition();
	while(pos != NULL)
	{
		pRow = (CRow*)m_obListOfRows.GetNext(pos);
		if(nIdx == nIndex)
		{
			break;	
		}
		nIdx++;
	}
	return pRow;
}

int CTableData::GetRowCount()
{
	return m_obListOfRows.GetCount();
}

void CTableData::SetColumnTitleLineColor(COLORREF crColumnTitleLineColor)
{
	m_crColumnTitleLineColor = crColumnTitleLineColor; 
}

void CTableData::SetRowLineColor(COLORREF crRowLineColor)
{
	m_crRowLineColor = crRowLineColor;
}

void CTableData::SetColumnTitleVLineColor(COLORREF crColumnTitleVLineColor)
{
	m_crColumnTitleVLineColor = crColumnTitleVLineColor; 
}

void CTableData::SetRowVLineColor(COLORREF crRowVLineColor)
{
	m_crRowVLineColor = crRowVLineColor;
}

int CTableData::GetColumnTitleCount()
{
	return m_listOfColumnTitles.GetCount();
}

SColumnTitle* CTableData::GetColumnTitle(int nIndex)
{
	SColumnTitle *psColumnTitle = NULL;
	int nIdx = 0;
	POSITION pos = m_listOfColumnTitles.GetHeadPosition();
	while(pos != NULL)
	{
		psColumnTitle=&m_listOfColumnTitles.GetNext(pos);
		if(nIdx == nIndex)
		{
			break;	
		}
		nIdx++;
	}
	return psColumnTitle;
}

COLORREF CTableData::GetColumnTitleLineColor()
{
	return m_crColumnTitleLineColor; 
}

COLORREF CTableData::GetRowLineColor()
{
	return m_crRowLineColor; 
}

COLORREF CTableData::GetColumnTitleVLineColor()
{
	return m_crColumnTitleVLineColor; 
}

COLORREF CTableData::GetRowVLineColor()
{
	return m_crRowVLineColor; 
}

SCellLine CTableData::GetItem(int nRow, int nCol, int nCellLine)
{
	SCellLine sCellLine;
	memset(&sCellLine,0,sizeof(SCellLine));

	if(nRow >= m_nNumRows || nCol >= m_nNumCols)
	{
		return sCellLine;
	}

	if(!m_obListOfRows.IsEmpty()) 
	{
		CRow* pRow;
		POSITION pos;
		int nRowCount = -1;

	   for(pos = m_obListOfRows.GetHeadPosition();pos != NULL;)
	   {
			nRowCount++;
			pRow = (CRow*)m_obListOfRows.GetNext(pos);

			if (nRowCount == nRow)
			{
				sCellLine = pRow->GetItem(nCol,nCellLine);
				return sCellLine;
				break;
			}
	   }
	}

	return sCellLine;
}

CTableData::CTableData(UINT nTableID)
{
	m_nTableID = nTableID;
}

UINT CTableData::GetTableID()
{
	return m_nTableID;
}

void CTableData::SetTableTitle(TCHAR *pszTitle)
{
	strcpy(m_szTableTitle,pszTitle);
}

void CTableData::SetTitleColor(COLORREF crTitleColor)
{
	m_crTitleColor = crTitleColor; 
}

TCHAR* CTableData::GetTableTitle()
{
	return m_szTableTitle;
}

COLORREF CTableData::GetTitleColor()
{
	return m_crTitleColor;
}

int CTableData::GetColumnCount()
{
	return m_nNumCols;
}

void CTableData::AddTitleAttributes(STitleAttrib sTitleAttrib)
{
	m_listOfTitleAttributes.AddTail(sTitleAttrib);
}

STitleAttrib& CTableData::GetNextAttribute(POSITION &rPosition)
{
	return m_listOfTitleAttributes.GetNext(rPosition);
}

POSITION CTableData::GetAttribHeadPosition()
{
	return m_listOfTitleAttributes.GetHeadPosition();
}

void CTableData::RemoveAll()
{
	CRow* pRow;
	POSITION pos;

   for(pos = m_obListOfRows.GetHeadPosition();pos != NULL;)
   {
		pRow = (CRow*)m_obListOfRows.GetNext(pos);
		delete pRow; 
   }

	m_obListOfRows.RemoveAll();
	m_listOfColumnTitles.RemoveAll();

	m_nNumRows = 0;
	m_nNumCols = 0;
}