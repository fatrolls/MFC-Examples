// Row.h: interface for the CRow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROW_H__584D7BF8_449E_427A_AC27_954F4D7F818C__INCLUDED_)
#define AFX_ROW_H__584D7BF8_449E_427A_AC27_954F4D7F818C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cell.h"

class CRow
{
public:
	CRow();
	virtual ~CRow();

protected:
	CObList m_obListOfCells;
	int m_nNumCells;
//	CCell m_oCell;

public:
	void RemoveItem(int nCol, int nCellLine);
	SCellLine GetItem(int nCol, int nCellLine);
	void ModifyItem(int nCol, int nCellLine, SCellLine* pSCellLine);
	int GetNoOfLineCount();
	void AddItem(int nCol, SCellLine* pSCellLine);
	int GetCellCount() const;

	CCell* GetCell(int nIndex);

};

#endif // !defined(AFX_ROW_H__584D7BF8_449E_427A_AC27_954F4D7F818C__INCLUDED_)
