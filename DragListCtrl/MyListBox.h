#if !defined(AFX_MYLISTBOX_H__4EF85914_8ECF_4C43_9524_B6ACA6CF7094__INCLUDED_)
#define AFX_MYLISTBOX_H__4EF85914_8ECF_4C43_9524_B6ACA6CF7094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListBox window


class CMyListBox : public CListBox
{
// Construction
public:
	CMyListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListBox)

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	LRESULT DragMoveItem(WPARAM wParam, LPARAM lParam) 	;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTBOX_H__4EF85914_8ECF_4C43_9524_B6ACA6CF7094__INCLUDED_)
