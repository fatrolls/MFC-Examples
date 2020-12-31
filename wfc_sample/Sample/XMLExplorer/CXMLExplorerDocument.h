// CXMLExplorerDocument.h : interface of the CXMLExplorerDocument class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CXMLEXPLORERDOCUMENT_H__41D52534_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
#define AFX_CXMLEXPLORERDOCUMENT_H__41D52534_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "MyTreeView.h"
#include "MyListView.h"

class CXMLExplorerDocument : public CDocument
{
protected: // create from serialization only
	CXMLExplorerDocument();
	DECLARE_DYNCREATE(CXMLExplorerDocument)

// Attributes
public:

   CMyTreeView * TreeView;
   CMyListView * ListView;

   CExtensibleMarkupLanguageDocument * XML;

// Operations
public:

   void ShowDocument( CExtensibleMarkupLanguageDocument  * document_p );
   void ShowElement(  CExtensibleMarkupLanguageElement   * element_p );
   void ShowEntities( CExtensibleMarkupLanguageDocument  * document_p );
   void ShowAttribute( CExtensibleMarkupLanguageAttribute * attribute_p );
   void ShowListOfAttributes( CExtensibleMarkupLanguageElement * xml_p );
   void ShowDefault( void );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLExplorerDocument)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXMLExplorerDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXMLExplorerDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXMLEXPLORERDOCUMENT_H__41D52534_19F6_11D3_BF11_00A0C9CCC695__INCLUDED_)
