#if !defined(SPLITTERWND_H__B24B6F5D_B43E_11D1_B5D6_767094000000__INCLUDED_)
#define SPLITTERWND_H__B24B6F5D_B43E_11D1_B5D6_767094000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestSplitterWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CxSplitterWnd window

class CxSplitterWnd : public CSplitterWnd
{
// Construction
public:
	CxSplitterWnd();
	virtual ~CxSplitterWnd();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxSplitterWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void StartTracking(int ht);

	virtual CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
	virtual void SetActivePane( int row, int col, CWnd* pWnd = NULL );

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	virtual BOOL OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult );


	// Generated message map functions
protected:
	//{{AFX_MSG(CxSplitterWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(SPLITTERWND_H__B24B6F5D_B43E_11D1_B5D6_767094000000__INCLUDED_)
