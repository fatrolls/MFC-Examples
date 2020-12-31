#if !defined(AFX_NEWHEADERCTRL_H__99EB0481_4FA1_11D1_980A_004095E0DEFA__INCLUDED_)
#define AFX_NEWHEADERCTRL_H__99EB0481_4FA1_11D1_980A_004095E0DEFA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NewHeaderCtrl.h : header file
//

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CNewHeaderCtrl window

class CNewHeaderCtrl : public CHeaderCtrl
{
// Construction
public:
	CNewHeaderCtrl();

// Attributes
protected:
	CImageList *m_pImageList;
	CMap< int, int, int, int> m_mapImageIndex;

public:

// Operations
public:
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	CImageList* SetImageList( CImageList* pImageList );
	int GetItemImage( int nItem );
	void SetItemImage( int nItem, int nImage );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewHeaderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewHeaderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewHeaderCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWHEADERCTRL_H__99EB0481_4FA1_11D1_980A_004095E0DEFA__INCLUDED_)
