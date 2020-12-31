#if !defined(AFX_TABLECONTAINER_H__B47A3AF5_F7BE_493D_B268_B87E9F4F302D__INCLUDED_)
#define AFX_TABLECONTAINER_H__B47A3AF5_F7BE_493D_B268_B87E9F4F302D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableContainer.h : header file
//
#include "TableData.h"
#include "TablePage.h"
#include "..\..\Common\UIClasses\SkinnedScrollBar.h"
/////////////////////////////////////////////////////////////////////////////
// CTableContainer window

class CTableContainer : public CWnd
{
// Construction
public:
	CTableContainer();

// Attributes
public:

protected:
	int m_nSelectedRow;
	int m_nCurrentTableID;
	CObList m_obListOfTables;
	CTablePage* m_pMainTablePage;
	CTablePage* m_pITTablePage;
	CTableData* m_pITTableData;
	CTablePage* m_pOTTablePage;
	CTableData* m_pOTTableData;
	CList <int,int> m_listOfTableID;
	CSkinnedScrollBar* m_pVScrollBar;
	CString m_csPKID;
	CString m_csSerialNumber;
	CString m_csCompanyName;
	
// Operations
public:
	
	void CreateTableEng(UINT nTableID);
	void RemoveTableEng(UINT nTableID);
	void DrawTable();
	BOOL AddItem(UINT nTableID, int nRow, int nCol, SCellLine* pSCellLine);
	BOOL ModifyItem(UINT nTableID, int nRow, int nCol, int nCellLine, SCellLine* pSCellLine);
	BOOL RemoveItem(UINT nTableID, int nRow, int nCol);
	void SetColumnWidth(UINT nTableID, int nWidth, int nIndex=-1);
	void AddColumnTitle(UINT nTableID, SColumnTitle *psColumnTitle);
	void SetColumnTitleLineColor(UINT nTableID, COLORREF crColumnTitleLineColor);
	void SetRowLineColor(UINT nTableID, COLORREF crRowLineColor);
	void SetColumnTitleVLineColor(UINT nTableID, COLORREF crColumnTitleVLineColor);
	void SetRowVLineColor(UINT nTableID, COLORREF crRowVLineColor);
	void SetDimensions(UINT nTableID,int nRows, int nCols);
	void SetTableTitle(UINT nTableID,TCHAR *pszTitle);
	void SetTableTitleColor(UINT nTableID, COLORREF crTitleColor);
	int GetRowCount(UINT nTableID);
	void PopulateTable(UINT nTableID);
	void PopulateDetailsTable(CTableData* pTableData, UINT nTableID, long lPKID);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableContainer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteEntry(UINT nTableID);
	void DisplayMainTable();
	BOOL DisplayDetailsTable(UINT nTableID);
	CString GetPageTitle();
	BOOL RemoveAllItems(UINT nTableID);
	void ShowVerticalScroll(int nTableHeight);
	SCellLine GetItem(UINT nTableID, int nRow, int nCol,int nCellLine);
	virtual ~CTableContainer();

	// Generated message map functions
protected:
	long m_lPKID;
	//{{AFX_MSG(CTableContainer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_csPageTitle;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLECONTAINER_H__B47A3AF5_F7BE_493D_B268_B87E9F4F302D__INCLUDED_)
