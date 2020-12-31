// TableData.h: interface for the CTableData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEDATA_H__ABC111EF_C44A_4203_89C6_AA1E47205A68__INCLUDED_)
#define AFX_TABLEDATA_H__ABC111EF_C44A_4203_89C6_AA1E47205A68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Row.h"
#include "Cell.h"

class CTableData
{
public:
	CTableData(UINT nTableID);
	CTableData();
	virtual ~CTableData();

protected:
	COLORREF m_crTitleColor;
	TCHAR m_szTableTitle[MIN_TEXT];
	UINT m_nTableID;
	int m_nNumRows;
	int m_nNumCols;
	CObList m_obListOfRows;
	int m_nColWidth[MAX_COLUMNS];
	CList <SColumnTitle,SColumnTitle&> m_listOfColumnTitles;
	CList <STitleAttrib,STitleAttrib&> m_listOfTitleAttributes;
	COLORREF m_crColumnTitleLineColor;
	COLORREF m_crRowLineColor;
	COLORREF m_crColumnTitleVLineColor;
	COLORREF m_crRowVLineColor;
	
public:
	void RemoveAll();
	POSITION GetAttribHeadPosition();
	STitleAttrib& GetNextAttribute(POSITION& rPosition);
	void AddTitleAttributes(STitleAttrib sTitleAttrib);
	int GetColumnCount();
	void SetTitleColor(COLORREF crTitleColor);
	void SetTableTitle(TCHAR *pszTitle);
	UINT GetTableID();
	SCellLine GetItem(int nRow, int nCol, int nCellLine);
	int GetColumnTitleCount();
	void SetRowLineColor(COLORREF crRowLineColor);
	void SetColumnTitleLineColor(COLORREF crColumnTitleLineColor);
	void SetColumnTitleVLineColor(COLORREF crColumnTitleVLineColor);
	void SetRowVLineColor(COLORREF crRowVLineColor);
	void SetDimensions(int nRows, int nCols);
	SColumnTitle* GetColumnTitle(int nIndex);	
	void AddItem(int nRow, int nCol, SCellLine* pSCellLine);
	void ModifyItem(int nRow, int nCol, int nCellLine, SCellLine* pSCellLine);
	void RemoveItem(int nRow);
	void AddColumnTitle(SColumnTitle* psColumnTitle);
	void SetColumnWidth(int nWidth, int nIndex=-1);
	int GetColumnWidth(int nIndex=-1) const;
	COLORREF GetColumnTitleLineColor();
	COLORREF GetRowLineColor();
	COLORREF GetColumnTitleVLineColor();
	COLORREF GetRowVLineColor();
	CRow* GetRow(int nIndex);
	int GetRowCount();
	const CTableData& operator =(const CTableData&);
	TCHAR* GetTableTitle();
	COLORREF GetTitleColor();
};

#endif // !defined(AFX_TABLEDATA_H__ABC111EF_C44A_4203_89C6_AA1E47205A68__INCLUDED_)
