// Cell.h: interface for the CCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELL_H__491C3DE1_B55A_4604_8146_E5FDB088DC05__INCLUDED_)
#define AFX_CELL_H__491C3DE1_B55A_4604_8146_E5FDB088DC05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCell  
{
public:
	CCell();
	virtual ~CCell();

protected:
	int m_nNumLines;
	CList <SCellLine,SCellLine&> m_listOfCellLines;
	COLORREF m_crBackColor;

public:
	void RemoveItem(int nLine);
	void AddItem(int nLine, SCellLine* pSCellLine);
	void SetCellBackColor(COLORREF crBackColor);
	int GetLineCount() const;
	SCellLine* GetCellLine(int nIndex);
	COLORREF GetCellBackColor() const;
	void ModifyItem(int nCellLine, SCellLine *pSCellLine);
	SCellLine GetItem(int nCellLine);
};

#endif // !defined(AFX_CELL_H__491C3DE1_B55A_4604_8146_E5FDB088DC05__INCLUDED_)
