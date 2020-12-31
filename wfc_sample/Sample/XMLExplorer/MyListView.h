#if !defined(AFX_MYLISTVIEW_H__41D5253E_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
#define AFX_MYLISTVIEW_H__41D5253E_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListView view

class CMyListView : public CListView
{
protected:
	CMyListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyListView)

   DWORD m_CurrentDisplay;


// Attributes
public:

// Operations
public:

   BOOL AddColumn( LPCTSTR column_name,
                   int     column_number,
                   int     width = (-1),
                   int     nSubItem = (-1),
                   int     mask = LVCF_FMT  | LVCF_WIDTH |
                                  LVCF_TEXT | LVCF_SUBITEM,
                   int     format = LVCFMT_LEFT );

   BOOL AddItem( int     row_number,
                 int     column_number,
                 LPCTSTR text,
                 int     image_index = (-1) );

   void Empty( void );

   void ShowDocument( CExtensibleMarkupLanguageDocument * document_p );
   void ShowElement( CExtensibleMarkupLanguageElement * element_p );
   void ShowEntities( CExtensibleMarkupLanguageDocument * document_p );
   void ShowAttribute( CExtensibleMarkupLanguageAttribute * attribute_p );
   void ShowDefault( void );
   void ShowListOfAttributes( CExtensibleMarkupLanguageElement * element_p );
//   void ShowEntity( CExtensibleMarkupLanguageDocument * document_p );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTVIEW_H__41D5253E_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
