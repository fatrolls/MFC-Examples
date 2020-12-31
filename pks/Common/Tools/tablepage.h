#if !defined(AFX_TABLEPAGE_H__351896E3_57C1_4888_B03E_D2060E1BE856__INCLUDED_)
#define AFX_TABLEPAGE_H__351896E3_57C1_4888_B03E_D2060E1BE856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TablePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTablePage window
#include "..\..\Common\UIClasses\SkinnedButton.h"
#include "EditDlg.h"

class CTablePage : public CWnd
{
// Construction
public:
	CTablePage();

// Attributes
public:

protected:
	CObList m_obListOfCheckBox;
	CList <UINT,UINT&> m_listOfCheckIDs;
	CDC m_memDC;
	CBitmap m_memBmp;
	int m_nLeftMargin;
	int m_nTopMargin;
	int m_nRightMargin;
	int m_nBottomMargin;
	COLORREF m_crBackColor;
	bool m_bWorkInProgress;

	int m_nRowIndex;

	CList <SCellInfo,SCellInfo&> m_ListOfCellInfo;
	
// Operations
public:
	void InitializeTablePage(LPRECT lpRect, CWnd* pParentWnd, UINT nID);
	void SetPageMargins(int nLeft, int nTop, int nRight, int nBottom);
	void SetPageBackColor(COLORREF crBackColor);
	void DrawPage(CObList* pObListOfTables);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTablePage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ResetCheckBoxes(CObList* pObListOfTables);
	void SetTableTopPosition(UINT nTableID,int nPos);
	int GetHeight();
	void DrawTableHeader(CTableData* pTableData, POINT& ptCursor);
	void EmptyAllCollections();
	void CreateCheckBoxes(CObList* pObListOfTables);
	void DestroyCheckBoxes();
//	CEdit * GetEditHandleWithInAPointIfPresent(POINT ptPoint);
	virtual ~CTablePage();

	// Generated message map functions
protected:
	BOOL m_bDetailsPage;
	int m_nHeight;
	SUpdateDetailMsg m_sUpdateMSG;
	SRecordMsgInfo m_sRecordMsgInfo;
	CEditDlg* m_pEdit;
	//{{AFX_MSG(CTablePage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEPAGE_H__351896E3_57C1_4888_B03E_D2060E1BE856__INCLUDED_)
