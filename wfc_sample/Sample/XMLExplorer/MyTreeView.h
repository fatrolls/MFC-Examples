#if !defined(AFX_MYTREEVIEW_H__41D5253F_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
#define AFX_MYTREEVIEW_H__41D5253F_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeView.h : header file

#define IMAGE_ROOT                   0
#define IMAGE_TILE_2                 1
#define IMAGE_TILE_3                 2
#define IMAGE_PROCESSING_INSTRUCTION 3
#define IMAGE_TEXT_SEGMENT           4
#define IMAGE_LIST_OF_ENTITIES       5
#define IMAGE_ENTITY                 6
#define IMAGE_ATTRIBUTES             7
#define IMAGE_ATTRIBUTE              8
#define IMAGE_META_DATA              9

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView view

class CMyTreeView : public CTreeView
{
   public:

      CImageList ImageList;

      HTREEITEM RootItem;
      HTREEITEM CurrentItem;

protected:

	CMyTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyTreeView)

// Attributes
public:

   enum _what_it_is
   {
      IT_IS_THE_ROOT = 1,
      IT_IS_AN_XML_DOCUMENT,
      IT_IS_AN_ELEMENT,
      IT_IS_AN_ENTITY,
      IT_IS_AN_ATTRIBUTE,
      IT_IS_A_LIST_OF_ATTRIBUTES
   };

// Operations
public:

   void DeleteChildren( HTREEITEM parent_item );
   DWORD ImageToWhatItIs( DWORD image_id ) const;
   void Populate( CExtensibleMarkupLanguageDocument * xml_p );
   void AddElement( CTreeCtrl& tree_control, HTREEITEM parent_item, CExtensibleMarkupLanguageElement * element_p );
   void AddEntities( CTreeCtrl& tree_control, HTREEITEM parent_item, CExtensibleMarkupLanguageDocument * element_p );
   void AddAttributes( CTreeCtrl& tree_control, HTREEITEM parent_item, CExtensibleMarkupLanguageElement * element_p );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEVIEW_H__41D5253F_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
